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
	.file	"baseled_test.c"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}
	cmp	r0, #1
	sub	sp, sp, #8
	mov	r4, #0
	mov	r6, r1
	str	r4, [sp]
	str	r4, [sp, #4]
	ble	.L15
	ldr	r0, .L18
	mov	r1, #1
.LPIC9:
	add	r0, pc, r0
	bl	open(PLT)
	cmn	r0, #1
	mov	r5, r0
	bne	.L16
	ldr	r0, .L18+4
.LPIC10:
	add	r0, pc, r0
	bl	puts(PLT)
.L3:
	mvn	r0, #0
	add	sp, sp, #8
	@ sp needed
	ldmfd	sp!, {r4, r5, r6, pc}
.L15:
	ldr	r0, .L18+8
.LPIC8:
	add	r0, pc, r0
	bl	puts(PLT)
	b	.L3
.L16:
	ldr	r0, [r6, #4]
	ldrb	r3, [r0]	@ zero_extendqisi2
	cmp	r3, #48
	bne	.L5
	ldrb	r3, [r0, #1]	@ zero_extendqisi2
	and	r3, r3, #223
	cmp	r3, #88
	beq	.L17
.L5:
	bl	atoi(PLT)
	uxtb	r0, r0
.L6:
	mov	r1, sp
	mov	r2, #0
	mov	ip, #1
.L9:
	mov	r3, r0, asr r2
	tst	r3, #1
	strneb	ip, [r1, r2]
	add	r2, r2, #1
	cmp	r2, #8
	bne	.L9
	mov	r1, sp
	mov	r0, r5
	bl	write(PLT)
	mov	r0, r5
	bl	close(PLT)
	mov	r0, #0
	bl	exit(PLT)
.L17:
	add	r0, r0, #2
	mov	r1, r4
	mov	r2, #16
	bl	strtol(PLT)
	uxtb	r0, r0
	b	.L6
.L19:
	.align	2
.L18:
	.word	.LC1-(.LPIC9+8)
	.word	.LC2-(.LPIC10+8)
	.word	.LC0-(.LPIC8+8)
	.size	main, .-main
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"please input the parameter! ex)./test 0xff\000"
	.space	1
.LC1:
	.ascii	"/dev/baseled\000"
	.space	3
.LC2:
	.ascii	"Device Open error!\000"
	.ident	"GCC: (GNU) 4.8"
	.section	.note.GNU-stack,"",%progbits
