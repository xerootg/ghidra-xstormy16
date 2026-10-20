/* CPU family header for xstormy16.

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

#ifndef CPU_XSTORMY16_H
#define CPU_XSTORMY16_H

/* Maximum number of instructions that are fetched at a time.
   This is for LIW type instructions sets (e.g. m32r).  */
#define MAX_LIW_INSNS 1

/* Maximum number of instructions that can be executed in parallel.  */
#define MAX_PARALLEL_INSNS 1

/* The size of an "int" needed to hold an instruction word.
   This is usually 32 bits, but some architectures needs 64 bits.  */
typedef CGEN_INSN_INT CGEN_INSN_WORD;

#include "cgen-engine.h"

/* CPU state information.  */
typedef struct {
  /* Hardware elements.  */
  struct {
  /* program counter */
  USI h_pc;
#define GET_H_PC() CPU (h_pc)
#define SET_H_PC(x) \
do { \
h_pc_set_handler (current_cpu, (x));\
;} while (0)
  /* registers */
  SI h_gr[16];
#define GET_H_GR(index) ((65535) & (CPU (h_gr[index])))
#define SET_H_GR(index, x) \
do { \
h_gr_set_handler (current_cpu, (index), (x));\
;} while (0)
  } hardware;
#define CPU_CGEN_HW(cpu) (& XSTORMY16_SIM_CPU (cpu)->cpu_data.hardware)
} XSTORMY16_CPU_DATA;

/* Virtual regs.  */

#define GET_H_RB(index) GET_H_GR (((index) + (8)))
#define SET_H_RB(index, x) \
do { \
SET_H_GR ((((index)) + (8)), (x));\
;} while (0)
#define GET_H_RBJ(index) GET_H_GR (((index) + (8)))
#define SET_H_RBJ(index, x) \
do { \
SET_H_GR ((((index)) + (8)), (x));\
;} while (0)
#define GET_H_RPSW() ((15) & (SRLSI (GET_H_GR (((UINT) 14)), 12)))
#define SET_H_RPSW(x) \
do { \
SET_H_GR (((UINT) 14), ORSI (ANDSI (GET_H_GR (((UINT) 14)), 4095), SLLHI ((x), 12)));\
;} while (0)
#define GET_H_Z8() ((1) & (SRLSI (GET_H_GR (((UINT) 14)), 0)))
#define SET_H_Z8(x) \
do { \
SET_H_GR (((UINT) 14), ORSI (ANDSI (GET_H_GR (((UINT) 14)), INVHI (SLLHI (1, 0))), SLLHI ((x), 0)));\
;} while (0)
#define GET_H_Z16() ((1) & (SRLSI (GET_H_GR (((UINT) 14)), 1)))
#define SET_H_Z16(x) \
do { \
SET_H_GR (((UINT) 14), ORSI (ANDSI (GET_H_GR (((UINT) 14)), INVHI (SLLHI (1, 1))), SLLHI ((x), 1)));\
;} while (0)
#define GET_H_CY() ((1) & (SRLSI (GET_H_GR (((UINT) 14)), 2)))
#define SET_H_CY(x) \
do { \
SET_H_GR (((UINT) 14), ORSI (ANDSI (GET_H_GR (((UINT) 14)), INVHI (SLLHI (1, 2))), SLLHI ((x), 2)));\
;} while (0)
#define GET_H_HC() ((1) & (SRLSI (GET_H_GR (((UINT) 14)), 3)))
#define SET_H_HC(x) \
do { \
SET_H_GR (((UINT) 14), ORSI (ANDSI (GET_H_GR (((UINT) 14)), INVHI (SLLHI (1, 3))), SLLHI ((x), 3)));\
;} while (0)
#define GET_H_OV() ((1) & (SRLSI (GET_H_GR (((UINT) 14)), 4)))
#define SET_H_OV(x) \
do { \
SET_H_GR (((UINT) 14), ORSI (ANDSI (GET_H_GR (((UINT) 14)), INVHI (SLLHI (1, 4))), SLLHI ((x), 4)));\
;} while (0)
#define GET_H_PT() ((1) & (SRLSI (GET_H_GR (((UINT) 14)), 5)))
#define SET_H_PT(x) \
do { \
SET_H_GR (((UINT) 14), ORSI (ANDSI (GET_H_GR (((UINT) 14)), INVHI (SLLHI (1, 5))), SLLHI ((x), 5)));\
;} while (0)
#define GET_H_S() ((1) & (SRLSI (GET_H_GR (((UINT) 14)), 6)))
#define SET_H_S(x) \
do { \
SET_H_GR (((UINT) 14), ORSI (ANDSI (GET_H_GR (((UINT) 14)), INVHI (SLLHI (1, 6))), SLLHI ((x), 6)));\
;} while (0)

