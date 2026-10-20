// Stands in for SID's hand-written xstormy16.h so that the CGEN-generated
// xstormy16-sem.cxx and xstormy16-decode.cxx from the SID snapshot compile without the
// SID component framework (oracle O1). fetch-sid.sh provides the generated files,
// cgen-ops.h, cgen-types.h and extract.inc; the hooks SID wrote by hand are included
// verbatim from sid-hooks.inc.
#pragma once
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <ostream>
#include <sstream>
#include <iostream>
using std::hex; using std::dec; using std::endl; using std::cerr;
#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
namespace sid {
typedef int8_t signed_host_int_1; typedef int16_t signed_host_int_2;
typedef int32_t signed_host_int_4; typedef int64_t signed_host_int_8;
typedef uint8_t host_int_1; typedef uint16_t host_int_2;
typedef uint32_t host_int_4; typedef uint64_t host_int_8;
}
#include "cgen-types.h"
#include "cgen-ops.h"
#include "ub-guards.h"
#include "extract.inc"
namespace cgen {
enum sem_status { SEM_STATUS_NORMAL, SEM_STATUS_BRANCH_TAKEN, SEM_STATUS_DELAYED_BRANCH_TAKEN, SEM_STATUS_STALLED };
enum virtual_insn_type { VIRTUAL_INSN_INVALID, VIRTUAL_INSN_BEGIN, VIRTUAL_INSN_COND,
	VIRTUAL_INSN_CHAIN, VIRTUAL_INSN_CTI_CHAIN, VIRTUAL_INSN_BEFORE, VIRTUAL_INSN_AFTER };
union cgoto_label { void *label; void **frags; };
}
using namespace cgen;
#include "xstormy16-desc.h"
#include "xstormy16-defs.h"
#include "xstormy16-decode.h"
#include "xs16-bus.h"

namespace xstormy16 {
class xstormy16_cpu {
public:
#include "xstormy16-cpu.h"
	bool reversible_p = false;
	void log_pc_change (USI) {}
	void log_gr_change (UINT, SI) {}
#include "sid-hooks.inc"

	int taken = 0;
	QI GETMEMQI (PCADDR, ADDR a) { return (QI) xs16_rd (a, 1); }
	HI GETMEMHI (PCADDR, ADDR a) { return (HI) xs16_rd (a, 2); }
	SI GETMEMSI (PCADDR, ADDR a) { return (SI) xs16_rd (a, 4); }
	void SETMEMQI (PCADDR, ADDR a, QI v) { xs16_wr (a, 1, (uint8_t) v); }
	void SETMEMHI (PCADDR, ADDR a, HI v) { xs16_wr (a, 2, (uint16_t) v); }
	void SETMEMSI (PCADDR, ADDR a, SI v) { xs16_wr (a, 4, (uint32_t) v); }
	UHI GETIMEMHI (PCADDR, ADDR a) { return (UHI) xs16_rd (a, 2); }

	bool trace_result_p = false, trace_extract_p = false;
	std::ostringstream trace_stream;
	void branch (PCADDR n, PCADDR &npc, sem_status &) { npc = n; taken = 1; }
	void done_insn (PCADDR npc, sem_status &) { h_pc_set (npc); }
	void done_cti_insn (PCADDR npc, sem_status &) { h_pc_set (npc); }
	void invalid_insn (PCADDR pc) { xs16_event ("invalid"); h_pc_set (pc); }
	// SID's versions signal traps to the board; the oracle only records that they ran.
	void syscall () { xs16_event ("syscall"); }
	void do_brk () { xs16_event ("brk"); }
	void do_halt () { xs16_event ("halt"); }
	void do_hold () { xs16_event ("hold"); }
	void do_holdx () { xs16_event ("holdx"); }
};
}
