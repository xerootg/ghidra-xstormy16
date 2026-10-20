/* Simulator instruction decoder for xstormy16.

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
#include "sim-assert.h"
#include "cgen-mem.h"
#include "cgen-ops.h"

/* The instruction descriptor array.
   This is computed at runtime.  Space for it is not malloc'd to save a
   teensy bit of cpu in the decoder.  Moving it to malloc space is trivial
   but won't be done until necessary (we don't currently support the runtime
   addition of instructions nor an SMP machine with different cpus).  */
static IDESC xstormy16_insn_data[XSTORMY16_INSN__MAX];

/* Commas between elements are contained in the macros.
   Some of these are conditionally compiled out.  */

static const struct insn_sem xstormy16_insn_sem[] =
{
  { VIRTUAL_INSN_X_INVALID, XSTORMY16_INSN_X_INVALID, XSTORMY16_SFMT_EMPTY },
  { VIRTUAL_INSN_X_AFTER, XSTORMY16_INSN_X_AFTER, XSTORMY16_SFMT_EMPTY },
  { VIRTUAL_INSN_X_BEFORE, XSTORMY16_INSN_X_BEFORE, XSTORMY16_SFMT_EMPTY },
  { VIRTUAL_INSN_X_CTI_CHAIN, XSTORMY16_INSN_X_CTI_CHAIN, XSTORMY16_SFMT_EMPTY },
  { VIRTUAL_INSN_X_CHAIN, XSTORMY16_INSN_X_CHAIN, XSTORMY16_SFMT_EMPTY },
  { VIRTUAL_INSN_X_BEGIN, XSTORMY16_INSN_X_BEGIN, XSTORMY16_SFMT_EMPTY },
  { XSTORMY16_INSN_MOVLMEMIMM, XSTORMY16_INSN_MOVLMEMIMM, XSTORMY16_SFMT_MOVLMEMIMM },
  { XSTORMY16_INSN_MOVHMEMIMM, XSTORMY16_INSN_MOVHMEMIMM, XSTORMY16_SFMT_MOVHMEMIMM },
  { XSTORMY16_INSN_MOVLGRMEM, XSTORMY16_INSN_MOVLGRMEM, XSTORMY16_SFMT_MOVLGRMEM },
  { XSTORMY16_INSN_MOVHGRMEM, XSTORMY16_INSN_MOVHGRMEM, XSTORMY16_SFMT_MOVHGRMEM },
  { XSTORMY16_INSN_MOVLMEMGR, XSTORMY16_INSN_MOVLMEMGR, XSTORMY16_SFMT_MOVLMEMGR },
  { XSTORMY16_INSN_MOVHMEMGR, XSTORMY16_INSN_MOVHMEMGR, XSTORMY16_SFMT_MOVHMEMGR },
  { XSTORMY16_INSN_MOVGRGRI, XSTORMY16_INSN_MOVGRGRI, XSTORMY16_SFMT_MOVGRGRI },
  { XSTORMY16_INSN_MOVGRGRIPOSTINC, XSTORMY16_INSN_MOVGRGRIPOSTINC, XSTORMY16_SFMT_MOVGRGRIPOSTINC },
  { XSTORMY16_INSN_MOVGRGRIPREDEC, XSTORMY16_INSN_MOVGRGRIPREDEC, XSTORMY16_SFMT_MOVGRGRIPREDEC },
  { XSTORMY16_INSN_MOVGRIGR, XSTORMY16_INSN_MOVGRIGR, XSTORMY16_SFMT_MOVGRIGR },
  { XSTORMY16_INSN_MOVGRIPOSTINCGR, XSTORMY16_INSN_MOVGRIPOSTINCGR, XSTORMY16_SFMT_MOVGRIPOSTINCGR },
  { XSTORMY16_INSN_MOVGRIPREDECGR, XSTORMY16_INSN_MOVGRIPREDECGR, XSTORMY16_SFMT_MOVGRIPREDECGR },
  { XSTORMY16_INSN_MOVGRGRII, XSTORMY16_INSN_MOVGRGRII, XSTORMY16_SFMT_MOVGRGRII },
  { XSTORMY16_INSN_MOVGRGRIIPOSTINC, XSTORMY16_INSN_MOVGRGRIIPOSTINC, XSTORMY16_SFMT_MOVGRGRIIPOSTINC },
  { XSTORMY16_INSN_MOVGRGRIIPREDEC, XSTORMY16_INSN_MOVGRGRIIPREDEC, XSTORMY16_SFMT_MOVGRGRIIPREDEC },
  { XSTORMY16_INSN_MOVGRIIGR, XSTORMY16_INSN_MOVGRIIGR, XSTORMY16_SFMT_MOVGRIIGR },
  { XSTORMY16_INSN_MOVGRIIPOSTINCGR, XSTORMY16_INSN_MOVGRIIPOSTINCGR, XSTORMY16_SFMT_MOVGRIIPOSTINCGR },
  { XSTORMY16_INSN_MOVGRIIPREDECGR, XSTORMY16_INSN_MOVGRIIPREDECGR, XSTORMY16_SFMT_MOVGRIIPREDECGR },
  { XSTORMY16_INSN_MOVGRGR, XSTORMY16_INSN_MOVGRGR, XSTORMY16_SFMT_MOVGRGR },
  { XSTORMY16_INSN_MOVWIMM8, XSTORMY16_INSN_MOVWIMM8, XSTORMY16_SFMT_MOVWIMM8 },
  { XSTORMY16_INSN_MOVWGRIMM8, XSTORMY16_INSN_MOVWGRIMM8, XSTORMY16_SFMT_MOVWGRIMM8 },
  { XSTORMY16_INSN_MOVWGRIMM16, XSTORMY16_INSN_MOVWGRIMM16, XSTORMY16_SFMT_MOVWGRIMM16 },
  { XSTORMY16_INSN_MOVLOWGR, XSTORMY16_INSN_MOVLOWGR, XSTORMY16_SFMT_MOVLOWGR },
  { XSTORMY16_INSN_MOVHIGHGR, XSTORMY16_INSN_MOVHIGHGR, XSTORMY16_SFMT_MOVLOWGR },
  { XSTORMY16_INSN_MOVFGRGRI, XSTORMY16_INSN_MOVFGRGRI, XSTORMY16_SFMT_MOVFGRGRI },
  { XSTORMY16_INSN_MOVFGRGRIPOSTINC, XSTORMY16_INSN_MOVFGRGRIPOSTINC, XSTORMY16_SFMT_MOVFGRGRIPOSTINC },
  { XSTORMY16_INSN_MOVFGRGRIPREDEC, XSTORMY16_INSN_MOVFGRGRIPREDEC, XSTORMY16_SFMT_MOVFGRGRIPREDEC },
  { XSTORMY16_INSN_MOVFGRIGR, XSTORMY16_INSN_MOVFGRIGR, XSTORMY16_SFMT_MOVFGRIGR },
  { XSTORMY16_INSN_MOVFGRIPOSTINCGR, XSTORMY16_INSN_MOVFGRIPOSTINCGR, XSTORMY16_SFMT_MOVFGRIPOSTINCGR },
  { XSTORMY16_INSN_MOVFGRIPREDECGR, XSTORMY16_INSN_MOVFGRIPREDECGR, XSTORMY16_SFMT_MOVFGRIPREDECGR },
  { XSTORMY16_INSN_MOVFGRGRII, XSTORMY16_INSN_MOVFGRGRII, XSTORMY16_SFMT_MOVFGRGRII },
  { XSTORMY16_INSN_MOVFGRGRIIPOSTINC, XSTORMY16_INSN_MOVFGRGRIIPOSTINC, XSTORMY16_SFMT_MOVFGRGRIIPOSTINC },
  { XSTORMY16_INSN_MOVFGRGRIIPREDEC, XSTORMY16_INSN_MOVFGRGRIIPREDEC, XSTORMY16_SFMT_MOVFGRGRIIPREDEC },
  { XSTORMY16_INSN_MOVFGRIIGR, XSTORMY16_INSN_MOVFGRIIGR, XSTORMY16_SFMT_MOVFGRIIGR },
  { XSTORMY16_INSN_MOVFGRIIPOSTINCGR, XSTORMY16_INSN_MOVFGRIIPOSTINCGR, XSTORMY16_SFMT_MOVFGRIIPOSTINCGR },
  { XSTORMY16_INSN_MOVFGRIIPREDECGR, XSTORMY16_INSN_MOVFGRIIPREDECGR, XSTORMY16_SFMT_MOVFGRIIPREDECGR },
  { XSTORMY16_INSN_MASKGRGR, XSTORMY16_INSN_MASKGRGR, XSTORMY16_SFMT_MASKGRGR },
  { XSTORMY16_INSN_MASKGRIMM16, XSTORMY16_INSN_MASKGRIMM16, XSTORMY16_SFMT_MASKGRIMM16 },
  { XSTORMY16_INSN_PUSHGR, XSTORMY16_INSN_PUSHGR, XSTORMY16_SFMT_PUSHGR },
  { XSTORMY16_INSN_POPGR, XSTORMY16_INSN_POPGR, XSTORMY16_SFMT_POPGR },
  { XSTORMY16_INSN_SWPN, XSTORMY16_INSN_SWPN, XSTORMY16_SFMT_SWPN },
  { XSTORMY16_INSN_SWPB, XSTORMY16_INSN_SWPB, XSTORMY16_SFMT_SWPN },
  { XSTORMY16_INSN_SWPW, XSTORMY16_INSN_SWPW, XSTORMY16_SFMT_SWPW },
  { XSTORMY16_INSN_ANDGRGR, XSTORMY16_INSN_ANDGRGR, XSTORMY16_SFMT_ANDGRGR },
  { XSTORMY16_INSN_ANDIMM8, XSTORMY16_INSN_ANDIMM8, XSTORMY16_SFMT_ANDIMM8 },
  { XSTORMY16_INSN_ANDGRIMM16, XSTORMY16_INSN_ANDGRIMM16, XSTORMY16_SFMT_ANDGRIMM16 },
  { XSTORMY16_INSN_ORGRGR, XSTORMY16_INSN_ORGRGR, XSTORMY16_SFMT_ANDGRGR },
  { XSTORMY16_INSN_ORIMM8, XSTORMY16_INSN_ORIMM8, XSTORMY16_SFMT_ANDIMM8 },
  { XSTORMY16_INSN_ORGRIMM16, XSTORMY16_INSN_ORGRIMM16, XSTORMY16_SFMT_ANDGRIMM16 },
  { XSTORMY16_INSN_XORGRGR, XSTORMY16_INSN_XORGRGR, XSTORMY16_SFMT_ANDGRGR },
  { XSTORMY16_INSN_XORIMM8, XSTORMY16_INSN_XORIMM8, XSTORMY16_SFMT_ANDIMM8 },
  { XSTORMY16_INSN_XORGRIMM16, XSTORMY16_INSN_XORGRIMM16, XSTORMY16_SFMT_ANDGRIMM16 },
  { XSTORMY16_INSN_NOTGR, XSTORMY16_INSN_NOTGR, XSTORMY16_SFMT_SWPN },
  { XSTORMY16_INSN_ADDGRGR, XSTORMY16_INSN_ADDGRGR, XSTORMY16_SFMT_ANDGRGR },
  { XSTORMY16_INSN_ADDGRIMM4, XSTORMY16_INSN_ADDGRIMM4, XSTORMY16_SFMT_ADDGRIMM4 },
  { XSTORMY16_INSN_ADDIMM8, XSTORMY16_INSN_ADDIMM8, XSTORMY16_SFMT_ANDIMM8 },
  { XSTORMY16_INSN_ADDGRIMM16, XSTORMY16_INSN_ADDGRIMM16, XSTORMY16_SFMT_ANDGRIMM16 },
  { XSTORMY16_INSN_ADCGRGR, XSTORMY16_INSN_ADCGRGR, XSTORMY16_SFMT_ADCGRGR },
  { XSTORMY16_INSN_ADCGRIMM4, XSTORMY16_INSN_ADCGRIMM4, XSTORMY16_SFMT_ADCGRIMM4 },
  { XSTORMY16_INSN_ADCIMM8, XSTORMY16_INSN_ADCIMM8, XSTORMY16_SFMT_ADCIMM8 },
  { XSTORMY16_INSN_ADCGRIMM16, XSTORMY16_INSN_ADCGRIMM16, XSTORMY16_SFMT_ADCGRIMM16 },
  { XSTORMY16_INSN_SUBGRGR, XSTORMY16_INSN_SUBGRGR, XSTORMY16_SFMT_ANDGRGR },
  { XSTORMY16_INSN_SUBGRIMM4, XSTORMY16_INSN_SUBGRIMM4, XSTORMY16_SFMT_ADDGRIMM4 },
  { XSTORMY16_INSN_SUBIMM8, XSTORMY16_INSN_SUBIMM8, XSTORMY16_SFMT_ANDIMM8 },
  { XSTORMY16_INSN_SUBGRIMM16, XSTORMY16_INSN_SUBGRIMM16, XSTORMY16_SFMT_ANDGRIMM16 },
  { XSTORMY16_INSN_SBCGRGR, XSTORMY16_INSN_SBCGRGR, XSTORMY16_SFMT_ADCGRGR },
  { XSTORMY16_INSN_SBCGRIMM4, XSTORMY16_INSN_SBCGRIMM4, XSTORMY16_SFMT_ADCGRIMM4 },
  { XSTORMY16_INSN_SBCGRIMM8, XSTORMY16_INSN_SBCGRIMM8, XSTORMY16_SFMT_ADCIMM8 },
  { XSTORMY16_INSN_SBCGRIMM16, XSTORMY16_INSN_SBCGRIMM16, XSTORMY16_SFMT_ADCGRIMM16 },
  { XSTORMY16_INSN_INCGRIMM2, XSTORMY16_INSN_INCGRIMM2, XSTORMY16_SFMT_INCGRIMM2 },
  { XSTORMY16_INSN_DECGRIMM2, XSTORMY16_INSN_DECGRIMM2, XSTORMY16_SFMT_INCGRIMM2 },
  { XSTORMY16_INSN_RRCGRGR, XSTORMY16_INSN_RRCGRGR, XSTORMY16_SFMT_ADCGRGR },
  { XSTORMY16_INSN_RRCGRIMM4, XSTORMY16_INSN_RRCGRIMM4, XSTORMY16_SFMT_ADCGRIMM4 },
  { XSTORMY16_INSN_RLCGRGR, XSTORMY16_INSN_RLCGRGR, XSTORMY16_SFMT_ADCGRGR },
  { XSTORMY16_INSN_RLCGRIMM4, XSTORMY16_INSN_RLCGRIMM4, XSTORMY16_SFMT_ADCGRIMM4 },
  { XSTORMY16_INSN_SHRGRGR, XSTORMY16_INSN_SHRGRGR, XSTORMY16_SFMT_SHRGRGR },
  { XSTORMY16_INSN_SHRGRIMM, XSTORMY16_INSN_SHRGRIMM, XSTORMY16_SFMT_SHRGRIMM },
  { XSTORMY16_INSN_SHLGRGR, XSTORMY16_INSN_SHLGRGR, XSTORMY16_SFMT_SHRGRGR },
  { XSTORMY16_INSN_SHLGRIMM, XSTORMY16_INSN_SHLGRIMM, XSTORMY16_SFMT_SHRGRIMM },
  { XSTORMY16_INSN_ASRGRGR, XSTORMY16_INSN_ASRGRGR, XSTORMY16_SFMT_SHRGRGR },
  { XSTORMY16_INSN_ASRGRIMM, XSTORMY16_INSN_ASRGRIMM, XSTORMY16_SFMT_SHRGRIMM },
  { XSTORMY16_INSN_SET1GRIMM, XSTORMY16_INSN_SET1GRIMM, XSTORMY16_SFMT_ADDGRIMM4 },
  { XSTORMY16_INSN_SET1GRGR, XSTORMY16_INSN_SET1GRGR, XSTORMY16_SFMT_ANDGRGR },
  { XSTORMY16_INSN_SET1LMEMIMM, XSTORMY16_INSN_SET1LMEMIMM, XSTORMY16_SFMT_SET1LMEMIMM },
  { XSTORMY16_INSN_SET1HMEMIMM, XSTORMY16_INSN_SET1HMEMIMM, XSTORMY16_SFMT_SET1HMEMIMM },
  { XSTORMY16_INSN_CLR1GRIMM, XSTORMY16_INSN_CLR1GRIMM, XSTORMY16_SFMT_ADDGRIMM4 },
  { XSTORMY16_INSN_CLR1GRGR, XSTORMY16_INSN_CLR1GRGR, XSTORMY16_SFMT_ANDGRGR },
  { XSTORMY16_INSN_CLR1LMEMIMM, XSTORMY16_INSN_CLR1LMEMIMM, XSTORMY16_SFMT_SET1LMEMIMM },
  { XSTORMY16_INSN_CLR1HMEMIMM, XSTORMY16_INSN_CLR1HMEMIMM, XSTORMY16_SFMT_SET1HMEMIMM },
  { XSTORMY16_INSN_CBWGR, XSTORMY16_INSN_CBWGR, XSTORMY16_SFMT_SWPN },
  { XSTORMY16_INSN_REVGR, XSTORMY16_INSN_REVGR, XSTORMY16_SFMT_SWPN },
  { XSTORMY16_INSN_BCCGRGR, XSTORMY16_INSN_BCCGRGR, XSTORMY16_SFMT_BCCGRGR },
  { XSTORMY16_INSN_BCCGRIMM8, XSTORMY16_INSN_BCCGRIMM8, XSTORMY16_SFMT_BCCGRIMM8 },
  { XSTORMY16_INSN_BCCIMM16, XSTORMY16_INSN_BCCIMM16, XSTORMY16_SFMT_BCCIMM16 },
  { XSTORMY16_INSN_BNGRIMM4, XSTORMY16_INSN_BNGRIMM4, XSTORMY16_SFMT_BNGRIMM4 },
  { XSTORMY16_INSN_BNGRGR, XSTORMY16_INSN_BNGRGR, XSTORMY16_SFMT_BNGRGR },
  { XSTORMY16_INSN_BNLMEMIMM, XSTORMY16_INSN_BNLMEMIMM, XSTORMY16_SFMT_BNLMEMIMM },
  { XSTORMY16_INSN_BNHMEMIMM, XSTORMY16_INSN_BNHMEMIMM, XSTORMY16_SFMT_BNHMEMIMM },
  { XSTORMY16_INSN_BPGRIMM4, XSTORMY16_INSN_BPGRIMM4, XSTORMY16_SFMT_BNGRIMM4 },
  { XSTORMY16_INSN_BPGRGR, XSTORMY16_INSN_BPGRGR, XSTORMY16_SFMT_BNGRGR },
  { XSTORMY16_INSN_BPLMEMIMM, XSTORMY16_INSN_BPLMEMIMM, XSTORMY16_SFMT_BNLMEMIMM },
  { XSTORMY16_INSN_BPHMEMIMM, XSTORMY16_INSN_BPHMEMIMM, XSTORMY16_SFMT_BNHMEMIMM },
  { XSTORMY16_INSN_BCC, XSTORMY16_INSN_BCC, XSTORMY16_SFMT_BCC },
  { XSTORMY16_INSN_BGR, XSTORMY16_INSN_BGR, XSTORMY16_SFMT_BGR },
  { XSTORMY16_INSN_BR, XSTORMY16_INSN_BR, XSTORMY16_SFMT_BR },
  { XSTORMY16_INSN_JMP, XSTORMY16_INSN_JMP, XSTORMY16_SFMT_JMP },
  { XSTORMY16_INSN_JMPF, XSTORMY16_INSN_JMPF, XSTORMY16_SFMT_JMPF },
  { XSTORMY16_INSN_CALLRGR, XSTORMY16_INSN_CALLRGR, XSTORMY16_SFMT_CALLRGR },
  { XSTORMY16_INSN_CALLRIMM, XSTORMY16_INSN_CALLRIMM, XSTORMY16_SFMT_CALLRIMM },
  { XSTORMY16_INSN_CALLGR, XSTORMY16_INSN_CALLGR, XSTORMY16_SFMT_CALLGR },
  { XSTORMY16_INSN_CALLFIMM, XSTORMY16_INSN_CALLFIMM, XSTORMY16_SFMT_CALLFIMM },
  { XSTORMY16_INSN_ICALLRGR, XSTORMY16_INSN_ICALLRGR, XSTORMY16_SFMT_ICALLRGR },
  { XSTORMY16_INSN_ICALLGR, XSTORMY16_INSN_ICALLGR, XSTORMY16_SFMT_ICALLGR },
  { XSTORMY16_INSN_ICALLFIMM, XSTORMY16_INSN_ICALLFIMM, XSTORMY16_SFMT_ICALLFIMM },
  { XSTORMY16_INSN_IRET, XSTORMY16_INSN_IRET, XSTORMY16_SFMT_IRET },
  { XSTORMY16_INSN_RET, XSTORMY16_INSN_RET, XSTORMY16_SFMT_RET },
  { XSTORMY16_INSN_MUL, XSTORMY16_INSN_MUL, XSTORMY16_SFMT_MUL },
  { XSTORMY16_INSN_DIV, XSTORMY16_INSN_DIV, XSTORMY16_SFMT_MUL },
  { XSTORMY16_INSN_SDIV, XSTORMY16_INSN_SDIV, XSTORMY16_SFMT_MUL },
  { XSTORMY16_INSN_SDIVLH, XSTORMY16_INSN_SDIVLH, XSTORMY16_SFMT_SDIVLH },
  { XSTORMY16_INSN_DIVLH, XSTORMY16_INSN_DIVLH, XSTORMY16_SFMT_SDIVLH },
  { XSTORMY16_INSN_RESET, XSTORMY16_INSN_RESET, XSTORMY16_SFMT_RESET },
  { XSTORMY16_INSN_NOP, XSTORMY16_INSN_NOP, XSTORMY16_SFMT_RESET },
  { XSTORMY16_INSN_HALT, XSTORMY16_INSN_HALT, XSTORMY16_SFMT_RESET },
  { XSTORMY16_INSN_HOLD, XSTORMY16_INSN_HOLD, XSTORMY16_SFMT_RESET },
  { XSTORMY16_INSN_HOLDX, XSTORMY16_INSN_HOLDX, XSTORMY16_SFMT_RESET },
  { XSTORMY16_INSN_BRK, XSTORMY16_INSN_BRK, XSTORMY16_SFMT_RESET },
  { XSTORMY16_INSN_SYSCALL, XSTORMY16_INSN_SYSCALL, XSTORMY16_SFMT_RESET },
};

