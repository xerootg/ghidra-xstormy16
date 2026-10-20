/* Case and result records shared by the driver and both oracle builds (C and C++).
 *
 * A case is one instruction executed from a seeded state on a flat byte bus. Memory
 * that the case did not write reads memhash(mseed, addr); the instruction words sit at
 * pc..pc+3. The SUT (test/semantic/sut) implements the same memhash, so both sides see
 * identical memory without shipping it. */
#ifndef XS16_CASE_H
#define XS16_CASE_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define XS16_MAX_ACC 64

typedef struct {
	char tag[48];
	uint32_t pc;
	uint16_t r[16];
	uint16_t w0, w1;
	uint32_t mseed;
} xs16_case;

enum { XS16_OK = 0, XS16_INVALID = 1, XS16_UNDEF = 2 };

/* UB guard bits (ASSUMPTIONS.md H4) */
enum { XS16_UB_SHIFT = 1, XS16_UB_DIV0 = 2, XS16_UB_DIVOVF = 4, XS16_UB_ROT = 8 };

typedef struct {
	int status;
	char insn[32];
	char cti;               /* '-', 'U' (unconditional) or 'C' (conditional); '*' if unknown */
	int taken;              /* the semantics called branch() */
	uint32_t npc;
	uint16_t r[16];
	unsigned ub;
	int nw, nr, nev;
	uint32_t waddr[XS16_MAX_ACC];
	uint8_t wval[XS16_MAX_ACC];   /* final byte value per written address */
	uint32_t raddr[XS16_MAX_ACC];
	const char *ev[8];
} xs16_result;

/* The deterministic fill both sides use for memory nobody wrote. */
static inline uint8_t xs16_memhash(uint32_t seed, uint32_t a)
{
	uint32_t h = a * 0x9E3779B1u ^ seed;
	h ^= h >> 15;
	h *= 0x85EBCA77u;
	h ^= h >> 13;
	h *= 0xC2B2AE35u;
	h ^= h >> 16;
	return (uint8_t)h;
}

/* Implemented by each oracle (o1-sid.cxx, o2-cgen26.c). */
void xs16_oracle_step(const xs16_case *c, xs16_result *res);
extern const char *xs16_oracle_name;

#ifdef __cplusplus
}
#endif
#endif
