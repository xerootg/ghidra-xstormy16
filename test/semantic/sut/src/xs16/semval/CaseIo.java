package xs16.semval;

import java.util.*;

/** Case and oracle-result records, in the text format of test/semantic/oracle/driver.cxx. */
final class CaseIo {
	private CaseIo() {
	}

	static final class Case {
		String tag;
		long pc;
		int[] r = new int[16];
		int w0, w1;
		int mseed;

		String tier() {
			int i = tag.indexOf(':');
			return i < 0 ? tag : tag.substring(0, i);
		}

		/** tag pc r0..r15 w0 w1 mseed (hex) */
		static Case parse(String line) {
			String[] t = line.trim().split("\\s+");
			if (t.length < 21 || t[0].startsWith("#")) {
				return null;
			}
			Case c = new Case();
			c.tag = t[0];
			c.pc = Long.parseLong(t[1], 16);
			for (int i = 0; i < 16; i++) {
				c.r[i] = Integer.parseInt(t[2 + i], 16);
			}
			c.w0 = Integer.parseInt(t[18], 16);
			c.w1 = Integer.parseInt(t[19], 16);
			c.mseed = (int) Long.parseLong(t[20], 16);
			return c;
		}
	}

	/** One oracle result line: tag status insn cti taken npc r0..r15 ub W=.. R=.. EV=.. */
	static final class OracleResult {
		String tag, status, insn;
		char cti;
		long npc;
		int[] r = new int[16];
		int ub;
		TreeMap<Long, Integer> writes = new TreeMap<>();
		Set<Long> reads = new HashSet<>();
		List<String> events = new ArrayList<>();

		static OracleResult parse(String line) {
			String[] t = line.trim().split("\\s+");
			OracleResult o = new OracleResult();
			o.tag = t[0];
			o.status = t[1];
			o.insn = t[2];
			o.cti = t[3].charAt(0);
			o.npc = Long.parseLong(t[5], 16);
			for (int i = 0; i < 16; i++) {
				o.r[i] = Integer.parseInt(t[6 + i], 16);
			}
			o.ub = Integer.parseInt(t[22], 16);
			for (String kv : list(t[23], "W=")) {
				int c = kv.indexOf(':');
				o.writes.put(Long.parseLong(kv.substring(0, c), 16),
					Integer.parseInt(kv.substring(c + 1), 16));
			}
			for (String a : list(t[24], "R=")) {
				o.reads.add(Long.parseLong(a, 16));
			}
			o.events.addAll(list(t[25], "EV="));
			return o;
		}

		private static List<String> list(String field, String prefix) {
			String body = field.substring(prefix.length());
			return body.isEmpty() ? List.of() : Arrays.asList(body.split(","));
		}
	}

	/** Same fill as xs16_memhash() in oracle/xs16-case.h. */
	static int memhash(int seed, long addr) {
		int h = (int) addr * 0x9E3779B1 ^ seed;
		h ^= h >>> 15;
		h *= 0x85EBCA77;
		h ^= h >>> 13;
		h *= 0xC2B2AE35;
		h ^= h >>> 16;
		return h & 0xff;
	}

	/** The flat bus byte at addr before the instruction runs: instruction words, else memhash. */
	static int flatByte(Case c, long addr) {
		long off = (addr - c.pc) & 0xffffffffL;
		if (off < 4) {
			int w = off < 2 ? c.w0 : c.w1;
			return (w >> (8 * (int) (off & 1))) & 0xff;
		}
		return memhash(c.mseed, addr);
	}
}
