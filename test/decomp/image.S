; Synthetic lens image scaffolding: the update-file header tag the loader looks for and a
; two-entry vector table (reset and one interrupt). The chip name is made up.

	.section .chipinfo,"a"
	.ascii	"CHIPINFORMATION\0XS16DECOMP\0"

	.section .vectors,"ax"
	.global	vectors
vectors:
	jmpf	t_flow_reset
	jmpf	t_iret_handler
