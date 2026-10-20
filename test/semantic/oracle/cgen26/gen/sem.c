/* Simulator instruction semantics for xstormy16.

THIS FILE IS MACHINE GENERATED WITH CGEN.

Copyright (C) 1996-2026 Free Software Foundation, Inc.

This file is part of the GNU simulators.

   This file is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.

*/

#define WANT_CPU xstormy16
#define WANT_CPU_XSTORMY16

#include "sim-main.h"
#include "cgen-mem.h"
#include "cgen-ops.h"

#undef GET_ATTR
#define GET_ATTR(cpu, num, attr) CGEN_ATTR_VALUE (NULL, abuf->idesc->attrs, CGEN_INSN_##attr)

/* This is used so that we can compile two copies of the semantic code,
   one with full feature support and one without that runs fast(er).
   FAST_P, when desired, is defined on the command line, -DFAST_P=1.  */
#if FAST_P
#define SEM_FN_NAME(cpu,fn) XCONCAT3 (cpu,_semf_,fn)
#undef CGEN_TRACE_RESULT
#define CGEN_TRACE_RESULT(cpu, abuf, name, type, val)
#else
#define SEM_FN_NAME(cpu,fn) XCONCAT3 (cpu,_sem_,fn)
#endif

/* x-invalid: --invalid-- */

static SEM_STATUS
SEM_FN_NAME (xstormy16,x_invalid) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 0);
  EXTRACT_IFMT_EMPTY_VARS /* */
  EXTRACT_IFMT_EMPTY_CODE

  {
    /* Update the recorded pc in the cpu state struct.
       Only necessary for WITH_SCACHE case, but to avoid the
       conditional compilation ....  */
    SET_H_PC (pc);
    /* Virtual insns have zero size.  Overwrite vpc with address of next insn
       using the default-insn-bitsize spec.  When executing insns in parallel
       we may want to queue the fault and continue execution.  */
    vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
    vpc = sim_engine_invalid_insn (current_cpu, pc, vpc);
  }

  SEM_NBRANCH_FINI (vpc, 0|(1<<CGEN_INSN_VIRTUAL));
#undef FLD
  return status;
}

/* x-after: --after-- */

static SEM_STATUS
SEM_FN_NAME (xstormy16,x_after) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 0);
  EXTRACT_IFMT_EMPTY_VARS /* */
  EXTRACT_IFMT_EMPTY_CODE

  {
#if WITH_SCACHE_PBB_XSTORMY16
    xstormy16_pbb_after (current_cpu, sem_arg);
#endif
  }

  SEM_NBRANCH_FINI (vpc, 0|(1<<CGEN_INSN_PBB)|(1<<CGEN_INSN_VIRTUAL));
#undef FLD
  return status;
}

/* x-before: --before-- */

static SEM_STATUS
SEM_FN_NAME (xstormy16,x_before) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 0);
  EXTRACT_IFMT_EMPTY_VARS /* */
  EXTRACT_IFMT_EMPTY_CODE

  {
#if WITH_SCACHE_PBB_XSTORMY16
    xstormy16_pbb_before (current_cpu, sem_arg);
#endif
  }

  SEM_NBRANCH_FINI (vpc, 0|(1<<CGEN_INSN_PBB)|(1<<CGEN_INSN_VIRTUAL));
#undef FLD
  return status;
}

/* x-cti-chain: --cti-chain-- */

static SEM_STATUS
SEM_FN_NAME (xstormy16,x_cti_chain) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 0);
  EXTRACT_IFMT_EMPTY_VARS /* */
  EXTRACT_IFMT_EMPTY_CODE

  {
#if WITH_SCACHE_PBB_XSTORMY16
#ifdef DEFINE_SWITCH
    vpc = xstormy16_pbb_cti_chain (current_cpu, sem_arg,
			       pbb_br_type, pbb_br_npc);
    BREAK (sem);
#else
    /* FIXME: Allow provision of explicit ifmt spec in insn spec.  */
    vpc = xstormy16_pbb_cti_chain (current_cpu, sem_arg,
			       CPU_PBB_BR_TYPE (current_cpu),
			       CPU_PBB_BR_NPC (current_cpu));
#endif
#endif
  }

  SEM_NBRANCH_FINI (vpc, 0|(1<<CGEN_INSN_PBB)|(1<<CGEN_INSN_VIRTUAL));
#undef FLD
  return status;
}

/* x-chain: --chain-- */

static SEM_STATUS
SEM_FN_NAME (xstormy16,x_chain) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 0);
  EXTRACT_IFMT_EMPTY_VARS /* */
  EXTRACT_IFMT_EMPTY_CODE

  {
#if WITH_SCACHE_PBB_XSTORMY16
    vpc = xstormy16_pbb_chain (current_cpu, sem_arg);
#ifdef DEFINE_SWITCH
    BREAK (sem);
#endif
#endif
  }

  SEM_NBRANCH_FINI (vpc, 0|(1<<CGEN_INSN_PBB)|(1<<CGEN_INSN_VIRTUAL));
#undef FLD
  return status;
}

/* x-begin: --begin-- */

static SEM_STATUS
SEM_FN_NAME (xstormy16,x_begin) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 0);
  EXTRACT_IFMT_EMPTY_VARS /* */
  EXTRACT_IFMT_EMPTY_CODE

  {
#if WITH_SCACHE_PBB_XSTORMY16
#if defined DEFINE_SWITCH || defined FAST_P
    /* In the switch case FAST_P is a constant, allowing several optimizations
       in any called inline functions.  */
    vpc = xstormy16_pbb_begin (current_cpu, FAST_P);
#else
#if 0 /* cgen engine can't handle dynamic fast/full switching yet.  */
    vpc = xstormy16_pbb_begin (current_cpu, STATE_RUN_FAST_P (CPU_STATE (current_cpu)));
#else
    vpc = xstormy16_pbb_begin (current_cpu, 0);
#endif
#endif
#endif
  }

  SEM_NBRANCH_FINI (vpc, 0|(1<<CGEN_INSN_PBB)|(1<<CGEN_INSN_VIRTUAL));
#undef FLD
  return status;
}

/* movlmemimm: mov$ws2 $lmem8,#$imm16 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movlmemimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVLMEMIMM_VARS /* f-op1 f-op2a f-op2m f-lmem8 f-imm16 */
  EXTRACT_IFMT_MOVLMEMIMM_CODE

if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = f_imm16;
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    HI opval = tmp_nvalue;
    SETMEMHI (current_cpu, pc, ANDSI (f_lmem8, 65534), opval);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (f_imm16, 255);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    QI opval = tmp_nvalue;
    SETMEMQI (current_cpu, pc, f_lmem8, opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movhmemimm: mov$ws2 $hmem8,#$imm16 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movhmemimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVHMEMIMM_VARS /* f-op1 f-op2a f-op2m f-hmem8 f-imm16 */
  EXTRACT_IFMT_MOVHMEMIMM_CODE

if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = f_imm16;
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    HI opval = tmp_nvalue;
    SETMEMHI (current_cpu, pc, ANDSI (f_hmem8, 65534), opval);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (f_imm16, 255);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    QI opval = tmp_nvalue;
    SETMEMQI (current_cpu, pc, f_hmem8, opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movlgrmem: mov$ws2 $Rm,$lmem8 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movlgrmem) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVLGRMEM_VARS /* f-op1 f-Rm f-op2m f-lmem8 */
  EXTRACT_IFMT_MOVLGRMEM_CODE

if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMHI (current_cpu, pc, ANDSI (f_lmem8, 65534));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rm, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMQI (current_cpu, pc, f_lmem8);
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rm, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movhgrmem: mov$ws2 $Rm,$hmem8 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movhgrmem) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVHGRMEM_VARS /* f-op1 f-Rm f-op2m f-hmem8 */
  EXTRACT_IFMT_MOVHGRMEM_CODE

if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMHI (current_cpu, pc, ANDSI (f_hmem8, 65534));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rm, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMQI (current_cpu, pc, f_hmem8);
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rm, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movlmemgr: mov$ws2 $lmem8,$Rm */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movlmemgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVLGRMEM_VARS /* f-op1 f-Rm f-op2m f-lmem8 */
  EXTRACT_IFMT_MOVLGRMEM_CODE

if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    HI opval = tmp_nvalue;
    SETMEMHI (current_cpu, pc, ANDSI (f_lmem8, 65534), opval);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    QI opval = tmp_nvalue;
    SETMEMQI (current_cpu, pc, f_lmem8, opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movhmemgr: mov$ws2 $hmem8,$Rm */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movhmemgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVHGRMEM_VARS /* f-op1 f-Rm f-op2m f-hmem8 */
  EXTRACT_IFMT_MOVHGRMEM_CODE

if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    HI opval = tmp_nvalue;
    SETMEMHI (current_cpu, pc, ANDSI (f_hmem8, 65534), opval);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    QI opval = tmp_nvalue;
    SETMEMQI (current_cpu, pc, f_hmem8, opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movgrgri: mov$ws2 $Rdm,($Rs) */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movgrgri) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGRI_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm */
  EXTRACT_IFMT_MOVGRGRI_CODE

if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMHI (current_cpu, pc, ANDSI (GET_H_GR (f_Rs), 65534));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (255, GETMEMQI (current_cpu, pc, GET_H_GR (f_Rs)));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movgrgripostinc: mov$ws2 $Rdm,($Rs++) */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movgrgripostinc) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGRI_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm */
  EXTRACT_IFMT_MOVGRGRI_CODE

{
if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMHI (current_cpu, pc, ANDSI (GET_H_GR (f_Rs), 65534));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (255, GETMEMQI (current_cpu, pc, GET_H_GR (f_Rs)));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}
  {
    SI opval = ADDSI (GET_H_GR (f_Rs), ADDSI (1, f_op2m));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movgrgripredec: mov$ws2 $Rdm,(--$Rs) */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movgrgripredec) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGRI_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm */
  EXTRACT_IFMT_MOVGRGRI_CODE

