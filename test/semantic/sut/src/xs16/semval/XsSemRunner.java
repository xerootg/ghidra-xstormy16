package xs16.semval;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.util.*;
import java.util.concurrent.*;

import com.google.gson.*;

import ghidra.GhidraApplicationLayout;
import ghidra.app.plugin.processors.sleigh.SleighLanguage;
import ghidra.app.plugin.processors.sleigh.symbol.Symbol;
import ghidra.app.plugin.processors.sleigh.symbol.SubtableSymbol;
import ghidra.GhidraLaunchable;
import ghidra.framework.Application;
import ghidra.framework.HeadlessGhidraApplicationConfiguration;
import ghidra.program.model.lang.*;
import ghidra.program.util.DefaultLanguageService;

/**
 * Differential runner: executes oracle cases on Ghidra's PcodeEmulator, compares with the
 * oracle's results and buckets the mismatches. Launched through ghidra.Ghidra so the
 * installed extension (the language under test) is found; see semval.sh.
 *
 *   run --cases F --oracle F --out DIR [--threads N]
 *   bench --cases F [--threads N] [--limit N]      SUT-only throughput, no comparison
 */
public class XsSemRunner implements GhidraLaunchable {
	static final String LANG = "Xstormy16:LE:32:default";
	static final int EXEMPLARS = 8;

	/** Per-case outcome, kept by case index so aggregation is independent of threading. */
	record Outcome(String key, String detail, String file, String chain) {
	}

	@Override
	public void launch(GhidraApplicationLayout layout, String[] args) throws Exception {
		Application.initializeApplication(layout, new HeadlessGhidraApplicationConfiguration());
		Map<String, String> opt = new HashMap<>();
		for (int i = 1; i + 1 < args.length; i += 2) {
			opt.put(args[i], args[i + 1]);
		}
		Language lang = DefaultLanguageService.getLanguageService().getLanguage(new LanguageID(LANG));
		int threads = Integer.parseInt(opt.getOrDefault("--threads",
			Integer.toString(Runtime.getRuntime().availableProcessors())));
		List<CaseIo.Case> cases = readCases(Path.of(opt.get("--cases")));
		if (args.length > 0 && args[0].equals("bench")) {
			int limit = Integer.parseInt(opt.getOrDefault("--limit", Integer.toString(cases.size())));
			bench(lang, cases.subList(0, Math.min(limit, cases.size())), threads);
			return;
		}
		List<CaseIo.OracleResult> oracle = new ArrayList<>();
		for (String l : Files.readAllLines(Path.of(opt.get("--oracle")))) {
			if (!l.isBlank()) {
				oracle.add(CaseIo.OracleResult.parse(l));
			}
		}
		if (oracle.size() != cases.size()) {
			throw new IllegalStateException("cases/oracle length mismatch");
		}
		run(lang, cases, oracle, threads, Path.of(opt.get("--out")));
	}

	/** Source lines of every constructor in the language, for the coverage gate. */
	static TreeSet<Integer> allCtorLines(Language lang) {
		TreeSet<Integer> lines = new TreeSet<>();
		for (Symbol sym : ((SleighLanguage) lang).getSymbolTable().getSymbolList()) {
			if (sym instanceof SubtableSymbol st) {
				for (int i = 0; i < st.getNumConstructors(); i++) {
					lines.add(st.getConstructor(i).getLineno());
				}
			}
		}
		return lines;
	}

	static List<CaseIo.Case> readCases(Path p) throws IOException {
		List<CaseIo.Case> out = new ArrayList<>();
		for (String l : Files.readAllLines(p)) {
			CaseIo.Case c = CaseIo.Case.parse(l);
			if (c != null) {
				out.add(c);
			}
		}
		return out;
	}

	static int hash(String s) {
		int h = 0x811c9dc5;
		for (int i = 0; i < s.length(); i++) {
			h = (h ^ s.charAt(i)) * 0x01000193;
		}
		return h & 0x7fffffff;
	}

	/** The same case with a nop instruction and the registers inverted. */
	static CaseIo.Case decoy(CaseIo.Case c) {
		CaseIo.Case d = new CaseIo.Case();
		d.tag = c.tag + ":decoy";
		d.pc = c.pc;
		for (int i = 0; i < 16; i++) {
			d.r[i] = ~c.r[i] & 0xffff;
		}
		d.mseed = ~c.mseed;
		return d;
	}

