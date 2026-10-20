// Oracle driver, linked against one oracle (o1-sid.cxx or o2-cgen26.c).
//
//   driver gen <tier> <seed> [<shard> <nshards>]   print the cases of a tier (S1, S2)
//   driver golden <file.vec>...                    print the cases of golden vector files
//   driver run                                     cases on stdin -> results on stdout
//   driver check <file.vec>...                     run golden vectors, compare to their
//                                                  "expect" fields, exit 1 on a mismatch
//
// Case line:   tag pc r0..r15 w0 w1 mseed                       (hex)
// Result line: tag status insn cti taken npc r0..r15 ub W=a:v,.. R=a,.. EV=e,..
// Every case is a pure function of (seed, tier, index), so the SUT can be handed the
// same file and shards can be regenerated anywhere.
#include "xs16-case.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// SplitMix64; the stream for a case is seeded from (seed, tier, index) only.
struct Rng {
	uint64_t s;
	uint64_t next()
	{
		uint64_t z = (s += 0x9E3779B97F4A7C15ull);
		z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
		z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
		return z ^ (z >> 31);
	}
	uint32_t below(uint32_t n) { return (uint32_t) (next() % n); }
};

static uint64_t hash_str(const char *s)
{
	uint64_t h = 1469598103934665603ull;
	for (; *s; s++)
		h = (h ^ (uint8_t) *s) * 1099511628211ull;
	return h;
}

static Rng case_rng(const char *seed, const char *tier, uint64_t index)
{
	Rng r{hash_str(seed) ^ (hash_str(tier) * 31) ^ (index * 0x2545F4914F6CDD1Dull)};
	r.next();
	return r;
}

static void print_case(const xs16_case &c)
{
	printf("%s %x", c.tag, c.pc);
	for (int i = 0; i < 16; i++)
		printf(" %x", c.r[i]);
	printf(" %x %x %x\n", c.w0, c.w1, c.mseed);
}

static bool parse_case(const char *line, xs16_case &c)
{
	char tag[sizeof c.tag];
	unsigned v[20];
	int n = 0;
	if (sscanf(line, "%47s%n", tag, &n) != 1 || tag[0] == '#')
		return false;
	const char *p = line + n;
	for (int i = 0; i < 20; i++) {
		char *e;
		unsigned long x = strtoul(p, &e, 16);
		if (e == p)
			return false;
		v[i] = (unsigned) x;
		p = e;
	}
	memset(&c, 0, sizeof c);
	snprintf(c.tag, sizeof c.tag, "%s", tag);
	c.pc = v[0];
	for (int i = 0; i < 16; i++)
		c.r[i] = (uint16_t) v[1 + i];
	c.w0 = (uint16_t) v[17];
	c.w1 = (uint16_t) v[18];
	c.mseed = v[19];
	return true;
}

static const char *status_name(int s)
{
	return s == XS16_OK ? "OK" : s == XS16_INVALID ? "INVALID" : "UNDEF";
}

// Divide-by-zero and INT_MIN/-1 have no defined result in either oracle: the case is
// REF_UNDEFINED and only the SUT's behaviour (it must not throw) is recorded.
static void step(const xs16_case &c, xs16_result &r)
{
	xs16_oracle_step(&c, &r);
	if (r.status == XS16_OK && (r.ub & (XS16_UB_DIV0 | XS16_UB_DIVOVF)))
		r.status = XS16_UNDEF;
}

static void print_result(const xs16_case &c, const xs16_result &r)
{
	printf("%s %s %s %c %d %x", c.tag, status_name(r.status), r.insn, r.cti, r.taken, r.npc);
	for (int i = 0; i < 16; i++)
		printf(" %x", r.r[i]);
	printf(" %x W=", r.ub);
	std::vector<std::pair<uint32_t, uint8_t>> w;
	for (int i = 0; i < r.nw; i++)
		w.push_back({r.waddr[i], r.wval[i]});
	std::sort(w.begin(), w.end());
	for (size_t i = 0; i < w.size(); i++)
		printf("%s%x:%x", i ? "," : "", w[i].first, w[i].second);
	std::vector<uint32_t> rd(r.raddr, r.raddr + r.nr);
	std::sort(rd.begin(), rd.end());
	printf(" R=");
	for (size_t i = 0; i < rd.size(); i++)
		printf("%s%x", i ? "," : "", rd[i]);
	printf(" EV=");
	for (int i = 0; i < r.nev; i++)
		printf("%s%s", i ? "," : "", r.ev[i]);
	printf("\n");
}

