/* Misc. support for CPU family xstormy16.

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
#include "cgen-ops.h"

/* Get the value of h-pc.  */

USI
xstormy16_h_pc_get (SIM_CPU *current_cpu)
{
  return CPU (h_pc);
}

/* Set a value for h-pc.  */

void
xstormy16_h_pc_set (SIM_CPU *current_cpu, USI newval)
{
  SET_H_PC (newval);
}

/* Get the value of h-gr.  */

SI
xstormy16_h_gr_get (SIM_CPU *current_cpu, UINT regno)
{
  return GET_H_GR (regno);
}

/* Set a value for h-gr.  */

void
xstormy16_h_gr_set (SIM_CPU *current_cpu, UINT regno, SI newval)
{
  SET_H_GR (regno, newval);
}

/* Get the value of h-Rb.  */

SI
xstormy16_h_Rb_get (SIM_CPU *current_cpu, UINT regno)
{
  return GET_H_RB (regno);
}

/* Set a value for h-Rb.  */

void
xstormy16_h_Rb_set (SIM_CPU *current_cpu, UINT regno, SI newval)
{
  SET_H_RB (regno, newval);
}

/* Get the value of h-Rbj.  */

SI
xstormy16_h_Rbj_get (SIM_CPU *current_cpu, UINT regno)
{
  return GET_H_RBJ (regno);
}

/* Set a value for h-Rbj.  */

void
xstormy16_h_Rbj_set (SIM_CPU *current_cpu, UINT regno, SI newval)
{
  SET_H_RBJ (regno, newval);
}

/* Get the value of h-Rpsw.  */

SI
xstormy16_h_Rpsw_get (SIM_CPU *current_cpu)
{
  return GET_H_RPSW ();
}

/* Set a value for h-Rpsw.  */

void
xstormy16_h_Rpsw_set (SIM_CPU *current_cpu, SI newval)
{
  SET_H_RPSW (newval);
}

/* Get the value of h-z8.  */

SI
xstormy16_h_z8_get (SIM_CPU *current_cpu)
{
  return GET_H_Z8 ();
}

/* Set a value for h-z8.  */

void
xstormy16_h_z8_set (SIM_CPU *current_cpu, SI newval)
{
  SET_H_Z8 (newval);
}

/* Get the value of h-z16.  */

SI
xstormy16_h_z16_get (SIM_CPU *current_cpu)
{
  return GET_H_Z16 ();
}

/* Set a value for h-z16.  */

void
xstormy16_h_z16_set (SIM_CPU *current_cpu, SI newval)
{
  SET_H_Z16 (newval);
}

/* Get the value of h-cy.  */

SI
xstormy16_h_cy_get (SIM_CPU *current_cpu)
{
  return GET_H_CY ();
}

/* Set a value for h-cy.  */

void
xstormy16_h_cy_set (SIM_CPU *current_cpu, SI newval)
{
  SET_H_CY (newval);
}

/* Get the value of h-hc.  */

SI
xstormy16_h_hc_get (SIM_CPU *current_cpu)
{
  return GET_H_HC ();
}

/* Set a value for h-hc.  */

void
xstormy16_h_hc_set (SIM_CPU *current_cpu, SI newval)
{
  SET_H_HC (newval);
}

/* Get the value of h-ov.  */

SI
xstormy16_h_ov_get (SIM_CPU *current_cpu)
{
  return GET_H_OV ();
}

/* Set a value for h-ov.  */

void
xstormy16_h_ov_set (SIM_CPU *current_cpu, SI newval)
{
  SET_H_OV (newval);
}

/* Get the value of h-pt.  */

SI
xstormy16_h_pt_get (SIM_CPU *current_cpu)
{
  return GET_H_PT ();
}

/* Set a value for h-pt.  */

void
xstormy16_h_pt_set (SIM_CPU *current_cpu, SI newval)
{
  SET_H_PT (newval);
}

/* Get the value of h-s.  */

SI
xstormy16_h_s_get (SIM_CPU *current_cpu)
{
  return GET_H_S ();
}

/* Set a value for h-s.  */

void
xstormy16_h_s_set (SIM_CPU *current_cpu, SI newval)
{
  SET_H_S (newval);
}