	static void bench(Language lang, List<CaseIo.Case> cases, int threads) throws Exception {
		ExecutorService pool = Executors.newFixedThreadPool(threads);
		List<Future<Long>> fs = new ArrayList<>();
		long t0 = System.nanoTime();
		for (int k = 0; k < threads; k++) {
			int kk = k;
			fs.add(pool.submit(() -> {
				Sut sut = new Sut(lang);
				long tw = System.nanoTime();
				for (int i = kk; i < cases.size(); i += threads) {
					sut.run(cases.get(i));
				}
				return System.nanoTime() - tw;
			}));
		}
		double busy = 0;
		for (Future<Long> f : fs) {
			busy += f.get() / 1e9;
		}
		pool.shutdown();
		double wall = (System.nanoTime() - t0) / 1e9;
		System.out.printf("bench: %d vectors, %d threads, %.2f s wall, %.0f vectors/s, %.0f vectors/s/thread%n",
			cases.size(), threads, wall, cases.size() / wall, cases.size() / busy);
	}

	static void run(Language lang, List<CaseIo.Case> cases, List<CaseIo.OracleResult> oracle,
			int threads, Path out) throws Exception {
		int n = cases.size();
		Outcome[] outcomes = new Outcome[n];
		long[] selftest = new long[4]; // reruns, rerun diffs, fresh runs, fresh diffs
		List<String> selftestDiffs = Collections.synchronizedList(new ArrayList<>());
		ExecutorService pool = Executors.newFixedThreadPool(threads);
		List<Future<?>> fs = new ArrayList<>();
		long t0 = System.nanoTime();
		for (int k = 0; k < threads; k++) {
			int kk = k;
			fs.add(pool.submit(() -> {
				Sut sut = new Sut(lang);
				// Reset self-test: 1% of cases are re-run at a later position on the same
				// emulator, 0.1% on a fresh one; their results must be identical.
				PriorityQueue<long[]> due = new PriorityQueue<>(Comparator.comparingLong(x -> x[0]));
				Map<Integer, String> sigs = new HashMap<>();
				long[] st = new long[4];
				for (int i = kk; i < n || !due.isEmpty(); i += threads) {
					if (i < n) {
						CaseIo.Case c = cases.get(i);
						if (!c.tag.equals(oracle.get(i).tag)) {
							throw new IllegalStateException("case/oracle mismatch at " + c.tag);
						}
						Sut.Result s = sut.run(c);
						Compare d = Compare.of(c, oracle.get(i), s);
						outcomes[i] = new Outcome(d.pass() ? null : d.bucketKey(oracle.get(i).insn),
							d.detail(), Sut.ctorFile(s.insn), d.ctor);
						int h = hash(c.tag);
						if (h % 100 == 0) {
							sigs.put(i, s.signature());
							due.add(new long[] { i + (long) threads * (1 + h / 100 % 50), i });
						}
						if (h % 1000 == 1) {
							st[2]++;
							if (!new Sut(lang).run(c).signature().equals(s.signature())) {
								st[3]++;
								selftestDiffs.add("fresh " + c.tag);
							}
						}
					}
					while (!due.isEmpty() && (due.peek()[0] <= i || i >= n)) {
						int j = (int) due.poll()[1];
						st[0]++;
						// A decoy at the same pc first, so stale decode or state shows up.
						sut.run(decoy(cases.get(j)));
						if (!sut.run(cases.get(j)).signature().equals(sigs.remove(j))) {
							st[1]++;
							selftestDiffs.add("rerun " + cases.get(j).tag);
						}
					}
				}
				synchronized (selftest) {
					for (int x = 0; x < 4; x++) {
						selftest[x] += st[x];
					}
				}
				return null;
			}));
		}
		for (Future<?> f : fs) {
			f.get();
		}
		pool.shutdown();
		double wall = (System.nanoTime() - t0) / 1e9;
		writeReport(cases, oracle, outcomes, selftest, selftestDiffs, threads, wall, out,
			allCtorLines(lang));
	}