/* Cover fns for register access.  */
USI xstormy16_h_pc_get (SIM_CPU *);
void xstormy16_h_pc_set (SIM_CPU *, USI);
SI xstormy16_h_gr_get (SIM_CPU *, UINT);
void xstormy16_h_gr_set (SIM_CPU *, UINT, SI);
SI xstormy16_h_Rb_get (SIM_CPU *, UINT);
void xstormy16_h_Rb_set (SIM_CPU *, UINT, SI);
SI xstormy16_h_Rbj_get (SIM_CPU *, UINT);
void xstormy16_h_Rbj_set (SIM_CPU *, UINT, SI);
SI xstormy16_h_Rpsw_get (SIM_CPU *);
void xstormy16_h_Rpsw_set (SIM_CPU *, SI);
SI xstormy16_h_z8_get (SIM_CPU *);
void xstormy16_h_z8_set (SIM_CPU *, SI);
SI xstormy16_h_z16_get (SIM_CPU *);
void xstormy16_h_z16_set (SIM_CPU *, SI);
SI xstormy16_h_cy_get (SIM_CPU *);
void xstormy16_h_cy_set (SIM_CPU *, SI);
SI xstormy16_h_hc_get (SIM_CPU *);
void xstormy16_h_hc_set (SIM_CPU *, SI);
SI xstormy16_h_ov_get (SIM_CPU *);
void xstormy16_h_ov_set (SIM_CPU *, SI);
SI xstormy16_h_pt_get (SIM_CPU *);
void xstormy16_h_pt_set (SIM_CPU *, SI);
SI xstormy16_h_s_get (SIM_CPU *);
void xstormy16_h_s_set (SIM_CPU *, SI);

/* These must be hand-written.  */
extern CPUREG_FETCH_FN xstormy16_fetch_register;
extern CPUREG_STORE_FN xstormy16_store_register;

/* The ARGBUF struct.  */
struct argbuf {
  /* These are the baseclass definitions.  */
  IADDR addr;
  const IDESC *idesc;
  char trace_p;
  char profile_p;
  /* ??? Temporary hack for skip insns.  */
  char skip_count;
  char unused;
  /* cpu specific data follows */
  CGEN_INSN_WORD insn;
  int written;
};

/* A cached insn.

   ??? SCACHE used to contain more than just argbuf.  We could delete the
   type entirely and always just use ARGBUF, but for future concerns and as
   a level of abstraction it is left in.  */

struct scache {
  struct argbuf argbuf;
};

/* Macros to simplify extraction, reading and semantic code.
   These define and assign the local vars that contain the insn's fields.  */

#define EXTRACT_IFMT_EMPTY_VARS \
  unsigned int length;
#define EXTRACT_IFMT_EMPTY_CODE \
  length = 0; \

#define EXTRACT_IFMT_MOVLMEMIMM_VARS \
  UINT f_op1; \
  UINT f_op2a; \
  UINT f_op2m; \
  UINT f_lmem8; \
  UINT f_imm16; \
  unsigned int length;
#define EXTRACT_IFMT_MOVLMEMIMM_CODE \
  length = 4; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 32, 0, 4); \
  f_op2a = EXTRACT_MSB0_UINT (insn, 32, 4, 3); \
  f_op2m = EXTRACT_MSB0_UINT (insn, 32, 7, 1); \
  f_lmem8 = EXTRACT_MSB0_UINT (insn, 32, 8, 8); \
  f_imm16 = EXTRACT_MSB0_UINT (insn, 32, 16, 16); \

#define EXTRACT_IFMT_MOVHMEMIMM_VARS \
  UINT f_op1; \
  UINT f_op2a; \
  UINT f_op2m; \
  HI f_hmem8; \
  UINT f_imm16; \
  unsigned int length;
#define EXTRACT_IFMT_MOVHMEMIMM_CODE \
  length = 4; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 32, 0, 4); \
  f_op2a = EXTRACT_MSB0_UINT (insn, 32, 4, 3); \
  f_op2m = EXTRACT_MSB0_UINT (insn, 32, 7, 1); \
  f_hmem8 = ((EXTRACT_MSB0_UINT (insn, 32, 8, 8)) + (32512)); \
  f_imm16 = EXTRACT_MSB0_UINT (insn, 32, 16, 16); \

