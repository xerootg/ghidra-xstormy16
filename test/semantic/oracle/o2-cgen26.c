/* Oracle O2: xstormy16 semantics regenerated from binutils' xstormy16.cpu by current
 * CGEN (gen/, see regen.sh), with the hooks the .cpu file calls written here. */
#include <stdio.h>
#include "sim-main.h"
#define SEMOPS_DEFINE_INLINE
#include "cgen-ops.h"
#include "ub-guards.h"
#include "xs16-bus.h"
#include "gen/sem.c"

unsigned xs16_ub;
const xs16_case *xs16_bus_case;
xs16_result *xs16_bus_res;
const char *xs16_oracle_name = "cgen26";

/* The decoder's switch, lifted out of gen/dec.c by the Makefile (decode-switch.inc). */
static int xs16_itype(CGEN_INSN_WORD base_insn, CGEN_INSN_WORD entire_insn)
{
	XSTORMY16_INSN_TYPE itype;
	{
#include "decode-switch.inc"
done:
	return itype;
}
static const char *const itype_names[] = {
#include "itype-names.inc"
};

void h_pc_set_handler(SIM_CPU *c, USI v) { c->cpu_data.hardware.h_pc = v; }
void h_gr_set_handler(SIM_CPU *c, UINT i, SI v) { c->cpu_data.hardware.h_gr[i] = v & 0xffff; }  /* H2 */
BI parity(SIM_CPU *c, SI v) { return __builtin_popcount((UHI) v) & 1; }                             /* H1 */
QI GETMEMQI(SIM_CPU *c, IADDR p, USI a) { return (QI) xs16_rd(a, 1); }
HI GETMEMHI(SIM_CPU *c, IADDR p, USI a) { return (HI) xs16_rd(a, 2); }
SI GETMEMSI(SIM_CPU *c, IADDR p, USI a) { return (SI) xs16_rd(a, 4); }
void SETMEMQI(SIM_CPU *c, IADDR p, USI a, QI v) { xs16_wr(a, 1, (UQI) v); }
void SETMEMHI(SIM_CPU *c, IADDR p, USI a, HI v) { xs16_wr(a, 2, (UHI) v); }
void SETMEMSI(SIM_CPU *c, IADDR p, USI a, SI v) { xs16_wr(a, 4, (USI) v); }
void do_halt(SIM_CPU *c) { xs16_event("halt"); }
void do_hold(SIM_CPU *c) { xs16_event("hold"); }
void do_holdx(SIM_CPU *c) { xs16_event("holdx"); }
void do_brk(SIM_CPU *c) { xs16_event("brk"); }
void syscall(SIM_CPU *c) { xs16_event("syscall"); }
USI sim_engine_invalid_insn(SIM_CPU *c, IADDR p, USI v) { xs16_event("invalid"); return v; }

static SEM_STATUS (*fn_for(int it))(SIM_CPU *, SEM_ARG, CGEN_INSN_WORD)
{
	for (const struct sem_fn_desc *s = sem_fns; s->fn; s++)
		if (s->index == it)
			return s->fn;
	return 0;
}

/* The generated decoder tests (w0 << 16 | w1) for 4-byte formats and w0 alone for 2-byte
 * ones, so try the 32-bit decode first and fall back when it is invalid or its semantic
 * function reports a 2-byte length (ASSUMPTIONS.md H5). */
void xs16_oracle_step(const xs16_case *c, xs16_result *res)
{
	SIM_CPU cpu, probe;
	ARGBUF ab = {0};
	memset(res, 0, sizeof *res);
	memset(&cpu, 0, sizeof cpu);
	cpu.cpu_data.hardware.h_pc = c->pc;
	for (int i = 0; i < 16; i++)
		cpu.cpu_data.hardware.h_gr[i] = c->r[i];
	CGEN_INSN_WORD insn = (USI) c->w0 << 16 | c->w1;
	int it = xs16_itype(c->w0, insn);
	if (it != XSTORMY16_INSN_X_INVALID) {
		xs16_result scratch;
		probe = cpu;
		xs16_bus_begin(c, &scratch);
		memset(&scratch, 0, sizeof scratch);
		fn_for(it)(&probe, &ab, insn);
		if (probe.len != 4)
			it = XSTORMY16_INSN_X_INVALID;
	}
	if (it == XSTORMY16_INSN_X_INVALID) {
		insn = c->w0;
		it = xs16_itype(c->w0, insn);
	}
	snprintf(res->insn, sizeof res->insn, "%s", itype_names[it]);
	res->cti = '-';
	if (it == XSTORMY16_INSN_X_INVALID) {
		res->status = XS16_INVALID;
		return;
	}
	xs16_bus_begin(c, res);
	xs16_ub = 0;
	fn_for(it)(&cpu, &ab, insn);
	res->cti = cpu.cti ? '*' : '-';
	res->taken = cpu.taken;
	res->npc = cpu.next_pc;
	for (int i = 0; i < 16; i++)
		res->r[i] = cpu.cpu_data.hardware.h_gr[i];
	res->ub = xs16_ub;
}