	static void writeReport(List<CaseIo.Case> cases, List<CaseIo.OracleResult> oracle,
			Outcome[] outcomes, long[] selftest, List<String> selftestDiffs, int threads,
			double wall, Path out, TreeSet<Integer> ctorLines) throws IOException {
		Files.createDirectories(out);
		TreeMap<String, JsonObject> buckets = new TreeMap<>();
		JsonObject golden = new JsonObject();
		TreeMap<String, Integer> status = new TreeMap<>();
		int pass = 0;
		TreeMap<Integer, Integer> ctorHits = new TreeMap<>();
		for (int i = 0; i < outcomes.length; i++) {
			CaseIo.Case c = cases.get(i);
			Outcome o = outcomes[i];
			if (!o.chain.equals("-")) {
				for (String l : o.chain.split(">")) {
					ctorHits.merge(Integer.parseInt(l), 1, Integer::sum);
				}
			}
			status.merge(c.tier() + ":" + oracle.get(i).status, 1, Integer::sum);
			if (c.tier().equals("S0")) {
				golden.addProperty(c.tag, o.key == null ? "pass" : o.key);
			}
			if (o.key == null) {
				pass++;
				continue;
			}
			JsonObject b = buckets.computeIfAbsent(o.key, k -> {
				String[] p = k.split("\\|", -1);
				JsonObject j = new JsonObject();
				j.addProperty("count", 0);
				j.add("tiers", new JsonObject());
				j.addProperty("insn", p[0]);
				j.addProperty("ctor", p[1]);
				j.addProperty("ctor_src", o.file + ":" + p[1].split(">")[0]);
				j.addProperty("fields", p[2]);
				j.addProperty("tags", p[3]);
				j.add("exemplars", new JsonArray());
				return j;
			});
			b.addProperty("count", b.get("count").getAsInt() + 1);
			JsonObject t = b.getAsJsonObject("tiers");
			t.addProperty(c.tier(), (t.has(c.tier()) ? t.get(c.tier()).getAsInt() : 0) + 1);
			JsonArray ex = b.getAsJsonArray("exemplars");
			if (ex.size() < EXEMPLARS) {
				ex.add(c.tag + " " + o.detail);
			}
		}
		JsonObject stats = new JsonObject();
		stats.addProperty("cases", outcomes.length);
		stats.addProperty("pass", pass);
		stats.addProperty("mismatch", outcomes.length - pass);
		stats.addProperty("buckets", buckets.size());
		JsonObject st = new JsonObject();
		status.forEach(st::addProperty);
		stats.add("oracle_status", st);
		stats.addProperty("selftest_reruns", selftest[0]);
		stats.addProperty("selftest_rerun_diffs", selftest[1]);
		stats.addProperty("selftest_fresh", selftest[2]);
		stats.addProperty("selftest_fresh_diffs", selftest[3]);
		JsonArray unhit = new JsonArray();
		ctorLines.stream().filter(l -> !ctorHits.containsKey(l)).forEach(unhit::add);
		stats.addProperty("ctors", ctorLines.size());
		stats.add("ctors_unhit", unhit);
		stats.addProperty("threads", threads);
		stats.addProperty("seconds", Math.round(wall * 10) / 10.0);
		JsonObject root = new JsonObject();
		root.add("stats", stats);
		JsonArray sd = new JsonArray();
		selftestDiffs.stream().sorted().forEach(sd::add);
		root.add("selftest_diffs", sd);
		root.add("golden", golden);
		JsonObject bj = new JsonObject();
		buckets.forEach(bj::add);
		root.add("buckets", bj);
		Gson gson = new GsonBuilder().setPrettyPrinting().disableHtmlEscaping().create();
		Files.writeString(out.resolve("buckets.json"), gson.toJson(root) + "\n", StandardCharsets.UTF_8);
		System.out.printf("semval: %d cases, %d pass, %d mismatching in %d buckets; self-test %d+%d reruns, %d diffs; %.1f s on %d threads%n",
			outcomes.length, pass, outcomes.length - pass, buckets.size(), selftest[0], selftest[2],
			selftest[1] + selftest[3], wall, threads);
	}
}