#define EXTRACT_IFMT_MOVLGRMEM_VARS \
  UINT f_op1; \
  UINT f_Rm; \
  UINT f_op2m; \
  UINT f_lmem8; \
  unsigned int length;
#define EXTRACT_IFMT_MOVLGRMEM_CODE \
  length = 2; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 16, 0, 4); \
  f_Rm = EXTRACT_MSB0_UINT (insn, 16, 4, 3); \
  f_op2m = EXTRACT_MSB0_UINT (insn, 16, 7, 1); \
  f_lmem8 = EXTRACT_MSB0_UINT (insn, 16, 8, 8); \

#define EXTRACT_IFMT_MOVHGRMEM_VARS \
  UINT f_op1; \
  UINT f_Rm; \
  UINT f_op2m; \
  HI f_hmem8; \
  unsigned int length;
#define EXTRACT_IFMT_MOVHGRMEM_CODE \
  length = 2; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 16, 0, 4); \
  f_Rm = EXTRACT_MSB0_UINT (insn, 16, 4, 3); \
  f_op2m = EXTRACT_MSB0_UINT (insn, 16, 7, 1); \
  f_hmem8 = ((EXTRACT_MSB0_UINT (insn, 16, 8, 8)) + (32512)); \

#define EXTRACT_IFMT_MOVGRGRI_VARS \
  UINT f_op1; \
  UINT f_op2a; \
  UINT f_op2m; \
  UINT f_Rs; \
  UINT f_op4m; \
  UINT f_Rdm; \
  unsigned int length;
#define EXTRACT_IFMT_MOVGRGRI_CODE \
  length = 2; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 16, 0, 4); \
  f_op2a = EXTRACT_MSB0_UINT (insn, 16, 4, 3); \
  f_op2m = EXTRACT_MSB0_UINT (insn, 16, 7, 1); \
  f_Rs = EXTRACT_MSB0_UINT (insn, 16, 8, 4); \
  f_op4m = EXTRACT_MSB0_UINT (insn, 16, 12, 1); \
  f_Rdm = EXTRACT_MSB0_UINT (insn, 16, 13, 3); \

#define EXTRACT_IFMT_MOVGRGRII_VARS \
  UINT f_op1; \
  UINT f_op2a; \
  UINT f_op2m; \
  UINT f_Rs; \
  UINT f_op4m; \
  UINT f_Rdm; \
  UINT f_op5; \
  INT f_imm12; \
  unsigned int length;
#define EXTRACT_IFMT_MOVGRGRII_CODE \
  length = 4; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 32, 0, 4); \
  f_op2a = EXTRACT_MSB0_UINT (insn, 32, 4, 3); \
  f_op2m = EXTRACT_MSB0_UINT (insn, 32, 7, 1); \
  f_Rs = EXTRACT_MSB0_UINT (insn, 32, 8, 4); \
  f_op4m = EXTRACT_MSB0_UINT (insn, 32, 12, 1); \
  f_Rdm = EXTRACT_MSB0_UINT (insn, 32, 13, 3); \
  f_op5 = EXTRACT_MSB0_UINT (insn, 32, 16, 4); \
  f_imm12 = EXTRACT_MSB0_SINT (insn, 32, 20, 12); \

#define EXTRACT_IFMT_MOVGRGR_VARS \
  UINT f_op1; \
  UINT f_op2; \
  UINT f_Rs; \
  UINT f_Rd; \
  unsigned int length;
#define EXTRACT_IFMT_MOVGRGR_CODE \
  length = 2; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 16, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 16, 4, 4); \
  f_Rs = EXTRACT_MSB0_UINT (insn, 16, 8, 4); \
  f_Rd = EXTRACT_MSB0_UINT (insn, 16, 12, 4); \

#define EXTRACT_IFMT_MOVWIMM8_VARS \
  UINT f_op1; \
  UINT f_op2; \
  UINT f_imm8; \
  unsigned int length;
#define EXTRACT_IFMT_MOVWIMM8_CODE \
  length = 2; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 16, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 16, 4, 4); \
  f_imm8 = EXTRACT_MSB0_UINT (insn, 16, 8, 8); \

#define EXTRACT_IFMT_MOVWGRIMM8_VARS \
  UINT f_op1; \
  UINT f_Rm; \
  UINT f_op2m; \
  UINT f_imm8; \
  unsigned int length;
