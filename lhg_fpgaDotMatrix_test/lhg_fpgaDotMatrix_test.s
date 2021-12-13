	.arch armv7-a
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"lhg_fpgaDotMatrix_test.c"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 720
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r0, .L22
	mov	r1, #1
	stmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, lr}
.LPIC16:
	add	r0, pc, r0
	sub	sp, sp, #724
	ldr	r4, .L22+4
	bl	open(PLT)
.LPIC19:
	add	r4, pc, r4
	cmn	r0, #1
	mov	r9, r0
	beq	.L2
	ldr	r0, .L22+8
	add	r10, sp, #20
.LPIC17:
	add	r0, pc, r0
	bl	printf(PLT)
	ldr	r0, .L22+12
	mov	r1, r10
	add	r2, sp, #120
.LPIC18:
	add	r0, pc, r0
	str	r2, [sp, #4]
	bl	scanf(PLT)
	mov	r0, r10
	bl	strlen(PLT)
	add	r3, sp, #119
	add	ip, sp, #139
	mov	r2, #48
	str	r0, [sp, #8]
.L4:
	strb	r2, [r3, #1]!
	cmp	r3, ip
	bne	.L4
	ldr	r3, [sp, #8]
	cmp	r3, #0
	ble	.L17
	ldr	r3, .L22+16
	sub	r10, r10, #1
	ldr	r2, [sp, #8]
	add	r8, sp, #140
	ldr	r7, .L22+20
	add	r6, sp, #16
	add	r2, r10, r2
	str	r2, [sp]
	ldr	r3, [r4, r3]
.LPIC20:
	add	r7, pc, r7
	str	r9, [sp, #12]
	mov	fp, r3
.L9:
	ldrb	r5, [r10, #1]!	@ zero_extendqisi2
	mov	r9, r8
	mov	r4, #0
	sub	r5, r5, #32
	add	r5, r5, r5, asl #2
	add	r5, fp, r5, asl #2
.L7:
	ldr	ip, [r5, r4]
	mov	r0, r6
	mov	r1, r7
	add	r4, r4, #4
	cmp	ip, #0
	add	r2, ip, #15
	mov	lr, ip, asr #31
	add	r9, r9, #2
	movge	r2, ip
	mov	lr, lr, lsr #28
	mov	r2, r2, asr #4
	add	ip, ip, lr
	and	r3, ip, #15
	rsb	r3, lr, r3
	bl	sprintf(PLT)
	ldrb	r2, [sp, #16]	@ zero_extendqisi2
	ldrb	r3, [sp, #17]	@ zero_extendqisi2
	cmp	r4, #20
	strb	r2, [r9, #-2]
	strb	r3, [r9, #-1]
	bne	.L7
	ldr	r3, [sp]
	mov	r2, #48
	add	r8, r8, #12
	strb	r2, [r8, #-2]
	cmp	r10, r3
	strb	r2, [r8, #-1]
	bne	.L9
	ldr	r3, [sp, #8]
	ldr	r9, [sp, #12]
	add	r0, r3, r3, asl #1
	mov	r0, r0, asl #2
	add	r0, r0, #20
.L5:
	add	r2, sp, #120
	mov	r3, #0
	add	r1, r2, r0
	mov	r2, #48
.L11:
	strb	r2, [r1, r3]
	add	r3, r3, #1
	cmp	r3, #20
	bne	.L11
	add	r0, r0, #2
	mov	r6, r0, asr #1
	cmp	r6, #0
	addgt	r3, sp, #120
	addgt	r6, r3, r6, asl #1
	movgt	r5, r3
	ble	.L13
.L15:
	mov	r4, #20
.L16:
	mov	r0, r9
	mov	r1, r5
	mov	r2, #20
	bl	write(PLT)
	subs	r4, r4, #1
	bne	.L16
	add	r5, r5, #2
	cmp	r5, r6
	bne	.L15
.L13:
	mov	r0, r9
	bl	close(PLT)
	ldr	r0, .L22+24
.LPIC22:
	add	r0, pc, r0
	bl	puts(PLT)
	mov	r0, #0
	add	sp, sp, #724
	@ sp needed
	ldmfd	sp!, {r4, r5, r6, r7, r8, r9, r10, fp, pc}
.L17:
	mov	r0, #20
	b	.L5
.L2:
	ldr	r0, .L22+28
.LPIC21:
	add	r0, pc, r0
	bl	puts(PLT)
	mov	r0, #1
	bl	exit(PLT)
.L23:
	.align	2
.L22:
	.word	.LC0-(.LPIC16+8)
	.word	_GLOBAL_OFFSET_TABLE_-(.LPIC19+8)
	.word	.LC1-(.LPIC17+8)
	.word	.LC2-(.LPIC18+8)
	.word	font(GOT)
	.word	.LC3-(.LPIC20+8)
	.word	.LC5-(.LPIC22+8)
	.word	.LC4-(.LPIC21+8)
	.size	main, .-main
	.global	font
	.data
	.align	2
	.type	font, %object
	.size	font, 1900
font:
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	79
	.word	0
	.word	0
	.word	0
	.word	7
	.word	0
	.word	7
	.word	0
	.word	20
	.word	127
	.word	20
	.word	127
	.word	20
	.word	36
	.word	42
	.word	127
	.word	42
	.word	18
	.word	35
	.word	19
	.word	8
	.word	100
	.word	98
	.word	54
	.word	73
	.word	85
	.word	34
	.word	80
	.word	0
	.word	5
	.word	3
	.word	0
	.word	0
	.word	0
	.word	28
	.word	34
	.word	65
	.word	0
	.word	0
	.word	65
	.word	34
	.word	28
	.word	0
	.word	20
	.word	8
	.word	62
	.word	8
	.word	20
	.word	8
	.word	8
	.word	62
	.word	8
	.word	8
	.word	0
	.word	80
	.word	48
	.word	0
	.word	0
	.word	8
	.word	8
	.word	8
	.word	8
	.word	8
	.word	0
	.word	96
	.word	96
	.word	0
	.word	0
	.word	32
	.word	16
	.word	8
	.word	4
	.word	2
	.word	62
	.word	81
	.word	73
	.word	69
	.word	62
	.word	0
	.word	66
	.word	127
	.word	64
	.word	0
	.word	66
	.word	97
	.word	81
	.word	73
	.word	70
	.word	33
	.word	65
	.word	69
	.word	75
	.word	49
	.word	24
	.word	20
	.word	18
	.word	127
	.word	16
	.word	39
	.word	69
	.word	69
	.word	69
	.word	57
	.word	60
	.word	74
	.word	73
	.word	73
	.word	48
	.word	1
	.word	113
	.word	9
	.word	5
	.word	3
	.word	54
	.word	73
	.word	73
	.word	73
	.word	54
	.word	6
	.word	73
	.word	73
	.word	41
	.word	30
	.word	0
	.word	54
	.word	54
	.word	0
	.word	0
	.word	0
	.word	86
	.word	54
	.word	0
	.word	0
	.word	8
	.word	20
	.word	34
	.word	65
	.word	0
	.word	20
	.word	20
	.word	20
	.word	20
	.word	20
	.word	0
	.word	65
	.word	34
	.word	20
	.word	8
	.word	2
	.word	1
	.word	81
	.word	9
	.word	6
	.word	50
	.word	73
	.word	121
	.word	65
	.word	62
	.word	126
	.word	17
	.word	17
	.word	17
	.word	126
	.word	127
	.word	73
	.word	73
	.word	73
	.word	54
	.word	62
	.word	65
	.word	65
	.word	65
	.word	34
	.word	127
	.word	65
	.word	65
	.word	34
	.word	28
	.word	127
	.word	73
	.word	73
	.word	73
	.word	65
	.word	127
	.word	9
	.word	9
	.word	9
	.word	1
	.word	62
	.word	65
	.word	73
	.word	73
	.word	122
	.word	127
	.word	8
	.word	8
	.word	8
	.word	127
	.word	0
	.word	65
	.word	127
	.word	65
	.word	0
	.word	32
	.word	64
	.word	65
	.word	63
	.word	1
	.word	127
	.word	8
	.word	20
	.word	34
	.word	65
	.word	127
	.word	64
	.word	64
	.word	64
	.word	64
	.word	127
	.word	2
	.word	12
	.word	2
	.word	127
	.word	127
	.word	4
	.word	8
	.word	16
	.word	127
	.word	62
	.word	65
	.word	65
	.word	65
	.word	62
	.word	127
	.word	9
	.word	9
	.word	9
	.word	6
	.word	62
	.word	65
	.word	81
	.word	33
	.word	94
	.word	127
	.word	9
	.word	25
	.word	41
	.word	70
	.word	38
	.word	73
	.word	73
	.word	73
	.word	50
	.word	1
	.word	1
	.word	127
	.word	1
	.word	1
	.word	63
	.word	64
	.word	64
	.word	64
	.word	63
	.word	31
	.word	32
	.word	64
	.word	32
	.word	31
	.word	63
	.word	64
	.word	56
	.word	64
	.word	63
	.word	99
	.word	20
	.word	8
	.word	20
	.word	99
	.word	7
	.word	8
	.word	112
	.word	8
	.word	7
	.word	97
	.word	81
	.word	73
	.word	69
	.word	67
	.word	0
	.word	127
	.word	65
	.word	65
	.word	0
	.word	2
	.word	4
	.word	8
	.word	16
	.word	32
	.word	0
	.word	65
	.word	65
	.word	127
	.word	0
	.word	4
	.word	2
	.word	1
	.word	2
	.word	4
	.word	64
	.word	64
	.word	64
	.word	64
	.word	64
	.word	0
	.word	1
	.word	2
	.word	4
	.word	0
	.word	32
	.word	84
	.word	84
	.word	84
	.word	120
	.word	127
	.word	72
	.word	68
	.word	68
	.word	56
	.word	56
	.word	68
	.word	68
	.word	68
	.word	32
	.word	56
	.word	68
	.word	68
	.word	72
	.word	127
	.word	56
	.word	84
	.word	84
	.word	84
	.word	24
	.word	8
	.word	126
	.word	9
	.word	1
	.word	2
	.word	12
	.word	82
	.word	82
	.word	82
	.word	62
	.word	127
	.word	8
	.word	4
	.word	4
	.word	120
	.word	0
	.word	4
	.word	125
	.word	0
	.word	0
	.word	32
	.word	64
	.word	68
	.word	61
	.word	0
	.word	127
	.word	16
	.word	40
	.word	68
	.word	0
	.word	0
	.word	65
	.word	127
	.word	64
	.word	0
	.word	124
	.word	4
	.word	24
	.word	4
	.word	124
	.word	124
	.word	8
	.word	4
	.word	4
	.word	120
	.word	56
	.word	68
	.word	68
	.word	68
	.word	56
	.word	124
	.word	20
	.word	20
	.word	20
	.word	8
	.word	8
	.word	20
	.word	20
	.word	24
	.word	124
	.word	124
	.word	8
	.word	4
	.word	4
	.word	8
	.word	72
	.word	84
	.word	84
	.word	84
	.word	32
	.word	4
	.word	63
	.word	68
	.word	64
	.word	32
	.word	60
	.word	64
	.word	64
	.word	32
	.word	124
	.word	28
	.word	32
	.word	64
	.word	32
	.word	28
	.word	60
	.word	64
	.word	48
	.word	64
	.word	60
	.word	68
	.word	40
	.word	16
	.word	40
	.word	68
	.word	12
	.word	80
	.word	80
	.word	80
	.word	60
	.word	68
	.word	100
	.word	84
	.word	76
	.word	68
	.word	0
	.word	8
	.word	54
	.word	65
	.word	0
	.word	0
	.word	0
	.word	119
	.word	0
	.word	0
	.word	0
	.word	65
	.word	54
	.word	8
	.word	0
	.word	8
	.word	4
	.word	8
	.word	16
	.word	8
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"/dev/lhg_fpgaDotMatrix_driver\000"
	.space	2
.LC1:
	.ascii	"Input text : \000"
	.space	2
.LC2:
	.ascii	"%s\000"
	.space	1
.LC3:
	.ascii	"%x%x\000"
	.space	3
.LC4:
	.ascii	"Device Open ERROR!\000"
	.space	1
.LC5:
	.ascii	"Program Exit !!\000"
	.ident	"GCC: (GNU) 4.8"
	.section	.note.GNU-stack,"",%progbits