static const struct insn_sem xstormy16_insn_sem_invalid =
{
  VIRTUAL_INSN_X_INVALID, XSTORMY16_INSN_X_INVALID, XSTORMY16_SFMT_EMPTY
};

/* Initialize an IDESC from the compile-time computable parts.  */

static INLINE void
init_idesc (SIM_CPU *cpu, IDESC *id, const struct insn_sem *t)
{
  const CGEN_INSN *insn_table = CGEN_CPU_INSN_TABLE (CPU_CPU_DESC (cpu))->init_entries;

  id->num = t->index;
  id->sfmt = t->sfmt;
  if ((int) t->type <= 0)
    id->idata = & cgen_virtual_insn_table[- (int) t->type];
  else
    id->idata = & insn_table[t->type];
  id->attrs = CGEN_INSN_ATTRS (id->idata);
  /* Oh my god, a magic number.  */
  id->length = CGEN_INSN_BITSIZE (id->idata) / 8;

#if WITH_PROFILE_MODEL_P
  id->timing = & MODEL_TIMING (CPU_MODEL (cpu)) [t->index];
  {
    SIM_DESC sd = CPU_STATE (cpu);
    SIM_ASSERT (t->index == id->timing->num);
  }
#endif

  /* Semantic pointers are initialized elsewhere.  */
}