//
// Tier generators
//

static const uint16_t B16[] = {0, 1, 2, 0x0f, 0x10, 0x7f, 0x80, 0xff, 0x100, 0x7ffe, 0x7fff,
	0x8000, 0x8001, 0xfffe, 0xffff, 0xf0};
static const uint16_t IMM16[] = {0, 1, 0x7f, 0x80, 0xff, 0x100, 0x7fff, 0x8000, 0xfffe, 0xffff};
static const uint16_t SPS[] = {0, 1, 2, 3, 0xfffc, 0xfffd, 0xfffe, 0xffff, 0x7f00, 0x7ffe, 0x8000};
// Boundary pcs for rel8/rel12 branches, br Rd, callr and the jmpf/callf 24-bit wrap.
static const uint32_t PCS[] = {0x7ffe, 0x8000, 0xfffc, 0xfffe, 0x10000, 0x27ffc, 0x27ffe,
	0xfffffc, 0xfffffe};
#define N(a) (sizeof(a) / sizeof((a)[0]))

static void random_state(Rng &g, xs16_case &c)
{
	for (int i = 0; i < 16; i++)
		c.r[i] = g.below(2) ? (uint16_t) g.next() : B16[g.below(N(B16))];
	c.r[14] = (uint16_t) g.next();
	if (g.below(2))
		c.r[15] = SPS[g.below(N(SPS))];
	c.w1 = g.below(3) ? IMM16[g.below(N(IMM16))] : (uint16_t) g.next();
	c.pc = g.below(4) ? 0x10000 + 2 * g.below(0xc000) : PCS[g.below(N(PCS))];
	c.mseed = (uint32_t) g.next();
}

// S1: every first word, four seeded states each.
static void gen_s1(const char *seed, unsigned shard, unsigned nshards)
{
	for (unsigned w0 = shard; w0 < 0x10000; w0 += nshards)
		for (unsigned k = 0; k < 4; k++) {
			xs16_case c = {};
			Rng g = case_rng(seed, "S1", w0 * 4 + k);
			random_state(g, c);
			c.w0 = (uint16_t) w0;
			snprintf(c.tag, sizeof c.tag, "S1:%04x:%u", w0, k);
			print_case(c);
		}
}

// S2 macro-lite: the flag macros and shift/rotate/mul/div through one canonical
// constructor each (Rd=r1, Rs=r2), over nibble/byte boundary values.
static const uint16_t V[] = {0, 1, 7, 8, 0x0f, 0x10, 0x7f, 0x80, 0xff, 0x100, 0x0fff, 0x1000,
	0x7ffe, 0x7fff, 0x8000, 0x8001, 0xfffe, 0xffff, 0x0f0f, 0xf0f0, 0x5555, 0xaaaa};
// Shift and bit counts, including >= 16 and >= 32 (rrc/rlc/bn/bp take Rs unmasked in places).
static const uint16_t CNT[] = {0, 1, 2, 7, 8, 14, 15, 16, 17, 0x1e, 0x1f, 0x20, 0x21, 0x10f,
	0x8000, 0xffff, 0x0f0f, 0x7fff, 0x100, 0x3f, 0x40, 0x11};
static const uint16_t DIVS[] = {2, 3, 7};

struct S2 {
	const char *seed;
	unsigned shard, nshards, n = 0;
	void emit(const char *name, uint16_t w0, uint16_t w1, uint16_t psw,
		  std::initializer_list<std::pair<int, uint16_t>> regs)
	{
		unsigned idx = n++;
		if (idx % nshards != shard)
			return;
		xs16_case c = {};
		Rng g = case_rng(seed, "S2", idx);
		for (int i = 0; i < 14; i++)
			c.r[i] = (uint16_t) g.next();
		c.r[14] = psw;
		c.r[15] = 0x7f00;
		for (auto &kv : regs)
			c.r[kv.first] = kv.second;
		c.w0 = w0;
		c.w1 = w1;
		c.pc = 0x12340;
		c.mseed = (uint32_t) g.next();
		snprintf(c.tag, sizeof c.tag, "S2:%s:%u", name, idx);
		print_case(c);
	}
};

