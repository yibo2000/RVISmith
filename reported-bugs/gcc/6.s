	.file	"frm.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_v1p0_zicsr2p0_zifencei2p0_zmmul1p0_zaamo1p0_zalrsc1p0_zfhmin1p0_zca1p0_zcd1p0_zve32f1p0_zve32x1p0_zve64d1p0_zve64f1p0_zve64x1p0_zvfh1p0_zvl128b1p0_zvl32b1p0_zvl64b1p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	initialize
	.type	initialize, @function
initialize:
	lui	a5,%hi(.LC1)
	vsetivli	zero,4,e16,mf2,ta,ma
	addi	a5,a5,%lo(.LC1)
	vle16.v	v2,0(a5)
	vmv.v.i	v1,0
	lui	a4,%hi(a)
	lui	a5,%hi(b)
	addi	a4,a4,%lo(a)
	addi	a5,a5,%lo(b)
	vse16.v	v2,0(a4)
	vse16.v	v1,0(a5)
	ret
	.size	initialize, .-initialize
	.align	1
	.globl	compute
	.type	compute, @function
compute:
	frrm	a0
	lui	a4,%hi(b)
	lui	a2,%hi(a)
	addi	a4,a4,%lo(b)
	addi	a2,a2,%lo(a)
	li	a3,4
.L4:
	fsrmi	2
	vsetvli	a5,a3,e16,m1,ta,ma
	vle16.v	v1,0(a2)
	slli	a1,a5,1
	subw	a3,a3,a5
	add	a2,a2,a1
	vfnmadd.vv	v1,v1,v1
	fsrm	a0
	vfmsub.vv	v1,v1,v1
	vse16.v	v1,0(a4)
	add	a4,a4,a1
	bgt	a3,zero,.L4
	ret
	.size	compute, .-compute
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC2:
	.string	"%lf "
	.section	.text.startup,"ax",@progbits
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sd	s0,16(sp)
	sd	ra,24(sp)
	sd	s1,8(sp)
	sd	s2,0(sp)
	call	initialize
	lui	s0,%hi(b)
	lui	a2,%hi(a)
	addi	a3,s0,%lo(b)
	addi	a2,a2,%lo(a)
	li	a4,4
.L8:
	fsrmi	2
	vsetvli	a5,a4,e16,m1,ta,ma
	vle16.v	v1,0(a2)
	slli	a1,a5,1
	subw	a4,a4,a5
	add	a2,a2,a1
	vfnmadd.vv	v1,v1,v1
	vfmsub.vv	v1,v1,v1
	vse16.v	v1,0(a3)
	add	a3,a3,a1
	bgt	a4,zero,.L8
	addi	s0,s0,%lo(b)
	lui	s1,%hi(.LC2)
	addi	s2,s0,8
	addi	s1,s1,%lo(.LC2)
.L9:
	flh	fa5,0(s0)
	mv	a0,s1
	addi	s0,s0,2
	fcvt.d.h	fa5,fa5
	fmv.x.d	a1,fa5
	call	printf
	bne	s2,s0,.L9
	li	a0,10
	call	putchar
	ld	ra,24(sp)
	ld	s0,16(sp)
	ld	s1,8(sp)
	ld	s2,0(sp)
	li	a0,0
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.globl	b
	.globl	a
	.section	.srodata.cst8,"aM",@progbits,8
	.align	3
.LC1:
	.half	-21653
	.half	3213
	.half	238
	.half	275
	.section	.sbss,"aw",@nobits
	.align	3
	.type	b, @object
	.size	b, 8
b:
	.zero	8
	.type	a, @object
	.size	a, 8
a:
	.zero	8
	.ident	"GCC: () 15.0.0 20241117 (experimental)"
	.section	.note.GNU-stack,"",@progbits
