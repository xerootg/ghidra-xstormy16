; Calls, returns, stack frames and the GCC xstormy16 ABI (checks 4, 5 and 6). Arguments
; arrive in r2.., results leave in r2, r13 is the frame pointer, r10-r13 are callee-saved
; and r0-r9 are call-clobbered. Values that must survive are stored to lmem 0x40.

	.text

t_call_leaf:
	nop
	ret

; An argument spilled with push and reloaded with pop around a call.
t_call_frame:
	push	r10
	push	r2
	callf	t_call_leaf
	pop	r3
	mov.w	0x40,r3
	pop	r10
	ret

; The same around an icallf: the call pushes PC and PSW (6 bytes) and the target irets.
t_icall_frame:
	push	r2
	icallf	t_icall_target
	pop	r3
	mov.w	0x40,r3
	ret

t_icall_target:
	mov	r3,#1
	mov.w	0x44,r3
	iret

; Interrupt handler (vector 1): saves what it uses, returns with iret.
	.global	t_iret_handler
t_iret_handler:
	push	r0
	push	r2
	mov	r2,#1
	mov.w	0x46,r2
	pop	r2
	pop	r0
	iret

; int add2(int a, int b) { return a + b; } and a caller that keeps the result.
t_abi_add2:
	add	r2,r3
	ret

t_abi_caller:
	mov	r2,#5
	mov	r3,#7
	callf	t_abi_add2
	mov.w	0x40,r2
	ret

; r8 is call-clobbered: its value before the call must not reach the store.
t_abi_clob8:
	mov	r8,#7
	ret

t_abi_keep8:
	mov	r8,r2
	callf	t_abi_clob8
	mov	r3,r8
	mov.w	0x40,r3
	ret

; r10 is callee-saved: the callee preserves it, so the argument reaches the store.
t_abi_clob10:
	push	r10
	mov	r10,#7
	pop	r10
	ret

t_abi_keep10:
	push	r10
	mov	r10,r2
	callf	t_abi_clob10
	mov	r3,r10
	mov.w	0x40,r3
	pop	r10
	ret

; GCC frame: r13 frame pointer, one local word at (r13,0), released before the return.
t_abi_frame:
	push	r13
	mov	r13,r15
	add	r15,#2
	mov.w	(r13,0),r2
	callf	t_call_leaf
	mov.w	r3,(r13,0)
	mov.w	0x40,r3
	sub	r15,#2
	pop	r13
	ret
