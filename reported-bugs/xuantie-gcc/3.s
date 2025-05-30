	.file	"0.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_v1p0_zicsr2p0_zifencei2p0_zfhmin1p0_zve32f1p0_zve32x1p0_zve64d1p0_zve64f1p0_zve64x1p0_zvfh1p0_zvl128b1p0_zvl32b1p0_zvl64b1p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC0:
	.string	"success"
	.section	.text.startup,"ax",@progbits
	.align	1
	.globl	main
	.type	main, @function
main:
	lui	a0,%hi(.LANCHOR0)
	addi	sp,sp,-32
	addi	a6,a0,%lo(.LANCHOR0)
	sd	s1,8(sp)
	addi	s1,a6,928
	sd	ra,24(sp)
	sd	s0,16(sp)
	sd	s2,0(sp)
	mv	a4,s1
	li	a5,0
	li	a3,230
.L2:
	sb	a5,0(a4)
	addiw	a5,a5,1
	addi	a4,a4,1
	bne	a5,a3,.L2
	addi	s2,a6,464
	mv	a5,s2
	li	s0,0
	li	a4,230
.L3:
	sh	s0,0(a5)
	addiw	s0,s0,1
	addi	a5,a5,2
	bne	s0,a4,.L3
	li	a1,0
	li	a2,460
	mv	a0,a6
	call	memset
	mv	a3,s2
	mv	a4,s1
	li	a1,92
.L4:
	vsetvli	a5,s0,e8,mf2,ta,ma
	vle8.v	v0,0(a4)
	vle16.v	v1,0(a3)
	slli	a2,a5,1
	subw	s0,s0,a5
	add	a4,a4,a5
	add	a3,a3,a2
	vmseq.vi	v0,v0,1
	vwadd.wx	v1,v1,a1,v0.t
	vse16.v	v0,0(a0)
	add	a0,a0,a2
	bgt	s0,zero,.L4
	lui	a0,%hi(.LC0)
	addi	a0,a0,%lo(.LC0)
	call	printf
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
	.globl	data_mask
	.bss
	.align	3
	.set	.LANCHOR0,. + 0
	.type	b, @object
	.size	b, 460
b:
	.zero	460
	.zero	4
	.type	a, @object
	.size	a, 460
a:
	.zero	460
	.zero	4
	.type	data_mask, @object
	.size	data_mask, 230
data_mask:
	.zero	230
	.ident	"GCC: (Xuantie-900 elf newlib gcc Toolchain V3.0.1 B-20241120) 14.1.1 20240710"
	.section	.note.GNU-stack,"",@progbits