#define EXTRACT_IFMT_MOVWGRIMM8_CODE \
  length = 2; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 16, 0, 4); \
  f_Rm = EXTRACT_MSB0_UINT (insn, 16, 4, 3); \
  f_op2m = EXTRACT_MSB0_UINT (insn, 16, 7, 1); \
  f_imm8 = EXTRACT_MSB0_UINT (insn, 16, 8, 8); \

#define EXTRACT_IFMT_MOVWGRIMM16_VARS \
  UINT f_op1; \
  UINT f_op2; \
  UINT f_op3; \
  UINT f_Rd; \
  UINT f_imm16; \
  unsigned int length;
#define EXTRACT_IFMT_MOVWGRIMM16_CODE \
  length = 4; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 32, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 32, 4, 4); \
  f_op3 = EXTRACT_MSB0_UINT (insn, 32, 8, 4); \
  f_Rd = EXTRACT_MSB0_UINT (insn, 32, 12, 4); \
  f_imm16 = EXTRACT_MSB0_UINT (insn, 32, 16, 16); \

#define EXTRACT_IFMT_MOVLOWGR_VARS \
  UINT f_op1; \
  UINT f_op2; \
  UINT f_op3; \
  UINT f_Rd; \
  unsigned int length;
#define EXTRACT_IFMT_MOVLOWGR_CODE \
  length = 2; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 16, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 16, 4, 4); \
  f_op3 = EXTRACT_MSB0_UINT (insn, 16, 8, 4); \
  f_Rd = EXTRACT_MSB0_UINT (insn, 16, 12, 4); \

#define EXTRACT_IFMT_MOVFGRGRII_VARS \
  UINT f_op1; \
  UINT f_op2a; \
  UINT f_op2m; \
  UINT f_Rs; \
  UINT f_op4m; \
  UINT f_Rdm; \
  UINT f_op5a; \
  UINT f_Rb; \
  INT f_imm12; \
  unsigned int length;
#define EXTRACT_IFMT_MOVFGRGRII_CODE \
  length = 4; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 32, 0, 4); \
  f_op2a = EXTRACT_MSB0_UINT (insn, 32, 4, 3); \
  f_op2m = EXTRACT_MSB0_UINT (insn, 32, 7, 1); \
  f_Rs = EXTRACT_MSB0_UINT (insn, 32, 8, 4); \
  f_op4m = EXTRACT_MSB0_UINT (insn, 32, 12, 1); \
  f_Rdm = EXTRACT_MSB0_UINT (insn, 32, 13, 3); \
  f_op5a = EXTRACT_MSB0_UINT (insn, 32, 16, 1); \
  f_Rb = EXTRACT_MSB0_UINT (insn, 32, 17, 3); \
  f_imm12 = EXTRACT_MSB0_SINT (insn, 32, 20, 12); \

#define EXTRACT_IFMT_ADDGRIMM4_VARS \
  UINT f_op1; \
  UINT f_op2; \
  UINT f_imm4; \
  UINT f_Rd; \
  unsigned int length;
#define EXTRACT_IFMT_ADDGRIMM4_CODE \
  length = 2; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 16, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 16, 4, 4); \
  f_imm4 = EXTRACT_MSB0_UINT (insn, 16, 8, 4); \
  f_Rd = EXTRACT_MSB0_UINT (insn, 16, 12, 4); \

#define EXTRACT_IFMT_INCGRIMM2_VARS \
  UINT f_op1; \
  UINT f_op2; \
  UINT f_op3a; \
  UINT f_imm2; \
  UINT f_Rd; \
  unsigned int length;
#define EXTRACT_IFMT_INCGRIMM2_CODE \
  length = 2; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 16, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 16, 4, 4); \
  f_op3a = EXTRACT_MSB0_UINT (insn, 16, 8, 2); \
  f_imm2 = EXTRACT_MSB0_UINT (insn, 16, 10, 2); \
  f_Rd = EXTRACT_MSB0_UINT (insn, 16, 12, 4); \

#define EXTRACT_IFMT_SET1LMEMIMM_VARS \
  UINT f_op1; \
  UINT f_imm3; \
  UINT f_op2m; \
  UINT f_lmem8; \
  unsigned int length;
#define EXTRACT_IFMT_SET1LMEMIMM_CODE \
  length = 2; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 16, 0, 4); \
  f_imm3 = EXTRACT_MSB0_UINT (insn, 16, 4, 3); \
  f_op2m = EXTRACT_MSB0_UINT (insn, 16, 7, 1); \
  f_lmem8 = EXTRACT_MSB0_UINT (insn, 16, 8, 8); \