static void gen_s2(const char *seed, unsigned shard, unsigned nshards)
{
	S2 s{seed, shard, nshards};
	struct { const char *name; uint16_t op; } alu[] = {
		{"add", 0x4900}, {"adc", 0x4b00}, {"sub", 0x4d00}, {"sbc", 0x4f00}};
	for (auto &o : alu)
		for (uint16_t a : V)
			for (uint16_t b : V)
				for (int cy = 0; cy < 2; cy++)
					s.emit(o.name, o.op | 0x21, 0, cy << 2, {{1, a}, {2, b}});
	// cmpf through b cc Rd,Rs (all 16 conditions) and b cc Rm,#imm8
	for (int cc = 0; cc < 16; cc++)
		for (uint16_t a : V)
			for (uint16_t b : V)
				s.emit("bccgrgr", 0x0d21, cc << 12 | 0x010, 0, {{1, a}, {2, b}});
	for (int cc = 0; cc < 16; cc++)
		for (uint16_t a : V)
			for (uint16_t b : {0, 1, 0x7f, 0x80, 0xff})
				s.emit("bccgrimm8", 0x2200 | b, cc << 12 | 0x010, 0, {{1, a}});
	struct { const char *name; uint16_t rr, ri; } sh[] = {
		{"rrc", 0x3800, 0x3900}, {"rlc", 0x3a00, 0x3b00}, {"shr", 0x3c00, 0x3d00},
		{"shl", 0x3e00, 0x3f00}, {"asr", 0x3600, 0x3700}};
	for (auto &o : sh)
		for (uint16_t a : V)
			for (int cy = 0; cy < 2; cy++) {
				for (uint16_t n : CNT)
					s.emit(o.name, o.rr | 0x21, 0, cy << 2, {{1, a}, {2, n}});
				for (int n = 0; n < 16; n++)
					s.emit(o.name, o.ri | n << 4 | 1, 0, cy << 2, {{1, a}});
			}
	struct { const char *name; uint16_t op; } bit[] = {
		{"bn", 0x0600}, {"bp", 0x0700}, {"clr1", 0x0a00}, {"set1", 0x0b00}};
	for (auto &o : bit)
		for (uint16_t a : V)
			for (uint16_t n : CNT)
				s.emit(o.name, o.op | 0x21, 0x010, 0, {{1, a}, {2, n}});
	for (uint16_t a : V)
		for (uint16_t b : V)
			s.emit("mul", 0x00d0, 0, 0, {{0, a}, {2, b}});
	std::vector<uint16_t> d(V, V + N(V));
	d.insert(d.end(), DIVS, DIVS + N(DIVS));
	for (const char *name : {"div", "sdiv"})
		for (uint16_t a : V)
			for (uint16_t b : d)
				s.emit(name, name[0] == 'd' ? 0x00c0 : 0x00c8, 0, 0, {{0, a}, {1, 0}, {2, b}});
	for (const char *name : {"divlh", "sdivlh"})
		for (uint16_t hi : V)
			for (uint16_t a : V)
				for (uint16_t b : d)
					s.emit(name, name[0] == 'd' ? 0x00e0 : 0x00e8, 0, 0,
					       {{0, a}, {1, hi}, {2, b}});
}

//
// Golden vectors: "tag key=val ... ; expect key=val ... [; xfail=<id>]"
//   keys: pc w0 w1 mseed r0..r15 psw sp; expect also npc, status, insn, m<addr>=<byte>
//

static const char *const RN[16] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9",
	"r10", "r11", "r12", "r13", "psw", "sp"};

static int reg_index(const std::string &k)
{
	for (int i = 0; i < 16; i++)
		if (k == RN[i] || (i == 14 && k == "r14") || (i == 15 && k == "r15"))
			return i;
	return -1;
}

struct Golden {
	xs16_case c;
	std::map<std::string, std::string> expect;
};

