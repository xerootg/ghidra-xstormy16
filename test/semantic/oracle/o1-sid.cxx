// Oracle O1: the CGEN-generated xstormy16 semantics shipped in the SID snapshot.
#include "xstormy16.h"
#include <cstring>
using namespace xstormy16;

unsigned xs16_ub;
extern "C" const xs16_case *xs16_bus_case;
extern "C" xs16_result *xs16_bus_res;
const xs16_case *xs16_bus_case;
xs16_result *xs16_bus_res;
extern "C" const char *xs16_oracle_name = "sid";

extern "C" void xs16_oracle_step(const xs16_case *c, xs16_result *res)
{
	memset(res, 0, sizeof *res);
	xs16_bus_begin(c, res);
	xs16_ub = 0;
	xstormy16_cpu cpu;
	cpu.hardware.h_pc = c->pc;
	for (int i = 0; i < 16; i++)
		cpu.hardware.h_gr[i] = c->r[i];
	xstormy16_scache sc;
	sc.addr = c->pc;
	USI insn = (USI) c->w0 << 16 | c->w1;
	sc.decode(&cpu, c->pc, insn, insn);
	xstormy16_idesc *id = sc.idesc;
	snprintf(res->insn, sizeof res->insn, "%s", id->insn_name);
	res->cti = id->attrs.get_cond_cti_attr() ? 'C' : id->attrs.get_uncond_cti_attr() ? 'U' : '-';
	if (id->sem_index == XSTORMY16_INSN_X_INVALID) {
		res->status = XS16_INVALID;
		return;
	}
	id->execute(&cpu, &sc);
	res->taken = cpu.taken;
	res->npc = cpu.hardware.h_pc;
	for (int i = 0; i < 16; i++)
		res->r[i] = cpu.hardware.h_gr[i];
	res->ub = xs16_ub;
}