{
  {
    SI opval = SUBSI (GET_H_GR (f_Rs), ADDSI (1, f_op2m));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMHI (current_cpu, pc, ANDSI (GET_H_GR (f_Rs), 65534));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (255, GETMEMQI (current_cpu, pc, GET_H_GR (f_Rs)));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movgrigr: mov$ws2 ($Rs),$Rdm */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movgrigr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGRI_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm */
  EXTRACT_IFMT_MOVGRGRI_CODE

{
if (f_op2m) {
  {
    HI opval = GET_H_GR (f_Rdm);
    SETMEMHI (current_cpu, pc, ANDSI (GET_H_GR (f_Rs), 65534), opval);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
  {
    QI opval = GET_H_GR (f_Rdm);
    SETMEMQI (current_cpu, pc, GET_H_GR (f_Rs), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rdm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movgripostincgr: mov$ws2 ($Rs++),$Rdm */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movgripostincgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGRI_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm */
  EXTRACT_IFMT_MOVGRGRI_CODE

{
if (f_op2m) {
  {
    HI opval = GET_H_GR (f_Rdm);
    SETMEMHI (current_cpu, pc, ANDSI (GET_H_GR (f_Rs), 65534), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
  {
    QI opval = GET_H_GR (f_Rdm);
    SETMEMQI (current_cpu, pc, GET_H_GR (f_Rs), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rdm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
  {
    SI opval = ADDSI (GET_H_GR (f_Rs), ADDSI (f_op2m, 1));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movgripredecgr: mov$ws2 (--$Rs),$Rdm */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movgripredecgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGRI_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm */
  EXTRACT_IFMT_MOVGRGRI_CODE

{
  {
    SI opval = SUBSI (GET_H_GR (f_Rs), ADDSI (f_op2m, 1));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rdm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
if (f_op2m) {
  {
    HI opval = GET_H_GR (f_Rdm);
    SETMEMHI (current_cpu, pc, ANDSI (GET_H_GR (f_Rs), 65534), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
  {
    QI opval = GET_H_GR (f_Rdm);
    SETMEMQI (current_cpu, pc, GET_H_GR (f_Rs), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movgrgrii: mov$ws2 $Rdm,($Rs,$imm12) */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movgrgrii) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVGRGRII_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm f-op5 f-imm12 */
  EXTRACT_IFMT_MOVGRGRII_CODE

if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMHI (current_cpu, pc, ANDSI (ADDSI (GET_H_GR (f_Rs), f_imm12), 65534));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (255, GETMEMQI (current_cpu, pc, ADDSI (GET_H_GR (f_Rs), f_imm12)));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movgrgriipostinc: mov$ws2 $Rdm,($Rs++,$imm12) */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movgrgriipostinc) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVGRGRII_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm f-op5 f-imm12 */
  EXTRACT_IFMT_MOVGRGRII_CODE

{
if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMHI (current_cpu, pc, ANDSI (ADDSI (GET_H_GR (f_Rs), f_imm12), 65534));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (255, GETMEMQI (current_cpu, pc, ADDSI (GET_H_GR (f_Rs), f_imm12)));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}
  {
    SI opval = ADDSI (GET_H_GR (f_Rs), ADDSI (f_op2m, 1));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movgrgriipredec: mov$ws2 $Rdm,(--$Rs,$imm12) */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movgrgriipredec) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVGRGRII_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm f-op5 f-imm12 */
  EXTRACT_IFMT_MOVGRGRII_CODE

{
  {
    SI opval = SUBSI (GET_H_GR (f_Rs), ADDSI (f_op2m, 1));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMHI (current_cpu, pc, ANDSI (ADDSI (GET_H_GR (f_Rs), f_imm12), 65534));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (255, GETMEMQI (current_cpu, pc, ADDSI (GET_H_GR (f_Rs), f_imm12)));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movgriigr: mov$ws2 ($Rs,$imm12),$Rdm */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movgriigr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVGRGRII_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm f-op5 f-imm12 */
  EXTRACT_IFMT_MOVGRGRII_CODE

{
if (f_op2m) {
  {
    HI opval = GET_H_GR (f_Rdm);
    SETMEMHI (current_cpu, pc, ANDSI (ADDSI (GET_H_GR (f_Rs), f_imm12), 65534), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
  {
    QI opval = GET_H_GR (f_Rdm);
    SETMEMQI (current_cpu, pc, ADDSI (GET_H_GR (f_Rs), f_imm12), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rdm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movgriipostincgr: mov$ws2 ($Rs++,$imm12),$Rdm */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movgriipostincgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVGRGRII_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm f-op5 f-imm12 */
  EXTRACT_IFMT_MOVGRGRII_CODE

{
if (f_op2m) {
  {
    HI opval = GET_H_GR (f_Rdm);
    SETMEMHI (current_cpu, pc, ANDSI (ADDSI (GET_H_GR (f_Rs), f_imm12), 65534), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
  {
    QI opval = GET_H_GR (f_Rdm);
    SETMEMQI (current_cpu, pc, ADDSI (GET_H_GR (f_Rs), f_imm12), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rdm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
  {
    SI opval = ADDSI (GET_H_GR (f_Rs), ADDSI (f_op2m, 1));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movgriipredecgr: mov$ws2 (--$Rs,$imm12),$Rdm */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movgriipredecgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVGRGRII_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm f-op5 f-imm12 */
  EXTRACT_IFMT_MOVGRGRII_CODE

{
  {
    SI opval = SUBSI (GET_H_GR (f_Rs), ADDSI (f_op2m, 1));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rdm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
if (f_op2m) {
  {
    HI opval = GET_H_GR (f_Rdm);
    SETMEMHI (current_cpu, pc, ANDSI (ADDSI (GET_H_GR (f_Rs), f_imm12), 65534), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
  {
    QI opval = GET_H_GR (f_Rdm);
    SETMEMQI (current_cpu, pc, ADDSI (GET_H_GR (f_Rs), f_imm12), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movgrgr: mov $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rs);
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movwimm8: mov.w Rx,#$imm8 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movwimm8) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVWIMM8_VARS /* f-op1 f-op2 f-imm8 */
  EXTRACT_IFMT_MOVWIMM8_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = f_imm8;
  {
    HI opval = tmp_nvalue;
    SET_H_GR (GET_H_RPSW (), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (GET_H_RPSW (), 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movwgrimm8: mov.w $Rm,#$imm8small */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movwgrimm8) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVWGRIMM8_VARS /* f-op1 f-Rm f-op2m f-imm8 */
  EXTRACT_IFMT_MOVWGRIMM8_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = f_imm8;
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rm, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movwgrimm16: mov.w $Rd,#$imm16 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movwgrimm16) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVWGRIMM16_VARS /* f-op1 f-op2 f-op3 f-Rd f-imm16 */
  EXTRACT_IFMT_MOVWGRIMM16_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = f_imm16;
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movlowgr: mov.b $Rd,RxL */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movlowgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVLOWGR_VARS /* f-op1 f-op2 f-op3 f-Rd */
  EXTRACT_IFMT_MOVLOWGR_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ORSI (ANDSI (GET_H_GR (f_Rd), 65280), ANDHI (GET_H_GR (GET_H_RPSW ()), 255));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (0, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movhighgr: mov.b $Rd,RxH */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movhighgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVLOWGR_VARS /* f-op1 f-op2 f-op3 f-Rd */
  EXTRACT_IFMT_MOVLOWGR_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ORSI (ANDSI (GET_H_GR (f_Rd), 255), ANDHI (GET_H_GR (GET_H_RPSW ()), 65280));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movfgrgri: movf$ws2 $Rdm,($Rs) */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movfgrgri) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGRI_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm */
  EXTRACT_IFMT_MOVGRGRI_CODE

if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMHI (current_cpu, pc, ANDSI (ORSI (SLLSI (GET_H_GR (((UINT) 8)), 16), GET_H_GR (f_Rs)), 0xfffffffe));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (255, GETMEMQI (current_cpu, pc, ORSI (SLLSI (GET_H_GR (((UINT) 8)), 16), GET_H_GR (f_Rs))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movfgrgripostinc: movf$ws2 $Rdm,($Rs++) */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movfgrgripostinc) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGRI_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm */
  EXTRACT_IFMT_MOVGRGRI_CODE

{
if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMHI (current_cpu, pc, ANDSI (JOINHISI (GET_H_GR (((UINT) 8)), GET_H_GR (f_Rs)), 0xfffffffe));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (255, GETMEMQI (current_cpu, pc, JOINHISI (GET_H_GR (((UINT) 8)), GET_H_GR (f_Rs))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}
  {
    SI opval = ADDSI (GET_H_GR (f_Rs), ADDSI (f_op2m, 1));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movfgrgripredec: movf$ws2 $Rdm,(--$Rs) */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movfgrgripredec) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGRI_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm */
  EXTRACT_IFMT_MOVGRGRI_CODE

{
  {
    SI opval = SUBSI (GET_H_GR (f_Rs), ADDSI (f_op2m, 1));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMHI (current_cpu, pc, ANDSI (JOINHISI (GET_H_GR (((UINT) 8)), GET_H_GR (f_Rs)), 0xfffffffe));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (255, GETMEMQI (current_cpu, pc, JOINHISI (GET_H_GR (((UINT) 8)), GET_H_GR (f_Rs))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movfgrigr: movf$ws2 ($Rs),$Rdm */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movfgrigr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGRI_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm */
  EXTRACT_IFMT_MOVGRGRI_CODE

{
if (f_op2m) {
  {
    HI opval = GET_H_GR (f_Rdm);
    SETMEMHI (current_cpu, pc, ANDSI (JOINHISI (GET_H_GR (((UINT) 8)), GET_H_GR (f_Rs)), 0xfffffffe), opval);
    written |= (1 << 6);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
  {
    QI opval = GET_H_GR (f_Rdm);
    SETMEMQI (current_cpu, pc, JOINHISI (GET_H_GR (((UINT) 8)), GET_H_GR (f_Rs)), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rdm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movfgripostincgr: movf$ws2 ($Rs++),$Rdm */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movfgripostincgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGRI_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm */
  EXTRACT_IFMT_MOVGRGRI_CODE

{
if (f_op2m) {
  {
    HI opval = GET_H_GR (f_Rdm);
    SETMEMHI (current_cpu, pc, ANDSI (JOINHISI (GET_H_GR (((UINT) 8)), GET_H_GR (f_Rs)), 0xfffffffe), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
  {
    QI opval = GET_H_GR (f_Rdm);
    SETMEMQI (current_cpu, pc, JOINHISI (GET_H_GR (((UINT) 8)), GET_H_GR (f_Rs)), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rdm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
  {
    SI opval = ADDSI (GET_H_GR (f_Rs), ADDSI (f_op2m, 1));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movfgripredecgr: movf$ws2 (--$Rs),$Rdm */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movfgripredecgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGRI_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm */
  EXTRACT_IFMT_MOVGRGRI_CODE

{
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rdm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
  {
    SI opval = SUBSI (GET_H_GR (f_Rs), ADDSI (f_op2m, 1));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
if (f_op2m) {
  {
    HI opval = GET_H_GR (f_Rdm);
    SETMEMHI (current_cpu, pc, ANDSI (JOINHISI (GET_H_GR (((UINT) 8)), GET_H_GR (f_Rs)), 0xfffffffe), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
  {
    QI opval = GET_H_GR (f_Rdm);
    SETMEMQI (current_cpu, pc, JOINHISI (GET_H_GR (((UINT) 8)), GET_H_GR (f_Rs)), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movfgrgrii: movf$ws2 $Rdm,($Rb,$Rs,$imm12) */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movfgrgrii) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVFGRGRII_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm f-op5a f-Rb f-imm12 */
  EXTRACT_IFMT_MOVFGRGRII_CODE

if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMHI (current_cpu, pc, ANDSI (ADDSI (JOINHISI (GET_H_RB (f_Rb), GET_H_GR (f_Rs)), f_imm12), 0xfffffffe));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (255, GETMEMQI (current_cpu, pc, ADDSI (JOINHISI (GET_H_RB (f_Rb), GET_H_GR (f_Rs)), f_imm12)));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movfgrgriipostinc: movf$ws2 $Rdm,($Rb,$Rs++,$imm12) */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movfgrgriipostinc) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVFGRGRII_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm f-op5a f-Rb f-imm12 */
  EXTRACT_IFMT_MOVFGRGRII_CODE

{
if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMHI (current_cpu, pc, ANDSI (ADDSI (JOINHISI (GET_H_RB (f_Rb), GET_H_GR (f_Rs)), f_imm12), 0xfffffffe));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (255, GETMEMQI (current_cpu, pc, ADDSI (JOINHISI (GET_H_RB (f_Rb), GET_H_GR (f_Rs)), f_imm12)));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}
  {
    SI opval = ADDSI (GET_H_GR (f_Rs), ADDSI (f_op2m, 1));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
if (EQSI (GET_H_GR (f_Rs), 0)) {
  {
    SI opval = ADDSI (GET_H_RB (f_Rb), 1);
    SET_H_RB (f_Rb, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "Rb", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movfgrgriipredec: movf$ws2 $Rdm,($Rb,--$Rs,$imm12) */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movfgrgriipredec) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVFGRGRII_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm f-op5a f-Rb f-imm12 */
  EXTRACT_IFMT_MOVFGRGRII_CODE

{
if (EQSI (GET_H_GR (f_Rs), 0)) {
  {
    SI opval = SUBSI (GET_H_RB (f_Rb), 1);
    SET_H_RB (f_Rb, opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "Rb", 'x', opval);
  }
}
  {
    SI opval = SUBSI (GET_H_GR (f_Rs), ADDSI (f_op2m, 1));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
if (f_op2m) {
{
  HI tmp_nvalue;
  tmp_nvalue = GETMEMHI (current_cpu, pc, ANDSI (ADDSI (JOINHISI (GET_H_RB (f_Rb), GET_H_GR (f_Rs)), f_imm12), 0xfffffffe));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
} else {
{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (255, GETMEMQI (current_cpu, pc, ADDSI (JOINHISI (GET_H_RB (f_Rb), GET_H_GR (f_Rs)), f_imm12)));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rdm, opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movfgriigr: movf$ws2 ($Rb,$Rs,$imm12),$Rdm */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movfgriigr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVFGRGRII_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm f-op5a f-Rb f-imm12 */
  EXTRACT_IFMT_MOVFGRGRII_CODE

{
if (f_op2m) {
  {
    HI opval = GET_H_GR (f_Rdm);
    SETMEMHI (current_cpu, pc, ANDSI (ADDSI (JOINHISI (GET_H_RB (f_Rb), GET_H_GR (f_Rs)), f_imm12), 0xfffffffe), opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
  {
    QI opval = GET_H_GR (f_Rdm);
    SETMEMQI (current_cpu, pc, ADDSI (JOINHISI (GET_H_RB (f_Rb), GET_H_GR (f_Rs)), f_imm12), opval);
    written |= (1 << 8);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rdm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movfgriipostincgr: movf$ws2 ($Rb,$Rs++,$imm12),$Rdm */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movfgriipostincgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVFGRGRII_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm f-op5a f-Rb f-imm12 */
  EXTRACT_IFMT_MOVFGRGRII_CODE

{
if (f_op2m) {
  {
    HI opval = GET_H_GR (f_Rdm);
    SETMEMHI (current_cpu, pc, ANDSI (ADDSI (JOINHISI (GET_H_RB (f_Rb), GET_H_GR (f_Rs)), f_imm12), 0xfffffffe), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
  {
    QI opval = GET_H_GR (f_Rdm);
    SETMEMQI (current_cpu, pc, ADDSI (JOINHISI (GET_H_RB (f_Rb), GET_H_GR (f_Rs)), f_imm12), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rdm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
  {
    SI opval = ADDSI (GET_H_GR (f_Rs), ADDSI (f_op2m, 1));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
if (EQSI (GET_H_GR (f_Rs), 0)) {
  {
    SI opval = ADDSI (GET_H_RB (f_Rb), 1);
    SET_H_RB (f_Rb, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "Rb", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* movfgriipredecgr: movf$ws2 ($Rb,--$Rs,$imm12),$Rdm */

static SEM_STATUS
SEM_FN_NAME (xstormy16,movfgriipredecgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVFGRGRII_VARS /* f-op1 f-op2a f-op2m f-Rs f-op4m f-Rdm f-op5a f-Rb f-imm12 */
  EXTRACT_IFMT_MOVFGRGRII_CODE

{
if (EQSI (GET_H_GR (f_Rs), 0)) {
  {
    SI opval = SUBSI (GET_H_RB (f_Rb), 1);
    SET_H_RB (f_Rb, opval);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "Rb", 'x', opval);
  }
}
  {
    SI opval = SUBSI (GET_H_GR (f_Rs), ADDSI (f_op2m, 1));
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
{
  HI tmp_nvalue;
  tmp_nvalue = GET_H_GR (f_Rdm);
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rdm, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (f_op2m, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
if (f_op2m) {
  {
    HI opval = GET_H_GR (f_Rdm);
    SETMEMHI (current_cpu, pc, ANDSI (ADDSI (JOINHISI (GET_H_RB (f_Rb), GET_H_GR (f_Rs)), f_imm12), 0xfffffffe), opval);
    written |= (1 << 9);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
} else {
  {
    QI opval = GET_H_GR (f_Rdm);
    SETMEMQI (current_cpu, pc, ADDSI (JOINHISI (GET_H_RB (f_Rb), GET_H_GR (f_Rs)), f_imm12), opval);
    written |= (1 << 10);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* maskgrgr: mask $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,maskgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ORHI (ANDHI (GET_H_GR (f_Rd), INVHI (GET_H_GR (f_Rs))), ANDHI (GET_H_GR (GET_H_RPSW ()), GET_H_GR (f_Rs)));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* maskgrimm16: mask $Rd,#$imm16 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,maskgrimm16) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVWGRIMM16_VARS /* f-op1 f-op2 f-op3 f-Rd f-imm16 */
  EXTRACT_IFMT_MOVWGRIMM16_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ORSI (ANDSI (GET_H_GR (f_Rd), INVSI (f_imm16)), ANDHI (GET_H_GR (GET_H_RPSW ()), f_imm16));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* pushgr: push $Rd */

static SEM_STATUS
SEM_FN_NAME (xstormy16,pushgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVLOWGR_VARS /* f-op1 f-op2 f-op3 f-Rd */
  EXTRACT_IFMT_MOVLOWGR_CODE

{
  {
    HI opval = GET_H_GR (f_Rd);
    SETMEMHI (current_cpu, pc, GET_H_GR (((UINT) 15)), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  {
    SI opval = ADDSI (GET_H_GR (((UINT) 15)), 2);
    SET_H_GR (((UINT) 15), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* popgr: pop $Rd */

static SEM_STATUS
SEM_FN_NAME (xstormy16,popgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVLOWGR_VARS /* f-op1 f-op2 f-op3 f-Rd */
  EXTRACT_IFMT_MOVLOWGR_CODE

{
  {
    SI opval = ADDSI (GET_H_GR (((UINT) 15)), -2);
    SET_H_GR (((UINT) 15), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = GETMEMHI (current_cpu, pc, GET_H_GR (((UINT) 15)));
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* swpn: swpn $Rd */

static SEM_STATUS
SEM_FN_NAME (xstormy16,swpn) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVLOWGR_VARS /* f-op1 f-op2 f-op3 f-Rd */
  EXTRACT_IFMT_MOVLOWGR_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ORSI (ORSI (ANDSI (SLLSI (GET_H_GR (f_Rd), 4), 240), ANDSI (SRLSI (GET_H_GR (f_Rd), 4), 15)), ANDSI (GET_H_GR (f_Rd), 65280));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (0, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* swpb: swpb $Rd */

static SEM_STATUS
SEM_FN_NAME (xstormy16,swpb) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVLOWGR_VARS /* f-op1 f-op2 f-op3 f-Rd */
  EXTRACT_IFMT_MOVLOWGR_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ORSI (SLLSI (GET_H_GR (f_Rd), 8), SRLSI (GET_H_GR (f_Rd), 8));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* swpw: swpw $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,swpw) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_foo;
  tmp_foo = GET_H_GR (f_Rs);
  {
    SI opval = GET_H_GR (f_Rd);
    SET_H_GR (f_Rs, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
{
  HI tmp_nvalue;
  tmp_nvalue = tmp_foo;
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* andgrgr: and $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,andgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (GET_H_GR (f_Rd), GET_H_GR (f_Rs));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* andimm8: and Rx,#$imm8 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,andimm8) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVWIMM8_VARS /* f-op1 f-op2 f-imm8 */
  EXTRACT_IFMT_MOVWIMM8_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ANDHI (GET_H_GR (GET_H_RPSW ()), f_imm8);
  {
    HI opval = tmp_nvalue;
    SET_H_GR (GET_H_RPSW (), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (GET_H_RPSW (), 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* andgrimm16: and $Rd,#$imm16 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,andgrimm16) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVWGRIMM16_VARS /* f-op1 f-op2 f-op3 f-Rd f-imm16 */
  EXTRACT_IFMT_MOVWGRIMM16_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (GET_H_GR (f_Rd), f_imm16);
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* orgrgr: or $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,orgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ORSI (GET_H_GR (f_Rd), GET_H_GR (f_Rs));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* orimm8: or Rx,#$imm8 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,orimm8) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVWIMM8_VARS /* f-op1 f-op2 f-imm8 */
  EXTRACT_IFMT_MOVWIMM8_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ORHI (GET_H_GR (GET_H_RPSW ()), f_imm8);
  {
    HI opval = tmp_nvalue;
    SET_H_GR (GET_H_RPSW (), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (GET_H_RPSW (), 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* orgrimm16: or $Rd,#$imm16 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,orgrimm16) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVWGRIMM16_VARS /* f-op1 f-op2 f-op3 f-Rd f-imm16 */
  EXTRACT_IFMT_MOVWGRIMM16_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ORSI (GET_H_GR (f_Rd), f_imm16);
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* xorgrgr: xor $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,xorgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = XORSI (GET_H_GR (f_Rd), GET_H_GR (f_Rs));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* xorimm8: xor Rx,#$imm8 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,xorimm8) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVWIMM8_VARS /* f-op1 f-op2 f-imm8 */
  EXTRACT_IFMT_MOVWIMM8_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = XORHI (GET_H_GR (GET_H_RPSW ()), f_imm8);
  {
    HI opval = tmp_nvalue;
    SET_H_GR (GET_H_RPSW (), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (GET_H_RPSW (), 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* xorgrimm16: xor $Rd,#$imm16 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,xorgrimm16) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVWGRIMM16_VARS /* f-op1 f-op2 f-op3 f-Rd f-imm16 */
  EXTRACT_IFMT_MOVWGRIMM16_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = XORSI (GET_H_GR (f_Rd), f_imm16);
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* notgr: not $Rd */

static SEM_STATUS
SEM_FN_NAME (xstormy16,notgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVLOWGR_VARS /* f-op1 f-op2 f-op3 f-Rd */
  EXTRACT_IFMT_MOVLOWGR_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = INVSI (GET_H_GR (f_Rd));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* addgrgr: add $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,addgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = ADDCSI (GET_H_GR (f_Rd), GET_H_GR (f_Rs), 0);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (ADDOFHI (GET_H_GR (f_Rd), GET_H_GR (f_Rs), 0), 4), SLLHI (ADDCFHI (GET_H_GR (f_Rd), GET_H_GR (f_Rs), 0), 2)), ORHI (ANDHI (SRLHI (ADDCHI (ANDSI (GET_H_GR (f_Rd), 15), ANDSI (GET_H_GR (f_Rs), 15), 0), 1), 8), SLLSI (f_Rd, 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* addgrimm4: add $Rd,#$imm4 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,addgrimm4) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_ADDGRIMM4_VARS /* f-op1 f-op2 f-imm4 f-Rd */
  EXTRACT_IFMT_ADDGRIMM4_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = ADDCSI (GET_H_GR (f_Rd), f_imm4, 0);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (ADDOFHI (GET_H_GR (f_Rd), f_imm4, 0), 4), SLLHI (ADDCFHI (GET_H_GR (f_Rd), f_imm4, 0), 2)), ORHI (ANDHI (SRLHI (ADDCHI (ANDSI (GET_H_GR (f_Rd), 15), ANDSI (f_imm4, 15), 0), 1), 8), SLLSI (f_Rd, 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* addimm8: add Rx,#$imm8 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,addimm8) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVWIMM8_VARS /* f-op1 f-op2 f-imm8 */
  EXTRACT_IFMT_MOVWIMM8_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = ADDCHI (GET_H_GR (GET_H_RPSW ()), f_imm8, 0);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (ADDOFHI (GET_H_GR (GET_H_RPSW ()), f_imm8, 0), 4), SLLHI (ADDCFHI (GET_H_GR (GET_H_RPSW ()), f_imm8, 0), 2)), ORHI (ANDHI (SRLHI (ADDCHI (ANDHI (GET_H_GR (GET_H_RPSW ()), 15), ANDSI (f_imm8, 15), 0), 1), 8), SLLSI (GET_H_RPSW (), 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (GET_H_RPSW (), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* addgrimm16: add $Rd,#$imm16 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,addgrimm16) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVWGRIMM16_VARS /* f-op1 f-op2 f-op3 f-Rd f-imm16 */
  EXTRACT_IFMT_MOVWGRIMM16_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = ADDCSI (GET_H_GR (f_Rd), f_imm16, 0);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (ADDOFHI (GET_H_GR (f_Rd), f_imm16, 0), 4), SLLHI (ADDCFHI (GET_H_GR (f_Rd), f_imm16, 0), 2)), ORHI (ANDHI (SRLHI (ADDCHI (ANDSI (GET_H_GR (f_Rd), 15), ANDSI (f_imm16, 15), 0), 1), 8), SLLSI (f_Rd, 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* adcgrgr: adc $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,adcgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = ADDCSI (GET_H_GR (f_Rd), GET_H_GR (f_Rs), GET_H_CY ());
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (ADDOFHI (GET_H_GR (f_Rd), GET_H_GR (f_Rs), GET_H_CY ()), 4), SLLHI (ADDCFHI (GET_H_GR (f_Rd), GET_H_GR (f_Rs), GET_H_CY ()), 2)), ORHI (ANDHI (SRLHI (ADDCHI (ANDSI (GET_H_GR (f_Rd), 15), ANDSI (GET_H_GR (f_Rs), 15), GET_H_CY ()), 1), 8), SLLSI (f_Rd, 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* adcgrimm4: adc $Rd,#$imm4 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,adcgrimm4) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_ADDGRIMM4_VARS /* f-op1 f-op2 f-imm4 f-Rd */
  EXTRACT_IFMT_ADDGRIMM4_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = ADDCSI (GET_H_GR (f_Rd), f_imm4, GET_H_CY ());
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (ADDOFHI (GET_H_GR (f_Rd), f_imm4, GET_H_CY ()), 4), SLLHI (ADDCFHI (GET_H_GR (f_Rd), f_imm4, GET_H_CY ()), 2)), ORHI (ANDHI (SRLHI (ADDCHI (ANDSI (GET_H_GR (f_Rd), 15), ANDSI (f_imm4, 15), GET_H_CY ()), 1), 8), SLLSI (f_Rd, 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* adcimm8: adc Rx,#$imm8 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,adcimm8) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVWIMM8_VARS /* f-op1 f-op2 f-imm8 */
  EXTRACT_IFMT_MOVWIMM8_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = ADDCHI (GET_H_GR (GET_H_RPSW ()), f_imm8, GET_H_CY ());
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (ADDOFHI (GET_H_GR (GET_H_RPSW ()), f_imm8, GET_H_CY ()), 4), SLLHI (ADDCFHI (GET_H_GR (GET_H_RPSW ()), f_imm8, GET_H_CY ()), 2)), ORHI (ANDHI (SRLHI (ADDCHI (ANDHI (GET_H_GR (GET_H_RPSW ()), 15), ANDSI (f_imm8, 15), GET_H_CY ()), 1), 8), SLLSI (GET_H_RPSW (), 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (GET_H_RPSW (), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* adcgrimm16: adc $Rd,#$imm16 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,adcgrimm16) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVWGRIMM16_VARS /* f-op1 f-op2 f-op3 f-Rd f-imm16 */
  EXTRACT_IFMT_MOVWGRIMM16_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = ADDCSI (GET_H_GR (f_Rd), f_imm16, GET_H_CY ());
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (ADDOFHI (GET_H_GR (f_Rd), f_imm16, GET_H_CY ()), 4), SLLHI (ADDCFHI (GET_H_GR (f_Rd), f_imm16, GET_H_CY ()), 2)), ORHI (ANDHI (SRLHI (ADDCHI (ANDSI (GET_H_GR (f_Rd), 15), ANDSI (f_imm16, 15), GET_H_CY ()), 1), 8), SLLSI (f_Rd, 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* subgrgr: sub $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,subgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = SUBCSI (GET_H_GR (f_Rd), GET_H_GR (f_Rs), 0);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (SUBOFHI (GET_H_GR (f_Rd), GET_H_GR (f_Rs), 0), 4), SLLHI (SUBCFHI (GET_H_GR (f_Rd), GET_H_GR (f_Rs), 0), 2)), ORHI (ANDHI (SRLHI (SUBCHI (ANDSI (GET_H_GR (f_Rd), 15), ANDSI (GET_H_GR (f_Rs), 15), 0), 1), 8), SLLSI (f_Rd, 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* subgrimm4: sub $Rd,#$imm4 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,subgrimm4) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_ADDGRIMM4_VARS /* f-op1 f-op2 f-imm4 f-Rd */
  EXTRACT_IFMT_ADDGRIMM4_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = SUBCSI (GET_H_GR (f_Rd), f_imm4, 0);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (SUBOFHI (GET_H_GR (f_Rd), f_imm4, 0), 4), SLLHI (SUBCFHI (GET_H_GR (f_Rd), f_imm4, 0), 2)), ORHI (ANDHI (SRLHI (SUBCHI (ANDSI (GET_H_GR (f_Rd), 15), ANDSI (f_imm4, 15), 0), 1), 8), SLLSI (f_Rd, 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* subimm8: sub Rx,#$imm8 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,subimm8) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVWIMM8_VARS /* f-op1 f-op2 f-imm8 */
  EXTRACT_IFMT_MOVWIMM8_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = SUBCHI (GET_H_GR (GET_H_RPSW ()), f_imm8, 0);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (SUBOFHI (GET_H_GR (GET_H_RPSW ()), f_imm8, 0), 4), SLLHI (SUBCFHI (GET_H_GR (GET_H_RPSW ()), f_imm8, 0), 2)), ORHI (ANDHI (SRLHI (SUBCHI (ANDHI (GET_H_GR (GET_H_RPSW ()), 15), ANDSI (f_imm8, 15), 0), 1), 8), SLLSI (GET_H_RPSW (), 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (GET_H_RPSW (), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* subgrimm16: sub $Rd,#$imm16 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,subgrimm16) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVWGRIMM16_VARS /* f-op1 f-op2 f-op3 f-Rd f-imm16 */
  EXTRACT_IFMT_MOVWGRIMM16_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = SUBCSI (GET_H_GR (f_Rd), f_imm16, 0);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (SUBOFHI (GET_H_GR (f_Rd), f_imm16, 0), 4), SLLHI (SUBCFHI (GET_H_GR (f_Rd), f_imm16, 0), 2)), ORHI (ANDHI (SRLHI (SUBCHI (ANDSI (GET_H_GR (f_Rd), 15), ANDSI (f_imm16, 15), 0), 1), 8), SLLSI (f_Rd, 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* sbcgrgr: sbc $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,sbcgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = SUBCSI (GET_H_GR (f_Rd), GET_H_GR (f_Rs), GET_H_CY ());
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (SUBOFHI (GET_H_GR (f_Rd), GET_H_GR (f_Rs), GET_H_CY ()), 4), SLLHI (SUBCFHI (GET_H_GR (f_Rd), GET_H_GR (f_Rs), GET_H_CY ()), 2)), ORHI (ANDHI (SRLHI (SUBCHI (ANDSI (GET_H_GR (f_Rd), 15), ANDSI (GET_H_GR (f_Rs), 15), GET_H_CY ()), 1), 8), SLLSI (f_Rd, 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* sbcgrimm4: sbc $Rd,#$imm4 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,sbcgrimm4) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_ADDGRIMM4_VARS /* f-op1 f-op2 f-imm4 f-Rd */
  EXTRACT_IFMT_ADDGRIMM4_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = SUBCSI (GET_H_GR (f_Rd), f_imm4, GET_H_CY ());
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (SUBOFHI (GET_H_GR (f_Rd), f_imm4, GET_H_CY ()), 4), SLLHI (SUBCFHI (GET_H_GR (f_Rd), f_imm4, GET_H_CY ()), 2)), ORHI (ANDHI (SRLHI (SUBCHI (ANDSI (GET_H_GR (f_Rd), 15), ANDSI (f_imm4, 15), GET_H_CY ()), 1), 8), SLLSI (f_Rd, 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* sbcgrimm8: sbc Rx,#$imm8 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,sbcgrimm8) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVWIMM8_VARS /* f-op1 f-op2 f-imm8 */
  EXTRACT_IFMT_MOVWIMM8_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = SUBCHI (GET_H_GR (GET_H_RPSW ()), f_imm8, GET_H_CY ());
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (SUBOFHI (GET_H_GR (GET_H_RPSW ()), f_imm8, GET_H_CY ()), 4), SLLHI (SUBCFHI (GET_H_GR (GET_H_RPSW ()), f_imm8, GET_H_CY ()), 2)), ORHI (ANDHI (SRLHI (SUBCHI (ANDHI (GET_H_GR (GET_H_RPSW ()), 15), ANDSI (f_imm8, 15), GET_H_CY ()), 1), 8), SLLSI (GET_H_RPSW (), 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (GET_H_RPSW (), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* sbcgrimm16: sbc $Rd,#$imm16 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,sbcgrimm16) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_MOVWGRIMM16_VARS /* f-op1 f-op2 f-op3 f-Rd f-imm16 */
  EXTRACT_IFMT_MOVWGRIMM16_CODE

{
  HI tmp_value;
  HI tmp_newpsw;
  tmp_value = SUBCSI (GET_H_GR (f_Rd), f_imm16, GET_H_CY ());
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (SUBOFHI (GET_H_GR (f_Rd), f_imm16, GET_H_CY ()), 4), SLLHI (SUBCFHI (GET_H_GR (f_Rd), f_imm16, GET_H_CY ()), 2)), ORHI (ANDHI (SRLHI (SUBCHI (ANDSI (GET_H_GR (f_Rd), 15), ANDSI (f_imm16, 15), GET_H_CY ()), 1), 8), SLLSI (f_Rd, 12))));
  {
    HI opval = tmp_value;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* incgrimm2: inc $Rd,#$imm2 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,incgrimm2) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_INCGRIMM2_VARS /* f-op1 f-op2 f-op3a f-imm2 f-Rd */
  EXTRACT_IFMT_INCGRIMM2_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ADDSI (GET_H_GR (f_Rd), ADDSI (f_imm2, 1));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* decgrimm2: dec $Rd,#$imm2 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,decgrimm2) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_INCGRIMM2_VARS /* f-op1 f-op2 f-op3a f-imm2 f-Rd */
  EXTRACT_IFMT_INCGRIMM2_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = SUBSI (GET_H_GR (f_Rd), ADDSI (f_imm2, 1));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* rrcgrgr: rrc $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,rrcgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  SI tmp_tmpfoo;
  tmp_tmpfoo = ORSI (ORSI (ANDSI (SLLSI (GET_H_GR (f_Rd), 17), 0xfffe0000), GET_H_GR (f_Rd)), SLLSI (GET_H_CY (), 16));
  tmp_tmpfoo = RORSI (tmp_tmpfoo, ANDSI (GET_H_GR (f_Rs), 15));
{
  HI tmp_nvalue;
  HI tmp_newpsw;
  tmp_nvalue = TRUNCSIHI (tmp_tmpfoo);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3992), SLLSI (ANDSI (ANDSI (SRLSI (tmp_tmpfoo, 16), 1), 1), 2)), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* rrcgrimm4: rrc $Rd,#$imm4 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,rrcgrimm4) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_ADDGRIMM4_VARS /* f-op1 f-op2 f-imm4 f-Rd */
  EXTRACT_IFMT_ADDGRIMM4_CODE

{
  SI tmp_tmpfoo;
  tmp_tmpfoo = ORSI (ORSI (ANDSI (SLLSI (GET_H_GR (f_Rd), 17), 0xfffe0000), GET_H_GR (f_Rd)), SLLSI (GET_H_CY (), 16));
  tmp_tmpfoo = RORSI (tmp_tmpfoo, ANDSI (f_imm4, 15));
{
  HI tmp_nvalue;
  HI tmp_newpsw;
  tmp_nvalue = TRUNCSIHI (tmp_tmpfoo);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3992), SLLSI (ANDSI (ANDSI (SRLSI (tmp_tmpfoo, 16), 1), 1), 2)), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* rlcgrgr: rlc $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,rlcgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  SI tmp_tmpfoo;
  tmp_tmpfoo = ORSI (ORSI (ANDSI (SLLSI (GET_H_GR (f_Rd), 15), 2147352576), GET_H_GR (f_Rd)), ORSI (SLLSI (GET_H_CY (), 31), SLLSI (GET_H_CY (), 16)));
  tmp_tmpfoo = ROLSI (tmp_tmpfoo, ANDSI (ANDSI (GET_H_GR (f_Rs), 15), 31));
{
  HI tmp_nvalue;
  HI tmp_newpsw;
  tmp_nvalue = TRUNCSIHI (tmp_tmpfoo);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3992), SLLSI (ANDSI (ANDSI (SRLSI (tmp_tmpfoo, 16), 1), 1), 2)), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* rlcgrimm4: rlc $Rd,#$imm4 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,rlcgrimm4) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_ADDGRIMM4_VARS /* f-op1 f-op2 f-imm4 f-Rd */
  EXTRACT_IFMT_ADDGRIMM4_CODE

{
  SI tmp_tmpfoo;
  tmp_tmpfoo = ORSI (ORSI (ANDSI (SLLSI (GET_H_GR (f_Rd), 15), 2147352576), GET_H_GR (f_Rd)), ORSI (SLLSI (GET_H_CY (), 31), SLLSI (GET_H_CY (), 16)));
  tmp_tmpfoo = ROLSI (tmp_tmpfoo, ANDSI (f_imm4, 31));
{
  HI tmp_nvalue;
  HI tmp_newpsw;
  tmp_nvalue = TRUNCSIHI (tmp_tmpfoo);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3992), SLLSI (ANDSI (ANDSI (SRLSI (tmp_tmpfoo, 16), 1), 1), 2)), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* shrgrgr: shr $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,shrgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_nvalue;
  HI tmp_newpsw;
  tmp_nvalue = SRLSI (GET_H_GR (f_Rd), ANDSI (GET_H_GR (f_Rs), 15));
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3992), SLLSI (ANDSI (ANDSI (((EQSI (ANDSI (GET_H_GR (f_Rs), 15), 0)) ? (GET_H_CY ()) : (SRLSI (GET_H_GR (f_Rd), SUBSI (ANDSI (GET_H_GR (f_Rs), 15), 1)))), 1), 1), 2)), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* shrgrimm: shr $Rd,#$imm4 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,shrgrimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_ADDGRIMM4_VARS /* f-op1 f-op2 f-imm4 f-Rd */
  EXTRACT_IFMT_ADDGRIMM4_CODE

{
  HI tmp_nvalue;
  HI tmp_newpsw;
  tmp_nvalue = SRLSI (GET_H_GR (f_Rd), f_imm4);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3992), SLLSI (ANDSI (ANDSI (((EQSI (f_imm4, 0)) ? (GET_H_CY ()) : (SRLSI (GET_H_GR (f_Rd), SUBSI (f_imm4, 1)))), 1), 1), 2)), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* shlgrgr: shl $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,shlgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_nvalue;
  HI tmp_newpsw;
  tmp_nvalue = SLLSI (GET_H_GR (f_Rd), ANDSI (GET_H_GR (f_Rs), 15));
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3992), SLLSI (ANDSI (SRLSI (((EQSI (ANDSI (GET_H_GR (f_Rs), 15), 0)) ? (SLLSI (GET_H_CY (), 15)) : (SLLSI (GET_H_GR (f_Rd), SUBSI (ANDSI (GET_H_GR (f_Rs), 15), 1)))), 15), 1), 2)), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* shlgrimm: shl $Rd,#$imm4 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,shlgrimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_ADDGRIMM4_VARS /* f-op1 f-op2 f-imm4 f-Rd */
  EXTRACT_IFMT_ADDGRIMM4_CODE

{
  HI tmp_nvalue;
  HI tmp_newpsw;
  tmp_nvalue = SLLSI (GET_H_GR (f_Rd), f_imm4);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3992), SLLSI (ANDSI (SRLSI (((EQSI (f_imm4, 0)) ? (SLLSI (GET_H_CY (), 15)) : (SLLSI (GET_H_GR (f_Rd), SUBSI (f_imm4, 1)))), 15), 1), 2)), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* asrgrgr: asr $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,asrgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_nvalue;
  HI tmp_newpsw;
  tmp_nvalue = SRAHI (GET_H_GR (f_Rd), ANDSI (GET_H_GR (f_Rs), 15));
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3992), SLLSI (ANDSI (ANDSI (((EQSI (ANDSI (GET_H_GR (f_Rs), 15), 0)) ? (GET_H_CY ()) : (SRLSI (GET_H_GR (f_Rd), SUBSI (ANDSI (GET_H_GR (f_Rs), 15), 1)))), 1), 1), 2)), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* asrgrimm: asr $Rd,#$imm4 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,asrgrimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_ADDGRIMM4_VARS /* f-op1 f-op2 f-imm4 f-Rd */
  EXTRACT_IFMT_ADDGRIMM4_CODE

{
  HI tmp_nvalue;
  HI tmp_newpsw;
  tmp_nvalue = SRAHI (GET_H_GR (f_Rd), f_imm4);
  tmp_newpsw = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3992), SLLSI (ANDSI (ANDSI (((EQSI (f_imm4, 0)) ? (GET_H_CY ()) : (SRLSI (GET_H_GR (f_Rd), SUBSI (f_imm4, 1)))), 1), 1), 2)), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_newpsw;
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* set1grimm: set1 $Rd,#$imm4 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,set1grimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_ADDGRIMM4_VARS /* f-op1 f-op2 f-imm4 f-Rd */
  EXTRACT_IFMT_ADDGRIMM4_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ORSI (GET_H_GR (f_Rd), SLLSI (1, f_imm4));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* set1grgr: set1 $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,set1grgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ORSI (GET_H_GR (f_Rd), SLLSI (1, ANDSI (GET_H_GR (f_Rs), 15)));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* set1lmemimm: set1 $lmem8,#$imm3 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,set1lmemimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_SET1LMEMIMM_VARS /* f-op1 f-imm3 f-op2m f-lmem8 */
  EXTRACT_IFMT_SET1LMEMIMM_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ORQI (GETMEMQI (current_cpu, pc, f_lmem8), SLLSI (1, f_imm3));
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (0, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    QI opval = tmp_nvalue;
    SETMEMQI (current_cpu, pc, f_lmem8, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* set1hmemimm: set1 $hmem8,#$imm3 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,set1hmemimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_SET1HMEMIMM_VARS /* f-op1 f-imm3 f-op2m f-hmem8 */
  EXTRACT_IFMT_SET1HMEMIMM_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ORQI (GETMEMQI (current_cpu, pc, f_hmem8), SLLSI (1, f_imm3));
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (0, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    QI opval = tmp_nvalue;
    SETMEMQI (current_cpu, pc, f_hmem8, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* clr1grimm: clr1 $Rd,#$imm4 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,clr1grimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_ADDGRIMM4_VARS /* f-op1 f-op2 f-imm4 f-Rd */
  EXTRACT_IFMT_ADDGRIMM4_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (GET_H_GR (f_Rd), INVSI (SLLSI (1, f_imm4)));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* clr1grgr: clr1 $Rd,$Rs */

static SEM_STATUS
SEM_FN_NAME (xstormy16,clr1grgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd */
  EXTRACT_IFMT_MOVGRGR_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ANDSI (GET_H_GR (f_Rd), INVSI (SLLSI (1, ANDSI (GET_H_GR (f_Rs), 15))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* clr1lmemimm: clr1 $lmem8,#$imm3 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,clr1lmemimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_SET1LMEMIMM_VARS /* f-op1 f-imm3 f-op2m f-lmem8 */
  EXTRACT_IFMT_SET1LMEMIMM_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ANDQI (GETMEMQI (current_cpu, pc, f_lmem8), INVSI (SLLSI (1, f_imm3)));
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (0, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    QI opval = tmp_nvalue;
    SETMEMQI (current_cpu, pc, f_lmem8, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* clr1hmemimm: clr1 $hmem8,#$imm3 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,clr1hmemimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_SET1HMEMIMM_VARS /* f-op1 f-imm3 f-op2m f-hmem8 */
  EXTRACT_IFMT_SET1HMEMIMM_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ANDQI (GETMEMQI (current_cpu, pc, f_hmem8), INVSI (SLLSI (1, f_imm3)));
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (0, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    QI opval = tmp_nvalue;
    SETMEMQI (current_cpu, pc, f_hmem8, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* cbwgr: cbw $Rd */

static SEM_STATUS
SEM_FN_NAME (xstormy16,cbwgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVLOWGR_VARS /* f-op1 f-op2 f-op3 f-Rd */
  EXTRACT_IFMT_MOVLOWGR_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = EXTQIHI (TRUNCSIQI (GET_H_GR (f_Rd)));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* revgr: rev $Rd */

static SEM_STATUS
SEM_FN_NAME (xstormy16,revgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVLOWGR_VARS /* f-op1 f-op2 f-op3 f-Rd */
  EXTRACT_IFMT_MOVLOWGR_CODE

{
  HI tmp_nvalue;
  tmp_nvalue = ORSI (SLLSI (ANDSI (GET_H_GR (f_Rd), 1), 15), ORSI (SLLSI (ANDSI (GET_H_GR (f_Rd), 2), 13), ORSI (SLLSI (ANDSI (GET_H_GR (f_Rd), 4), 11), ORSI (SLLSI (ANDSI (GET_H_GR (f_Rd), 8), 9), ORSI (SLLSI (ANDSI (GET_H_GR (f_Rd), 16), 7), ORSI (SLLSI (ANDSI (GET_H_GR (f_Rd), 32), 5), ORSI (SLLSI (ANDSI (GET_H_GR (f_Rd), 64), 3), ORSI (SLLSI (ANDSI (GET_H_GR (f_Rd), 128), 1), ORSI (SRLSI (ANDSI (GET_H_GR (f_Rd), 256), 1), ORSI (SRLSI (ANDSI (GET_H_GR (f_Rd), 512), 3), ORSI (SRLSI (ANDSI (GET_H_GR (f_Rd), 1024), 5), ORSI (SRLSI (ANDSI (GET_H_GR (f_Rd), 2048), 7), ORSI (SRLSI (ANDSI (GET_H_GR (f_Rd), 4096), 9), ORSI (SRLSI (ANDSI (GET_H_GR (f_Rd), 8192), 11), ORSI (SRLSI (ANDSI (GET_H_GR (f_Rd), 16384), 13), SRLSI (ANDSI (GET_H_GR (f_Rd), 32768), 15))))))))))))))));
  {
    HI opval = tmp_nvalue;
    SET_H_GR (f_Rd, opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3996), ORSI (SLLSI (f_Rd, 12), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6)))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* bccgrgr: b$bcond5 $Rd,$Rs,$rel12 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,bccgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_BCCGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd f-op5 f-rel12 */
  EXTRACT_IFMT_BCCGRGR_CODE

{
{
  HI tmp_value;
  tmp_value = SUBSI (GET_H_GR (f_Rd), GET_H_GR (f_Rs));
  {
    SI opval = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (SUBOFHI (GET_H_GR (f_Rd), GET_H_GR (f_Rs), 0), 4), SLLHI (SUBCFHI (GET_H_GR (f_Rd), GET_H_GR (f_Rs), 0), 2)), ORHI (ANDHI (SRLHI (SUBHI (ANDSI (GET_H_GR (f_Rd), 15), ANDSI (GET_H_GR (f_Rs), 15)), 1), 8), SLLSI (f_Rd, 12))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
{
  BI tmp_tmp;
  switch (f_op5)
  {
  case 0 : {
  tmp_tmp = NOTSI (XORSI (GET_H_S (), GET_H_OV ()));
}
    break;
  case 1 : {
  tmp_tmp = NOTSI (GET_H_CY ());
}
    break;
  case 2 : {
  tmp_tmp = XORSI (GET_H_S (), GET_H_OV ());
}
    break;
  case 3 : {
  tmp_tmp = GET_H_CY ();
}
    break;
  case 4 : {
  tmp_tmp = NOTSI (ORSI (XORSI (GET_H_S (), GET_H_OV ()), GET_H_Z16 ()));
}
    break;
  case 5 : {
  tmp_tmp = NOTSI (ORSI (GET_H_CY (), GET_H_Z16 ()));
}
    break;
  case 6 : {
  tmp_tmp = ORSI (XORSI (GET_H_S (), GET_H_OV ()), GET_H_Z16 ());
}
    break;
  case 7 : {
  tmp_tmp = ORSI (GET_H_CY (), GET_H_Z16 ());
}
    break;
  case 8 : {
  tmp_tmp = NOTSI (GET_H_S ());
}
    break;
  case 9 : {
  tmp_tmp = NOTSI (GET_H_OV ());
}
    break;
  case 10 : {
  tmp_tmp = GET_H_S ();
}
    break;
  case 11 : {
  tmp_tmp = GET_H_OV ();
}
    break;
  case 12 : {
  tmp_tmp = NOTSI (GET_H_Z8 ());
}
    break;
  case 13 : {
  tmp_tmp = NOTSI (GET_H_Z16 ());
}
    break;
  case 14 : {
  tmp_tmp = GET_H_Z8 ();
}
    break;
  case 15 : {
  tmp_tmp = GET_H_Z16 ();
}
    break;
  }
if (tmp_tmp) {
  {
    USI opval = f_rel12;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_COND_CTI));
#undef FLD
  return status;
}

/* bccgrimm8: b$bcond5 $Rm,#$imm8,$rel12 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,bccgrimm8) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_BCCGRIMM8_VARS /* f-op1 f-Rm f-op2m f-imm8 f-op5 f-rel12 */
  EXTRACT_IFMT_BCCGRIMM8_CODE

{
{
  HI tmp_value;
  tmp_value = SUBSI (GET_H_GR (f_Rm), f_imm8);
  {
    SI opval = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (SUBOFHI (GET_H_GR (f_Rm), f_imm8, 0), 4), SLLHI (SUBCFHI (GET_H_GR (f_Rm), f_imm8, 0), 2)), ORHI (ANDHI (SRLHI (SUBHI (ANDSI (GET_H_GR (f_Rm), 15), ANDSI (f_imm8, 15)), 1), 8), SLLSI (f_Rm, 12))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
{
  BI tmp_tmp;
  switch (f_op5)
  {
  case 0 : {
  tmp_tmp = NOTSI (XORSI (GET_H_S (), GET_H_OV ()));
}
    break;
  case 1 : {
  tmp_tmp = NOTSI (GET_H_CY ());
}
    break;
  case 2 : {
  tmp_tmp = XORSI (GET_H_S (), GET_H_OV ());
}
    break;
  case 3 : {
  tmp_tmp = GET_H_CY ();
}
    break;
  case 4 : {
  tmp_tmp = NOTSI (ORSI (XORSI (GET_H_S (), GET_H_OV ()), GET_H_Z16 ()));
}
    break;
  case 5 : {
  tmp_tmp = NOTSI (ORSI (GET_H_CY (), GET_H_Z16 ()));
}
    break;
  case 6 : {
  tmp_tmp = ORSI (XORSI (GET_H_S (), GET_H_OV ()), GET_H_Z16 ());
}
    break;
  case 7 : {
  tmp_tmp = ORSI (GET_H_CY (), GET_H_Z16 ());
}
    break;
  case 8 : {
  tmp_tmp = NOTSI (GET_H_S ());
}
    break;
  case 9 : {
  tmp_tmp = NOTSI (GET_H_OV ());
}
    break;
  case 10 : {
  tmp_tmp = GET_H_S ();
}
    break;
  case 11 : {
  tmp_tmp = GET_H_OV ();
}
    break;
  case 12 : {
  tmp_tmp = NOTSI (GET_H_Z8 ());
}
    break;
  case 13 : {
  tmp_tmp = NOTSI (GET_H_Z16 ());
}
    break;
  case 14 : {
  tmp_tmp = GET_H_Z8 ();
}
    break;
  case 15 : {
  tmp_tmp = GET_H_Z16 ();
}
    break;
  }
if (tmp_tmp) {
  {
    USI opval = f_rel12;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_COND_CTI));
#undef FLD
  return status;
}

/* bccimm16: b$bcond2 Rx,#$imm16,${rel8-4} */

static SEM_STATUS
SEM_FN_NAME (xstormy16,bccimm16) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_BCCIMM16_VARS /* f-op1 f-op2 f-rel8-4 f-imm16 */
  EXTRACT_IFMT_BCCIMM16_CODE

{
{
  HI tmp_value;
  tmp_value = SUBHI (GET_H_GR (GET_H_RPSW ()), f_imm16);
  {
    SI opval = ORSI (ORSI (ANDSI (GET_H_GR (((UINT) 14)), 3968), ORBI (ORBI (EQHI (ANDHI (tmp_value, 255), 0), SLLHI (EQHI (tmp_value, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_value), 5), SLLHI (LTQI (SRLHI (tmp_value, MULSI (1, 8)), 0), 6)))), ORHI (ORHI (SLLHI (SUBOFHI (GET_H_GR (GET_H_RPSW ()), f_imm16, 0), 4), SLLHI (SUBCFHI (GET_H_GR (GET_H_RPSW ()), f_imm16, 0), 2)), ORHI (ANDHI (SRLHI (SUBHI (ANDHI (GET_H_GR (GET_H_RPSW ()), 15), ANDSI (f_imm16, 15)), 1), 8), SLLSI (GET_H_RPSW (), 12))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
{
  BI tmp_tmp;
  switch (f_op2)
  {
  case 0 : {
  tmp_tmp = NOTSI (XORSI (GET_H_S (), GET_H_OV ()));
}
    break;
  case 1 : {
  tmp_tmp = NOTSI (GET_H_CY ());
}
    break;
  case 2 : {
  tmp_tmp = XORSI (GET_H_S (), GET_H_OV ());
}
    break;
  case 3 : {
  tmp_tmp = GET_H_CY ();
}
    break;
  case 4 : {
  tmp_tmp = NOTSI (ORSI (XORSI (GET_H_S (), GET_H_OV ()), GET_H_Z16 ()));
}
    break;
  case 5 : {
  tmp_tmp = NOTSI (ORSI (GET_H_CY (), GET_H_Z16 ()));
}
    break;
  case 6 : {
  tmp_tmp = ORSI (XORSI (GET_H_S (), GET_H_OV ()), GET_H_Z16 ());
}
    break;
  case 7 : {
  tmp_tmp = ORSI (GET_H_CY (), GET_H_Z16 ());
}
    break;
  case 8 : {
  tmp_tmp = NOTSI (GET_H_S ());
}
    break;
  case 9 : {
  tmp_tmp = NOTSI (GET_H_OV ());
}
    break;
  case 10 : {
  tmp_tmp = GET_H_S ();
}
    break;
  case 11 : {
  tmp_tmp = GET_H_OV ();
}
    break;
  case 12 : {
  tmp_tmp = NOTSI (GET_H_Z8 ());
}
    break;
  case 13 : {
  tmp_tmp = NOTSI (GET_H_Z16 ());
}
    break;
  case 14 : {
  tmp_tmp = GET_H_Z8 ();
}
    break;
  case 15 : {
  tmp_tmp = GET_H_Z16 ();
}
    break;
  }
if (tmp_tmp) {
  {
    USI opval = f_rel8_4;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 11);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_COND_CTI));
#undef FLD
  return status;
}

/* bngrimm4: bn $Rd,#$imm4,$rel12 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,bngrimm4) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_BNGRIMM4_VARS /* f-op1 f-op2 f-imm4 f-Rd f-op5 f-rel12 */
  EXTRACT_IFMT_BNGRIMM4_CODE

{
  {
    SI opval = f_Rd;
    SET_H_RPSW (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "Rpsw", 'x', opval);
  }
if (EQSI (ANDSI (GET_H_GR (f_Rd), SLLSI (1, f_imm4)), 0)) {
  {
    USI opval = f_rel12;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_COND_CTI));
#undef FLD
  return status;
}

/* bngrgr: bn $Rd,$Rs,$rel12 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,bngrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_BNGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd f-op5 f-rel12 */
  EXTRACT_IFMT_BNGRGR_CODE

{
  {
    SI opval = f_Rd;
    SET_H_RPSW (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "Rpsw", 'x', opval);
  }
if (EQSI (ANDSI (GET_H_GR (f_Rd), SLLSI (1, GET_H_GR (f_Rs))), 0)) {
  {
    USI opval = f_rel12;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_COND_CTI));
#undef FLD
  return status;
}

/* bnlmemimm: bn $lmem8,#$imm3b,$rel12 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,bnlmemimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_BNLMEMIMM_VARS /* f-op1 f-op2 f-lmem8 f-op5a f-imm3b f-rel12 */
  EXTRACT_IFMT_BNLMEMIMM_CODE

if (EQQI (ANDQI (GETMEMQI (current_cpu, pc, f_lmem8), SLLSI (1, f_imm3b)), 0)) {
  {
    USI opval = f_rel12;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_COND_CTI));
#undef FLD
  return status;
}

/* bnhmemimm: bn $hmem8,#$imm3b,$rel12 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,bnhmemimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_BNHMEMIMM_VARS /* f-op1 f-op2 f-hmem8 f-op5a f-imm3b f-rel12 */
  EXTRACT_IFMT_BNHMEMIMM_CODE

if (EQQI (ANDQI (GETMEMQI (current_cpu, pc, f_hmem8), SLLSI (1, f_imm3b)), 0)) {
  {
    USI opval = f_rel12;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_COND_CTI));
#undef FLD
  return status;
}

/* bpgrimm4: bp $Rd,#$imm4,$rel12 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,bpgrimm4) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_BNGRIMM4_VARS /* f-op1 f-op2 f-imm4 f-Rd f-op5 f-rel12 */
  EXTRACT_IFMT_BNGRIMM4_CODE

{
  {
    SI opval = f_Rd;
    SET_H_RPSW (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "Rpsw", 'x', opval);
  }
if (NESI (ANDSI (GET_H_GR (f_Rd), SLLSI (1, f_imm4)), 0)) {
  {
    USI opval = f_rel12;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_COND_CTI));
#undef FLD
  return status;
}

/* bpgrgr: bp $Rd,$Rs,$rel12 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,bpgrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_BNGRGR_VARS /* f-op1 f-op2 f-Rs f-Rd f-op5 f-rel12 */
  EXTRACT_IFMT_BNGRGR_CODE

{
  {
    SI opval = f_Rd;
    SET_H_RPSW (opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "Rpsw", 'x', opval);
  }
if (NESI (ANDSI (GET_H_GR (f_Rd), SLLSI (1, GET_H_GR (f_Rs))), 0)) {
  {
    USI opval = f_rel12;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 5);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_COND_CTI));
#undef FLD
  return status;
}

/* bplmemimm: bp $lmem8,#$imm3b,$rel12 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,bplmemimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_BNLMEMIMM_VARS /* f-op1 f-op2 f-lmem8 f-op5a f-imm3b f-rel12 */
  EXTRACT_IFMT_BNLMEMIMM_CODE

if (NEQI (ANDQI (GETMEMQI (current_cpu, pc, f_lmem8), SLLSI (1, f_imm3b)), 0)) {
  {
    USI opval = f_rel12;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_COND_CTI));
#undef FLD
  return status;
}

/* bphmemimm: bp $hmem8,#$imm3b,$rel12 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,bphmemimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_BNHMEMIMM_VARS /* f-op1 f-op2 f-hmem8 f-op5a f-imm3b f-rel12 */
  EXTRACT_IFMT_BNHMEMIMM_CODE

if (NEQI (ANDQI (GETMEMQI (current_cpu, pc, f_hmem8), SLLSI (1, f_imm3b)), 0)) {
  {
    USI opval = f_rel12;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 4);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_COND_CTI));
#undef FLD
  return status;
}

/* bcc: b$bcond2 ${rel8-2} */

static SEM_STATUS
SEM_FN_NAME (xstormy16,bcc) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_BCC_VARS /* f-op1 f-op2 f-rel8-2 */
  EXTRACT_IFMT_BCC_CODE

{
  BI tmp_tmp;
  switch (f_op2)
  {
  case 0 : {
  tmp_tmp = NOTSI (XORSI (GET_H_S (), GET_H_OV ()));
}
    break;
  case 1 : {
  tmp_tmp = NOTSI (GET_H_CY ());
}
    break;
  case 2 : {
  tmp_tmp = XORSI (GET_H_S (), GET_H_OV ());
}
    break;
  case 3 : {
  tmp_tmp = GET_H_CY ();
}
    break;
  case 4 : {
  tmp_tmp = NOTSI (ORSI (XORSI (GET_H_S (), GET_H_OV ()), GET_H_Z16 ()));
}
    break;
  case 5 : {
  tmp_tmp = NOTSI (ORSI (GET_H_CY (), GET_H_Z16 ()));
}
    break;
  case 6 : {
  tmp_tmp = ORSI (XORSI (GET_H_S (), GET_H_OV ()), GET_H_Z16 ());
}
    break;
  case 7 : {
  tmp_tmp = ORSI (GET_H_CY (), GET_H_Z16 ());
}
    break;
  case 8 : {
  tmp_tmp = NOTSI (GET_H_S ());
}
    break;
  case 9 : {
  tmp_tmp = NOTSI (GET_H_OV ());
}
    break;
  case 10 : {
  tmp_tmp = GET_H_S ();
}
    break;
  case 11 : {
  tmp_tmp = GET_H_OV ();
}
    break;
  case 12 : {
  tmp_tmp = NOTSI (GET_H_Z8 ());
}
    break;
  case 13 : {
  tmp_tmp = NOTSI (GET_H_Z16 ());
}
    break;
  case 14 : {
  tmp_tmp = GET_H_Z8 ();
}
    break;
  case 15 : {
  tmp_tmp = GET_H_Z16 ();
}
    break;
  }
if (tmp_tmp) {
  {
    USI opval = f_rel8_2;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    written |= (1 << 7);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}
}

  abuf->written = written;
  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_COND_CTI));
#undef FLD
  return status;
}

/* bgr: br $Rd */

static SEM_STATUS
SEM_FN_NAME (xstormy16,bgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVLOWGR_VARS /* f-op1 f-op2 f-op3 f-Rd */
  EXTRACT_IFMT_MOVLOWGR_CODE

  {
    USI opval = ADDSI (ADDSI (pc, 2), GET_H_GR (f_Rd));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }

  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_UNCOND_CTI));
#undef FLD
  return status;
}

/* br: br $rel12a */

static SEM_STATUS
SEM_FN_NAME (xstormy16,br) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_BR_VARS /* f-op1 f-rel12a f-op4b */
  EXTRACT_IFMT_BR_CODE

  {
    USI opval = f_rel12a;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }

  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_UNCOND_CTI));
#undef FLD
  return status;
}

/* jmp: jmp $Rbj,$Rd */

static SEM_STATUS
SEM_FN_NAME (xstormy16,jmp) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_JMP_VARS /* f-op1 f-op2 f-op3b f-Rbj f-Rd */
  EXTRACT_IFMT_JMP_CODE

  {
    USI opval = JOINHISI (GET_H_RBJ (f_Rbj), GET_H_GR (f_Rd));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }

  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_UNCOND_CTI));
#undef FLD
  return status;
}

/* jmpf: jmpf $abs24 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,jmpf) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_JMPF_VARS /* f-op1 f-op2 f-abs24-1 f-abs24-2 f-abs24 */
  EXTRACT_IFMT_JMPF_CODE

  {
    USI opval = f_abs24;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }

  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_UNCOND_CTI));
#undef FLD
  return status;
}

/* callrgr: callr $Rd */

static SEM_STATUS
SEM_FN_NAME (xstormy16,callrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVLOWGR_VARS /* f-op1 f-op2 f-op3 f-Rd */
  EXTRACT_IFMT_MOVLOWGR_CODE

{
  {
    SI opval = ADDSI (pc, 2);
    SETMEMSI (current_cpu, pc, GET_H_GR (((UINT) 15)), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  {
    SI opval = ADDSI (GET_H_GR (((UINT) 15)), 4);
    SET_H_GR (((UINT) 15), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    USI opval = ADDSI (GET_H_GR (f_Rd), ADDSI (pc, 2));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_UNCOND_CTI));
#undef FLD
  return status;
}

/* callrimm: callr $rel12a */

static SEM_STATUS
SEM_FN_NAME (xstormy16,callrimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_BR_VARS /* f-op1 f-rel12a f-op4b */
  EXTRACT_IFMT_BR_CODE

{
  {
    SI opval = ADDSI (pc, 2);
    SETMEMSI (current_cpu, pc, GET_H_GR (((UINT) 15)), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  {
    SI opval = ADDSI (GET_H_GR (((UINT) 15)), 4);
    SET_H_GR (((UINT) 15), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    USI opval = f_rel12a;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_UNCOND_CTI));
#undef FLD
  return status;
}

/* callgr: call $Rbj,$Rd */

static SEM_STATUS
SEM_FN_NAME (xstormy16,callgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_JMP_VARS /* f-op1 f-op2 f-op3b f-Rbj f-Rd */
  EXTRACT_IFMT_JMP_CODE

{
  {
    SI opval = ADDSI (pc, 2);
    SETMEMSI (current_cpu, pc, GET_H_GR (((UINT) 15)), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  {
    SI opval = ADDSI (GET_H_GR (((UINT) 15)), 4);
    SET_H_GR (((UINT) 15), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    USI opval = JOINHISI (GET_H_RBJ (f_Rbj), GET_H_GR (f_Rd));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_UNCOND_CTI));
#undef FLD
  return status;
}

/* callfimm: callf $abs24 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,callfimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_JMPF_VARS /* f-op1 f-op2 f-abs24-1 f-abs24-2 f-abs24 */
  EXTRACT_IFMT_JMPF_CODE

{
  {
    SI opval = ADDSI (pc, 4);
    SETMEMSI (current_cpu, pc, GET_H_GR (((UINT) 15)), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  {
    SI opval = ADDSI (GET_H_GR (((UINT) 15)), 4);
    SET_H_GR (((UINT) 15), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    USI opval = f_abs24;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_UNCOND_CTI));
#undef FLD
  return status;
}

/* icallrgr: icallr $Rd */

static SEM_STATUS
SEM_FN_NAME (xstormy16,icallrgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_MOVLOWGR_VARS /* f-op1 f-op2 f-op3 f-Rd */
  EXTRACT_IFMT_MOVLOWGR_CODE

{
  {
    SI opval = ADDSI (pc, 2);
    SETMEMSI (current_cpu, pc, GET_H_GR (((UINT) 15)), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  {
    HI opval = GET_H_GR (((UINT) 14));
    SETMEMHI (current_cpu, pc, ADDSI (GET_H_GR (((UINT) 15)), 4), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  {
    SI opval = ADDSI (GET_H_GR (((UINT) 15)), 6);
    SET_H_GR (((UINT) 15), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    USI opval = ADDSI (GET_H_GR (f_Rd), ADDSI (pc, 2));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_UNCOND_CTI));
#undef FLD
  return status;
}

/* icallgr: icall $Rbj,$Rd */

static SEM_STATUS
SEM_FN_NAME (xstormy16,icallgr) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_JMP_VARS /* f-op1 f-op2 f-op3b f-Rbj f-Rd */
  EXTRACT_IFMT_JMP_CODE

{
  {
    SI opval = ADDSI (pc, 2);
    SETMEMSI (current_cpu, pc, GET_H_GR (((UINT) 15)), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  {
    HI opval = GET_H_GR (((UINT) 14));
    SETMEMHI (current_cpu, pc, ADDSI (GET_H_GR (((UINT) 15)), 4), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  {
    SI opval = ADDSI (GET_H_GR (((UINT) 15)), 6);
    SET_H_GR (((UINT) 15), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    USI opval = JOINHISI (GET_H_RBJ (f_Rbj), GET_H_GR (f_Rd));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_UNCOND_CTI));
#undef FLD
  return status;
}

/* icallfimm: icallf $abs24 */

static SEM_STATUS
SEM_FN_NAME (xstormy16,icallfimm) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 4);
  EXTRACT_IFMT_JMPF_VARS /* f-op1 f-op2 f-abs24-1 f-abs24-2 f-abs24 */
  EXTRACT_IFMT_JMPF_CODE

{
  {
    SI opval = ADDSI (pc, 4);
    SETMEMSI (current_cpu, pc, GET_H_GR (((UINT) 15)), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  {
    HI opval = GET_H_GR (((UINT) 14));
    SETMEMHI (current_cpu, pc, ADDSI (GET_H_GR (((UINT) 15)), 4), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "memory", 'x', opval);
  }
  {
    SI opval = ADDSI (GET_H_GR (((UINT) 15)), 6);
    SET_H_GR (((UINT) 15), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    USI opval = f_abs24;
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_UNCOND_CTI));
#undef FLD
  return status;
}

/* iret: iret */

static SEM_STATUS
SEM_FN_NAME (xstormy16,iret) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_IRET_VARS /* f-op */
  EXTRACT_IFMT_IRET_CODE

{
  {
    SI opval = SUBSI (GET_H_GR (((UINT) 15)), 6);
    SET_H_GR (((UINT) 15), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    USI opval = GETMEMSI (current_cpu, pc, GET_H_GR (((UINT) 15)));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
  {
    SI opval = GETMEMHI (current_cpu, pc, ADDSI (GET_H_GR (((UINT) 15)), 4));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_UNCOND_CTI));
#undef FLD
  return status;
}

/* ret: ret */

static SEM_STATUS
SEM_FN_NAME (xstormy16,ret) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_BRANCH_INIT
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_IRET_VARS /* f-op */
  EXTRACT_IFMT_IRET_CODE

{
  {
    SI opval = SUBSI (GET_H_GR (((UINT) 15)), 4);
    SET_H_GR (((UINT) 15), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    USI opval = GETMEMSI (current_cpu, pc, GET_H_GR (((UINT) 15)));
    SEM_BRANCH_VIA_ADDR (current_cpu, sem_arg, opval, vpc);
    CGEN_TRACE_RESULT (current_cpu, abuf, "pc", 'x', opval);
  }
}

  SEM_BRANCH_FINI (vpc, 0|(1<<CGEN_INSN_UNCOND_CTI));
#undef FLD
  return status;
}

/* mul: mul */

static SEM_STATUS
SEM_FN_NAME (xstormy16,mul) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_IRET_VARS /* f-op */
  EXTRACT_IFMT_IRET_CODE

{
  SI tmp_value;
  tmp_value = MULSI (ANDSI (GET_H_GR (((UINT) 0)), 65535), ANDSI (GET_H_GR (((UINT) 2)), 65535));
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (TRUNCSIHI (tmp_value), 255), 0), SLLHI (EQHI (TRUNCSIHI (tmp_value), 0), 1)), ORHI (SLLHI (parity (current_cpu, TRUNCSIHI (tmp_value)), 5), SLLHI (LTQI (SRLHI (TRUNCSIHI (tmp_value), MULSI (1, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = TRUNCSIHI (tmp_value);
    SET_H_GR (((UINT) 0), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = TRUNCSIHI (SRLSI (tmp_value, 16));
    SET_H_GR (((UINT) 1), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* div: div */

static SEM_STATUS
SEM_FN_NAME (xstormy16,div) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_IRET_VARS /* f-op */
  EXTRACT_IFMT_IRET_CODE

{
  {
    SI opval = UMODSI (GET_H_GR (((UINT) 0)), GET_H_GR (((UINT) 2)));
    SET_H_GR (((UINT) 1), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
{
  HI tmp_nvalue;
  tmp_nvalue = UDIVSI (GET_H_GR (((UINT) 0)), GET_H_GR (((UINT) 2)));
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_nvalue;
    SET_H_GR (((UINT) 0), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* sdiv: sdiv */

static SEM_STATUS
SEM_FN_NAME (xstormy16,sdiv) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_IRET_VARS /* f-op */
  EXTRACT_IFMT_IRET_CODE

{
  {
    SI opval = MODHI (GET_H_GR (((UINT) 0)), GET_H_GR (((UINT) 2)));
    SET_H_GR (((UINT) 1), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
{
  HI tmp_nvalue;
  tmp_nvalue = DIVHI (GET_H_GR (((UINT) 0)), GET_H_GR (((UINT) 2)));
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_nvalue;
    SET_H_GR (((UINT) 0), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* sdivlh: sdivlh */

static SEM_STATUS
SEM_FN_NAME (xstormy16,sdivlh) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_IRET_VARS /* f-op */
  EXTRACT_IFMT_IRET_CODE

{
  SI tmp_value;
  tmp_value = ADDSI (SLLSI (ANDSI (GET_H_GR (((UINT) 1)), 65535), 16), ANDSI (GET_H_GR (((UINT) 0)), 65535));
  {
    SI opval = MODSI (tmp_value, EXTHISI (TRUNCSIHI (GET_H_GR (((UINT) 2)))));
    SET_H_GR (((UINT) 1), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
{
  HI tmp_nvalue;
  tmp_nvalue = DIVSI (tmp_value, EXTHISI (TRUNCSIHI (GET_H_GR (((UINT) 2)))));
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_nvalue;
    SET_H_GR (((UINT) 0), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* divlh: divlh */

static SEM_STATUS
SEM_FN_NAME (xstormy16,divlh) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_IRET_VARS /* f-op */
  EXTRACT_IFMT_IRET_CODE

{
  SI tmp_value;
  tmp_value = ADDSI (SLLSI (ANDSI (GET_H_GR (((UINT) 1)), 65535), 16), ANDSI (GET_H_GR (((UINT) 0)), 65535));
  {
    SI opval = UMODSI (tmp_value, GET_H_GR (((UINT) 2)));
    SET_H_GR (((UINT) 1), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
{
  HI tmp_nvalue;
  tmp_nvalue = UDIVSI (tmp_value, GET_H_GR (((UINT) 2)));
  {
    SI opval = ORSI (ANDSI (GET_H_GR (((UINT) 14)), 65436), ORBI (ORBI (EQHI (ANDHI (tmp_nvalue, 255), 0), SLLHI (EQHI (tmp_nvalue, 0), 1)), ORHI (SLLHI (parity (current_cpu, tmp_nvalue), 5), SLLHI (LTQI (SRLHI (tmp_nvalue, MULSI (1, 8)), 0), 6))));
    SET_H_GR (((UINT) 14), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
  {
    SI opval = tmp_nvalue;
    SET_H_GR (((UINT) 0), opval);
    CGEN_TRACE_RESULT (current_cpu, abuf, "gr", 'x', opval);
  }
}
}

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* reset: reset */

static SEM_STATUS
SEM_FN_NAME (xstormy16,reset) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_IRET_VARS /* f-op */
  EXTRACT_IFMT_IRET_CODE

((void) 0); /*nop*/

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* nop: nop */

static SEM_STATUS
SEM_FN_NAME (xstormy16,nop) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_IRET_VARS /* f-op */
  EXTRACT_IFMT_IRET_CODE

((void) 0); /*nop*/

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* halt: halt */

static SEM_STATUS
SEM_FN_NAME (xstormy16,halt) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_IRET_VARS /* f-op */
  EXTRACT_IFMT_IRET_CODE

do_halt (current_cpu);

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* hold: hold */

static SEM_STATUS
SEM_FN_NAME (xstormy16,hold) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_IRET_VARS /* f-op */
  EXTRACT_IFMT_IRET_CODE

do_hold (current_cpu);

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* holdx: holdx */

static SEM_STATUS
SEM_FN_NAME (xstormy16,holdx) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_IRET_VARS /* f-op */
  EXTRACT_IFMT_IRET_CODE

do_holdx (current_cpu);

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* brk: brk */

static SEM_STATUS
SEM_FN_NAME (xstormy16,brk) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_IRET_VARS /* f-op */
  EXTRACT_IFMT_IRET_CODE

do_brk (current_cpu);

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* syscall: --unused-- */

static SEM_STATUS
SEM_FN_NAME (xstormy16,syscall) (SIM_CPU *current_cpu, SEM_ARG sem_arg, CGEN_INSN_WORD insn)
{
  SEM_STATUS status = 0;
  ARGBUF *abuf = SEM_ARGBUF (sem_arg);
#define FLD(f) f
  int UNUSED written = 0;
  IADDR UNUSED pc = GET_H_PC ();
  SEM_PC vpc = SEM_NEXT_VPC (sem_arg, pc, 2);
  EXTRACT_IFMT_IRET_VARS /* f-op */
  EXTRACT_IFMT_IRET_CODE

syscall (current_cpu);

  SEM_NBRANCH_FINI (vpc, 0);
#undef FLD
  return status;
}

/* Table of all semantic fns.  */

static const struct sem_fn_desc sem_fns[] = {
  { XSTORMY16_INSN_X_INVALID, SEM_FN_NAME (xstormy16,x_invalid) },
  { XSTORMY16_INSN_X_AFTER, SEM_FN_NAME (xstormy16,x_after) },
  { XSTORMY16_INSN_X_BEFORE, SEM_FN_NAME (xstormy16,x_before) },
  { XSTORMY16_INSN_X_CTI_CHAIN, SEM_FN_NAME (xstormy16,x_cti_chain) },
  { XSTORMY16_INSN_X_CHAIN, SEM_FN_NAME (xstormy16,x_chain) },
  { XSTORMY16_INSN_X_BEGIN, SEM_FN_NAME (xstormy16,x_begin) },
  { XSTORMY16_INSN_MOVLMEMIMM, SEM_FN_NAME (xstormy16,movlmemimm) },
  { XSTORMY16_INSN_MOVHMEMIMM, SEM_FN_NAME (xstormy16,movhmemimm) },
  { XSTORMY16_INSN_MOVLGRMEM, SEM_FN_NAME (xstormy16,movlgrmem) },
  { XSTORMY16_INSN_MOVHGRMEM, SEM_FN_NAME (xstormy16,movhgrmem) },
  { XSTORMY16_INSN_MOVLMEMGR, SEM_FN_NAME (xstormy16,movlmemgr) },
  { XSTORMY16_INSN_MOVHMEMGR, SEM_FN_NAME (xstormy16,movhmemgr) },
  { XSTORMY16_INSN_MOVGRGRI, SEM_FN_NAME (xstormy16,movgrgri) },
  { XSTORMY16_INSN_MOVGRGRIPOSTINC, SEM_FN_NAME (xstormy16,movgrgripostinc) },
  { XSTORMY16_INSN_MOVGRGRIPREDEC, SEM_FN_NAME (xstormy16,movgrgripredec) },
  { XSTORMY16_INSN_MOVGRIGR, SEM_FN_NAME (xstormy16,movgrigr) },
  { XSTORMY16_INSN_MOVGRIPOSTINCGR, SEM_FN_NAME (xstormy16,movgripostincgr) },
  { XSTORMY16_INSN_MOVGRIPREDECGR, SEM_FN_NAME (xstormy16,movgripredecgr) },
  { XSTORMY16_INSN_MOVGRGRII, SEM_FN_NAME (xstormy16,movgrgrii) },
  { XSTORMY16_INSN_MOVGRGRIIPOSTINC, SEM_FN_NAME (xstormy16,movgrgriipostinc) },
  { XSTORMY16_INSN_MOVGRGRIIPREDEC, SEM_FN_NAME (xstormy16,movgrgriipredec) },
  { XSTORMY16_INSN_MOVGRIIGR, SEM_FN_NAME (xstormy16,movgriigr) },
  { XSTORMY16_INSN_MOVGRIIPOSTINCGR, SEM_FN_NAME (xstormy16,movgriipostincgr) },
  { XSTORMY16_INSN_MOVGRIIPREDECGR, SEM_FN_NAME (xstormy16,movgriipredecgr) },
  { XSTORMY16_INSN_MOVGRGR, SEM_FN_NAME (xstormy16,movgrgr) },
  { XSTORMY16_INSN_MOVWIMM8, SEM_FN_NAME (xstormy16,movwimm8) },
  { XSTORMY16_INSN_MOVWGRIMM8, SEM_FN_NAME (xstormy16,movwgrimm8) },
  { XSTORMY16_INSN_MOVWGRIMM16, SEM_FN_NAME (xstormy16,movwgrimm16) },
  { XSTORMY16_INSN_MOVLOWGR, SEM_FN_NAME (xstormy16,movlowgr) },
  { XSTORMY16_INSN_MOVHIGHGR, SEM_FN_NAME (xstormy16,movhighgr) },
  { XSTORMY16_INSN_MOVFGRGRI, SEM_FN_NAME (xstormy16,movfgrgri) },
  { XSTORMY16_INSN_MOVFGRGRIPOSTINC, SEM_FN_NAME (xstormy16,movfgrgripostinc) },
  { XSTORMY16_INSN_MOVFGRGRIPREDEC, SEM_FN_NAME (xstormy16,movfgrgripredec) },
  { XSTORMY16_INSN_MOVFGRIGR, SEM_FN_NAME (xstormy16,movfgrigr) },
  { XSTORMY16_INSN_MOVFGRIPOSTINCGR, SEM_FN_NAME (xstormy16,movfgripostincgr) },
  { XSTORMY16_INSN_MOVFGRIPREDECGR, SEM_FN_NAME (xstormy16,movfgripredecgr) },
  { XSTORMY16_INSN_MOVFGRGRII, SEM_FN_NAME (xstormy16,movfgrgrii) },
  { XSTORMY16_INSN_MOVFGRGRIIPOSTINC, SEM_FN_NAME (xstormy16,movfgrgriipostinc) },
  { XSTORMY16_INSN_MOVFGRGRIIPREDEC, SEM_FN_NAME (xstormy16,movfgrgriipredec) },
  { XSTORMY16_INSN_MOVFGRIIGR, SEM_FN_NAME (xstormy16,movfgriigr) },
  { XSTORMY16_INSN_MOVFGRIIPOSTINCGR, SEM_FN_NAME (xstormy16,movfgriipostincgr) },
  { XSTORMY16_INSN_MOVFGRIIPREDECGR, SEM_FN_NAME (xstormy16,movfgriipredecgr) },
  { XSTORMY16_INSN_MASKGRGR, SEM_FN_NAME (xstormy16,maskgrgr) },
  { XSTORMY16_INSN_MASKGRIMM16, SEM_FN_NAME (xstormy16,maskgrimm16) },
  { XSTORMY16_INSN_PUSHGR, SEM_FN_NAME (xstormy16,pushgr) },
  { XSTORMY16_INSN_POPGR, SEM_FN_NAME (xstormy16,popgr) },
  { XSTORMY16_INSN_SWPN, SEM_FN_NAME (xstormy16,swpn) },
  { XSTORMY16_INSN_SWPB, SEM_FN_NAME (xstormy16,swpb) },
  { XSTORMY16_INSN_SWPW, SEM_FN_NAME (xstormy16,swpw) },
  { XSTORMY16_INSN_ANDGRGR, SEM_FN_NAME (xstormy16,andgrgr) },
  { XSTORMY16_INSN_ANDIMM8, SEM_FN_NAME (xstormy16,andimm8) },
  { XSTORMY16_INSN_ANDGRIMM16, SEM_FN_NAME (xstormy16,andgrimm16) },
  { XSTORMY16_INSN_ORGRGR, SEM_FN_NAME (xstormy16,orgrgr) },
  { XSTORMY16_INSN_ORIMM8, SEM_FN_NAME (xstormy16,orimm8) },
  { XSTORMY16_INSN_ORGRIMM16, SEM_FN_NAME (xstormy16,orgrimm16) },
  { XSTORMY16_INSN_XORGRGR, SEM_FN_NAME (xstormy16,xorgrgr) },
  { XSTORMY16_INSN_XORIMM8, SEM_FN_NAME (xstormy16,xorimm8) },
  { XSTORMY16_INSN_XORGRIMM16, SEM_FN_NAME (xstormy16,xorgrimm16) },
  { XSTORMY16_INSN_NOTGR, SEM_FN_NAME (xstormy16,notgr) },
  { XSTORMY16_INSN_ADDGRGR, SEM_FN_NAME (xstormy16,addgrgr) },
  { XSTORMY16_INSN_ADDGRIMM4, SEM_FN_NAME (xstormy16,addgrimm4) },
  { XSTORMY16_INSN_ADDIMM8, SEM_FN_NAME (xstormy16,addimm8) },
  { XSTORMY16_INSN_ADDGRIMM16, SEM_FN_NAME (xstormy16,addgrimm16) },
  { XSTORMY16_INSN_ADCGRGR, SEM_FN_NAME (xstormy16,adcgrgr) },
  { XSTORMY16_INSN_ADCGRIMM4, SEM_FN_NAME (xstormy16,adcgrimm4) },
  { XSTORMY16_INSN_ADCIMM8, SEM_FN_NAME (xstormy16,adcimm8) },
  { XSTORMY16_INSN_ADCGRIMM16, SEM_FN_NAME (xstormy16,adcgrimm16) },
  { XSTORMY16_INSN_SUBGRGR, SEM_FN_NAME (xstormy16,subgrgr) },
  { XSTORMY16_INSN_SUBGRIMM4, SEM_FN_NAME (xstormy16,subgrimm4) },
  { XSTORMY16_INSN_SUBIMM8, SEM_FN_NAME (xstormy16,subimm8) },
  { XSTORMY16_INSN_SUBGRIMM16, SEM_FN_NAME (xstormy16,subgrimm16) },
  { XSTORMY16_INSN_SBCGRGR, SEM_FN_NAME (xstormy16,sbcgrgr) },
  { XSTORMY16_INSN_SBCGRIMM4, SEM_FN_NAME (xstormy16,sbcgrimm4) },
  { XSTORMY16_INSN_SBCGRIMM8, SEM_FN_NAME (xstormy16,sbcgrimm8) },
  { XSTORMY16_INSN_SBCGRIMM16, SEM_FN_NAME (xstormy16,sbcgrimm16) },
  { XSTORMY16_INSN_INCGRIMM2, SEM_FN_NAME (xstormy16,incgrimm2) },
  { XSTORMY16_INSN_DECGRIMM2, SEM_FN_NAME (xstormy16,decgrimm2) },
  { XSTORMY16_INSN_RRCGRGR, SEM_FN_NAME (xstormy16,rrcgrgr) },
  { XSTORMY16_INSN_RRCGRIMM4, SEM_FN_NAME (xstormy16,rrcgrimm4) },
  { XSTORMY16_INSN_RLCGRGR, SEM_FN_NAME (xstormy16,rlcgrgr) },
  { XSTORMY16_INSN_RLCGRIMM4, SEM_FN_NAME (xstormy16,rlcgrimm4) },
  { XSTORMY16_INSN_SHRGRGR, SEM_FN_NAME (xstormy16,shrgrgr) },
  { XSTORMY16_INSN_SHRGRIMM, SEM_FN_NAME (xstormy16,shrgrimm) },
  { XSTORMY16_INSN_SHLGRGR, SEM_FN_NAME (xstormy16,shlgrgr) },
  { XSTORMY16_INSN_SHLGRIMM, SEM_FN_NAME (xstormy16,shlgrimm) },
  { XSTORMY16_INSN_ASRGRGR, SEM_FN_NAME (xstormy16,asrgrgr) },
  { XSTORMY16_INSN_ASRGRIMM, SEM_FN_NAME (xstormy16,asrgrimm) },
  { XSTORMY16_INSN_SET1GRIMM, SEM_FN_NAME (xstormy16,set1grimm) },
  { XSTORMY16_INSN_SET1GRGR, SEM_FN_NAME (xstormy16,set1grgr) },
  { XSTORMY16_INSN_SET1LMEMIMM, SEM_FN_NAME (xstormy16,set1lmemimm) },
  { XSTORMY16_INSN_SET1HMEMIMM, SEM_FN_NAME (xstormy16,set1hmemimm) },
  { XSTORMY16_INSN_CLR1GRIMM, SEM_FN_NAME (xstormy16,clr1grimm) },
  { XSTORMY16_INSN_CLR1GRGR, SEM_FN_NAME (xstormy16,clr1grgr) },
  { XSTORMY16_INSN_CLR1LMEMIMM, SEM_FN_NAME (xstormy16,clr1lmemimm) },
  { XSTORMY16_INSN_CLR1HMEMIMM, SEM_FN_NAME (xstormy16,clr1hmemimm) },
  { XSTORMY16_INSN_CBWGR, SEM_FN_NAME (xstormy16,cbwgr) },
  { XSTORMY16_INSN_REVGR, SEM_FN_NAME (xstormy16,revgr) },
  { XSTORMY16_INSN_BCCGRGR, SEM_FN_NAME (xstormy16,bccgrgr) },
  { XSTORMY16_INSN_BCCGRIMM8, SEM_FN_NAME (xstormy16,bccgrimm8) },
  { XSTORMY16_INSN_BCCIMM16, SEM_FN_NAME (xstormy16,bccimm16) },
  { XSTORMY16_INSN_BNGRIMM4, SEM_FN_NAME (xstormy16,bngrimm4) },
  { XSTORMY16_INSN_BNGRGR, SEM_FN_NAME (xstormy16,bngrgr) },
  { XSTORMY16_INSN_BNLMEMIMM, SEM_FN_NAME (xstormy16,bnlmemimm) },
  { XSTORMY16_INSN_BNHMEMIMM, SEM_FN_NAME (xstormy16,bnhmemimm) },
  { XSTORMY16_INSN_BPGRIMM4, SEM_FN_NAME (xstormy16,bpgrimm4) },
  { XSTORMY16_INSN_BPGRGR, SEM_FN_NAME (xstormy16,bpgrgr) },
  { XSTORMY16_INSN_BPLMEMIMM, SEM_FN_NAME (xstormy16,bplmemimm) },
  { XSTORMY16_INSN_BPHMEMIMM, SEM_FN_NAME (xstormy16,bphmemimm) },
  { XSTORMY16_INSN_BCC, SEM_FN_NAME (xstormy16,bcc) },
  { XSTORMY16_INSN_BGR, SEM_FN_NAME (xstormy16,bgr) },
  { XSTORMY16_INSN_BR, SEM_FN_NAME (xstormy16,br) },
  { XSTORMY16_INSN_JMP, SEM_FN_NAME (xstormy16,jmp) },
  { XSTORMY16_INSN_JMPF, SEM_FN_NAME (xstormy16,jmpf) },
  { XSTORMY16_INSN_CALLRGR, SEM_FN_NAME (xstormy16,callrgr) },
  { XSTORMY16_INSN_CALLRIMM, SEM_FN_NAME (xstormy16,callrimm) },
  { XSTORMY16_INSN_CALLGR, SEM_FN_NAME (xstormy16,callgr) },
  { XSTORMY16_INSN_CALLFIMM, SEM_FN_NAME (xstormy16,callfimm) },
  { XSTORMY16_INSN_ICALLRGR, SEM_FN_NAME (xstormy16,icallrgr) },
  { XSTORMY16_INSN_ICALLGR, SEM_FN_NAME (xstormy16,icallgr) },
  { XSTORMY16_INSN_ICALLFIMM, SEM_FN_NAME (xstormy16,icallfimm) },
  { XSTORMY16_INSN_IRET, SEM_FN_NAME (xstormy16,iret) },
  { XSTORMY16_INSN_RET, SEM_FN_NAME (xstormy16,ret) },
  { XSTORMY16_INSN_MUL, SEM_FN_NAME (xstormy16,mul) },
  { XSTORMY16_INSN_DIV, SEM_FN_NAME (xstormy16,div) },
  { XSTORMY16_INSN_SDIV, SEM_FN_NAME (xstormy16,sdiv) },
  { XSTORMY16_INSN_SDIVLH, SEM_FN_NAME (xstormy16,sdivlh) },
  { XSTORMY16_INSN_DIVLH, SEM_FN_NAME (xstormy16,divlh) },
  { XSTORMY16_INSN_RESET, SEM_FN_NAME (xstormy16,reset) },
  { XSTORMY16_INSN_NOP, SEM_FN_NAME (xstormy16,nop) },
  { XSTORMY16_INSN_HALT, SEM_FN_NAME (xstormy16,halt) },
  { XSTORMY16_INSN_HOLD, SEM_FN_NAME (xstormy16,hold) },
  { XSTORMY16_INSN_HOLDX, SEM_FN_NAME (xstormy16,holdx) },
  { XSTORMY16_INSN_BRK, SEM_FN_NAME (xstormy16,brk) },
  { XSTORMY16_INSN_SYSCALL, SEM_FN_NAME (xstormy16,syscall) },
  { 0, 0 }
};

/* Add the semantic fns to IDESC_TABLE.  */

void
SEM_FN_NAME (xstormy16,init_idesc_table) (SIM_CPU *current_cpu)
{
  IDESC *idesc_table = CPU_IDESC (current_cpu);
  const struct sem_fn_desc *sf;
  int mach_num = MACH_NUM (CPU_MACH (current_cpu));

  for (sf = &sem_fns[0]; sf->fn != 0; ++sf)
    {
      const CGEN_INSN *insn = idesc_table[sf->index].idata;
      int valid_p = (CGEN_INSN_VIRTUAL_P (insn)
		     || CGEN_INSN_MACH_HAS_P (insn, mach_num));
#if FAST_P
      if (valid_p)
	idesc_table[sf->index].sem_fast = sf->fn;
      else
	idesc_table[sf->index].sem_fast = SEM_FN_NAME (xstormy16,x_invalid);
#else
      if (valid_p)
	idesc_table[sf->index].sem_full = sf->fn;
      else
	idesc_table[sf->index].sem_full = SEM_FN_NAME (xstormy16,x_invalid);
#endif
    }
}

