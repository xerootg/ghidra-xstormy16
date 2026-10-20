; Register-indirect Rx, far SFR accesses, near flash reads, jump tables and system
; instructions (checks 1, 7 and 8, reset/halt flow).

	.text

; Rx after a flag-setting instruction: Rx is r3.
t_rx_known:
	add	r3,#1
	or	Rx,#0x10
	mov.w	0x40,r3
	ret

; Rx used before anything in the function sets it: it names a caller's register.
t_rx_entry:
	or	Rx,#5
	ret

; Two far reads of the same SFR must stay two reads.
t_far_sfr_twice:
	mov	r8,#0
	mov	r6,#0x7f10
	movf.w	r2,(r6)
	movf.w	r3,(r6)
	add	r2,r3
	mov.w	0x40,r2
	ret

; The near equivalent, for comparison.
t_near_sfr_twice:
	mov	r6,#0x7f10
	mov.w	r2,(r6)
	mov.w	r3,(r6)
	add	r2,r3
	mov.w	0x40,r2
	ret

; A near read above 0x8000 sees flash.
t_near_flash:
	mov	r6,#d_flash_word
	mov.w	r2,(r6)
	mov.w	0x40,r2
	ret

	.p2align 1
d_flash_word:
	.word	0x1234

; switch (r2) through a GCC-style table: br Rd into a run of jmpf.
t_jt_switch:
	bhi	r2,#3,9f
	shl	r2,#2
	br	r2
	jmpf	10f
	jmpf	11f
	jmpf	12f
	jmpf	13f
10:	mov	r3,#0x11
	br	8f
11:	mov	r3,#0x22
	br	8f
12:	mov	r3,#0x33
	br	8f
13:	mov	r3,#0x44
	br	8f
9:	mov	r3,#0
8:	mov.w	0x40,r3
	ret

; Software reset does not come back; halt resumes after an interrupt.
	.global	t_flow_reset
t_flow_reset:
	mov	r2,#1
	mov.w	0x40,r2
	reset
	mov.w	0x42,r2
	ret

t_flow_halt:
	halt
	mov	r2,#1
	mov.w	0x40,r2
	ret