#define EXTRACT_IFMT_SET1HMEMIMM_VARS \
  UINT f_op1; \
  UINT f_imm3; \
  UINT f_op2m; \
  HI f_hmem8; \
  unsigned int length;
#define EXTRACT_IFMT_SET1HMEMIMM_CODE \
  length = 2; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 16, 0, 4); \
  f_imm3 = EXTRACT_MSB0_UINT (insn, 16, 4, 3); \
  f_op2m = EXTRACT_MSB0_UINT (insn, 16, 7, 1); \
  f_hmem8 = ((EXTRACT_MSB0_UINT (insn, 16, 8, 8)) + (32512)); \

#define EXTRACT_IFMT_BCCGRGR_VARS \
  UINT f_op1; \
  UINT f_op2; \
  UINT f_Rs; \
  UINT f_Rd; \
  UINT f_op5; \
  SI f_rel12; \
  unsigned int length;
#define EXTRACT_IFMT_BCCGRGR_CODE \
  length = 4; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 32, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 32, 4, 4); \
  f_Rs = EXTRACT_MSB0_UINT (insn, 32, 8, 4); \
  f_Rd = EXTRACT_MSB0_UINT (insn, 32, 12, 4); \
  f_op5 = EXTRACT_MSB0_UINT (insn, 32, 16, 4); \
  f_rel12 = ((EXTRACT_MSB0_SINT (insn, 32, 20, 12)) + (((pc) + (4)))); \

#define EXTRACT_IFMT_BCCGRIMM8_VARS \
  UINT f_op1; \
  UINT f_Rm; \
  UINT f_op2m; \
  UINT f_imm8; \
  UINT f_op5; \
  SI f_rel12; \
  unsigned int length;
#define EXTRACT_IFMT_BCCGRIMM8_CODE \
  length = 4; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 32, 0, 4); \
  f_Rm = EXTRACT_MSB0_UINT (insn, 32, 4, 3); \
  f_op2m = EXTRACT_MSB0_UINT (insn, 32, 7, 1); \
  f_imm8 = EXTRACT_MSB0_UINT (insn, 32, 8, 8); \
  f_op5 = EXTRACT_MSB0_UINT (insn, 32, 16, 4); \
  f_rel12 = ((EXTRACT_MSB0_SINT (insn, 32, 20, 12)) + (((pc) + (4)))); \

#define EXTRACT_IFMT_BCCIMM16_VARS \
  UINT f_op1; \
  UINT f_op2; \
  SI f_rel8_4; \
  UINT f_imm16; \
  unsigned int length;
#define EXTRACT_IFMT_BCCIMM16_CODE \
  length = 4; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 32, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 32, 4, 4); \
  f_rel8_4 = ((EXTRACT_MSB0_SINT (insn, 32, 8, 8)) + (((pc) + (4)))); \
  f_imm16 = EXTRACT_MSB0_UINT (insn, 32, 16, 16); \

#define EXTRACT_IFMT_BNGRIMM4_VARS \
  UINT f_op1; \
  UINT f_op2; \
  UINT f_imm4; \
  UINT f_Rd; \
  UINT f_op5; \
  SI f_rel12; \
  unsigned int length;
#define EXTRACT_IFMT_BNGRIMM4_CODE \
  length = 4; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 32, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 32, 4, 4); \
  f_imm4 = EXTRACT_MSB0_UINT (insn, 32, 8, 4); \
  f_Rd = EXTRACT_MSB0_UINT (insn, 32, 12, 4); \
  f_op5 = EXTRACT_MSB0_UINT (insn, 32, 16, 4); \
  f_rel12 = ((EXTRACT_MSB0_SINT (insn, 32, 20, 12)) + (((pc) + (4)))); \

#define EXTRACT_IFMT_BNGRGR_VARS \
  UINT f_op1; \
  UINT f_op2; \
  UINT f_Rs; \
  UINT f_Rd; \
  UINT f_op5; \
  SI f_rel12; \
  unsigned int length;
#define EXTRACT_IFMT_BNGRGR_CODE \
  length = 4; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 32, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 32, 4, 4); \
  f_Rs = EXTRACT_MSB0_UINT (insn, 32, 8, 4); \
  f_Rd = EXTRACT_MSB0_UINT (insn, 32, 12, 4); \
  f_op5 = EXTRACT_MSB0_UINT (insn, 32, 16, 4); \
  f_rel12 = ((EXTRACT_MSB0_SINT (insn, 32, 20, 12)) + (((pc) + (4)))); \

