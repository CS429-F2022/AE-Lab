	.arch armv8-a
	.text
	.align	2
start:
	movk	x1, #69
	stur	x1, [sp, #-8]
	ldur	x0, [sp, #-8]

	eor 	x5, x5, x5
	mvn 	x5, x5
	stur	x0, [x5]

	ret
	.size	start, .-start
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
