; Compare-and-branch folding (checks 2 and 3, plus bn/bp). Each function stores 1 or 0 to
; lmem 0x40 depending on one branch, so the CBRANCH condition is all that differs.

	.text

; b<cc> Rd,Rs / b<cc> Rm,#imm8 / b<cc> Rx,#imm16 for one condition code.
	.macro	ccfns name, cc
t_cc_rr_\name:
	b\cc	r2,r3,1f
	mov	r2,#0
	mov.w	0x40,r2
	ret
1:	mov	r2,#1
	mov.w	0x40,r2
	ret

t_cc_ri_\name:
	b\cc	r2,#0x12,1f
	mov	r2,#0
	mov.w	0x40,r2
	ret
1:	mov	r2,#1
	mov.w	0x40,r2
	ret

; mov sets Rx to r4, so the branch compares a copy of r2.
t_cc_rx_\name:
	mov	r4,r2
	b\cc	Rx,#0x1234,1f
	mov	r2,#0
	mov.w	0x40,r2
	ret
1:	mov	r2,#1
	mov.w	0x40,r2
	ret
	.endm

	ccfns	ge, ge
	ccfns	nc, nc
	ccfns	lt, lt
	ccfns	c, c
	ccfns	gt, gt
	ccfns	hi, hi
	ccfns	le, le
	ccfns	ls, ls
	ccfns	pl, pl
	ccfns	nv, nv
	ccfns	mi, mi
	ccfns	v, v
	ccfns	nzb, nz.b
	ccfns	nz, nz
	ccfns	zb, z.b
	ccfns	z, z

; 32-bit signed compare, (r3:r2) < (r5:r4): the high word goes through sbc, so blt tests
; S^OV of a subtract with carry-in.
t_wide_slt:
	sub	r2,r4
	sbc	r3,r5
	blt	1f
	mov	r2,#0
	mov.w	0x40,r2
	ret
1:	mov	r2,#1
	mov.w	0x40,r2
	ret

; 32-bit add, (r3:r2) += (r5:r4)
t_wide_add:
	add	r2,r4
	adc	r3,r5
	mov.w	0x40,r2
	mov.w	0x42,r3
	ret

; Bit tests: no flags involved, the condition is a masked load or register.
t_bit_lmem:
	bn	0x40,#3,1f
	mov	r2,#1
	mov.w	0x42,r2
	ret
1:	mov	r2,#0
	mov.w	0x42,r2
	ret

t_bit_hmem:
	bp	0x7f10,#2,1f
	mov	r2,#1
	mov.w	0x42,r2
	ret
1:	mov	r2,#0
	mov.w	0x42,r2
	ret

t_bit_reg_imm:
	bp	r2,#4,1f
	mov	r2,#1
	mov.w	0x42,r2
	ret
1:	mov	r2,#0
	mov.w	0x42,r2
	ret

t_bit_reg_reg:
	bn	r2,r3,1f
	mov	r2,#1
	mov.w	0x42,r2
	ret
1:	mov	r2,#0
	mov.w	0x42,r2
	ret

; Explicit r14 reads (interrupt-enable bit PSW[7]): reading psw packs the flags into it, but
; a test of PSW[11:7] must not turn the incoming flags into inputs (no-flag-inputs).
t_psw_bit:
	bn	psw,#7,1f
	mov	r2,#0
	mov.w	0x40,r2
	ret
1:	mov	r2,#1
	mov.w	0x40,r2
	ret

t_psw_read:
	mov	r2,psw
	shr	r2,#7
	and	r2,#1
	mov.w	0x40,r2
	ret
