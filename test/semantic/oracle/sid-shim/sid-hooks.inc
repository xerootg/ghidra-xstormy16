// Hand-written hooks copied verbatim from SID (sid-20180601,
// sid/component/cgen-cpu/xstormy16/xstormy16.h and xstormy16.cxx).
// Copyright (C) 1999, 2000, 2006 Red Hat.
// This file is part of SID and is licensed under the GPL.
// See the file COPYING.SID for conditions for redistribution.
// (GPL version 2 or later; see test/semantic/NOTICE.)
//
// Included inside class xstormy16_cpu by xstormy16.h. The reversible-execution logging
// they call is stubbed out there.

      void h_pc_set_handler (USI newval)
        {
	  if (UNLIKELY (this->reversible_p))
	    log_pc_change (newval);
	  this->hardware.h_pc = newval;
        }

      // Log any changes to the gr registers, if we're reversible.
      void h_gr_set_handler (UINT regno, SI newval)
        {
	  if (UNLIKELY (this->reversible_p))
	    log_gr_change (regno, newval);
	  this->hardware.h_gr[regno] = (0xffff & newval);
        }

// Count the bits in (16bit) register `reg', modulo 2.
int
parity (int reg)
{
  int tmp;
  tmp = reg ^ (reg >> 8);
  tmp ^= tmp >> 4;
  tmp ^= tmp >> 2;
  tmp ^= tmp >> 1;
  return tmp & 1;
}
