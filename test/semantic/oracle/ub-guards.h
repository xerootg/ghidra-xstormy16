/* Replaces the CGEN shift, rotate and divide ops with versions whose result does not
 * depend on the host compiler or CPU (ASSUMPTIONS.md H4). Out-of-range shifts and
 * divisions by zero or INT_MIN/-1 return 0 and set a bit in xs16_ub, so the case is
 * reported as ORACLE_UB instead of comparing a host-specific value. Rotates follow
 * gdb's sim/common/cgen-utils.c RORSI/ROLSI (a count of 0 leaves the value unchanged).
 * Include after cgen-ops.h. */
#ifndef XS16_UB_GUARDS_H
#define XS16_UB_GUARDS_H
#include <stdint.h>
#include "xs16-case.h"

extern unsigned xs16_ub;

static inline uint32_t xs16_shl(uint32_t x, uint32_t y) { if (y >= 32) { xs16_ub |= XS16_UB_SHIFT; return 0; } return x << y; }
static inline uint32_t xs16_shr(uint32_t x, uint32_t y) { if (y >= 32) { xs16_ub |= XS16_UB_SHIFT; return 0; } return x >> y; }
static inline int32_t xs16_sar(int32_t x, uint32_t y) { if (y >= 32) { xs16_ub |= XS16_UB_SHIFT; return x < 0 ? -1 : 0; } return x >> y; }
static inline uint32_t xs16_ror(uint32_t x, uint32_t y)
{
	if (y >= 32) { xs16_ub |= XS16_UB_ROT; return 0; }
	return y == 0 ? x : (x >> y) | (x << (32 - y));
}
static inline uint32_t xs16_rol(uint32_t x, uint32_t y)
{
	if (y >= 32) { xs16_ub |= XS16_UB_ROT; return 0; }
	return y == 0 ? x : (x << y) | (x >> (32 - y));
}
static inline int32_t xs16_sdiv(int32_t x, int32_t y, int mod)
{
	if (y == 0) { xs16_ub |= XS16_UB_DIV0; return 0; }
	if (x == INT32_MIN && y == -1) { xs16_ub |= XS16_UB_DIVOVF; return 0; }
	return mod ? x % y : x / y;
}
static inline uint32_t xs16_udiv(uint32_t x, uint32_t y, int mod)
{
	if (y == 0) { xs16_ub |= XS16_UB_DIV0; return 0; }
	return mod ? x % y : x / y;
}

#undef SLLHI
#undef SRLHI
#undef SRAHI
#undef SLLSI
#undef SRLSI
#undef SRASI
#undef RORSI
#undef ROLSI
#undef DIVHI
#undef UDIVHI
#undef MODHI
#undef UMODHI
#undef DIVSI
#undef UDIVSI
#undef MODSI
#undef UMODSI
/* HI operands are promoted to int before shifting in C, so the limit is 32, not 16. */
#define SLLHI(x, y) ((int32_t)xs16_shl((uint16_t)(x), (uint32_t)(y)))
#define SRLHI(x, y) ((int32_t)xs16_shr((uint16_t)(x), (uint32_t)(y)))
#define SRAHI(x, y) xs16_sar((int16_t)(x), (uint32_t)(y))
#define SLLSI(x, y) xs16_shl((uint32_t)(x), (uint32_t)(y))
#define SRLSI(x, y) xs16_shr((uint32_t)(x), (uint32_t)(y))
#define SRASI(x, y) xs16_sar((int32_t)(x), (uint32_t)(y))
#define RORSI(x, y) ((int32_t)xs16_ror((uint32_t)(x), (uint32_t)(y)))
#define ROLSI(x, y) ((int32_t)xs16_rol((uint32_t)(x), (uint32_t)(y)))
#define DIVHI(x, y) ((int16_t)xs16_sdiv((int16_t)(x), (int16_t)(y), 0))
#define MODHI(x, y) ((int16_t)xs16_sdiv((int16_t)(x), (int16_t)(y), 1))
#define UDIVHI(x, y) ((uint16_t)xs16_udiv((uint16_t)(x), (uint16_t)(y), 0))
#define UMODHI(x, y) ((uint16_t)xs16_udiv((uint16_t)(x), (uint16_t)(y), 1))
#define DIVSI(x, y) xs16_sdiv((int32_t)(x), (int32_t)(y), 0)
#define MODSI(x, y) xs16_sdiv((int32_t)(x), (int32_t)(y), 1)
#define UDIVSI(x, y) xs16_udiv((uint32_t)(x), (uint32_t)(y), 0)
#define UMODSI(x, y) xs16_udiv((uint32_t)(x), (uint32_t)(y), 1)
#endif