#define EXTRACT_IFMT_BNLMEMIMM_VARS \
  UINT f_op1; \
  UINT f_op2; \
  UINT f_lmem8; \
  UINT f_op5a; \
  UINT f_imm3b; \
  SI f_rel12; \
  unsigned int length;
#define EXTRACT_IFMT_BNLMEMIMM_CODE \
  length = 4; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 32, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 32, 4, 4); \
  f_lmem8 = EXTRACT_MSB0_UINT (insn, 32, 8, 8); \
  f_op5a = EXTRACT_MSB0_UINT (insn, 32, 16, 1); \
  f_imm3b = EXTRACT_MSB0_UINT (insn, 32, 17, 3); \
  f_rel12 = ((EXTRACT_MSB0_SINT (insn, 32, 20, 12)) + (((pc) + (4)))); \

#define EXTRACT_IFMT_BNHMEMIMM_VARS \
  UINT f_op1; \
  UINT f_op2; \
  HI f_hmem8; \
  UINT f_op5a; \
  UINT f_imm3b; \
  SI f_rel12; \
  unsigned int length;
#define EXTRACT_IFMT_BNHMEMIMM_CODE \
  length = 4; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 32, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 32, 4, 4); \
  f_hmem8 = ((EXTRACT_MSB0_UINT (insn, 32, 8, 8)) + (32512)); \
  f_op5a = EXTRACT_MSB0_UINT (insn, 32, 16, 1); \
  f_imm3b = EXTRACT_MSB0_UINT (insn, 32, 17, 3); \
  f_rel12 = ((EXTRACT_MSB0_SINT (insn, 32, 20, 12)) + (((pc) + (4)))); \

#define EXTRACT_IFMT_BCC_VARS \
  UINT f_op1; \
  UINT f_op2; \
  SI f_rel8_2; \
  unsigned int length;
#define EXTRACT_IFMT_BCC_CODE \
  length = 2; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 16, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 16, 4, 4); \
  f_rel8_2 = ((EXTRACT_MSB0_SINT (insn, 16, 8, 8)) + (((pc) + (2)))); \

#define EXTRACT_IFMT_BR_VARS \
  UINT f_op1; \
  SI f_rel12a; \
  UINT f_op4b; \
  unsigned int length;
#define EXTRACT_IFMT_BR_CODE \
  length = 2; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 16, 0, 4); \
  f_rel12a = ((((EXTRACT_MSB0_SINT (insn, 16, 4, 11)) * (2))) + (((pc) + (2)))); \
  f_op4b = EXTRACT_MSB0_UINT (insn, 16, 15, 1); \

#define EXTRACT_IFMT_JMP_VARS \
  UINT f_op1; \
  UINT f_op2; \
  UINT f_op3b; \
  UINT f_Rbj; \
  UINT f_Rd; \
  unsigned int length;
#define EXTRACT_IFMT_JMP_CODE \
  length = 2; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 16, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 16, 4, 4); \
  f_op3b = EXTRACT_MSB0_UINT (insn, 16, 8, 3); \
  f_Rbj = EXTRACT_MSB0_UINT (insn, 16, 11, 1); \
  f_Rd = EXTRACT_MSB0_UINT (insn, 16, 12, 4); \

#define EXTRACT_IFMT_JMPF_VARS \
  UINT f_op1; \
  UINT f_op2; \
  UINT f_abs24_1; \
  UINT f_abs24_2; \
  UINT f_abs24; \
  unsigned int length;
#define EXTRACT_IFMT_JMPF_CODE \
  length = 4; \
  f_op1 = EXTRACT_MSB0_UINT (insn, 32, 0, 4); \
  f_op2 = EXTRACT_MSB0_UINT (insn, 32, 4, 4); \
  f_abs24_1 = EXTRACT_MSB0_UINT (insn, 32, 8, 8); \
  f_abs24_2 = EXTRACT_MSB0_UINT (insn, 32, 16, 16); \
  f_abs24 = ((((f_abs24_2) << (8))) | (f_abs24_1));\

#define EXTRACT_IFMT_IRET_VARS \
  UINT f_op; \
  unsigned int length;
#define EXTRACT_IFMT_IRET_CODE \
  length = 2; \
  f_op = EXTRACT_MSB0_UINT (insn, 16, 0, 16); \

/* Collection of various things for the trace handler to use.  */

typedef struct trace_record {
  IADDR pc;
  /* FIXME:wip */
} TRACE_RECORD;

#endif /* CPU_XSTORMY16_H */