/* Initialize the instruction descriptor table.  */

void
xstormy16_init_idesc_table (SIM_CPU *cpu)
{
  IDESC *id,*tabend;
  const struct insn_sem *t,*tend;
  int tabsize = XSTORMY16_INSN__MAX;
  IDESC *table = xstormy16_insn_data;

  memset (table, 0, tabsize * sizeof (IDESC));

  /* First set all entries to the `invalid insn'.  */
  t = & xstormy16_insn_sem_invalid;
  for (id = table, tabend = table + tabsize; id < tabend; ++id)
    init_idesc (cpu, id, t);

  /* Now fill in the values for the chosen cpu.  */
  for (t = xstormy16_insn_sem, tend = t + ARRAY_SIZE (xstormy16_insn_sem);
       t != tend; ++t)
    {
      init_idesc (cpu, & table[t->index], t);
    }

  /* Link the IDESC table into the cpu.  */
  CPU_IDESC (cpu) = table;
}

/* Given an instruction, return a pointer to its IDESC entry.  */

const IDESC *
xstormy16_decode (SIM_CPU *current_cpu, IADDR pc,
              CGEN_INSN_WORD base_insn, CGEN_INSN_WORD entire_insn,
              ARGBUF *abuf)
{
  /* Result of decoder.  */
  XSTORMY16_INSN_TYPE itype;

  {
    CGEN_INSN_WORD insn = base_insn;

    {
      unsigned int val0 = (((insn >> 5) & (1023 << 1)) | ((insn >> 3) & (1 << 0)));
      switch (val0)
      {
      case 0:
        {
          unsigned int val1 = (((insn >> 1) & (3 << 3)) | ((insn >> 0) & (7 << 0)));
          switch (val1)
          {
          case 0: itype = XSTORMY16_INSN_NOP; goto done;
          case 1: itype = XSTORMY16_INSN_SYSCALL; goto done;
          case 2: itype = XSTORMY16_INSN_IRET; goto done;
          case 3: itype = XSTORMY16_INSN_RET; goto done;
          case 5: itype = XSTORMY16_INSN_BRK; goto done;
          case 8:
          case 9:
          case 10:
          case 11:
          case 12:
          case 13:
          case 14:
          case 15: itype = XSTORMY16_INSN_CALLRGR; goto done;
          case 16:
          case 17:
          case 18:
          case 19:
          case 20:
          case 21:
          case 22:
          case 23: itype = XSTORMY16_INSN_BGR; goto done;
          case 24:
          case 25:
          case 26:
          case 27:
          case 28:
          case 29:
          case 30:
          case 31: itype = XSTORMY16_INSN_ICALLRGR; goto done;
          default: itype = XSTORMY16_INSN_X_INVALID; goto done;
          }
        }
      case 1:
        {
          unsigned int val1 = (((insn >> 1) & (3 << 3)) | ((insn >> 0) & (7 << 0)));
          switch (val1)
          {
          case 0: itype = XSTORMY16_INSN_HALT; goto done;
          case 2: itype = XSTORMY16_INSN_HOLD; goto done;
          case 3: itype = XSTORMY16_INSN_HOLDX; goto done;
          case 7: itype = XSTORMY16_INSN_RESET; goto done;
          case 8:
          case 9:
          case 10:
          case 11:
          case 12:
          case 13:
          case 14:
          case 15: itype = XSTORMY16_INSN_CALLRGR; goto done;
          case 16:
          case 17:
          case 18:
          case 19:
          case 20:
          case 21:
          case 22:
          case 23: itype = XSTORMY16_INSN_BGR; goto done;
          case 24:
          case 25:
          case 26:
          case 27:
          case 28:
          case 29:
          case 30:
          case 31: itype = XSTORMY16_INSN_ICALLRGR; goto done;
          default: itype = XSTORMY16_INSN_X_INVALID; goto done;
          }
        }
      case 2:
      case 3:
        {
          unsigned int val1 = (((insn >> 5) & (1 << 0)));
          switch (val1)
          {
          case 0: itype = XSTORMY16_INSN_JMP; goto done;
          case 1: itype = XSTORMY16_INSN_ICALLGR; goto done;
          default: itype = XSTORMY16_INSN_X_INVALID; goto done;
          }
        }
      case 4:
      case 5:
        {
          unsigned int val1 = (((insn >> 4) & (3 << 0)));
          switch (val1)
          {
          case 0: itype = XSTORMY16_INSN_PUSHGR; goto done;
          case 1: itype = XSTORMY16_INSN_POPGR; goto done;
          case 2:
          case 3: itype = XSTORMY16_INSN_CALLGR; goto done;
          default: itype = XSTORMY16_INSN_X_INVALID; goto done;
          }
        }
      case 6:
        {
          unsigned int val1 = (((insn >> 4) & (3 << 0)));
          switch (val1)
          {
          case 0:
            if ((entire_insn & 0xffff) == 0xc0)
              { itype = XSTORMY16_INSN_DIV; goto done; }
            itype = XSTORMY16_INSN_X_INVALID; goto done;
          case 1:
            if ((entire_insn & 0xffff) == 0xd0)
              { itype = XSTORMY16_INSN_MUL; goto done; }
            itype = XSTORMY16_INSN_X_INVALID; goto done;
          case 2:
            if ((entire_insn & 0xffff) == 0xe0)
              { itype = XSTORMY16_INSN_DIVLH; goto done; }
            itype = XSTORMY16_INSN_X_INVALID; goto done;
          default: itype = XSTORMY16_INSN_X_INVALID; goto done;
          }
        }
      case 7:
        {
          unsigned int val1 = (((insn >> 5) & (1 << 0)));
          switch (val1)
          {
          case 0:
            if ((entire_insn & 0xffff) == 0xc8)
              { itype = XSTORMY16_INSN_SDIV; goto done; }
            itype = XSTORMY16_INSN_X_INVALID; goto done;
          case 1:
            if ((entire_insn & 0xffff) == 0xe8)
              { itype = XSTORMY16_INSN_SDIVLH; goto done; }
            itype = XSTORMY16_INSN_X_INVALID; goto done;
          default: itype = XSTORMY16_INSN_X_INVALID; goto done;
          }
        }
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15: itype = XSTORMY16_INSN_CALLFIMM; goto done;
      case 16:
      case 17:
      case 18:
      case 19:
      case 20:
      case 21:
      case 22:
      case 23: itype = XSTORMY16_INSN_JMPF; goto done;
      case 24:
      case 25:
      case 26:
      case 27:
      case 28:
      case 29:
      case 30:
      case 31: itype = XSTORMY16_INSN_ICALLFIMM; goto done;
      case 32:
      case 33:
      case 34:
      case 35:
      case 36:
      case 37:
      case 38:
      case 39:
        if ((entire_insn & 0xff00f000) == 0x4000000)
          { itype = XSTORMY16_INSN_BNGRIMM4; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 40:
      case 41:
      case 42:
      case 43:
      case 44:
      case 45:
      case 46:
      case 47:
        if ((entire_insn & 0xff00f000) == 0x5000000)
          { itype = XSTORMY16_INSN_BPGRIMM4; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 48:
      case 49:
      case 50:
      case 51:
      case 52:
      case 53:
      case 54:
      case 55:
        if ((entire_insn & 0xff00f000) == 0x6000000)
          { itype = XSTORMY16_INSN_BNGRGR; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 56:
      case 57:
      case 58:
      case 59:
      case 60:
      case 61:
      case 62:
      case 63:
        if ((entire_insn & 0xff00f000) == 0x7000000)
          { itype = XSTORMY16_INSN_BPGRGR; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 64:
      case 65:
      case 66:
      case 67:
      case 68:
      case 69:
      case 70:
      case 71: itype = XSTORMY16_INSN_CLR1GRIMM; goto done;
      case 72:
      case 73:
      case 74:
      case 75:
      case 76:
      case 77:
      case 78:
      case 79: itype = XSTORMY16_INSN_SET1GRIMM; goto done;
      case 80:
      case 81:
      case 82:
      case 83:
      case 84:
      case 85:
      case 86:
      case 87: itype = XSTORMY16_INSN_CLR1GRGR; goto done;
      case 88:
      case 89:
      case 90:
      case 91:
      case 92:
      case 93:
      case 94:
      case 95: itype = XSTORMY16_INSN_SET1GRGR; goto done;
      case 104:
      case 105:
      case 106:
      case 107:
      case 108:
      case 109:
      case 110:
      case 111: itype = XSTORMY16_INSN_BCCGRGR; goto done;
      case 128:
      case 129:
      case 130:
      case 131:
      case 132:
      case 133:
      case 134:
      case 135:
      case 136:
      case 137:
      case 138:
      case 139:
      case 140:
      case 141:
      case 142:
      case 143:
      case 144:
      case 145:
      case 146:
      case 147:
      case 148:
      case 149:
      case 150:
      case 151:
      case 152:
      case 153:
      case 154:
      case 155:
      case 156:
      case 157:
      case 158:
      case 159:
      case 160:
      case 161:
      case 162:
      case 163:
      case 164:
      case 165:
      case 166:
      case 167:
      case 168:
      case 169:
      case 170:
      case 171:
      case 172:
      case 173:
      case 174:
      case 175:
      case 176:
      case 177:
      case 178:
      case 179:
      case 180:
      case 181:
      case 182:
      case 183:
      case 184:
      case 185:
      case 186:
      case 187:
      case 188:
      case 189:
      case 190:
      case 191:
      case 192:
      case 193:
      case 194:
      case 195:
      case 196:
      case 197:
      case 198:
      case 199:
      case 200:
      case 201:
      case 202:
      case 203:
      case 204:
      case 205:
      case 206:
      case 207:
      case 208:
      case 209:
      case 210:
      case 211:
      case 212:
      case 213:
      case 214:
      case 215:
      case 216:
      case 217:
      case 218:
      case 219:
      case 220:
      case 221:
      case 222:
      case 223:
      case 224:
      case 225:
      case 226:
      case 227:
      case 228:
      case 229:
      case 230:
      case 231:
      case 232:
      case 233:
      case 234:
      case 235:
      case 236:
      case 237:
      case 238:
      case 239:
      case 240:
      case 241:
      case 242:
      case 243:
      case 244:
      case 245:
      case 246:
      case 247:
      case 248:
      case 249:
      case 250:
      case 251:
      case 252:
      case 253:
      case 254:
      case 255:
        {
          unsigned int val1 = (((insn >> 0) & (1 << 0)));
          switch (val1)
          {
          case 0: itype = XSTORMY16_INSN_BR; goto done;
          case 1: itype = XSTORMY16_INSN_CALLRIMM; goto done;
          default: itype = XSTORMY16_INSN_X_INVALID; goto done;
          }
        }
      case 256:
      case 257:
      case 258:
      case 259:
      case 260:
      case 261:
      case 262:
      case 263:
      case 272:
      case 273:
      case 274:
      case 275:
      case 276:
      case 277:
      case 278:
      case 279:
      case 288:
      case 289:
      case 290:
      case 291:
      case 292:
      case 293:
      case 294:
      case 295:
      case 304:
      case 305:
      case 306:
      case 307:
      case 308:
      case 309:
      case 310:
      case 311:
      case 320:
      case 321:
      case 322:
      case 323:
      case 324:
      case 325:
      case 326:
      case 327:
      case 336:
      case 337:
      case 338:
      case 339:
      case 340:
      case 341:
      case 342:
      case 343:
      case 352:
      case 353:
      case 354:
      case 355:
      case 356:
      case 357:
      case 358:
      case 359:
      case 368:
      case 369:
      case 370:
      case 371:
      case 372:
      case 373:
      case 374:
      case 375: itype = XSTORMY16_INSN_BCCGRIMM8; goto done;
      case 264:
      case 265:
      case 266:
      case 267:
      case 268:
      case 269:
      case 270:
      case 271:
      case 280:
      case 281:
      case 282:
      case 283:
      case 284:
      case 285:
      case 286:
      case 287:
      case 296:
      case 297:
      case 298:
      case 299:
      case 300:
      case 301:
      case 302:
      case 303:
      case 312:
      case 313:
      case 314:
      case 315:
      case 316:
      case 317:
      case 318:
      case 319:
      case 328:
      case 329:
      case 330:
      case 331:
      case 332:
      case 333:
      case 334:
      case 335:
      case 344:
      case 345:
      case 346:
      case 347:
      case 348:
      case 349:
      case 350:
      case 351:
      case 360:
      case 361:
      case 362:
      case 363:
      case 364:
      case 365:
      case 366:
      case 367:
      case 376:
      case 377:
      case 378:
      case 379:
      case 380:
      case 381:
      case 382:
      case 383: itype = XSTORMY16_INSN_MOVWGRIMM8; goto done;
      case 384:
      case 385: itype = XSTORMY16_INSN_INCGRIMM2; goto done;
      case 386:
      case 387: itype = XSTORMY16_INSN_DECGRIMM2; goto done;
      case 388:
      case 389:
        {
          unsigned int val1 = (((insn >> 4) & (3 << 0)));
          switch (val1)
          {
          case 0: itype = XSTORMY16_INSN_SWPB; goto done;
          case 1: itype = XSTORMY16_INSN_SWPN; goto done;
          case 2: itype = XSTORMY16_INSN_CBWGR; goto done;
          case 3: itype = XSTORMY16_INSN_NOTGR; goto done;
          default: itype = XSTORMY16_INSN_X_INVALID; goto done;
          }
        }
      case 390:
      case 391:
        {
          unsigned int val1 = (((insn >> 4) & (3 << 0)));
          switch (val1)
          {
          case 0: itype = XSTORMY16_INSN_MOVLOWGR; goto done;
          case 1: itype = XSTORMY16_INSN_MOVHIGHGR; goto done;
          case 2: itype = XSTORMY16_INSN_MASKGRIMM16; goto done;
          case 3: itype = XSTORMY16_INSN_REVGR; goto done;
          default: itype = XSTORMY16_INSN_X_INVALID; goto done;
          }
        }
      case 392:
      case 393:
        {
          unsigned int val1 = (((insn >> 4) & (3 << 0)));
          switch (val1)
          {
          case 0: itype = XSTORMY16_INSN_ANDGRIMM16; goto done;
          case 1: itype = XSTORMY16_INSN_ORGRIMM16; goto done;
          case 2: itype = XSTORMY16_INSN_XORGRIMM16; goto done;
          case 3: itype = XSTORMY16_INSN_MOVWGRIMM16; goto done;
          default: itype = XSTORMY16_INSN_X_INVALID; goto done;
          }
        }
      case 394:
      case 395:
        {
          unsigned int val1 = (((insn >> 4) & (3 << 0)));
          switch (val1)
          {
          case 0: itype = XSTORMY16_INSN_ADDGRIMM16; goto done;
          case 1: itype = XSTORMY16_INSN_ADCGRIMM16; goto done;
          case 2: itype = XSTORMY16_INSN_SUBGRIMM16; goto done;
          case 3: itype = XSTORMY16_INSN_SBCGRIMM16; goto done;
          default: itype = XSTORMY16_INSN_X_INVALID; goto done;
          }
        }
      case 400:
      case 401:
      case 402:
      case 403:
      case 404:
      case 405:
      case 406:
      case 407: itype = XSTORMY16_INSN_SWPW; goto done;
      case 408:
      case 409:
      case 410:
      case 411:
      case 412:
      case 413:
      case 414:
      case 415: itype = XSTORMY16_INSN_MASKGRGR; goto done;
      case 432:
      case 433:
      case 434:
      case 435:
      case 436:
      case 437:
      case 438:
      case 439: itype = XSTORMY16_INSN_ASRGRGR; goto done;
      case 440:
      case 441:
      case 442:
      case 443:
      case 444:
      case 445:
      case 446:
      case 447: itype = XSTORMY16_INSN_ASRGRIMM; goto done;
      case 448:
      case 449:
      case 450:
      case 451:
      case 452:
      case 453:
      case 454:
      case 455: itype = XSTORMY16_INSN_RRCGRGR; goto done;
      case 456:
      case 457:
      case 458:
      case 459:
      case 460:
      case 461:
      case 462:
      case 463: itype = XSTORMY16_INSN_RRCGRIMM4; goto done;
      case 464:
      case 465:
      case 466:
      case 467:
      case 468:
      case 469:
      case 470:
      case 471: itype = XSTORMY16_INSN_RLCGRGR; goto done;
      case 472:
      case 473:
      case 474:
      case 475:
      case 476:
      case 477:
      case 478:
      case 479: itype = XSTORMY16_INSN_RLCGRIMM4; goto done;
      case 480:
      case 481:
      case 482:
      case 483:
      case 484:
      case 485:
      case 486:
      case 487: itype = XSTORMY16_INSN_SHRGRGR; goto done;
      case 488:
      case 489:
      case 490:
      case 491:
      case 492:
      case 493:
      case 494:
      case 495: itype = XSTORMY16_INSN_SHRGRIMM; goto done;
      case 496:
      case 497:
      case 498:
      case 499:
      case 500:
      case 501:
      case 502:
      case 503: itype = XSTORMY16_INSN_SHLGRGR; goto done;
      case 504:
      case 505:
      case 506:
      case 507:
      case 508:
      case 509:
      case 510:
      case 511: itype = XSTORMY16_INSN_SHLGRIMM; goto done;
      case 512:
      case 513:
      case 514:
      case 515:
      case 516:
      case 517:
      case 518:
      case 519: itype = XSTORMY16_INSN_ANDGRGR; goto done;
      case 520:
      case 521:
      case 522:
      case 523:
      case 524:
      case 525:
      case 526:
      case 527: itype = XSTORMY16_INSN_ANDIMM8; goto done;
      case 528:
      case 529:
      case 530:
      case 531:
      case 532:
      case 533:
      case 534:
      case 535: itype = XSTORMY16_INSN_ORGRGR; goto done;
      case 536:
      case 537:
      case 538:
      case 539:
      case 540:
      case 541:
      case 542:
      case 543: itype = XSTORMY16_INSN_ORIMM8; goto done;
      case 544:
      case 545:
      case 546:
      case 547:
      case 548:
      case 549:
      case 550:
      case 551: itype = XSTORMY16_INSN_XORGRGR; goto done;
      case 552:
      case 553:
      case 554:
      case 555:
      case 556:
      case 557:
      case 558:
      case 559: itype = XSTORMY16_INSN_XORIMM8; goto done;
      case 560:
      case 561:
      case 562:
      case 563:
      case 564:
      case 565:
      case 566:
      case 567: itype = XSTORMY16_INSN_MOVGRGR; goto done;
      case 568:
      case 569:
      case 570:
      case 571:
      case 572:
      case 573:
      case 574:
      case 575: itype = XSTORMY16_INSN_MOVWIMM8; goto done;
      case 584:
      case 585:
      case 586:
      case 587:
      case 588:
      case 589:
      case 590:
      case 591: itype = XSTORMY16_INSN_ADDGRGR; goto done;
      case 600:
      case 601:
      case 602:
      case 603:
      case 604:
      case 605:
      case 606:
      case 607: itype = XSTORMY16_INSN_ADCGRGR; goto done;
      case 616:
      case 617:
      case 618:
      case 619:
      case 620:
      case 621:
      case 622:
      case 623: itype = XSTORMY16_INSN_SUBGRGR; goto done;
      case 632:
      case 633:
      case 634:
      case 635:
      case 636:
      case 637:
      case 638:
      case 639: itype = XSTORMY16_INSN_SBCGRGR; goto done;
      case 648:
      case 649:
      case 650:
      case 651:
      case 652:
      case 653:
      case 654:
      case 655: itype = XSTORMY16_INSN_ADDGRIMM4; goto done;
      case 664:
      case 665:
      case 666:
      case 667:
      case 668:
      case 669:
      case 670:
      case 671: itype = XSTORMY16_INSN_ADCGRIMM4; goto done;
      case 680:
      case 681:
      case 682:
      case 683:
      case 684:
      case 685:
      case 686:
      case 687: itype = XSTORMY16_INSN_SUBGRIMM4; goto done;
      case 696:
      case 697:
      case 698:
      case 699:
      case 700:
      case 701:
      case 702:
      case 703: itype = XSTORMY16_INSN_SBCGRIMM4; goto done;
      case 712:
      case 713:
      case 714:
      case 715:
      case 716:
      case 717:
      case 718:
      case 719: itype = XSTORMY16_INSN_ADDIMM8; goto done;
      case 728:
      case 729:
      case 730:
      case 731:
      case 732:
      case 733:
      case 734:
      case 735: itype = XSTORMY16_INSN_ADCIMM8; goto done;
      case 744:
      case 745:
      case 746:
      case 747:
      case 748:
      case 749:
      case 750:
      case 751: itype = XSTORMY16_INSN_SUBIMM8; goto done;
      case 760:
      case 761:
      case 762:
      case 763:
      case 764:
      case 765:
      case 766:
      case 767: itype = XSTORMY16_INSN_SBCGRIMM8; goto done;
      case 768:
      case 770:
      case 772:
      case 774:
      case 776:
      case 778:
      case 780:
      case 782: itype = XSTORMY16_INSN_MOVGRGRIPOSTINC; goto done;
      case 769:
      case 771:
      case 773:
      case 775:
      case 777:
      case 779:
      case 781:
      case 783:
        if ((entire_insn & 0xfe08f000) == 0x60080000)
          { itype = XSTORMY16_INSN_MOVGRGRIIPOSTINC; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 784:
      case 786:
      case 788:
      case 790:
      case 792:
      case 794:
      case 796:
      case 798: itype = XSTORMY16_INSN_MOVGRIPOSTINCGR; goto done;
      case 785:
      case 787:
      case 789:
      case 791:
      case 793:
      case 795:
      case 797:
      case 799:
        if ((entire_insn & 0xfe08f000) == 0x62080000)
          { itype = XSTORMY16_INSN_MOVGRIIPOSTINCGR; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 800:
      case 802:
      case 804:
      case 806:
      case 808:
      case 810:
      case 812:
      case 814: itype = XSTORMY16_INSN_MOVFGRGRIPOSTINC; goto done;
      case 801:
      case 803:
      case 805:
      case 807:
      case 809:
      case 811:
      case 813:
      case 815:
        if ((entire_insn & 0xfe088000) == 0x64080000)
          { itype = XSTORMY16_INSN_MOVFGRGRIIPOSTINC; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 816:
      case 818:
      case 820:
      case 822:
      case 824:
      case 826:
      case 828:
      case 830: itype = XSTORMY16_INSN_MOVFGRIPOSTINCGR; goto done;
      case 817:
      case 819:
      case 821:
      case 823:
      case 825:
      case 827:
      case 829:
      case 831:
        if ((entire_insn & 0xfe088000) == 0x66080000)
          { itype = XSTORMY16_INSN_MOVFGRIIPOSTINCGR; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 832:
      case 834:
      case 836:
      case 838:
      case 840:
      case 842:
      case 844:
      case 846: itype = XSTORMY16_INSN_MOVGRGRIPREDEC; goto done;
      case 833:
      case 835:
      case 837:
      case 839:
      case 841:
      case 843:
      case 845:
      case 847:
        if ((entire_insn & 0xfe08f000) == 0x68080000)
          { itype = XSTORMY16_INSN_MOVGRGRIIPREDEC; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 848:
      case 850:
      case 852:
      case 854:
      case 856:
      case 858:
      case 860:
      case 862: itype = XSTORMY16_INSN_MOVGRIPREDECGR; goto done;
      case 849:
      case 851:
      case 853:
      case 855:
      case 857:
      case 859:
      case 861:
      case 863:
        if ((entire_insn & 0xfe08f000) == 0x6a080000)
          { itype = XSTORMY16_INSN_MOVGRIIPREDECGR; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 864:
      case 866:
      case 868:
      case 870:
      case 872:
      case 874:
      case 876:
      case 878: itype = XSTORMY16_INSN_MOVFGRGRIPREDEC; goto done;
      case 865:
      case 867:
      case 869:
      case 871:
      case 873:
      case 875:
      case 877:
      case 879:
        if ((entire_insn & 0xfe088000) == 0x6c080000)
          { itype = XSTORMY16_INSN_MOVFGRGRIIPREDEC; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 880:
      case 882:
      case 884:
      case 886:
      case 888:
      case 890:
      case 892:
      case 894: itype = XSTORMY16_INSN_MOVFGRIPREDECGR; goto done;
      case 881:
      case 883:
      case 885:
      case 887:
      case 889:
      case 891:
      case 893:
      case 895:
        if ((entire_insn & 0xfe088000) == 0x6e080000)
          { itype = XSTORMY16_INSN_MOVFGRIIPREDECGR; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 896:
      case 898:
      case 900:
      case 902:
      case 904:
      case 906:
      case 908:
      case 910: itype = XSTORMY16_INSN_MOVGRGRI; goto done;
      case 897:
      case 899:
      case 901:
      case 903:
      case 905:
      case 907:
      case 909:
      case 911:
        if ((entire_insn & 0xfe08f000) == 0x70080000)
          { itype = XSTORMY16_INSN_MOVGRGRII; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 912:
      case 914:
      case 916:
      case 918:
      case 920:
      case 922:
      case 924:
      case 926: itype = XSTORMY16_INSN_MOVGRIGR; goto done;
      case 913:
      case 915:
      case 917:
      case 919:
      case 921:
      case 923:
      case 925:
      case 927:
        if ((entire_insn & 0xfe08f000) == 0x72080000)
          { itype = XSTORMY16_INSN_MOVGRIIGR; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 928:
      case 930:
      case 932:
      case 934:
      case 936:
      case 938:
      case 940:
      case 942: itype = XSTORMY16_INSN_MOVFGRGRI; goto done;
      case 929:
      case 931:
      case 933:
      case 935:
      case 937:
      case 939:
      case 941:
      case 943:
        if ((entire_insn & 0xfe088000) == 0x74080000)
          { itype = XSTORMY16_INSN_MOVFGRGRII; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 944:
      case 946:
      case 948:
      case 950:
      case 952:
      case 954:
      case 956:
      case 958: itype = XSTORMY16_INSN_MOVFGRIGR; goto done;
      case 945:
      case 947:
      case 949:
      case 951:
      case 953:
      case 955:
      case 957:
      case 959:
        if ((entire_insn & 0xfe088000) == 0x76080000)
          { itype = XSTORMY16_INSN_MOVFGRIIGR; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 960:
      case 961:
      case 962:
      case 963:
      case 964:
      case 965:
      case 966:
      case 967:
      case 968:
      case 969:
      case 970:
      case 971:
      case 972:
      case 973:
      case 974:
      case 975: itype = XSTORMY16_INSN_MOVLMEMIMM; goto done;
      case 976:
      case 977:
      case 978:
      case 979:
      case 980:
      case 981:
      case 982:
      case 983:
      case 984:
      case 985:
      case 986:
      case 987:
      case 988:
      case 989:
      case 990:
      case 991: itype = XSTORMY16_INSN_MOVHMEMIMM; goto done;
      case 992:
      case 993:
      case 994:
      case 995:
      case 996:
      case 997:
      case 998:
      case 999:
        if ((entire_insn & 0xff008000) == 0x7c000000)
          { itype = XSTORMY16_INSN_BNLMEMIMM; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 1000:
      case 1001:
      case 1002:
      case 1003:
      case 1004:
      case 1005:
      case 1006:
      case 1007:
        if ((entire_insn & 0xff008000) == 0x7d000000)
          { itype = XSTORMY16_INSN_BPLMEMIMM; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 1008:
      case 1009:
      case 1010:
      case 1011:
      case 1012:
      case 1013:
      case 1014:
      case 1015:
        if ((entire_insn & 0xff008000) == 0x7e000000)
          { itype = XSTORMY16_INSN_BNHMEMIMM; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 1016:
      case 1017:
      case 1018:
      case 1019:
      case 1020:
      case 1021:
      case 1022:
      case 1023:
        if ((entire_insn & 0xff008000) == 0x7f000000)
          { itype = XSTORMY16_INSN_BPHMEMIMM; goto done; }
        itype = XSTORMY16_INSN_X_INVALID; goto done;
      case 1024:
      case 1025:
      case 1026:
      case 1027:
      case 1028:
      case 1029:
      case 1030:
      case 1031:
      case 1032:
      case 1033:
      case 1034:
      case 1035:
      case 1036:
      case 1037:
      case 1038:
      case 1039:
      case 1040:
      case 1041:
      case 1042:
      case 1043:
      case 1044:
      case 1045:
      case 1046:
      case 1047:
      case 1048:
      case 1049:
      case 1050:
      case 1051:
      case 1052:
      case 1053:
      case 1054:
      case 1055:
      case 1056:
      case 1057:
      case 1058:
      case 1059:
      case 1060:
      case 1061:
      case 1062:
      case 1063:
      case 1064:
      case 1065:
      case 1066:
      case 1067:
      case 1068:
      case 1069:
      case 1070:
      case 1071:
      case 1072:
      case 1073:
      case 1074:
      case 1075:
      case 1076:
      case 1077:
      case 1078:
      case 1079:
      case 1080:
      case 1081:
      case 1082:
      case 1083:
      case 1084:
      case 1085:
      case 1086:
      case 1087:
      case 1088:
      case 1089:
      case 1090:
      case 1091:
      case 1092:
      case 1093:
      case 1094:
      case 1095:
      case 1096:
      case 1097:
      case 1098:
      case 1099:
      case 1100:
      case 1101:
      case 1102:
      case 1103:
      case 1104:
      case 1105:
      case 1106:
      case 1107:
      case 1108:
      case 1109:
      case 1110:
      case 1111:
      case 1112:
      case 1113:
      case 1114:
      case 1115:
      case 1116:
      case 1117:
      case 1118:
      case 1119:
      case 1120:
      case 1121:
      case 1122:
      case 1123:
      case 1124:
      case 1125:
      case 1126:
      case 1127:
      case 1128:
      case 1129:
      case 1130:
      case 1131:
      case 1132:
      case 1133:
      case 1134:
      case 1135:
      case 1136:
      case 1137:
      case 1138:
      case 1139:
      case 1140:
      case 1141:
      case 1142:
      case 1143:
      case 1144:
      case 1145:
      case 1146:
      case 1147:
      case 1148:
      case 1149:
      case 1150:
      case 1151: itype = XSTORMY16_INSN_MOVLGRMEM; goto done;
      case 1152:
      case 1153:
      case 1154:
      case 1155:
      case 1156:
      case 1157:
      case 1158:
      case 1159:
      case 1160:
      case 1161:
      case 1162:
      case 1163:
      case 1164:
      case 1165:
      case 1166:
      case 1167:
      case 1168:
      case 1169:
      case 1170:
      case 1171:
      case 1172:
      case 1173:
      case 1174:
      case 1175:
      case 1176:
      case 1177:
      case 1178:
      case 1179:
      case 1180:
      case 1181:
      case 1182:
      case 1183:
      case 1184:
      case 1185:
      case 1186:
      case 1187:
      case 1188:
      case 1189:
      case 1190:
      case 1191:
      case 1192:
      case 1193:
      case 1194:
      case 1195:
      case 1196:
      case 1197:
      case 1198:
      case 1199:
      case 1200:
      case 1201:
      case 1202:
      case 1203:
      case 1204:
      case 1205:
      case 1206:
      case 1207:
      case 1208:
      case 1209:
      case 1210:
      case 1211:
      case 1212:
      case 1213:
      case 1214:
      case 1215:
      case 1216:
      case 1217:
      case 1218:
      case 1219:
      case 1220:
      case 1221:
      case 1222:
      case 1223:
      case 1224:
      case 1225:
      case 1226:
      case 1227:
      case 1228:
      case 1229:
      case 1230:
      case 1231:
      case 1232:
      case 1233:
      case 1234:
      case 1235:
      case 1236:
      case 1237:
      case 1238:
      case 1239:
      case 1240:
      case 1241:
      case 1242:
      case 1243:
      case 1244:
      case 1245:
      case 1246:
      case 1247:
      case 1248:
      case 1249:
      case 1250:
      case 1251:
      case 1252:
      case 1253:
      case 1254:
      case 1255:
      case 1256:
      case 1257:
      case 1258:
      case 1259:
      case 1260:
      case 1261:
      case 1262:
      case 1263:
      case 1264:
      case 1265:
      case 1266:
      case 1267:
      case 1268:
      case 1269:
      case 1270:
      case 1271:
      case 1272:
      case 1273:
      case 1274:
      case 1275:
      case 1276:
      case 1277:
      case 1278:
      case 1279: itype = XSTORMY16_INSN_MOVLMEMGR; goto done;
      case 1280:
      case 1281:
      case 1282:
      case 1283:
      case 1284:
      case 1285:
      case 1286:
      case 1287:
      case 1288:
      case 1289:
      case 1290:
      case 1291:
      case 1292:
      case 1293:
      case 1294:
      case 1295:
      case 1296:
      case 1297:
      case 1298:
      case 1299:
      case 1300:
      case 1301:
      case 1302:
      case 1303:
      case 1304:
      case 1305:
      case 1306:
      case 1307:
      case 1308:
      case 1309:
      case 1310:
      case 1311:
      case 1312:
      case 1313:
      case 1314:
      case 1315:
      case 1316:
      case 1317:
      case 1318:
      case 1319:
      case 1320:
      case 1321:
      case 1322:
      case 1323:
      case 1324:
      case 1325:
      case 1326:
      case 1327:
      case 1328:
      case 1329:
      case 1330:
      case 1331:
      case 1332:
      case 1333:
      case 1334:
      case 1335:
      case 1336:
      case 1337:
      case 1338:
      case 1339:
      case 1340:
      case 1341:
      case 1342:
      case 1343:
      case 1344:
      case 1345:
      case 1346:
      case 1347:
      case 1348:
      case 1349:
      case 1350:
      case 1351:
      case 1352:
      case 1353:
      case 1354:
      case 1355:
      case 1356:
      case 1357:
      case 1358:
      case 1359:
      case 1360:
      case 1361:
      case 1362:
      case 1363:
      case 1364:
      case 1365:
      case 1366:
      case 1367:
      case 1368:
      case 1369:
      case 1370:
      case 1371:
      case 1372:
      case 1373:
      case 1374:
      case 1375:
      case 1376:
      case 1377:
      case 1378:
      case 1379:
      case 1380:
      case 1381:
      case 1382:
      case 1383:
      case 1384:
      case 1385:
      case 1386:
      case 1387:
      case 1388:
      case 1389:
      case 1390:
      case 1391:
      case 1392:
      case 1393:
      case 1394:
      case 1395:
      case 1396:
      case 1397:
      case 1398:
      case 1399:
      case 1400:
      case 1401:
      case 1402:
      case 1403:
      case 1404:
      case 1405:
      case 1406:
      case 1407: itype = XSTORMY16_INSN_MOVHGRMEM; goto done;
      case 1408:
      case 1409:
      case 1410:
      case 1411:
      case 1412:
      case 1413:
      case 1414:
      case 1415:
      case 1416:
      case 1417:
      case 1418:
      case 1419:
      case 1420:
      case 1421:
      case 1422:
      case 1423:
      case 1424:
      case 1425:
      case 1426:
      case 1427:
      case 1428:
      case 1429:
      case 1430:
      case 1431:
      case 1432:
      case 1433:
      case 1434:
      case 1435:
      case 1436:
      case 1437:
      case 1438:
      case 1439:
      case 1440:
      case 1441:
      case 1442:
      case 1443:
      case 1444:
      case 1445:
      case 1446:
      case 1447:
      case 1448:
      case 1449:
      case 1450:
      case 1451:
      case 1452:
      case 1453:
      case 1454:
      case 1455:
      case 1456:
      case 1457:
      case 1458:
      case 1459:
      case 1460:
      case 1461:
      case 1462:
      case 1463:
      case 1464:
      case 1465:
      case 1466:
      case 1467:
      case 1468:
      case 1469:
      case 1470:
      case 1471:
      case 1472:
      case 1473:
      case 1474:
      case 1475:
      case 1476:
      case 1477:
      case 1478:
      case 1479:
      case 1480:
      case 1481:
      case 1482:
      case 1483:
      case 1484:
      case 1485:
      case 1486:
      case 1487:
      case 1488:
      case 1489:
      case 1490:
      case 1491:
      case 1492:
      case 1493:
      case 1494:
      case 1495:
      case 1496:
      case 1497:
      case 1498:
      case 1499:
      case 1500:
      case 1501:
      case 1502:
      case 1503:
      case 1504:
      case 1505:
      case 1506:
      case 1507:
      case 1508:
      case 1509:
      case 1510:
      case 1511:
      case 1512:
      case 1513:
      case 1514:
      case 1515:
      case 1516:
      case 1517:
      case 1518:
      case 1519:
      case 1520:
      case 1521:
      case 1522:
      case 1523:
      case 1524:
      case 1525:
      case 1526:
      case 1527:
      case 1528:
      case 1529:
      case 1530:
      case 1531:
      case 1532:
      case 1533:
      case 1534:
      case 1535: itype = XSTORMY16_INSN_MOVHMEMGR; goto done;
      case 1536:
      case 1537:
      case 1538:
      case 1539:
      case 1540:
      case 1541:
      case 1542:
      case 1543:
      case 1544:
      case 1545:
      case 1546:
      case 1547:
      case 1548:
      case 1549:
      case 1550:
      case 1551:
      case 1552:
      case 1553:
      case 1554:
      case 1555:
      case 1556:
      case 1557:
      case 1558:
      case 1559:
      case 1560:
      case 1561:
      case 1562:
      case 1563:
      case 1564:
      case 1565:
      case 1566:
      case 1567:
      case 1568:
      case 1569:
      case 1570:
      case 1571:
      case 1572:
      case 1573:
      case 1574:
      case 1575:
      case 1576:
      case 1577:
      case 1578:
      case 1579:
      case 1580:
      case 1581:
      case 1582:
      case 1583:
      case 1584:
      case 1585:
      case 1586:
      case 1587:
      case 1588:
      case 1589:
      case 1590:
      case 1591:
      case 1592:
      case 1593:
      case 1594:
      case 1595:
      case 1596:
      case 1597:
      case 1598:
      case 1599:
      case 1600:
      case 1601:
      case 1602:
      case 1603:
      case 1604:
      case 1605:
      case 1606:
      case 1607:
      case 1608:
      case 1609:
      case 1610:
      case 1611:
      case 1612:
      case 1613:
      case 1614:
      case 1615:
      case 1616:
      case 1617:
      case 1618:
      case 1619:
      case 1620:
      case 1621:
      case 1622:
      case 1623:
      case 1624:
      case 1625:
      case 1626:
      case 1627:
      case 1628:
      case 1629:
      case 1630:
      case 1631:
      case 1632:
      case 1633:
      case 1634:
      case 1635:
      case 1636:
      case 1637:
      case 1638:
      case 1639:
      case 1640:
      case 1641:
      case 1642:
      case 1643:
      case 1644:
      case 1645:
      case 1646:
      case 1647:
      case 1648:
      case 1649:
      case 1650:
      case 1651:
      case 1652:
      case 1653:
      case 1654:
      case 1655:
      case 1656:
      case 1657:
      case 1658:
      case 1659:
      case 1660:
      case 1661:
      case 1662:
      case 1663: itype = XSTORMY16_INSN_BCCIMM16; goto done;
      case 1664:
      case 1665:
      case 1666:
      case 1667:
      case 1668:
      case 1669:
      case 1670:
      case 1671:
      case 1672:
      case 1673:
      case 1674:
      case 1675:
      case 1676:
      case 1677:
      case 1678:
      case 1679:
      case 1680:
      case 1681:
      case 1682:
      case 1683:
      case 1684:
      case 1685:
      case 1686:
      case 1687:
      case 1688:
      case 1689:
      case 1690:
      case 1691:
      case 1692:
      case 1693:
      case 1694:
      case 1695:
      case 1696:
      case 1697:
      case 1698:
      case 1699:
      case 1700:
      case 1701:
      case 1702:
      case 1703:
      case 1704:
      case 1705:
      case 1706:
      case 1707:
      case 1708:
      case 1709:
      case 1710:
      case 1711:
      case 1712:
      case 1713:
      case 1714:
      case 1715:
      case 1716:
      case 1717:
      case 1718:
      case 1719:
      case 1720:
      case 1721:
      case 1722:
      case 1723:
      case 1724:
      case 1725:
      case 1726:
      case 1727:
      case 1728:
      case 1729:
      case 1730:
      case 1731:
      case 1732:
      case 1733:
      case 1734:
      case 1735:
      case 1736:
      case 1737:
      case 1738:
      case 1739:
      case 1740:
      case 1741:
      case 1742:
      case 1743:
      case 1744:
      case 1745:
      case 1746:
      case 1747:
      case 1748:
      case 1749:
      case 1750:
      case 1751:
      case 1752:
      case 1753:
      case 1754:
      case 1755:
      case 1756:
      case 1757:
      case 1758:
      case 1759:
      case 1760:
      case 1761:
      case 1762:
      case 1763:
      case 1764:
      case 1765:
      case 1766:
      case 1767:
      case 1768:
      case 1769:
      case 1770:
      case 1771:
      case 1772:
      case 1773:
      case 1774:
      case 1775:
      case 1776:
      case 1777:
      case 1778:
      case 1779:
      case 1780:
      case 1781:
      case 1782:
      case 1783:
      case 1784:
      case 1785:
      case 1786:
      case 1787:
      case 1788:
      case 1789:
      case 1790:
      case 1791: itype = XSTORMY16_INSN_BCC; goto done;
      case 1792:
      case 1793:
      case 1794:
      case 1795:
      case 1796:
      case 1797:
      case 1798:
      case 1799:
      case 1808:
      case 1809:
      case 1810:
      case 1811:
      case 1812:
      case 1813:
      case 1814:
      case 1815:
      case 1824:
      case 1825:
      case 1826:
      case 1827:
      case 1828:
      case 1829:
      case 1830:
      case 1831:
      case 1840:
      case 1841:
      case 1842:
      case 1843:
      case 1844:
      case 1845:
      case 1846:
      case 1847:
      case 1856:
      case 1857:
      case 1858:
      case 1859:
      case 1860:
      case 1861:
      case 1862:
      case 1863:
      case 1872:
      case 1873:
      case 1874:
      case 1875:
      case 1876:
      case 1877:
      case 1878:
      case 1879:
      case 1888:
      case 1889:
      case 1890:
      case 1891:
      case 1892:
      case 1893:
      case 1894:
      case 1895:
      case 1904:
      case 1905:
      case 1906:
      case 1907:
      case 1908:
      case 1909:
      case 1910:
      case 1911: itype = XSTORMY16_INSN_CLR1LMEMIMM; goto done;
      case 1800:
      case 1801:
      case 1802:
      case 1803:
      case 1804:
      case 1805:
      case 1806:
      case 1807:
      case 1816:
      case 1817:
      case 1818:
      case 1819:
      case 1820:
      case 1821:
      case 1822:
      case 1823:
      case 1832:
      case 1833:
      case 1834:
      case 1835:
      case 1836:
      case 1837:
      case 1838:
      case 1839:
      case 1848:
      case 1849:
      case 1850:
      case 1851:
      case 1852:
      case 1853:
      case 1854:
      case 1855:
      case 1864:
      case 1865:
      case 1866:
      case 1867:
      case 1868:
      case 1869:
      case 1870:
      case 1871:
      case 1880:
      case 1881:
      case 1882:
      case 1883:
      case 1884:
      case 1885:
      case 1886:
      case 1887:
      case 1896:
      case 1897:
      case 1898:
      case 1899:
      case 1900:
      case 1901:
      case 1902:
      case 1903:
      case 1912:
      case 1913:
      case 1914:
      case 1915:
      case 1916:
      case 1917:
      case 1918:
      case 1919: itype = XSTORMY16_INSN_SET1LMEMIMM; goto done;
      case 1920:
      case 1921:
      case 1922:
      case 1923:
      case 1924:
      case 1925:
      case 1926:
      case 1927:
      case 1936:
      case 1937:
      case 1938:
      case 1939:
      case 1940:
      case 1941:
      case 1942:
      case 1943:
      case 1952:
      case 1953:
      case 1954:
      case 1955:
      case 1956:
      case 1957:
      case 1958:
      case 1959:
      case 1968:
      case 1969:
      case 1970:
      case 1971:
      case 1972:
      case 1973:
      case 1974:
      case 1975:
      case 1984:
      case 1985:
      case 1986:
      case 1987:
      case 1988:
      case 1989:
      case 1990:
      case 1991:
      case 2000:
      case 2001:
      case 2002:
      case 2003:
      case 2004:
      case 2005:
      case 2006:
      case 2007:
      case 2016:
      case 2017:
      case 2018:
      case 2019:
      case 2020:
      case 2021:
      case 2022:
      case 2023:
      case 2032:
      case 2033:
      case 2034:
      case 2035:
      case 2036:
      case 2037:
      case 2038:
      case 2039: itype = XSTORMY16_INSN_CLR1HMEMIMM; goto done;
      case 1928:
      case 1929:
      case 1930:
      case 1931:
      case 1932:
      case 1933:
      case 1934:
      case 1935:
      case 1944:
      case 1945:
      case 1946:
      case 1947:
      case 1948:
      case 1949:
      case 1950:
      case 1951:
      case 1960:
      case 1961:
      case 1962:
      case 1963:
      case 1964:
      case 1965:
      case 1966:
      case 1967:
      case 1976:
      case 1977:
      case 1978:
      case 1979:
      case 1980:
      case 1981:
      case 1982:
      case 1983:
      case 1992:
      case 1993:
      case 1994:
      case 1995:
      case 1996:
      case 1997:
      case 1998:
      case 1999:
      case 2008:
      case 2009:
      case 2010:
      case 2011:
      case 2012:
      case 2013:
      case 2014:
      case 2015:
      case 2024:
      case 2025:
      case 2026:
      case 2027:
      case 2028:
      case 2029:
      case 2030:
      case 2031:
      case 2040:
      case 2041:
      case 2042:
      case 2043:
      case 2044:
      case 2045:
      case 2046:
      case 2047: itype = XSTORMY16_INSN_SET1HMEMIMM; goto done;
      default: itype = XSTORMY16_INSN_X_INVALID; goto done;
      }
    }
  }

  /* Extraction is defered until the semantic code.  */

 done:
  return &xstormy16_insn_data[itype];
}