static std::vector<Golden> read_golden(const char *path)
{
	std::vector<Golden> out;
	FILE *f = fopen(path, "r");
	if (!f) {
		perror(path);
		exit(2);
	}
	char line[1024];
	while (fgets(line, sizeof line, f)) {
		std::string s(line);
		size_t h = s.find('#');
		if (h != std::string::npos)
			s.erase(h);
		std::vector<std::string> parts;
		size_t pos = 0, semi;
		while ((semi = s.find(';', pos)) != std::string::npos) {
			parts.push_back(s.substr(pos, semi - pos));
			pos = semi + 1;
		}
		parts.push_back(s.substr(pos));
		Golden g = {};
		g.c.pc = 0x10000;
		g.c.r[15] = 0x7f00;
		g.c.mseed = 0x1234;
		bool any = false;
		for (size_t p = 0; p < parts.size(); p++) {
			char *save, *tok = strtok_r(&parts[p][0], " \t\r\n", &save);
			bool first = true;
			for (; tok; tok = strtok_r(nullptr, " \t\r\n", &save), first = false) {
				if (p == 0 && first) {
					snprintf(g.c.tag, sizeof g.c.tag, "S0:%s", tok);
					any = true;
					continue;
				}
				if (p > 0 && first && !strcmp(tok, "expect"))
					continue;
				char *eq = strchr(tok, '=');
				if (!eq) {
					fprintf(stderr, "%s: bad token %s\n", path, tok);
					exit(2);
				}
				std::string k(tok, eq - tok), v(eq + 1);
				if (p > 0) {
					g.expect[k] = v;
					continue;
				}
				unsigned long x = strtoul(v.c_str(), nullptr, 16);
				int ri = reg_index(k);
				if (ri >= 0)
					g.c.r[ri] = (uint16_t) x;
				else if (k == "pc")
					g.c.pc = (uint32_t) x;
				else if (k == "w0")
					g.c.w0 = (uint16_t) x;
				else if (k == "w1")
					g.c.w1 = (uint16_t) x;
				else if (k == "mseed")
					g.c.mseed = (uint32_t) x;
				else {
					fprintf(stderr, "%s: unknown key %s\n", path, k.c_str());
					exit(2);
				}
			}
		}
		if (any)
			out.push_back(g);
	}
	fclose(f);
	return out;
}

static int check_golden(const Golden &g)
{
	xs16_result r;
	step(g.c, r);
	int bad = 0;
	for (auto &kv : g.expect) {
		const std::string &k = kv.first;
		std::string got;
		char buf[32];
		int ri = reg_index(k);
		if (k == "xfail" || k == "finding")
			continue;
		if (ri >= 0)
			snprintf(buf, sizeof buf, "%x", r.r[ri]), got = buf;
		else if (k == "npc")
			snprintf(buf, sizeof buf, "%x", r.npc), got = buf;
		else if (k == "status")
			got = status_name(r.status);
		else if (k == "insn")
			got = r.insn;
		else if (k[0] == 'm') {
			uint32_t a = (uint32_t) strtoul(k.c_str() + 1, nullptr, 16);
			got = "-";
			for (int i = 0; i < r.nw; i++)
				if (r.waddr[i] == a)
					snprintf(buf, sizeof buf, "%x", r.wval[i]), got = buf;
		} else {
			fprintf(stderr, "%s: unknown expect key %s\n", g.c.tag, k.c_str());
			return 1;
		}
		std::string want = kv.second;
		if (ri >= 0 || k == "npc" || k[0] == 'm')
			snprintf(buf, sizeof buf, "%lx", strtoul(want.c_str(), nullptr, 16)), want = buf;
		if (got != want) {
			printf("FAIL %s [%s] %s: want %s got %s\n", g.c.tag, xs16_oracle_name, k.c_str(),
			       want.c_str(), got.c_str());
			bad = 1;
		}
	}
	return bad;
}

int main(int argc, char **argv)
{
	if (argc >= 4 && !strcmp(argv[1], "gen")) {
		unsigned shard = argc > 5 ? atoi(argv[4]) : 0, nshards = argc > 5 ? atoi(argv[5]) : 1;
		if (!strcmp(argv[2], "S1"))
			gen_s1(argv[3], shard, nshards);
		else if (!strcmp(argv[2], "S2"))
			gen_s2(argv[3], shard, nshards);
		else {
			fprintf(stderr, "unknown tier %s\n", argv[2]);
			return 2;
		}
		return 0;
	}
	if (argc >= 3 && (!strcmp(argv[1], "golden") || !strcmp(argv[1], "check"))) {
		int bad = 0, n = 0;
		for (int i = 2; i < argc; i++)
			for (auto &g : read_golden(argv[i])) {
				n++;
				if (argv[1][0] == 'g')
					print_case(g.c);
				else
					bad |= check_golden(g);
			}
		if (argv[1][0] == 'c')
			printf("golden: %d vectors, %s on %s\n", n, bad ? "FAILED" : "all pass",
			       xs16_oracle_name);
		return bad;
	}
	if (argc == 2 && !strcmp(argv[1], "run")) {
		char line[512];
		xs16_case c;
		xs16_result r;
		while (fgets(line, sizeof line, stdin))
			if (parse_case(line, c)) {
				step(c, r);
				print_result(c, r);
			}
		return 0;
	}
	fprintf(stderr, "usage: driver gen <tier> <seed> [<shard> <nshards>] | golden <vec>... |"
			" run | check <vec>...\n");
	return 2;
}
