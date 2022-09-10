	.arch armv8-a
	.text
	.align	2
start:
	movk	x0, #4660, LSL 48
	movk	x0, #57005, LSL 32
	movk	x0, #48879, LSL 16
	movk	x0, #51966

	eor 	x5, x5, x5
	mvn 	x5, x5
	stur	x0, [x5]

	ret
	.size	start, .-start
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
