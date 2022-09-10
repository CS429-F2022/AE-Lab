	.arch armv8-a
	.text
	.align	2
start:
	movk	x0, #15
	movk	x1, #16
	movk	x2, #5
	movk	x3, #29
	movk	x4, #1
	adds	x0, x1, x0 
	subs	x0, x0, x2		
	ands	x0, x0, x3
	orr		x0, x0, x4

	eor 	x5, x5, x5
	mvn 	x5, x5
	stur	x0, [x5]

	ret
	.size	start, .-start
	.ident	"GCC: (Ubuntu/Linaro 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
