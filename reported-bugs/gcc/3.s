	.file	"3.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_v1p0_zicsr2p0_zifencei2p0_zmmul1p0_zaamo1p0_zalrsc1p0_zfhmin1p0_zca1p0_zcd1p0_zve32f1p0_zve32x1p0_zve64d1p0_zve64f1p0_zve64x1p0_zvfh1p0_zvl128b1p0_zvl32b1p0_zvl64b1p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC0:
	.string	"%d "
	.section	.text.startup,"ax",@progbits
	.align	1
	.globl	main
	.type	main, @function
main:
	vsetivli	zero,4,e16,mf2,ta,ma
	vid.v	v2
	vsetivli	zero,2,e16,mf4,ta,ma
	vid.v	v1
	li	a5,5
	vsetivli	zero,4,e16,mf2,ta,ma
	vmul.vx	v2,v2,a5
	vsetivli	zero,2,e16,mf4,ta,ma
	vmul.vx	v1,v1,a5
	addi	sp,sp,-48
	li	a4,40
	sd	s1,24(sp)
	vadd.vx	v1,v1,a4
	li	a5,20
	vsetivli	zero,4,e16,mf2,ta,ma
	lui	s1,%hi(.LANCHOR0)
	addi	s1,s1,%lo(.LANCHOR0)
	vadd.vx	v3,v2,a5
	sd	s0,32(sp)
	sd	ra,40(sp)
	sd	s2,16(sp)
	sd	s3,8(sp)
	addi	a4,s1,40
	vsetivli	zero,2,e16,mf4,ta,ma
	vse16.v	v1,0(a4)
	addi	a5,s1,32
	vsetivli	zero,4,e16,mf2,ta,ma
	addi	s0,s1,24
	li	a2,20
	mv	a0,s1
	li	a1,0
	vse16.v	v3,0(a5)
	vse16.v	v2,0(s0)
	call	memset
	mv	a3,s1
	mv	a2,s0
	li	a4,10
.L2:
	vsetvli	a5,a4,e16,mf4,ta,ma
	vle16.v	v1,0(a2)
	slli	a1,a5,1
	subw	a4,a4,a5
	add	a2,a2,a1
	vasub.vx	v1,v1,zero
	vse16.v	v1,0(a3)
	add	a3,a3,a1
	bgt	a4,zero,.L2
	lui	s2,%hi(.LC0)
	addi	s3,s1,44
	addi	s2,s2,%lo(.LC0)
.L4:
	lh	a1,0(s0)
	lh	a5,0(s1)
	srliw	a4,a1,31
	addw	a1,a1,a4
	srai	a1,a1,1
	bne	a1,a5,.L11
	mv	a0,s2
	addi	s0,s0,2
	call	printf
	addi	s1,s1,2
	bne	s3,s0,.L4
	li	a0,10
	call	putchar
	ld	ra,40(sp)
	ld	s0,32(sp)
	ld	s1,24(sp)
	ld	s2,16(sp)
	ld	s3,8(sp)
	li	a0,0
	addi	sp,sp,48
	jr	ra
.L11:
	call	abort
	.size	main, .-main
	.globl	b
	.globl	a
	.bss
	.align	3
	.set	.LANCHOR0,. + 0
	.type	b, @object
	.size	b, 20
b:
	.zero	20
	.zero	4
	.type	a, @object
	.size	a, 20
a:
	.zero	20
	.ident	"GCC: () 15.0.0 20241117 (experimental)"
	.section	.note.GNU-stack,"",@progbits
