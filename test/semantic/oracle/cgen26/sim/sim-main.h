/* Stands in for gdb's sim/common so the CGEN-generated gen/sem.c compiles on its own
 * (oracle O2). Only the types, SEM_* macros and field extractors the generated code
 * uses are defined; everything a simulator needs beyond one instruction is left out. */
#ifndef SIM_MAIN_H
#define SIM_MAIN_H
#include <stdint.h>
#include <string.h>
typedef int8_t QI; typedef uint8_t UQI; typedef int16_t HI; typedef uint16_t UHI;
typedef int32_t SI; typedef uint32_t USI; typedef int64_t DI; typedef uint64_t UDI;
typedef int BI; typedef unsigned int UINT; typedef int INT;
typedef float SF; typedef double DF; typedef long double XF; typedef long double TF;
typedef uint32_t IADDR; typedef uint32_t SEM_PC; typedef uint32_t CGEN_INSN_INT;
typedef int SEM_STATUS;
#define UNUSED __attribute__((unused))
#define XCONCAT3(a, b, c) a##b##c
#define EXTERN_INLINE static inline
#define HOST_BYTE_ORDER 0
#define BFD_ENDIAN_BIG 1
#define ATTRIBUTE_NORETURN __attribute__((noreturn))
#define MAKEDI(h, l) ((DI) (((UDI) (USI) (h) << 32) | (USI) (l)))

typedef struct cgen_insn CGEN_INSN;
typedef struct { const CGEN_INSN *idata; void *sem_fast, *sem_full; int attrs; } IDESC;
typedef int CPUREG_FETCH_FN; typedef int CPUREG_STORE_FN;
typedef struct { int written; IDESC *idesc; } ARGBUF;
typedef ARGBUF *SEM_ARG;

struct sim_cpu;
typedef struct sim_cpu SIM_CPU;
void h_pc_set_handler(SIM_CPU *, USI);
void h_gr_set_handler(SIM_CPU *, UINT, SI);
BI parity(SIM_CPU *, SI);
QI GETMEMQI(SIM_CPU *, IADDR, USI); HI GETMEMHI(SIM_CPU *, IADDR, USI); SI GETMEMSI(SIM_CPU *, IADDR, USI);
void SETMEMQI(SIM_CPU *, IADDR, USI, QI); void SETMEMHI(SIM_CPU *, IADDR, USI, HI); void SETMEMSI(SIM_CPU *, IADDR, USI, SI);
void do_halt(SIM_CPU *); void do_hold(SIM_CPU *); void do_holdx(SIM_CPU *); void do_brk(SIM_CPU *); void syscall(SIM_CPU *);
USI sim_engine_invalid_insn(SIM_CPU *, IADDR, USI);

#include "cpu.h"
#include "dec.h"

struct sim_cpu {
	XSTORMY16_CPU_DATA cpu_data;
	USI next_pc;
	int len, cti, taken;
};
#define XSTORMY16_SIM_CPU(cpu) (cpu)
#define CPU(x) (current_cpu->cpu_data.hardware.x)
#define CPU_IDESC(cpu) ((IDESC *) 0)
#define CPU_MACH(cpu) 0
#define MACH_NUM(m) 0
#define CGEN_INSN_VIRTUAL_P(insn) 0
#define CGEN_INSN_MACH_HAS_P(insn, m) 0
#define CGEN_ATTR_VALUE(a, b, c) 0

#define SEM_ARGBUF(a) (a)
#define SEM_NEXT_VPC(sa, pc, l) (current_cpu->len = (l), (pc) + (l))
#define SEM_BRANCH_INIT
#define SEM_BRANCH_VIA_ADDR(cpu, sa, addr, vpc) do { (vpc) = (addr); (cpu)->taken = 1; } while (0)
#define SEM_BRANCH_VIA_CACHE(cpu, sa, addr, vpc) SEM_BRANCH_VIA_ADDR (cpu, sa, addr, vpc)
#define SEM_BRANCH_FINI(vpc, a) (current_cpu->next_pc = (vpc), current_cpu->cti = 1)
#define SEM_NBRANCH_FINI(vpc, a) (current_cpu->next_pc = (vpc))
#define CGEN_TRACE_RESULT(cpu, abuf, name, type, val)
#define EXTRACT_MSB0_UINT(insn, total, start, length) \
	((UINT) (((insn) >> ((total) - (start) - (length))) & ((1u << (length)) - 1)))
#define EXTRACT_MSB0_SINT(insn, total, start, length) \
	((INT) (((INT) ((insn) << (32 - (total) + (start)))) >> (32 - (length))))
#define JOINHISI(h, l) ((SI) (((USI) (UHI) (h) << 16) | (USI) (UHI) (l)))

struct sem_fn_desc { int index; SEM_STATUS (*fn)(SIM_CPU *, SEM_ARG, CGEN_INSN_WORD); };
#endif
