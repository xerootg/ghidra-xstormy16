/* Flat byte bus for one case, shared by both oracles: reads see the case's own writes,
 * then the instruction words at pc, then memhash. Reads and writes are logged per byte
 * so the comparator can check them as address sets (ASSUMPTIONS.md H3). */
#ifndef XS16_BUS_H
#define XS16_BUS_H
#include "xs16-case.h"

/* Defined once by each oracle; every translation unit shares them. */
#ifdef __cplusplus
extern "C" {
#endif
extern const xs16_case *xs16_bus_case;
extern xs16_result *xs16_bus_res;
#ifdef __cplusplus
}
#endif

static void xs16_bus_begin(const xs16_case *c, xs16_result *res)
{
	xs16_bus_case = c;
	xs16_bus_res = res;
}

static uint8_t xs16_rd8(uint32_t a)
{
	xs16_result *r = xs16_bus_res;
	const xs16_case *c = xs16_bus_case;
	int i;
	for (i = 0; i < r->nr && r->raddr[i] != a; i++)
		;
	if (i == r->nr && r->nr < XS16_MAX_ACC)
		r->raddr[r->nr++] = a;
	for (i = 0; i < r->nw; i++)
		if (r->waddr[i] == a)
			return r->wval[i];
	uint32_t off = a - c->pc;
	if (off < 4) {
		uint16_t w = off < 2 ? c->w0 : c->w1;
		return (uint8_t)(w >> (8 * (off & 1)));
	}
	return xs16_memhash(c->mseed, a);
}

static void xs16_wr8(uint32_t a, uint8_t v)
{
	xs16_result *r = xs16_bus_res;
	int i;
	for (i = 0; i < r->nw; i++)
		if (r->waddr[i] == a) {
			r->wval[i] = v;
			return;
		}
	if (r->nw < XS16_MAX_ACC) {
		r->waddr[r->nw] = a;
		r->wval[r->nw++] = v;
	}
}

/* Little-endian multi-byte accesses; addresses are not wrapped (CGEN uses 32-bit ADDR). */
static uint32_t xs16_rd(uint32_t a, int n)
{
	uint32_t v = 0;
	for (int i = 0; i < n; i++)
		v |= (uint32_t)xs16_rd8(a + i) << (8 * i);
	return v;
}

static void xs16_wr(uint32_t a, int n, uint32_t v)
{
	for (int i = 0; i < n; i++)
		xs16_wr8(a + i, (uint8_t)(v >> (8 * i)));
}

static void xs16_event(const char *e)
{
	xs16_result *r = xs16_bus_res;
	if (r->nev < 8)
		r->ev[r->nev++] = e;
}
#endif
