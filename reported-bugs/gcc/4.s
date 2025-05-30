	.file	"0.c"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_v1p0_zicsr2p0_zifencei2p0_zmmul1p0_zaamo1p0_zalrsc1p0_zfhmin1p0_zca1p0_zcd1p0_zve32f1p0_zve32x1p0_zve64d1p0_zve64f1p0_zve64x1p0_zvfh1p0_zvl128b1p0_zvl32b1p0_zvl64b1p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	convert_binary_u16_f16
	.type	convert_binary_u16_f16, @function
convert_binary_u16_f16:
	not	a5,a0
	srli	a4,a5,10
	andi	a4,a4,31
	bne	a4,zero,.L2
	andi	a4,a0,1023
	mv	a5,zero
	bne	a4,zero,.L5
.L2:
	mv	a5,a0
.L5:
	fmv.h.x	fa0,a5
	ret
	.size	convert_binary_u16_f16, .-convert_binary_u16_f16
	.align	1
	.globl	convert_binary_u32_f32
	.type	convert_binary_u32_f32, @function
convert_binary_u32_f32:
	not	a5,a0
	srli	a4,a5,23
	andi	a4,a4,255
	bne	a4,zero,.L9
	slli	a4,a0,41
	mv	a5,zero
	bne	a4,zero,.L12
.L9:
	mv	a5,a0
.L12:
	fmv.s.x	fa0,a5
	ret
	.size	convert_binary_u32_f32, .-convert_binary_u32_f32
	.align	1
	.globl	convert_binary_u64_f64
	.type	convert_binary_u64_f64, @function
convert_binary_u64_f64:
	not	a5,a0
	srli	a4,a5,52
	andi	a4,a4,2047
	bne	a4,zero,.L15
	slli	a5,a0,12
	fmv.d.x	fa0,zero
	bne	a5,zero,.L18
.L15:
	fmv.d.x	fa0,a0
.L18:
	ret
	.size	convert_binary_u64_f64, .-convert_binary_u64_f64
	.section	.text.startup,"ax",@progbits
	.align	1
	.globl	main
	.type	main, @function
main:
	csrr	t0,vlenb
	li	t1,49
	mul	t1,t1,t0
	li	a1,-3362816
	addi	a1,a1,-1627
	slli	a1,a1,13
	addi	a1,a1,251
	li	a0,-30720000
	slli	a1,a1,13
	addi	sp,sp,-960
	li	t6,-813883392
	addi	a0,a0,-1233
	addi	a1,a1,-1529
	sd	s0,952(sp)
	addi	t6,t6,1701
	li	s0,71426048
	li	t0,581373952
	li	t2,819253248
	slli	a0,a0,13
	slli	a1,a1,15
	sd	s1,944(sp)
	sd	s2,936(sp)
	sd	s3,928(sp)
	sd	s4,920(sp)
	sd	s5,912(sp)
	sd	s6,904(sp)
	sd	s7,896(sp)
	sd	s8,888(sp)
	sd	s9,880(sp)
	sd	s10,872(sp)
	sd	s11,864(sp)
	slli	t6,t6,33
	sub	sp,sp,t1
	addi	s0,s0,-61
	addi	a1,a1,-1480
	slli	t0,t0,2
	addi	t2,t2,155
	addi	a0,a0,-1569
	addi	t0,t0,1320
	slli	t2,t2,33
	sd	a1,808(sp)
	lui	a4,%hi(.LANCHOR0)
	add	a1,t6,s0
	slli	a0,a0,12
	addi	a4,a4,%lo(.LANCHOR0)
	sd	a1,824(sp)
	addi	a0,a0,1253
	add	a1,t2,t0
	sd	a1,832(sp)
	slli	a0,a0,13
	addi	a1,a4,200
	lui	s1,%hi(.LC2)
	lui	s5,%hi(.LC11)
	addi	a0,a0,-44
	sd	a1,712(sp)
	lui	t4,%hi(.LANCHOR1)
	addi	a1,a4,600
	addi	t4,t4,%lo(.LANCHOR1)
	flh	ft5,%lo(.LC2)(s1)
	fld	fa1,%lo(.LC11)(s5)
	lui	s11,%hi(.LC3)
	lui	s10,%hi(.LC4)
	lui	s9,%hi(.LC6)
	lui	s8,%hi(.LC7)
	lui	s7,%hi(.LC9)
	lui	s6,%hi(.LC10)
	lui	s3,%hi(.LC14)
	lui	s2,%hi(.LC15)
	lui	s1,%hi(.LC17)
	lui	s5,%hi(.LC13)
	sd	a0,792(sp)
	sd	a1,704(sp)
	addi	a1,a4,1208
	flh	ft4,%lo(.LC3)(s11)
	flh	ft3,%lo(.LC4)(s10)
	fld	ft2,%lo(.LC6)(s9)
	flw	ft1,%lo(.LC7)(s8)
	flh	ft0,%lo(.LC9)(s7)
	flh	fa0,%lo(.LC10)(s6)
	fld	fa2,%lo(.LC13)(s5)
	flw	fa3,%lo(.LC14)(s3)
	flw	fa4,%lo(.LC15)(s2)
	flw	fa5,%lo(.LC17)(s1)
	sd	a1,696(sp)
	addi	a1,t4,-1488
	sd	a1,688(sp)
	addi	a1,t4,-584
	sd	a1,680(sp)
	addi	a1,t4,216
	sd	a1,672(sp)
	lui	a3,%hi(.LANCHOR2)
	addi	a1,t4,416
	addi	a3,a3,%lo(.LANCHOR2)
	sd	a1,664(sp)
	addi	a1,t4,520
	sd	a1,656(sp)
	addi	a1,a3,-1976
	sd	a1,648(sp)
	addi	a1,a3,-1776
	sd	a1,296(sp)
	addi	a1,a3,-1576
	sd	a1,640(sp)
	addi	a1,a3,24
	sd	a1,632(sp)
	addi	a1,a3,624
	sd	a1,624(sp)
	lui	a5,%hi(.LANCHOR3)
	addi	a1,a3,728
	addi	a5,a5,%lo(.LANCHOR3)
	addi	t0,a3,1336
	addi	s7,t4,-1384
	addi	s11,t4,1320
	sd	a1,616(sp)
	addi	t2,a3,-1176
	addi	t6,a3,-376
	addi	s8,a3,-176
	addi	a0,a3,224
	addi	a1,a3,832
	addi	t4,a3,936
	addi	a3,a3,1440
	sd	a3,600(sp)
	addi	a3,a5,-1856
	sd	a3,592(sp)
	addi	a3,a5,-1752
	sd	a3,584(sp)
	addi	a3,a5,-1648
	sd	a3,576(sp)
	addi	a3,a5,-1544
	sd	a3,568(sp)
	addi	a3,a5,-944
	sd	a3,560(sp)
	addi	a3,a5,-744
	sd	a3,552(sp)
	addi	a3,a5,-544
	sd	a3,544(sp)
	addi	a3,a5,-440
	sd	a3,536(sp)
	addi	a3,a5,-240
	sd	a3,528(sp)
	addi	a3,a5,-136
	sd	a3,520(sp)
	lui	t1,%hi(.LANCHOR4)
	addi	a3,a5,64
	addi	t1,t1,%lo(.LANCHOR4)
	sd	a3,512(sp)
	addi	a3,a5,864
	sd	a3,504(sp)
	addi	a3,t1,-1528
	sd	a3,496(sp)
	addi	a3,t1,-728
	sd	a3,488(sp)
	addi	a3,t1,72
	sd	a3,480(sp)
	addi	a3,t1,472
	sd	a3,472(sp)
	lui	a2,%hi(.LANCHOR5)
	addi	a3,t1,872
	addi	a2,a2,%lo(.LANCHOR5)
	sd	t0,608(sp)
	sd	a3,464(sp)
	addi	t0,t1,-1128
	addi	s10,t1,1272
	addi	a3,t1,1472
	addi	t1,t1,1776
	sd	t1,288(sp)
	addi	t1,a2,-1920
	sd	t1,280(sp)
	addi	t1,a2,-1416
	sd	t1,272(sp)
	addi	t1,a2,-1016
	sd	t1,456(sp)
	addi	t1,a2,-912
	sd	t1,448(sp)
	addi	t1,a2,-112
	sd	t1,264(sp)
	addi	t1,a2,288
	sd	t1,256(sp)
	addi	t1,a2,488
	sd	t1,248(sp)
	addi	t1,a2,888
	sd	t1,240(sp)
	addi	t1,a2,1288
	sd	t1,232(sp)
	lui	a7,%hi(.LANCHOR6)
	addi	t1,a2,1488
	addi	a7,a7,%lo(.LANCHOR6)
	sd	t1,224(sp)
	addi	t1,a2,1688
	addi	a2,a2,1888
	sd	a2,208(sp)
	addi	a2,a7,-1808
	sd	a2,200(sp)
	addi	a2,a7,-1008
	sd	a2,440(sp)
	addi	a2,a7,-208
	sd	a2,192(sp)
	addi	a2,a7,-8
	sd	a2,184(sp)
	addi	a2,a7,192
	sd	a2,176(sp)
	addi	a2,a7,392
	sd	a2,168(sp)
	addi	a2,a7,592
	sd	a2,160(sp)
	addi	a2,a7,792
	sd	a2,432(sp)
	lui	t3,%hi(.LANCHOR7)
	addi	a2,a7,1592
	addi	t3,t3,%lo(.LANCHOR7)
	sd	a2,152(sp)
	addi	a2,a7,1992
	sd	a2,424(sp)
	addi	a2,t3,-2000
	sd	a2,416(sp)
	addi	a2,t3,-1896
	sd	a2,408(sp)
	addi	a2,t3,-688
	sd	a2,144(sp)
	addi	a2,t3,112
	sd	a2,136(sp)
	addi	a2,t3,912
	sd	a2,400(sp)
	lui	a6,%hi(.LANCHOR8)
	addi	a2,t3,1712
	addi	a6,a6,%lo(.LANCHOR8)
	sd	a2,128(sp)
	addi	a2,t3,1912
	sd	a2,120(sp)
	addi	a2,a6,-1984
	sd	a2,112(sp)
	addi	a2,a6,-1584
	sd	a2,104(sp)
	addi	a2,a6,-1184
	sd	a2,96(sp)
	addi	a2,a6,-984
	sd	a2,392(sp)
	addi	a2,a6,-880
	sd	a2,88(sp)
	sd	t1,216(sp)
	addi	a2,a6,-80
	sd	a2,80(sp)
	addi	a2,a6,1120
	sd	a2,384(sp)
	addi	a2,a6,1320
	lui	s1,%hi(.LANCHOR9)
	sd	a2,72(sp)
	addi	a2,a6,1520
	addi	s1,s1,%lo(.LANCHOR9)
	sd	a2,64(sp)
	addi	a2,a6,1720
	sd	a2,376(sp)
	addi	a2,s1,-1576
	sd	a2,368(sp)
	addi	a2,s1,-1376
	sd	a2,56(sp)
	addi	a2,s1,-976
	sd	a2,48(sp)
	addi	a2,s1,-576
	sd	a2,40(sp)
	addi	a2,s1,-176
	sd	a2,360(sp)
	addi	a2,s1,-72
	sd	a2,32(sp)
	addi	a2,s1,128
	lui	t5,%hi(.LANCHOR10)
	sd	a2,352(sp)
	addi	a2,s1,928
	addi	t5,t5,%lo(.LANCHOR10)
	frrm	s4
	sd	a2,24(sp)
	csrwi	vxrm,0
	addi	a2,s1,1328
	sd	a2,16(sp)
	addi	a2,t5,-1568
	fsrmi	0
	sd	a2,344(sp)
	addi	a2,t5,-1464
	sd	a2,336(sp)
	addi	a2,t5,-560
	sd	a2,8(sp)
	addi	a2,t5,-360
	sd	a2,328(sp)
	addi	a2,t5,-256
	sd	a2,320(sp)
	li	a2,953679872
	addi	a2,a2,1082
	csrr	a7,vlenb
	srli	a7,a7,2
	sd	a2,800(sp)
	li	a2,1243648000
	addiw	a2,a2,-93
	slli	a6,a7,3
	add	a6,a6,a7
	sw	a2,816(sp)
	li	a2,-16384
	addiw	a2,a2,1154
	add	a6,a6,sp
	csrr	a7,vlenb
	sh	a2,860(a6)
	srli	a7,a7,2
	li	a2,321777664
	addiw	a2,a2,483
	slli	a6,a7,3
	sw	a2,820(sp)
	add	a6,a6,a7
	li	a2,4096
	addiw	a2,a2,184
	add	a6,a6,sp
	sh	a2,862(a6)
	vsetvli	a2,zero,e8,mf8,ta,ma
	sd	a2,856(sp)
	vsetvli	a2,zero,e8,m4,ta,ma
	addi	s6,a4,704
	addi	s5,a4,1408
	addi	s1,s1,1728
	addi	t5,t5,-56
	sd	a2,848(sp)
	vsetvli	a2,zero,e8,m1,ta,ma
	addi	s3,a5,-1144
	addi	s9,a5,968
	addi	s2,a4,1104
	addi	s0,a4,1808
	addi	a5,a5,1768
	li	t3,100
	sd	a2,840(sp)
	sd	t5,720(sp)
	sd	s1,304(sp)
	sd	s11,728(sp)
	sd	s7,736(sp)
	sd	s5,744(sp)
	sd	s6,752(sp)
.L21:
	ld	a6,16(sp)
	vsetvli	a2,t3,e64,m1,ta,ma
	sd	a0,784(sp)
	sd	a5,776(sp)
	sd	t0,768(sp)
	vle32.v	v5,0(a6)
	ld	t1,368(sp)
	ld	a6,720(sp)
	vid.v	v12
	vle16.v	v2,0(t1)
	vle8.v	v1,0(a6)
	ld	s1,800(sp)
	vsetvli	zero,zero,e8,mf8,ta,ma
	vid.v	v3
	vsetvli	zero,zero,e64,m1,ta,ma
	vsll.vi	v14,v12,1
	csrr	a0,vlenb
	vsetvli	zero,zero,e32,mf2,ta,ma
	vslidedown.vx	v5,v5,s1
	srli	a0,a0,1
	li	a5,91
	mul	a5,a5,a0
	vmv1r.v	v15,v5
	vid.v	v6
	vsetvli	zero,zero,e16,mf4,ta,ma
	vfwnmsac.vf	v15,ft3,v2
	vsetvli	zero,zero,e8,mf8,ta,ma
	vmseq.vi	v0,v1,1
	vsetvli	zero,zero,e32,mf2,ta,ma
	ld	a7,8(sp)
	vfcvt.x.f.v	v2,v5,v0.t
	addi	a5,a5,864
	vsetvli	s1,zero,e32,mf2,ta,ma
	add	a5,a5,sp
	vse32.v	v2,0(a5)
	fsrm	s4
	add	s1,a6,a2
	subw	t3,t3,a2
	sd	t3,760(sp)
	vsetvli	zero,a2,e16,mf4,ta,ma
	sd	s1,720(sp)
	vluxei64.v	v4,(a7),v14,v0.t
	vsetvli	zero,zero,e8,mf8,ta,ma
	vsll.vi	v27,v3,1
	ld	a7,96(sp)
	vsll.vi	v9,v3,2
	vsetvli	zero,zero,e32,mf2,ta,ma
	vsll.vi	v7,v6,3
	vsetvli	zero,zero,e16,mf4,ta,ma
	vluxei8.v	v18,(a7),v27,v0.t
	ld	a7,288(sp)
	vsetvli	zero,zero,e32,mf2,ta,ma
	csrr	a0,vlenb
	vloxei8.v	v10,(a7),v9
	ld	a7,88(sp)
	vsetvli	zero,zero,e16,mf4,ta,ma
	vfmin.vf	v4,v4,ft5
	vsetvli	zero,zero,e64,m1,ta,ma
	vluxei32.v	v11,(a7),v7,v0.t
	vsetvli	zero,zero,e16,mf4,ta,ma
	vfsgnj.vf	v8,v4,ft4,v0.t
	vid.v	v2
	slli	a5,a0,4
	vsetvli	zero,zero,e32,mf2,ta,ma
	vsll.vi	v4,v6,1
	add	a5,a5,a0
	vsetvli	zero,zero,e64,m1,ta,ma
	vsll.vi	v24,v12,3
	vsll.vi	v16,v12,0
	addi	a5,a5,864
	vsetvli	zero,zero,e16,mf4,ta,ma
	vsll.vi	v17,v2,1
	vsll.vi	v13,v2,0
	add	a5,a5,sp
	vsll.vi	v2,v2,2
	vsetvli	s1,zero,e16,mf4,ta,ma
	vse16.v	v18,0(a5)
	vsetvli	zero,a2,e16,mf4,ta,ma
	vfwmacc.vv	v10,v18,v8
	srli	a0,a0,2
	slli	a5,a0,3
	add	a5,a5,a0
	addi	a5,a5,864
	vsetvli	s1,zero,e32,mf2,ta,ma
	add	a5,a5,sp
	vse32.v	v10,0(a5)
	ld	t5,104(sp)
	csrr	a0,vlenb
	li	a5,10
	vsetvli	zero,a2,e64,m1,ta,ma
	mul	a5,a5,a0
	vfsub.vf	v22,v11,ft2,v0.t
	vsetvli	zero,zero,e32,mf2,ta,ma
	vloxei8.v	v30,(t5),v9,v0.t
	ld	t5,320(sp)
	ld	s1,80(sp)
	vsll.vi	v10,v6,0
	vsetvli	zero,zero,e16,mf4,ta,ma
	vluxei32.v	v11,(t5),v4,v0.t
	vsetvli	zero,zero,e64,m1,ta,ma
	vluxei32.v	v8,(s1),v7
	addi	a5,a5,864
	add	a5,a5,sp
	ld	s1,376(sp)
	csrr	t3,vlenb
	fsrmi	0
	li	t0,-37
	li	a7,76
	vs1r.v	v8,0(a5)
	slli	a5,a0,4
	addi	a5,a5,864
	add	a5,a5,sp
	srli	a0,a0,2
	vloxei64.v	v9,(s1),v24,v0.t
	vsetvli	zero,zero,e16,mf4,ta,ma
	vs1r.v	v9,0(a5)
	addi	a5,sp,864
	vs1r.v	v14,0(a5)
	li	a5,69
	mul	a5,a5,a0
	ld	s5,64(sp)
	csrr	a0,vlenb
	srli	a0,a0,1
	vluxei64.v	v19,(s5),v14
	vsetvli	s6,zero,e16,mf4,ta,ma
	ld	s5,72(sp)
	ld	s7,112(sp)
	addi	a5,a5,864
	add	a5,a5,sp
	vse16.v	v19,0(a5)
	li	a5,35
	mul	a5,a5,a0
	vsetvli	zero,a2,e16,mf4,ta,ma
	csrr	a0,vlenb
	srli	a0,a0,2
	vle16.v	v9,0(s5),v0.t
	vsetvli	a6,zero,e16,mf4,ta,ma
	ld	s5,392(sp)
	csrr	a6,vlenb
	srli	a6,a6,1
	addi	a5,a5,864
	add	a5,a5,sp
	vse16.v	v9,0(a5)
	csrr	a5,vlenb
	slli	a5,a5,3
	addi	a5,a5,864
	add	a5,a5,sp
	vs1r.v	v16,0(a5)
	li	a5,73
	mul	a5,a5,a0
	vsetvli	zero,a2,e8,mf8,ta,ma
	csrr	a0,vlenb
	srli	a0,a0,3
	vloxei64.v	v8,(s5),v16,v0.t
	vsetvli	s6,zero,e8,mf8,ta,ma
	ld	s6,32(sp)
	addi	a5,a5,864
	add	a5,a5,sp
	vse8.v	v8,0(a5)
	li	a5,23
	mul	a5,a5,a0
	csrr	a0,vlenb
	addi	a5,a5,864
	add	a5,a5,sp
	vse16.v	v17,0(a5)
	vsetvli	zero,a2,e16,mf4,ta,ma
	li	a5,11
	mul	a5,a5,a0
	ld	a0,336(sp)
	vluxei16.v	v25,(s6),v17
	ld	s6,232(sp)
	vle16.v	v14,0(s6)
	ld	s6,328(sp)
	vsetvli	zero,a2,e8,m2,ta,ma
	addi	a5,a5,864
	vle8.v	v8,0(s6)
	add	a5,a5,sp
	vsetvli	zero,a2,e8,mf8,ta,ma
	vs2r.v	v8,0(a5)
	li	a5,37
	mul	a5,a5,a6
	li	a6,13
	vloxei16.v	v18,(a0),v13
	vsetvli	zero,zero,e32,mf2,ta,ma
	vmv1r.v	v13,v18
	vluxei16.v	v18,(s7),v2
	addi	a5,a5,864
	vsetvli	s11,zero,e32,mf2,ta,ma
	add	a5,a5,sp
	mul	a6,a6,t3
	ld	s7,24(sp)
	vse32.v	v18,0(a5)
	ld	a5,344(sp)
	vsetvli	zero,a2,e8,m1,ta,ma
	add	s11,s6,a2
	vle8.v	v20,0(a5)
	vsetvli	zero,a2,e64,m1,ta,ma
	addi	a6,a6,864
	add	a6,a6,sp
	vs1r.v	v20,0(a6)
	ld	a6,304(sp)
	vle64.v	v21,0(a6)
	li	a6,14
	mul	a6,a6,t3
	srli	t3,t3,1
	vsetvli	zero,a2,e32,m1,ta,ma
	addi	a6,a6,864
	add	a6,a6,sp
	vs1r.v	v21,0(a6)
	li	a6,19
	mul	a6,a6,t3
	csrr	t3,vlenb
	srli	t3,t3,1
	vle32.v	v2,0(s7)
	vsetvli	s7,zero,e32,mf2,ta,ma
	addi	a6,a6,864
	add	a6,a6,sp
	vse32.v	v15,0(a6)
	sd	s11,328(sp)
	ld	s7,352(sp)
	add	s11,a0,a2
	sd	s11,336(sp)
	ld	a0,40(sp)
	add	s11,a5,a2
	sd	s11,344(sp)
	vsetvli	zero,a2,e32,mf2,ta,ma
	vmv1r.v	v28,v5
	vfnmsac.vf	v28,ft1,v15
	ld	s6,360(sp)
	vle64.v	v15,0(s7)
	vsetvli	zero,zero,e8,mf8,ta,ma
	vle32.v	v29,0(a0)
	ld	a0,48(sp)
	vluxei32.v	v8,(s6),v10
	vsetvli	zero,a2,e32,m1,ta,ma
	vle32.v	v26,0(a0)
	csrr	a0,vlenb
	slli	a5,a0,4
	sub	a5,a5,a0
	addi	a5,a5,864
	add	a5,a5,sp
	vs1r.v	v26,0(a5)
	ld	a0,56(sp)
	vsetvli	zero,a2,e32,m4,ta,ma
	csrr	a5,vlenb
	slli	a5,a5,2
	addi	a5,a5,864
	vle32.v	v16,0(a0)
	add	a5,a5,sp
	csrr	a6,vlenb
	srli	a6,a6,2
	ld	a0,384(sp)
	vsetvli	zero,a2,e16,mf4,ta,ma
	vs4r.v	v16,0(a5)
	li	a5,71
	mul	a5,a5,a6
	ld	a6,136(sp)
	fsrm	s4
	vle16.v	v31,0(a0)
	vsetvli	s11,zero,e16,mf4,ta,ma
	ld	s11,120(sp)
	addi	a5,a5,864
	add	a5,a5,sp
	vse16.v	v31,0(a5)
	li	a5,45
	mul	a5,a5,t3
	vsetvli	zero,a2,e16,mf4,ta,ma
	vle16.v	v16,0(s11)
	ld	s11,128(sp)
	vle16.v	v19,0(s11)
	vsetvli	s11,zero,e16,mf4,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	ld	s11,400(sp)
	vse16.v	v19,0(a5)
	li	a5,47
	mul	a5,a5,t3
	vsetvli	zero,a2,e64,m1,ta,ma
	vle64.v	v18,0(s11)
	addi	a5,a5,864
	add	a5,a5,sp
	vs1r.v	v18,0(a5)
	li	a5,49
	mul	a5,a5,t3
	li	t3,27
	vle64.v	v0,0(a6)
	ld	a6,144(sp)
	addi	a5,a5,864
	add	a5,a5,sp
	vs1r.v	v0,0(a5)
	csrr	a5,vlenb
	srli	a5,a5,3
	mul	t3,t3,a5
	vle64.v	v20,0(a6)
	ld	a6,200(sp)
	vle64.v	v21,0(a6)
	ld	a6,208(sp)
	vmv1r.v	v18,v20
	addi	t3,t3,864
	vle32.v	v31,0(a6)
	ld	a6,240(sp)
	add	t3,t3,sp
	vle32.v	v17,0(a6)
	ld	a6,416(sp)
	vle8.v	v23,0(a6)
	vsetvli	a5,zero,e8,mf8,ta,ma
	vse8.v	v13,0(t3)
	vsetvli	zero,a2,e8,mf8,ta,ma
	vnsra.wv	v26,v16,v13
	csrr	a5,vlenb
	vmv1r.v	v13,v22
	addi	a5,a5,864
	add	a5,a5,sp
	vsetvli	zero,zero,e64,m1,ta,ma
	vs1r.v	v22,0(a5)
	vfnmadd.vv	v13,v20,v22
	add	a5,s6,a2
	vsetvli	zero,zero,e8,mf8,ta,ma
	vmseq.vi	v0,v1,1
	sd	a5,360(sp)
	add	a5,s5,a2
	sd	a5,392(sp)
	add	a5,a6,a2
	sd	a5,416(sp)
	vsetvli	zero,zero,e16,mf4,ta,ma
	li	a5,-400
	csrr	a6,vlenb
	vmadd.vx	v11,a5,v25,v0.t
	srli	a6,a6,1
	li	a5,89
	mul	a5,a5,a6
	vsetvli	s5,zero,e16,mf4,ta,ma
	ld	s5,440(sp)
	csrr	a6,vlenb
	ld	s6,280(sp)
	csrr	t3,vlenb
	srli	t3,t3,2
	vmv1r.v	v22,v13
	fsrmi	0
	addi	a5,a5,864
	add	a5,a5,sp
	vse16.v	v11,0(a5)
	vsetvli	zero,a2,e8,mf8,ta,ma
	vmv.v.v	v25,v26
	vsetvli	zero,zero,e64,m1,ta,ma
	vsll.vi	v12,v12,2
	vsetvli	zero,zero,e32,mf2,ta,ma
	vsll.vi	v9,v6,2
	vsetvli	zero,zero,e8,mf8,ta,ma
	vdiv.vx	v25,v25,t0,v0.t
	vsetvli	zero,zero,e64,m1,ta,ma
	vloxei64.v	v11,(s5),v24
	slli	a5,a6,5
	sub	a5,a5,a6
	addi	a5,a5,864
	add	a5,a5,sp
	vsetvli	zero,zero,e32,mf2,ta,ma
	vs1r.v	v11,0(a5)
	mv	a5,a6
	li	a6,44
	mul	a6,a6,a5
	csrr	t0,vlenb
	vluxei64.v	v11,(s6),v12,v0.t
	vsetvli	a5,zero,e32,mf2,ta,ma
	ld	s6,176(sp)
	csrr	a5,vlenb
	addi	a6,a6,864
	add	a6,a6,sp
	vse32.v	v11,0(a6)
	vsetvli	zero,a2,e16,mf4,ta,ma
	slli	a6,a5,5
	addi	a6,a6,864
	add	a6,a6,sp
	vluxei32.v	v24,(s6),v4
	vsetvli	a5,zero,e16,mf4,ta,ma
	ld	s6,216(sp)
	csrr	a5,vlenb
	srli	a5,a5,2
	vse16.v	v24,0(a6)
	vsetvli	zero,a2,e16,mf4,ta,ma
	slli	a6,a5,7
	add	a6,a6,a5
	addi	a6,a6,864
	add	a6,a6,sp
	vluxei8.v	v12,(s6),v27
	vsetvli	a5,zero,e16,mf4,ta,ma
	ld	s6,248(sp)
	csrr	a5,vlenb
	srli	a5,a5,1
	vse16.v	v12,0(a6)
	vsetvli	zero,a2,e32,mf2,ta,ma
	slli	a6,a5,6
	add	a6,a6,a5
	addi	a6,a6,864
	add	a6,a6,sp
	vle32.v	v12,0(s6),v0.t
	vsetvli	a5,zero,e32,mf2,ta,ma
	csrr	a5,vlenb
	ld	s6,256(sp)
	vse32.v	v12,0(a6)
	li	a6,48
	mul	a6,a6,a5
	vsetvli	zero,a2,e16,mf4,ta,ma
	vluxei32.v	v24,(s6),v4
	vsetvli	a5,zero,e16,mf4,ta,ma
	ld	a5,824(sp)
	addi	a6,a6,864
	add	a6,a6,sp
	vse16.v	v24,0(a6)
	vsetvli	zero,a2,e8,mf8,ta,ma
	vmseq.vi	v0,v23,1
	vsetvli	zero,zero,e64,m1,ta,ma
	ld	a6,408(sp)
	vmadc.vxm	v15,v15,a5,v0
	li	a5,195
	mul	a5,a5,t3
	vle8.v	v13,0(a6)
	csrr	t3,vlenb
	vsetvli	s6,zero,e8,mf8,ta,ma
	srli	t3,t3,1
	ld	s6,424(sp)
	addi	a5,a5,864
	add	a5,a5,sp
	vse8.v	v13,0(a5)
	li	a5,51
	mul	a5,a5,t3
	vsetvli	zero,a2,e8,m1,ta,ma
	csrr	t3,vlenb
	srli	t3,t3,1
	vle8.v	v23,0(s6)
	vsetvli	zero,a2,e32,mf2,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vs1r.v	v23,0(a5)
	ld	a5,152(sp)
	vle32.v	v10,0(a5)
	li	a5,53
	mul	a5,a5,t3
	vsetvli	t3,zero,e32,mf2,ta,ma
	csrr	t3,vlenb
	srli	t3,t3,2
	addi	a5,a5,864
	add	a5,a5,sp
	vse32.v	v10,0(a5)
	slli	a5,t3,3
	add	a5,a5,t3
	vsetvli	zero,a2,e8,mf8,ta,ma
	addi	a5,a5,864
	vmseq.vi	v0,v1,1
	add	a5,a5,sp
	vsetvli	t3,zero,e32,mf2,ta,ma
	vle32.v	v10,0(a5)
	csrr	t3,vlenb
	li	a5,46
	mul	a5,a5,t3
	vsetvli	zero,a2,e32,mf2,ta,ma
	vfwnmacc.vv	v18,v10,v5,v0.t
	vsetvli	zero,zero,e64,m1,ta,ma
	vfmacc.vf	v21,fa2,v22,v0.t
	vmv1r.v	v0,v15
	fsrm	s4
	addi	a5,a5,864
	add	a5,a5,sp
	vs1r.v	v18,0(a5)
	li	a5,47
	mul	a5,a5,t3
	add	t3,a6,a2
	sd	t3,408(sp)
	add	t3,s6,a2
	sd	t3,424(sp)
	csrr	t3,vlenb
	ld	s6,160(sp)
	li	a6,1391071232
	slli	a6,a6,1
	addi	a6,a6,1175
	addi	a5,a5,864
	add	a5,a5,sp
	vs1r.v	v21,0(a5)
	ld	a5,432(sp)
	sd	a5,0(sp)
	vle64.v	v5,0(a5)
	li	a5,27
	mul	a5,a5,t3
	addi	a5,a5,864
	add	a5,a5,sp
	vs1r.v	v5,0(a5)
	li	a5,28
	mul	a5,a5,t3
	vle16.v	v20,0(s6)
	ld	s6,168(sp)
	vle16.v	v24,0(s6)
	ld	s6,184(sp)
	vsetvli	zero,a2,e16,m1,ta,ma
	addi	a5,a5,864
	vle16.v	v5,0(s6)
	add	a5,a5,sp
	ld	s6,192(sp)
	vsetvli	zero,a2,e16,m2,ta,ma
	vs1r.v	v5,0(a5)
	li	a5,29
	mul	a5,a5,t3
	vle16.v	v18,0(s6)
	ld	s6,224(sp)
	vsetvli	zero,a2,e16,mf4,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vs2r.v	v18,0(a5)
	slli	a5,t3,5
	add	a5,a5,t3
	addi	a5,a5,864
	add	a5,a5,sp
	vle16.v	v21,0(s6)
	ld	s6,264(sp)
	vsetvli	zero,a2,e32,m1,ta,ma
	vle32.v	v11,0(s6)
	vsetvli	zero,a2,e8,m2,ta,ma
	vs1r.v	v11,0(a5)
	li	a5,42
	mul	a5,a5,t3
	ld	s6,456(sp)
	ld	t3,272(sp)
	vle8.v	v10,0(s6)
	addi	a5,a5,864
	add	a5,a5,sp
	vs2r.v	v10,0(a5)
	slli	a5,t0,3
	add	a5,a5,t0
	addi	a5,a5,864
	vsetvli	t0,zero,e32,mf2,ta,ma
	add	a5,a5,sp
	vse32.v	v9,0(a5)
	vsetvli	zero,a2,e32,mf2,ta,ma
	csrr	t0,vlenb
	srli	t0,t0,3
	vloxei32.v	v23,(t3),v9
	ld	t3,856(sp)
	vsetvli	zero,t3,e8,mf8,ta,ma
	csrr	t3,vlenb
	srli	t3,t3,2
	slli	a5,t3,3
	add	a5,a5,t3
	add	a5,a5,sp
	lhu	t3,860(a5)
	li	a5,25
	mul	a5,a5,t0
	vmv.v.i	v5,0
	vsetvli	t0,zero,e16,mf4,ta,ma
	csrr	t0,vlenb
	srli	t0,t0,1
	addi	a5,a5,864
	add	a5,a5,sp
	vse16.v	v14,0(a5)
	vsetvli	zero,a2,e16,mf4,ta,ma
	vor.vx	v18,v14,t3
	csrr	t3,vlenb
	srli	t3,t3,1
	slli	a5,t3,3
	sub	a5,a5,t3
	addi	a5,a5,864
	vsetvli	t3,zero,e8,mf8,ta,ma
	add	a5,a5,sp
	vse8.v	v8,0(a5)
	vsetvli	zero,a2,e8,mf8,ta,ma
	vasubu.vx	v22,v8,a7
	li	a5,34
	csrr	a7,vlenb
	mul	a5,a5,a7
	ld	t3,448(sp)
	vmerge.vim	v19,v5,1,v0
	vsetvli	zero,a2,e64,m8,ta,ma
	vle64.v	v8,0(t3)
	ld	a7,296(sp)
	addi	a5,a5,864
	add	a5,a5,sp
	vs8r.v	v8,0(a5)
	li	a5,89
	mul	a5,a5,t0
	vsetvli	t0,zero,e16,mf4,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vle16.v	v0,0(a5)
	vsetvli	zero,a2,e16,mf4,ta,ma
	vse16.v	v0,0(a7)
	csrr	a7,vlenb
	slli	a5,a7,4
	add	a5,a5,a7
	addi	a5,a5,864
	vsetvli	a7,zero,e16,mf4,ta,ma
	add	a5,a5,sp
	vle16.v	v11,0(a5)
	csrr	a5,vlenb
	addi	a5,a5,864
	vsetvli	zero,a2,e16,mf4,ta,ma
	add	a5,a5,sp
	csrr	a7,vlenb
	vfmax.vf	v15,v11,fa0
	srli	a7,a7,1
	vl1re64.v	v11,0(a5)
	li	a5,89
	mul	a5,a5,a7
	vsetvli	zero,zero,e8,mf8,ta,ma
	vmseq.vi	v0,v1,1
	vsetvli	zero,zero,e32,mf2,ta,ma
	csrr	a7,vlenb
	vfwmsac.vf	v11,fa3,v31,v0.t
	srli	a7,a7,2
	vmv1r.v	v9,v28
	vfnmacc.vf	v9,fa4,v17
	vsetvli	t0,zero,e32,mf2,ta,ma
	fsrmi	0
	addi	a5,a5,864
	add	a5,a5,sp
	vs1r.v	v11,0(a5)
	li	a5,193
	mul	a5,a5,a7
	add	a7,s6,a2
	sd	a7,456(sp)
	csrr	a7,vlenb
	addi	a5,a5,864
	add	a5,a5,sp
	vse32.v	v9,0(a5)
	slli	a5,a7,4
	add	a5,a5,a7
	addi	a5,a5,864
	add	a5,a5,sp
	csrr	a7,vlenb
	vse8.v	v19,0(a5)
	srli	a7,a7,2
	li	a5,69
	mul	a5,a5,a7
	vsetvli	zero,a2,e8,mf8,ta,ma
	csrr	a7,vlenb
	vse8.v	v19,0(a3)
	vsetvli	t0,zero,e16,mf4,ta,ma
	srli	a7,a7,2
	addi	a5,a5,864
	add	a5,a5,sp
	vle16.v	v19,0(a5)
	li	a5,71
	mul	a5,a5,a7
	csrr	a7,vlenb
	srli	a7,a7,1
	addi	a5,a5,864
	add	a5,a5,sp
	vle16.v	v9,0(a5)
	li	a5,35
	mul	a5,a5,a7
	csrr	a7,vlenb
	addi	a5,a5,864
	add	a5,a5,sp
	vle16.v	v12,0(a5)
	li	a5,14
	mul	a5,a5,a7
	vsetvli	zero,a2,e16,mf4,ta,ma
	srli	a7,a7,3
	vmacc.vv	v19,v12,v9
	vsetvli	t0,zero,e8,mf8,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vlm.v	v0,0(a5)
	li	a5,391
	mul	a5,a5,a7
	vsetvli	zero,a2,e16,mf4,ta,ma
	vsadd.vv	v11,v19,v12
	vsetvli	zero,zero,e8,mf8,ta,ma
	vmerge.vim	v19,v5,1,v0
	lw	a7,816(sp)
	vsetvli	t0,zero,e8,mf8,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vse8.v	v19,0(a5)
	vsetvli	zero,a2,e32,mf2,ta,ma
	vnmsub.vx	v2,a7,v2
	csrr	a7,vlenb
	srli	a7,a7,1
	li	a5,45
	mul	a5,a5,a7
	vsetvli	a7,zero,e16,mf4,ta,ma
	csrr	a7,vlenb
	srli	a7,a7,3
	addi	a5,a5,864
	add	a5,a5,sp
	vle16.v	v19,0(a5)
	li	a5,25
	mul	a5,a5,a7
	vsetvli	zero,a2,e16,mf4,ta,ma
	vremu.vx	v14,v19,a2
	vsetvli	a7,zero,e16,mf4,ta,ma
	csrr	a7,vlenb
	srli	a7,a7,1
	addi	a5,a5,864
	add	a5,a5,sp
	vle16.v	v9,0(a5)
	slli	a5,a7,3
	sub	a5,a5,a7
	addi	a5,a5,864
	add	a5,a5,sp
	vle8.v	v13,0(a5)
	csrr	a7,vlenb
	li	a5,14
	mul	a5,a5,a7
	vsetvli	zero,a2,e8,mf8,ta,ma
	lw	a7,820(sp)
	vwsubu.wv	v19,v9,v13
	vsetvli	t0,zero,e16,mf4,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vse16.v	v19,0(a5)
	vsetvli	zero,a2,e32,mf2,ta,ma
	vrsub.vx	v2,v2,a7
	csrr	a7,vlenb
	slli	a5,a7,4
	sub	a5,a5,a7
	addi	a5,a5,864
	add	a5,a5,sp
	vl1re32.v	v0,0(a5)
	slli	a5,a7,4
	sub	a5,a5,a7
	addi	a5,a5,864
	add	a5,a5,sp
	srli	a7,a7,1
	vredmin.vs	v29,v29,v0
	vsetvli	zero,zero,e8,mf8,ta,ma
	vmseq.vi	v0,v1,1
	vsetvli	t0,zero,e32,mf2,ta,ma
	vs1r.v	v29,0(a5)
	li	a5,91
	mul	a5,a5,a7
	csrr	a7,vlenb
	srli	a7,a7,1
	addi	a5,a5,864
	add	a5,a5,sp
	vle32.v	v29,0(a5)
	li	a5,37
	mul	a5,a5,a7
	li	a7,539230208
	addi	a7,a7,931
	addi	a5,a5,864
	add	a5,a5,sp
	vle32.v	v12,0(a5)
	vsetvli	zero,a2,e32,mf2,ta,ma
	vsra.vx	v2,v2,a6
	csrr	a6,vlenb
	srli	a6,a6,2
	li	a5,73
	mul	a5,a5,a6
	vnmsac.vv	v30,v29,v12,v0.t
	csrr	a6,vlenb
	vsetvli	t0,zero,e8,mf8,ta,ma
	srli	a6,a6,2
	addi	a5,a5,864
	add	a5,a5,sp
	vle8.v	v29,0(a5)
	li	a5,69
	mul	a5,a5,a6
	vsetvli	zero,a2,e8,mf8,ta,ma
	csrr	a6,vlenb
	srli	a6,a6,3
	vnsrl.wv	v29,v9,v29
	vsetvli	t0,zero,e8,mf8,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vse8.v	v29,0(a5)
	li	a5,25
	mul	a5,a5,a6
	csrr	a6,vlenb
	srli	a6,a6,1
	addi	a5,a5,864
	add	a5,a5,sp
	vse16.v	v18,0(a5)
	li	a5,49
	mul	a5,a5,a6
	vsetvli	zero,a2,e16,mf4,ta,ma
	vmul.vv	v29,v9,v18,v0.t
	csrr	a6,vlenb
	vsetvli	zero,zero,e64,m1,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vl1re64.v	v0,0(a5)
	li	a5,11
	mul	a5,a5,a6
	srli	a6,a6,2
	vremu.vx	v13,v0,a2
	vsetvli	t0,zero,e8,mf8,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vle8.v	v9,0(a5)
	li	a5,195
	mul	a5,a5,a6
	csrr	a6,vlenb
	srli	a6,a6,2
	addi	a5,a5,864
	add	a5,a5,sp
	vle8.v	v18,0(a5)
	slli	a5,a6,3
	add	a5,a5,a6
	vsetvli	zero,a2,e8,mf8,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vmseq.vi	v12,v18,1
	vsetvli	t0,zero,e32,mf2,ta,ma
	vle32.v	v10,0(a5)
	vsetvli	zero,a2,e8,mf8,ta,ma
	vmseq.vi	v0,v1,1
	vsetvli	zero,zero,e32,mf2,ta,ma
	csrr	a6,vlenb
	srli	a6,a6,1
	vfnmacc.vv	v10,v17,v31,v0.t
	slli	a5,a6,3
	sub	a5,a5,a6
	addi	a5,a5,864
	vsetvli	t0,zero,e32,mf2,ta,ma
	add	a5,a5,sp
	vse32.v	v10,0(a5)
	vsetvli	zero,a2,e16,mf4,ta,ma
	vsuxei32.v	v29,(s3),v4,v0.t
	vsetvli	zero,zero,e8,mf8,ta,ma
	vsll.vi	v10,v3,0
	vsetvli	zero,zero,e16,mf4,ta,ma
	vrgather.vv	v31,v16,v14
	vsetvli	zero,zero,e8,mf8,ta,ma
	ld	s6,704(sp)
	vsll.vi	v3,v3,3
	li	a5,53
	vsoxei8.v	v22,(s6),v10
	vsetvli	zero,zero,e16,mf4,ta,ma
	vmv.v.v	v10,v15
	fsrm	s4
	li	a6,116
	ld	t0,848(sp)
	vsetvli	zero,t0,e8,m4,ta,ma
	csrr	t0,vlenb
	srli	t0,t0,1
	mul	a5,a5,t0
	vmv.v.i	v16,0
	vsetvli	t0,zero,e32,mf2,ta,ma
	csrr	t0,vlenb
	addi	a5,a5,864
	add	a5,a5,sp
	vle32.v	v8,0(a5)
	li	a5,27
	mul	a5,a5,t0
	srli	t0,t0,1
	vsetvli	zero,a2,e32,mf2,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vl1re64.v	v14,0(a5)
	li	a5,47
	mul	a5,a5,t0
	csrr	t0,vlenb
	vwredsumu.vs	v14,v8,v14
	vsetvli	zero,zero,e64,m1,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vl1re64.v	v0,0(a5)
	li	a5,11
	mul	a5,a5,t0
	vrgather.vv	v8,v0,v13
	addi	a5,a5,864
	add	a5,a5,sp
	vs1r.v	v8,0(a5)
	li	a5,13
	mul	a5,a5,t0
	vsetvli	t0,zero,e8,m4,ta,ma
	csrr	t0,vlenb
	srli	t0,t0,1
	addi	a5,a5,864
	add	a5,a5,sp
	vlm.v	v0,0(a5)
	li	a5,37
	mul	a5,a5,t0
	vsetvli	zero,a2,e8,m4,ta,ma
	csrr	t0,vlenb
	vmerge.vim	v16,v16,1,v0
	vsetvli	zero,a2,e8,mf8,ta,ma
	vmseq.vi	v0,v1,1
	vsetvli	zero,zero,e64,m1,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vs4r.v	v16,0(a5)
	li	a5,10
	mul	a5,a5,t0
	ld	t0,808(sp)
	addi	a5,a5,864
	add	a5,a5,sp
	vl1re64.v	v8,0(a5)
	csrr	a5,vlenb
	slli	a5,a5,4
	addi	a5,a5,864
	add	a5,a5,sp
	vl1re64.v	v19,0(a5)
	vmv1r.v	v17,v8
	li	a5,51
	vnmsub.vx	v17,t0,v19,v0.t
	csrr	t0,vlenb
	srli	t0,t0,1
	mul	a5,a5,t0
	vsetvli	t0,zero,e8,mf8,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vlm.v	v0,0(a5)
	csrr	a5,vlenb
	slli	a5,a5,5
	vsetvli	zero,a2,e8,mf8,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vmerge.vim	v18,v5,1,v0
	vmseq.vi	v0,v1,1
	vsetvli	t0,zero,e16,mf4,ta,ma
	vle16.v	v22,0(a5)
	csrr	a5,vlenb
	srli	a5,a5,2
	li	t0,73
	mul	t0,t0,a5
	vsetvli	zero,a2,e16,mf4,ta,ma
	vfncvt.rtz.xu.f.w	v13,v23,v0.t
	csrr	a5,vlenb
	vslideup.vx	v24,v22,a7,v0.t
	srli	a5,a5,1
	vsetvli	a7,zero,e16,mf4,ta,ma
	slli	a7,a5,3
	sub	a7,a7,a5
	addi	a7,a7,864
	addi	t0,t0,864
	add	t0,t0,sp
	vse16.v	v13,0(t0)
	ld	t0,792(sp)
	vsetvli	zero,a2,e64,m1,ta,ma
	vasub.vv	v16,v17,v19
	vmslt.vx	v13,v8,t0
	add	a7,a7,sp
	vsetvli	t0,zero,e32,mf2,ta,ma
	csrr	a5,vlenb
	vle32.v	v23,0(a7)
	srli	a5,a5,2
	li	a7,71
	mul	a7,a7,a5
	vsetvli	zero,a2,e32,mf2,ta,ma
	csrr	a5,vlenb
	vmv1r.v	v19,v28
	vfmsub.vv	v19,v23,v28,v0.t
	vsetvli	t0,zero,e32,mf2,ta,ma
	add	t0,s6,a2
	ld	s6,304(sp)
	sd	t0,704(sp)
	fsrmi	0
	addi	a7,a7,864
	add	a7,a7,sp
	vse32.v	v19,0(a7)
	slli	a7,a2,3
	add	s6,s6,a7
	sd	s6,304(sp)
	li	s6,28
	mul	s6,s6,a5
	srli	a5,a5,3
	addi	s6,s6,864
	add	s6,s6,sp
	vlm.v	v0,0(s6)
	li	s6,27
	mul	s6,s6,a5
	vsetvli	zero,a2,e8,mf8,ta,ma
	csrr	a5,vlenb
	vmerge.vim	v19,v5,1,v0
	vmnot.m	v0,v13
	vmsbc.vvm	v9,v9,v9,v0
	vmseq.vi	v0,v1,1
	vsetvli	t0,zero,e8,mf8,ta,ma
	addi	s6,s6,864
	add	s6,s6,sp
	vle8.v	v13,0(s6)
	vsetvli	zero,a2,e8,mf8,ta,ma
	vmulhu.vx	v13,v13,a6,v0.t
	slli	a6,a5,5
	sub	a6,a6,a5
	addi	a6,a6,864
	vsetvli	t0,zero,e8,mf8,ta,ma
	add	a6,a6,sp
	vse8.v	v13,0(s6)
	vl1re64.v	v13,0(a6)
	li	a6,10
	mul	a6,a6,a5
	ld	t0,832(sp)
	vsetvli	zero,a2,e64,m1,ta,ma
	srli	a5,a5,2
	vnmsub.vx	v13,t0,v8,v0.t
	vsetvli	t0,zero,e16,mf4,ta,ma
	addi	a6,a6,864
	add	a6,a6,sp
	vs1r.v	v13,0(a6)
	slli	a6,a5,7
	add	a6,a6,a5
	addi	a6,a6,864
	add	a6,a6,sp
	csrr	a5,vlenb
	vle16.v	v8,0(a6)
	li	a6,13
	mul	a6,a6,a5
	vsetvli	zero,a2,e16,mf4,ta,ma
	srli	a5,a5,1
	vnmsac.vv	v8,v21,v20,v0.t
	vsetvli	t0,zero,e16,mf4,ta,ma
	addi	a6,a6,864
	add	a6,a6,sp
	vse16.v	v8,0(a6)
	vsetvli	zero,a2,e8,mf8,ta,ma
	vmorn.mm	v0,v9,v12
	slli	a6,a5,6
	add	a6,a6,a5
	csrr	a5,vlenb
	vmerge.vim	v5,v5,1,v0
	slli	a5,a5,2
	vsetvli	zero,zero,e64,mf4,ta,ma
	vfmv.s.f	v9,ft0
	vfmv.s.f	v8,fa1
	addi	a6,a6,864
	vsetvli	zero,zero,e8,mf8,ta,ma
	addi	a5,a5,864
	vmseq.vi	v0,v1,1
	add	a6,a6,sp
	vsetvli	t0,zero,e32,mf2,ta,ma
	add	a5,a5,sp
	vle32.v	v22,0(a6)
	vle32.v	v13,0(a5)
	vmv1r.v	v12,v6
	vsetvli	zero,a2,e32,mf2,ta,ma
	csrr	a5,vlenb
	slli	a5,a5,4
	addi	a5,a5,864
	vmacc.vv	v12,v22,v13,v0.t
	add	a5,a5,sp
	vsetvli	t0,zero,e32,mf2,ta,ma
	li	a6,48
	vse32.v	v12,0(a5)
	csrr	a5,vlenb
	mul	a6,a6,a5
	srli	a5,a5,2
	addi	a6,a6,864
	add	a6,a6,sp
	vle16.v	v21,0(a6)
	slli	a6,a5,3
	add	a6,a6,a5
	add	a6,a6,sp
	lhu	t0,862(a6)
	vsetvli	zero,a2,e16,mf4,ta,ma
	csrr	a5,vlenb
	vslide1up.vx	v22,v21,t0
	vsetvli	t0,zero,e16,mf4,ta,ma
	add	t0,s7,a7
	sd	t0,352(sp)
	add	t0,s1,a7
	ld	s1,80(sp)
	srli	a5,a5,1
	li	a6,35
	mul	a6,a6,a5
	sd	t0,376(sp)
	csrr	a5,vlenb
	add	t0,s1,a7
	li	s1,44
	sd	t0,80(sp)
	mul	s1,s1,a5
	srli	a5,a5,2
	addi	a6,a6,864
	add	a6,a6,sp
	vse16.v	v22,0(a6)
	ld	a6,88(sp)
	add	t0,a6,a7
	sd	t0,88(sp)
	addi	s1,s1,864
	add	s1,s1,sp
	vle32.v	v0,0(s1)
	li	s1,193
	mul	s1,s1,a5
	ld	t0,840(sp)
	ld	a6,136(sp)
	csrr	a5,vlenb
	addi	s1,s1,864
	add	s1,s1,sp
	vle32.v	v21,0(s1)
	vsetvli	zero,a2,e32,mf2,ta,ma
	slli	s1,a5,5
	add	s1,s1,a5
	addi	s1,s1,864
	add	s1,s1,sp
	vfmsub.vf	v0,fa5,v21
	vsetvli	zero,t0,e8,m1,ta,ma
	add	t0,s11,a7
	sd	t0,400(sp)
	add	t0,a6,a7
	vmv.v.i	v20,0
	sd	t0,136(sp)
	vsetvli	t0,zero,e8,m1,ta,ma
	vmv1r.v	v13,v0
	srli	a5,a5,1
	vlm.v	v0,0(s1)
	li	s1,45
	mul	s1,s1,a5
	vsetvli	zero,a2,e8,m1,ta,ma
	addi	a5,sp,864
	vmerge.vim	v12,v20,1,v0
	vsetvli	zero,a2,e8,mf8,ta,ma
	vmv1r.v	v0,v26
	vnmsub.vv	v0,v25,v26
	addi	s1,s1,864
	add	s1,s1,sp
	vs1r.v	v12,0(s1)
	li	s1,37
	vmv1r.v	v12,v0
	vse32.v	v13,0(t4)
	vse8.v	v25,0(a1)
	vsetvli	zero,zero,e16,mf4,ta,ma
	vl1re64.v	v23,0(a5)
	vsoxei64.v	v10,(a4),v23
	vsuxei8.v	v11,(t6),v27
	vsetvli	zero,a2,e8,m4,ta,ma
	sd	a7,312(sp)
	ld	a6,144(sp)
	ld	a5,0(sp)
	add	t0,a6,a7
	ld	a6,200(sp)
	sd	t0,144(sp)
	add	t0,a5,a7
	sd	t0,432(sp)
	add	t0,s5,a7
	sd	t0,440(sp)
	add	t0,a6,a7
	csrr	a6,vlenb
	srli	a6,a6,1
	mul	s1,s1,a6
	ld	a5,616(sp)
	sd	t0,200(sp)
	add	t0,t3,a7
	sd	t0,448(sp)
	slli	a6,a2,1
	add	t0,a5,a2
	add	t1,t1,a6
	csrr	t3,vlenb
	srli	t3,t3,3
	addi	s1,s1,864
	add	s1,s1,sp
	vl4re8.v	v20,0(s1)
	li	s1,391
	vse8.v	v20,0(a5)
	vsetvli	zero,a2,e8,mf8,ta,ma
	vsmul.vv	v21,v0,v0
	sd	t0,616(sp)
	ld	a7,8(sp)
	add	t0,t5,a6
	sd	t0,320(sp)
	add	t0,a7,a6
	csrr	a7,vlenb
	srli	a7,a7,3
	mul	s1,s1,a7
	sd	t0,8(sp)
	vsetvli	t0,zero,e8,mf8,ta,ma
	ld	a5,624(sp)
	addi	s1,s1,864
	add	s1,s1,sp
	vle8.v	v0,0(s1)
	vsetvli	zero,a2,e8,mf8,ta,ma
	vse8.v	v0,0(a5)
	vmseq.vi	v0,v1,1
	ld	s6,32(sp)
	add	t0,s6,a6
	sd	t0,32(sp)
	add	t0,a5,a2
	sd	t0,624(sp)
	ld	s5,64(sp)
	sd	t1,368(sp)
	li	a5,14
	add	t1,s5,a6
	ld	s5,72(sp)
	sd	t1,64(sp)
	add	t1,s5,a6
	sd	t1,72(sp)
	vse32.v	v13,0(t4)
	add	t1,a0,a6
	sd	t1,384(sp)
	ld	a7,96(sp)
	ld	s11,120(sp)
	ld	a0,784(sp)
	add	a7,a7,a6
	sd	a7,96(sp)
	add	a7,s11,a6
	ld	s11,128(sp)
	sd	a7,120(sp)
	add	a7,s11,a6
	ld	s11,160(sp)
	sd	a7,128(sp)
	add	a7,s11,a6
	sd	a7,160(sp)
	vse32.v	v2,0(a0)
	ld	s11,168(sp)
	ld	s5,176(sp)
	add	a7,s11,a6
	ld	s11,184(sp)
	sd	a7,168(sp)
	add	a7,s5,a6
	sd	a7,176(sp)
	add	a7,s11,a6
	ld	s11,192(sp)
	ld	s5,216(sp)
	sd	a7,184(sp)
	add	s11,s11,a6
	sd	s11,192(sp)
	add	s11,s5,a6
	sd	s11,216(sp)
	vse64.v	v16,0(t2)
	slli	a7,a2,2
	ld	s11,224(sp)
	add	s11,s11,a6
	sd	s11,224(sp)
	ld	s6,232(sp)
	ld	s5,256(sp)
	add	s11,s6,a6
	sd	s11,232(sp)
	add	s11,s5,a6
	ld	s5,296(sp)
	sd	s11,256(sp)
	add	s5,s5,a6
	sd	s5,296(sp)
	vse32.v	v2,0(a0)
	ld	t1,16(sp)
	ld	s1,24(sp)
	add	s5,t1,a7
	sd	s5,16(sp)
	add	s5,s1,a7
	ld	s1,40(sp)
	sd	s5,24(sp)
	add	s5,s1,a7
	ld	s1,48(sp)
	sd	s5,40(sp)
	add	s5,s1,a7
	sd	s5,48(sp)
	vse16.v	v11,0(t6)
	ld	s1,56(sp)
	ld	t5,104(sp)
	ld	s7,112(sp)
	add	s5,s1,a7
	sd	s5,56(sp)
	add	s5,t5,a7
	ld	t5,152(sp)
	ld	s1,208(sp)
	sd	s5,104(sp)
	add	t5,t5,a7
	sd	t5,152(sp)
	add	s5,s7,a7
	add	t5,s1,a7
	sd	s5,112(sp)
	sd	t5,208(sp)
	vse16.v	v15,0(s8),v0.t
	vsetvli	zero,zero,e16,mf4,ta,ma
	vsoxei32.v	v31,(s10),v4
	ld	s1,240(sp)
	add	t5,s1,a7
	sd	t5,240(sp)
	ld	s1,248(sp)
	ld	s6,280(sp)
	add	t5,s1,a7
	ld	s1,264(sp)
	sd	t5,248(sp)
	add	t5,s1,a7
	ld	s1,272(sp)
	sd	t5,264(sp)
	add	s1,s1,a7
	sd	s1,272(sp)
	add	s1,s6,a7
	sd	s1,280(sp)
	ld	s1,464(sp)
	vse32.v	v6,0(s1),v0.t
	add	s1,s1,a7
	sd	s1,464(sp)
	ld	t1,288(sp)
	ld	s1,632(sp)
	add	t1,t1,a7
	sd	t1,288(sp)
	csrr	t1,vlenb
	mul	a5,a5,t1
	vsetvli	t1,zero,e16,mf4,ta,ma
	csrr	t1,vlenb
	addi	a5,a5,864
	add	a5,a5,sp
	vle16.v	v0,0(a5)
	vsetvli	zero,a2,e16,mf4,ta,ma
	slli	a5,t1,4
	sub	a5,a5,t1
	addi	a5,a5,864
	add	a5,a5,sp
	vse16.v	v0,0(s1)
	add	s1,s1,a6
	vsetvli	zero,a2,e32,m1,ta,ma
	sd	s1,632(sp)
	vl1re32.v	v0,0(a5)
	ld	s1,472(sp)
	slli	a5,t1,2
	addi	a5,a5,864
	add	a5,a5,sp
	vse32.v	v0,0(s1)
	vsetvli	t1,zero,e32,mf2,ta,ma
	csrr	t1,vlenb
	srli	t1,t1,1
	add	s1,s1,a7
	sd	s1,472(sp)
	vle32.v	v0,0(a5)
	li	a5,19
	mul	a5,a5,t1
	ld	s1,480(sp)
	vsetvli	zero,a2,e32,mf2,ta,ma
	vse32.v	v0,0(s1)
	vsetvli	t1,zero,e32,mf2,ta,ma
	add	s1,s1,a7
	sd	s1,480(sp)
	addi	a5,a5,864
	add	a5,a5,sp
	vle32.v	v20,0(a5)
	ld	s1,640(sp)
	vsetvli	zero,a2,e64,m1,ta,ma
	addi	a5,sp,864
	vse32.v	v20,0(s1)
	ld	t1,488(sp)
	add	s1,s1,a7
	vsoxei8.v	v17,(t1),v3
	vsetvli	zero,zero,e16,mf4,ta,ma
	vl1re64.v	v23,0(a5)
	li	a5,25
	mul	a5,a5,t3
	csrr	t3,vlenb
	vsuxei64.v	v11,(t6),v23
	vsetvli	s5,zero,e16,mf4,ta,ma
	addi	a5,a5,864
	add	a5,a5,sp
	vle16.v	v23,0(a5)
	ld	t5,696(sp)
	vsetvli	zero,a2,e8,mf8,ta,ma
	vmseq.vi	v0,v1,1
	csrr	a5,vlenb
	addi	a5,a5,864
	vse16.v	v23,0(t5)
	add	a5,a5,sp
	vse32.v	v2,0(a0),v0.t
	vsetvli	zero,zero,e16,mf4,ta,ma
	vsoxei32.v	v11,(t6),v4
	add	t6,t6,a6
	sd	s1,640(sp)
	ld	s5,312(sp)
	ld	t0,768(sp)
	add	t1,t1,s5
	sd	t1,488(sp)
	add	t1,t5,a6
	sd	t1,696(sp)
	vse32.v	v30,0(t0),v0.t
	csrr	t1,vlenb
	srli	t1,t1,2
	vse16.v	v10,0(a4)
	vl1re64.v	v6,0(a5)
	li	a5,69
	mul	a5,a5,t1
	ld	s1,656(sp)
	vse64.v	v6,0(s1)
	vsetvli	t1,zero,e8,mf8,ta,ma
	add	s1,s1,s5
	sd	s1,656(sp)
	addi	a5,a5,864
	add	a5,a5,sp
	vle8.v	v20,0(a5)
	ld	s1,664(sp)
	vsetvli	zero,a2,e8,mf8,ta,ma
	slli	a5,t3,3
	add	a5,a5,t3
	addi	a5,a5,864
	vse8.v	v20,0(s1)
	srli	t3,t3,2
	vsetvli	t5,zero,e32,mf2,ta,ma
	add	a5,a5,sp
	add	s1,s1,a2
	vle32.v	v6,0(a5)
	slli	a5,t3,3
	add	a5,a5,t3
	addi	a5,a5,864
	add	a5,a5,sp
	ld	t1,712(sp)
	vle32.v	v11,0(a5)
	vsetvli	zero,a2,e32,mf2,ta,ma
	li	a5,11
	csrr	t3,vlenb
	srli	t5,t3,3
	vsoxei32.v	v11,(t1),v6,v0.t
	sd	s1,664(sp)
	add	s1,t1,a7
	sd	s1,712(sp)
	vse16.v	v29,0(s3)
	csrr	t1,vlenb
	mul	a5,a5,t1
	add	s3,s3,a6
	vse32.v	v30,0(t0),v0.t
	add	t0,t0,a7
	vse16.v	v31,0(s10)
	addi	a5,a5,864
	add	a5,a5,sp
	vsetvli	zero,zero,e64,m1,ta,ma
	add	s10,s10,a6
	vl1re64.v	v29,0(a5)
	ld	s1,680(sp)
	li	a5,47
	mul	a5,a5,t1
	srli	t1,t1,1
	vsoxei32.v	v29,(s1),v7
	add	s1,s1,s5
	sd	s1,680(sp)
	ld	s1,496(sp)
	addi	a5,a5,864
	add	a5,a5,sp
	vse32.v	v28,0(s1),v0.t
	add	s1,s1,a7
	sd	s1,496(sp)
	li	s1,89
	vl1re64.v	v20,0(a5)
	mul	s1,s1,t1
	ld	a5,776(sp)
	vse64.v	v20,0(a5)
	addi	s1,s1,864
	add	s1,s1,sp
	vl1re64.v	v22,0(s1)
	csrr	s1,vlenb
	slli	t1,s1,4
	add	t1,t1,s1
	addi	t1,t1,864
	add	t1,t1,sp
	vsoxei32.v	v22,(s9),v7
	vsetvli	s1,zero,e8,mf8,ta,ma
	vle8.v	v11,0(t1)
	vsetvli	zero,a2,e64,m1,ta,ma
	li	t1,46
	mul	t1,t1,t3
	li	t3,23
	vse8.v	v11,0(a3)
	vse64.v	v14,0(s0)
	addi	t1,t1,864
	add	t1,t1,sp
	mul	t3,t3,t5
	ld	s1,688(sp)
	vse8.v	v5,0(s1)
	add	s1,s1,a2
	addi	t3,t3,864
	add	t3,t3,sp
	vl1re64.v	v5,0(t1)
	ld	s6,736(sp)
	vsuxei8.v	v5,(s6),v3,v0.t
	vse8.v	v11,0(a3)
	vsetvli	t5,zero,e16,mf4,ta,ma
	add	a3,a3,a2
	vle16.v	v17,0(t3)
	ld	t1,648(sp)
	vsetvli	zero,a2,e16,mf4,ta,ma
	li	t3,73
	vsoxei16.v	v9,(t1),v17
	sd	s1,688(sp)
	add	s1,s6,s5
	sd	s1,736(sp)
	add	s1,t1,a6
	sd	s1,648(sp)
	ld	s1,504(sp)
	csrr	t1,vlenb
	srli	t1,t1,2
	vse8.v	v18,0(s1)
	vsoxei32.v	v15,(s8),v4
	add	s1,s1,a2
	mul	t3,t3,t1
	add	s8,s8,a6
	sd	s1,504(sp)
	vse64.v	v14,0(s0)
	add	s0,s0,s5
	vse8.v	v25,0(a1)
	vsoxei8.v	v10,(a4),v27
	vsetvli	zero,zero,e64,m1,ta,ma
	addi	t3,t3,864
	add	t3,t3,sp
	add	a4,a4,a6
	ld	s1,512(sp)
	vsoxei8.v	v8,(s1),v3
	add	s1,s1,s5
	sd	s1,512(sp)
	vse8.v	v25,0(a1)
	ld	s1,672(sp)
	vse16.v	v24,0(s1)
	vsetvli	t1,zero,e16,mf4,ta,ma
	add	s1,s1,a6
	li	t1,29
	sd	s1,672(sp)
	vle16.v	v3,0(t3)
	ld	s1,520(sp)
	csrr	t3,vlenb
	mul	t1,t1,t3
	vsetvli	zero,a2,e16,mf4,ta,ma
	vse16.v	v3,0(s1)
	add	s1,s1,a6
	sd	s1,520(sp)
	ld	s1,528(sp)
	vse8.v	v19,0(s1)
	addi	t1,t1,864
	add	t1,t1,sp
	add	s1,s1,a2
	vsetvli	zero,a2,e16,m1,ta,ma
	sd	s1,528(sp)
	vl1re16.v	v3,0(t1)
	srli	t1,t3,3
	li	t3,27
	mul	t3,t3,t1
	ld	s1,536(sp)
	vse16.v	v3,0(s1)
	vsetvli	t1,zero,e8,mf8,ta,ma
	li	t1,10
	add	s1,s1,a6
	sd	s1,536(sp)
	addi	t3,t3,864
	add	t3,t3,sp
	vle8.v	v3,0(t3)
	csrr	t3,vlenb
	mul	t1,t1,t3
	ld	s1,544(sp)
	vsetvli	zero,a2,e64,m1,ta,ma
	vse8.v	v3,0(s1)
	add	s1,s1,a2
	addi	t1,t1,864
	add	t1,t1,sp
	vl1re64.v	v3,0(t1)
	ld	t1,728(sp)
	vsuxei32.v	v3,(t1),v7,v0.t
	sd	s1,544(sp)
	add	s1,t1,s5
	sd	s1,728(sp)
	vse64.v	v20,0(a5)
	mv	t1,t3
	li	t3,13
	mul	t3,t3,t1
	add	a5,a5,s5
	vse32.v	v2,0(a0)
	vsuxei32.v	v22,(s9),v7
	add	a0,a0,a7
	add	s9,s9,s5
	vse8.v	v25,0(a1)
	addi	t3,t3,864
	vsetvli	t1,zero,e16,mf4,ta,ma
	add	t3,t3,sp
	vle16.v	v3,0(t3)
	ld	s1,552(sp)
	vsetvli	zero,a2,e16,mf4,ta,ma
	li	t3,35
	vsoxei8.v	v3,(s1),v27,v0.t
	add	s1,s1,a6
	vse8.v	v26,0(s2),v0.t
	vse8.v	v26,0(s2)
	vsetvli	zero,zero,e32,mf2,ta,ma
	vsuxei32.v	v13,(t4),v6,v0.t
	add	t4,t4,a7
	add	s2,s2,a2
	sd	s1,552(sp)
	vse8.v	v25,0(a1),v0.t
	csrr	s1,vlenb
	slli	t1,s1,4
	addi	t1,t1,864
	vsetvli	s1,zero,e32,mf2,ta,ma
	add	t1,t1,sp
	vle32.v	v3,0(t1)
	csrr	t1,vlenb
	srli	t1,t1,1
	mul	t3,t3,t1
	ld	s1,744(sp)
	vsetvli	zero,a2,e32,mf2,ta,ma
	vse32.v	v3,0(s1),v0.t
	vsetvli	t1,zero,e16,mf4,ta,ma
	add	s1,s1,a7
	sd	s1,744(sp)
	addi	t3,t3,864
	add	t3,t3,sp
	vle16.v	v22,0(t3)
	ld	s1,560(sp)
	vsetvli	zero,a2,e16,mf4,ta,ma
	vse16.v	v22,0(s1)
	add	s1,s1,a6
	csrr	a6,vlenb
	srli	a6,a6,1
	slli	t1,a6,3
	sd	s1,560(sp)
	vse8.v	v25,0(a1),v0.t
	sub	t1,t1,a6
	addi	t1,t1,864
	vsetvli	a6,zero,e32,mf2,ta,ma
	add	t1,t1,sp
	li	a6,45
	vle32.v	v23,0(t1)
	csrr	t1,vlenb
	srli	t1,t1,1
	mul	a6,a6,t1
	ld	s1,568(sp)
	vsetvli	zero,a2,e32,mf2,ta,ma
	csrr	t1,vlenb
	vse32.v	v23,0(s1)
	add	s1,s1,a7
	vsetvli	zero,a2,e8,m1,ta,ma
	slli	t1,t1,3
	addi	t1,t1,864
	sd	s1,568(sp)
	addi	a6,a6,864
	add	a6,a6,sp
	vl1re8.v	v2,0(a6)
	ld	s1,576(sp)
	add	t1,t1,sp
	add	a1,a1,a2
	vse8.v	v2,0(s1)
	add	s1,s1,a2
	vsetvli	zero,a2,e8,mf8,ta,ma
	sd	s1,576(sp)
	ld	s1,584(sp)
	vse8.v	v12,0(s1)
	add	s1,s1,a2
	vl1re64.v	v2,0(t1)
	ld	a6,592(sp)
	vsoxei64.v	v21,(a6),v2
	sd	s1,584(sp)
	add	s1,a6,a2
	sd	s1,592(sp)
	csrr	s1,vlenb
	srli	s1,s1,2
	li	a6,71
	mul	a6,a6,s1
	vsetvli	s1,zero,e32,mf2,ta,ma
	ld	s1,752(sp)
	addi	a6,a6,864
	add	a6,a6,sp
	vle32.v	v19,0(a6)
	vsetvli	zero,a2,e32,mf2,ta,ma
	li	a6,34
	vse32.v	v19,0(s1),v0.t
	add	s1,s1,a7
	csrr	a7,vlenb
	mul	a6,a6,a7
	sd	s1,752(sp)
	vse64.v	v16,0(t2)
	vsetvli	zero,a2,e64,m2,ta,ma
	add	t2,t2,s5
	ld	s1,600(sp)
	addi	a6,a6,864
	add	a6,a6,sp
	vl2re64.v	v2,0(a6)
	mv	a6,a7
	li	a7,42
	mul	a7,a7,a6
	vse64.v	v2,0(s1)
	vsetvli	a6,zero,e8,mf8,ta,ma
	add	s1,s1,s5
	sd	s1,600(sp)
	ld	s1,608(sp)
	addi	a7,a7,864
	add	a7,a7,sp
	vle8.v	v1,0(a7)
	vsetvli	zero,a2,e8,mf8,ta,ma
	add	a2,s1,a2
	vse8.v	v1,0(s1)
	sd	a2,608(sp)
	ld	t3,760(sp)
	bgt	t3,zero,.L21
	fsrm	s4
	csrr	t0,vlenb
	li	t1,49
	mul	t1,t1,t0
	li	a0,0
	add	sp,sp,t1
	ld	s0,952(sp)
	ld	s1,944(sp)
	ld	s2,936(sp)
	ld	s3,928(sp)
	ld	s4,920(sp)
	ld	s5,912(sp)
	ld	s6,904(sp)
	ld	s7,896(sp)
	ld	s8,888(sp)
	ld	s9,880(sp)
	ld	s10,872(sp)
	ld	s11,864(sp)
	addi	sp,sp,960
	jr	ra
	.size	main, .-main
	.globl	data_store_vreg_memory_9
	.globl	data_store_vreg_memory_8
	.globl	data_store_vreg_memory_72
	.globl	data_store_vreg_memory_7
	.globl	data_store_vreg_memory_63
	.globl	data_store_vreg_memory_61
	.globl	data_store_vreg_memory_60
	.globl	data_store_vreg_memory_5
	.globl	data_store_vreg_memory_47
	.globl	data_store_vreg_memory_42
	.globl	data_store_vreg_memory_41
	.globl	data_store_vreg_memory_40
	.globl	data_store_vreg_memory_38
	.globl	data_store_vreg_memory_36
	.globl	data_store_vreg_memory_33
	.globl	data_store_vreg_memory_31
	.globl	data_store_vreg_memory_30
	.globl	data_store_vreg_memory_3
	.globl	data_store_vreg_memory_28
	.globl	data_store_vreg_memory_24
	.globl	data_store_vreg_memory_21
	.globl	data_store_vreg_memory_2
	.globl	data_store_vreg_memory_17
	.globl	data_store_vreg_memory_16
	.globl	data_store_vreg_memory_13
	.globl	data_store_vreg_memory_11
	.globl	data_store_vreg_memory_1
	.globl	data_store_vreg_9
	.globl	data_store_vreg_8
	.globl	data_store_vreg_7
	.globl	data_store_vreg_6
	.globl	data_store_vreg_5
	.globl	data_store_vreg_42
	.globl	data_store_vreg_41
	.globl	data_store_vreg_40
	.globl	data_store_vreg_4
	.globl	data_store_vreg_39
	.globl	data_store_vreg_38
	.globl	data_store_vreg_37
	.globl	data_store_vreg_36
	.globl	data_store_vreg_35
	.globl	data_store_vreg_34
	.globl	data_store_vreg_33
	.globl	data_store_vreg_32
	.globl	data_store_vreg_31
	.globl	data_store_vreg_30
	.globl	data_store_vreg_3
	.globl	data_store_vreg_29
	.globl	data_store_vreg_28
	.globl	data_store_vreg_27
	.globl	data_store_vreg_26
	.globl	data_store_vreg_25
	.globl	data_store_vreg_24
	.globl	data_store_vreg_23
	.globl	data_store_vreg_22
	.globl	data_store_vreg_21
	.globl	data_store_vreg_20
	.globl	data_store_vreg_2
	.globl	data_store_vreg_19
	.globl	data_store_vreg_18
	.globl	data_store_vreg_17
	.globl	data_store_vreg_16
	.globl	data_store_vreg_15
	.globl	data_store_vreg_14
	.globl	data_store_vreg_13
	.globl	data_store_vreg_12
	.globl	data_store_vreg_11
	.globl	data_store_vreg_10
	.globl	data_store_vreg_1
	.globl	data_store_vreg_0
	.globl	data_load_9
	.globl	data_load_8
	.globl	data_load_79
	.globl	data_load_78
	.globl	data_load_77
	.globl	data_load_76
	.globl	data_load_75
	.globl	data_load_74
	.globl	data_load_73
	.globl	data_load_72
	.globl	data_load_71
	.globl	data_load_70
	.globl	data_load_7
	.globl	data_load_69
	.globl	data_load_68
	.globl	data_load_67
	.globl	data_load_66
	.globl	data_load_65
	.globl	data_load_64
	.globl	data_load_63
	.globl	data_load_62
	.globl	data_load_61
	.globl	data_load_60
	.globl	data_load_6
	.globl	data_load_59
	.globl	data_load_58
	.globl	data_load_57
	.globl	data_load_56
	.globl	data_load_55
	.globl	data_load_54
	.globl	data_load_53
	.globl	data_load_52
	.globl	data_load_51
	.globl	data_load_50
	.globl	data_load_5
	.globl	data_load_49
	.globl	data_load_48
	.globl	data_load_47
	.globl	data_load_46
	.globl	data_load_45
	.globl	data_load_44
	.globl	data_load_43
	.globl	data_load_42
	.globl	data_load_41
	.globl	data_load_40
	.globl	data_load_4
	.globl	data_load_39
	.globl	data_load_38
	.globl	data_load_37
	.globl	data_load_36
	.globl	data_load_35
	.globl	data_load_34
	.globl	data_load_33
	.globl	data_load_32
	.globl	data_load_31
	.globl	data_load_30
	.globl	data_load_3
	.globl	data_load_29
	.globl	data_load_28
	.globl	data_load_27
	.globl	data_load_26
	.globl	data_load_25
	.globl	data_load_24
	.globl	data_load_23
	.globl	data_load_22
	.globl	data_load_21
	.globl	data_load_20
	.globl	data_load_2
	.globl	data_load_19
	.globl	data_load_18
	.globl	data_load_17
	.globl	data_load_16
	.globl	data_load_15
	.globl	data_load_14
	.globl	data_load_13
	.globl	data_load_12
	.globl	data_load_11
	.globl	data_load_10
	.globl	data_load_1
	.globl	data_load_0
	.globl	data_mask
	.section	.srodata.cst2,"aM",@progbits,2
	.align	1
.LC2:
	.half	5566
	.align	1
.LC3:
	.half	20419
	.align	1
.LC4:
	.half	13771
	.section	.srodata.cst8,"aM",@progbits,8
	.align	3
.LC6:
	.word	45746
	.word	0
	.section	.srodata.cst4,"aM",@progbits,4
	.align	2
.LC7:
	.word	10330
	.section	.srodata.cst2
	.align	1
.LC9:
	.half	-6664
	.align	1
.LC10:
	.half	3391
	.section	.srodata.cst8
	.align	3
.LC11:
	.word	30491
	.word	0
	.align	3
.LC13:
	.word	14616
	.word	0
	.section	.srodata.cst4
	.align	2
.LC14:
	.word	52139
	.align	2
.LC15:
	.word	9735
	.align	2
.LC17:
	.word	21630
	.bss
	.align	3
	.set	.LANCHOR0,. + 0
	.set	.LANCHOR1,. + 4096
	.set	.LANCHOR2,. + 8192
	.set	.LANCHOR3,. + 12288
	.set	.LANCHOR4,. + 16384
	.set	.LANCHOR5,. + 20480
	.set	.LANCHOR6,. + 24576
	.set	.LANCHOR7,. + 28672
	.set	.LANCHOR8,. + 32768
	.set	.LANCHOR9,. + 36864
	.set	.LANCHOR10,. + 40960
	.type	data_store_vreg_memory_9, @object
	.size	data_store_vreg_memory_9, 200
data_store_vreg_memory_9:
	.zero	200
	.type	data_store_vreg_memory_8, @object
	.size	data_store_vreg_memory_8, 400
data_store_vreg_memory_8:
	.zero	400
	.type	data_store_vreg_memory_7, @object
	.size	data_store_vreg_memory_7, 100
data_store_vreg_memory_7:
	.zero	100
	.zero	4
	.type	data_store_vreg_memory_61, @object
	.size	data_store_vreg_memory_61, 400
data_store_vreg_memory_61:
	.zero	400
	.type	data_store_vreg_memory_60, @object
	.size	data_store_vreg_memory_60, 100
data_store_vreg_memory_60:
	.zero	100
	.zero	4
	.type	data_store_vreg_memory_5, @object
	.size	data_store_vreg_memory_5, 200
data_store_vreg_memory_5:
	.zero	200
	.type	data_store_vreg_memory_47, @object
	.size	data_store_vreg_memory_47, 400
data_store_vreg_memory_47:
	.zero	400
	.type	data_store_vreg_memory_42, @object
	.size	data_store_vreg_memory_42, 800
data_store_vreg_memory_42:
	.zero	800
	.type	data_store_vreg_memory_41, @object
	.size	data_store_vreg_memory_41, 100
data_store_vreg_memory_41:
	.zero	100
	.zero	4
	.type	data_store_vreg_memory_40, @object
	.size	data_store_vreg_memory_40, 800
data_store_vreg_memory_40:
	.zero	800
	.type	data_store_vreg_memory_38, @object
	.size	data_store_vreg_memory_38, 800
data_store_vreg_memory_38:
	.zero	800
	.type	data_store_vreg_memory_36, @object
	.size	data_store_vreg_memory_36, 200
data_store_vreg_memory_36:
	.zero	200
	.type	data_store_vreg_memory_31, @object
	.size	data_store_vreg_memory_31, 100
data_store_vreg_memory_31:
	.zero	100
	.zero	4
	.type	data_store_vreg_memory_30, @object
	.size	data_store_vreg_memory_30, 800
data_store_vreg_memory_30:
	.zero	800
	.type	data_store_vreg_memory_3, @object
	.size	data_store_vreg_memory_3, 800
data_store_vreg_memory_3:
	.zero	800
	.type	data_store_vreg_memory_24, @object
	.size	data_store_vreg_memory_24, 200
data_store_vreg_memory_24:
	.zero	200
	.type	data_store_vreg_memory_2, @object
	.size	data_store_vreg_memory_2, 200
data_store_vreg_memory_2:
	.zero	200
	.type	data_store_vreg_memory_17, @object
	.size	data_store_vreg_memory_17, 400
data_store_vreg_memory_17:
	.zero	400
	.type	data_store_vreg_memory_16, @object
	.size	data_store_vreg_memory_16, 800
data_store_vreg_memory_16:
	.zero	800
	.type	data_store_vreg_memory_13, @object
	.size	data_store_vreg_memory_13, 200
data_store_vreg_memory_13:
	.zero	200
	.type	data_store_vreg_memory_11, @object
	.size	data_store_vreg_memory_11, 200
data_store_vreg_memory_11:
	.zero	200
	.type	data_store_vreg_memory_1, @object
	.size	data_store_vreg_memory_1, 200
data_store_vreg_memory_1:
	.zero	200
	.type	data_store_vreg_9, @object
	.size	data_store_vreg_9, 400
data_store_vreg_9:
	.zero	400
	.type	data_store_vreg_8, @object
	.size	data_store_vreg_8, 100
data_store_vreg_8:
	.zero	100
	.zero	4
	.type	data_store_vreg_7, @object
	.size	data_store_vreg_7, 100
data_store_vreg_7:
	.zero	100
	.zero	4
	.type	data_store_vreg_5, @object
	.size	data_store_vreg_5, 100
data_store_vreg_5:
	.zero	100
	.zero	4
	.type	data_store_vreg_4, @object
	.size	data_store_vreg_4, 400
data_store_vreg_4:
	.zero	400
	.type	data_store_vreg_36, @object
	.size	data_store_vreg_36, 100
data_store_vreg_36:
	.zero	100
	.zero	4
	.type	data_store_vreg_35, @object
	.size	data_store_vreg_35, 800
data_store_vreg_35:
	.zero	800
	.type	data_store_vreg_34, @object
	.size	data_store_vreg_34, 100
data_store_vreg_34:
	.zero	100
	.zero	4
	.type	data_store_vreg_33, @object
	.size	data_store_vreg_33, 100
data_store_vreg_33:
	.zero	100
	.zero	4
	.type	data_store_vreg_31, @object
	.size	data_store_vreg_31, 100
data_store_vreg_31:
	.zero	100
	.zero	4
	.type	data_store_vreg_30, @object
	.size	data_store_vreg_30, 400
data_store_vreg_30:
	.zero	400
	.type	data_store_vreg_3, @object
	.size	data_store_vreg_3, 200
data_store_vreg_3:
	.zero	200
	.type	data_store_vreg_29, @object
	.size	data_store_vreg_29, 200
data_store_vreg_29:
	.zero	200
	.type	data_store_vreg_27, @object
	.size	data_store_vreg_27, 200
data_store_vreg_27:
	.zero	200
	.type	data_store_vreg_26, @object
	.size	data_store_vreg_26, 100
data_store_vreg_26:
	.zero	100
	.zero	4
	.type	data_store_vreg_25, @object
	.size	data_store_vreg_25, 200
data_store_vreg_25:
	.zero	200
	.type	data_store_vreg_24, @object
	.size	data_store_vreg_24, 100
data_store_vreg_24:
	.zero	100
	.zero	4
	.type	data_store_vreg_23, @object
	.size	data_store_vreg_23, 200
data_store_vreg_23:
	.zero	200
	.type	data_store_vreg_21, @object
	.size	data_store_vreg_21, 800
data_store_vreg_21:
	.zero	800
	.type	data_store_vreg_20, @object
	.size	data_store_vreg_20, 100
data_store_vreg_20:
	.zero	100
	.zero	4
	.type	data_store_vreg_19, @object
	.size	data_store_vreg_19, 800
data_store_vreg_19:
	.zero	800
	.type	data_store_vreg_18, @object
	.size	data_store_vreg_18, 800
data_store_vreg_18:
	.zero	800
	.type	data_store_vreg_17, @object
	.size	data_store_vreg_17, 400
data_store_vreg_17:
	.zero	400
	.type	data_store_vreg_16, @object
	.size	data_store_vreg_16, 400
data_store_vreg_16:
	.zero	400
	.type	data_store_vreg_14, @object
	.size	data_store_vreg_14, 800
data_store_vreg_14:
	.zero	800
	.type	data_store_vreg_13, @object
	.size	data_store_vreg_13, 400
data_store_vreg_13:
	.zero	400
	.type	data_store_vreg_12, @object
	.size	data_store_vreg_12, 400
data_store_vreg_12:
	.zero	400
	.type	data_store_vreg_11, @object
	.size	data_store_vreg_11, 400
data_store_vreg_11:
	.zero	400
	.type	data_store_vreg_10, @object
	.size	data_store_vreg_10, 200
data_store_vreg_10:
	.zero	200
	.type	data_store_vreg_1, @object
	.size	data_store_vreg_1, 100
data_store_vreg_1:
	.zero	100
	.zero	4
	.type	data_load_9, @object
	.size	data_load_9, 200
data_load_9:
	.zero	200
	.type	data_load_8, @object
	.size	data_load_8, 400
data_load_8:
	.zero	400
	.type	data_load_77, @object
	.size	data_load_77, 400
data_load_77:
	.zero	400
	.type	data_load_76, @object
	.size	data_load_76, 100
data_load_76:
	.zero	100
	.zero	4
	.type	data_load_69, @object
	.size	data_load_69, 400
data_load_69:
	.zero	400
	.type	data_load_68, @object
	.size	data_load_68, 100
data_load_68:
	.zero	100
	.zero	4
	.type	data_load_67, @object
	.size	data_load_67, 800
data_load_67:
	.zero	800
	.type	data_load_65, @object
	.size	data_load_65, 400
data_load_65:
	.zero	400
	.type	data_load_64, @object
	.size	data_load_64, 200
data_load_64:
	.zero	200
	.type	data_load_63, @object
	.size	data_load_63, 400
data_load_63:
	.zero	400
	.type	data_load_61, @object
	.size	data_load_61, 400
data_load_61:
	.zero	400
	.type	data_load_6, @object
	.size	data_load_6, 200
data_load_6:
	.zero	200
	.type	data_load_59, @object
	.size	data_load_59, 200
data_load_59:
	.zero	200
	.type	data_load_58, @object
	.size	data_load_58, 200
data_load_58:
	.zero	200
	.type	data_load_57, @object
	.size	data_load_57, 400
data_load_57:
	.zero	400
	.type	data_load_56, @object
	.size	data_load_56, 800
data_load_56:
	.zero	800
	.type	data_load_55, @object
	.size	data_load_55, 800
data_load_55:
	.zero	800
	.type	data_load_54, @object
	.size	data_load_54, 200
data_load_54:
	.zero	200
	.type	data_load_53, @object
	.size	data_load_53, 200
data_load_53:
	.zero	200
	.type	data_load_51, @object
	.size	data_load_51, 200
data_load_51:
	.zero	200
	.type	data_load_50, @object
	.size	data_load_50, 200
data_load_50:
	.zero	200
	.type	data_load_49, @object
	.size	data_load_49, 200
data_load_49:
	.zero	200
	.type	data_load_48, @object
	.size	data_load_48, 800
data_load_48:
	.zero	800
	.type	data_load_47, @object
	.size	data_load_47, 400
data_load_47:
	.zero	400
	.type	data_load_46, @object
	.size	data_load_46, 100
data_load_46:
	.zero	100
	.zero	4
	.type	data_load_45, @object
	.size	data_load_45, 100
data_load_45:
	.zero	100
	.zero	4
	.type	data_load_44, @object
	.size	data_load_44, 100
data_load_44:
	.zero	100
	.zero	4
	.type	data_load_41, @object
	.size	data_load_41, 100
data_load_41:
	.zero	100
	.zero	4
	.type	data_load_40, @object
	.size	data_load_40, 800
data_load_40:
	.zero	800
	.type	data_load_4, @object
	.size	data_load_4, 200
data_load_4:
	.zero	200
	.type	data_load_39, @object
	.size	data_load_39, 800
data_load_39:
	.zero	800
	.type	data_load_38, @object
	.size	data_load_38, 800
data_load_38:
	.zero	800
	.type	data_load_37, @object
	.size	data_load_37, 800
data_load_37:
	.zero	800
	.type	data_load_36, @object
	.size	data_load_36, 200
data_load_36:
	.zero	200
	.type	data_load_35, @object
	.size	data_load_35, 200
data_load_35:
	.zero	200
	.type	data_load_34, @object
	.size	data_load_34, 400
data_load_34:
	.zero	400
	.type	data_load_33, @object
	.size	data_load_33, 400
data_load_33:
	.zero	400
	.type	data_load_32, @object
	.size	data_load_32, 200
data_load_32:
	.zero	200
	.type	data_load_31, @object
	.size	data_load_31, 100
data_load_31:
	.zero	100
	.zero	4
	.type	data_load_30, @object
	.size	data_load_30, 800
data_load_30:
	.zero	800
	.type	data_load_3, @object
	.size	data_load_3, 800
data_load_3:
	.zero	800
	.type	data_load_29, @object
	.size	data_load_29, 400
data_load_29:
	.zero	400
	.type	data_load_28, @object
	.size	data_load_28, 200
data_load_28:
	.zero	200
	.type	data_load_27, @object
	.size	data_load_27, 200
data_load_27:
	.zero	200
	.type	data_load_26, @object
	.size	data_load_26, 200
data_load_26:
	.zero	200
	.type	data_load_25, @object
	.size	data_load_25, 800
data_load_25:
	.zero	800
	.type	data_load_24, @object
	.size	data_load_24, 200
data_load_24:
	.zero	200
	.type	data_load_23, @object
	.size	data_load_23, 400
data_load_23:
	.zero	400
	.type	data_load_22, @object
	.size	data_load_22, 400
data_load_22:
	.zero	400
	.type	data_load_21, @object
	.size	data_load_21, 400
data_load_21:
	.zero	400
	.type	data_load_20, @object
	.size	data_load_20, 100
data_load_20:
	.zero	100
	.zero	4
	.type	data_load_2, @object
	.size	data_load_2, 200
data_load_2:
	.zero	200
	.type	data_load_19, @object
	.size	data_load_19, 800
data_load_19:
	.zero	800
	.type	data_load_18, @object
	.size	data_load_18, 400
data_load_18:
	.zero	400
	.type	data_load_17, @object
	.size	data_load_17, 400
data_load_17:
	.zero	400
	.type	data_load_16, @object
	.size	data_load_16, 800
data_load_16:
	.zero	800
	.type	data_load_15, @object
	.size	data_load_15, 100
data_load_15:
	.zero	100
	.zero	4
	.type	data_load_14, @object
	.size	data_load_14, 100
data_load_14:
	.zero	100
	.zero	4
	.type	data_load_12, @object
	.size	data_load_12, 800
data_load_12:
	.zero	800
	.type	data_load_11, @object
	.size	data_load_11, 200
data_load_11:
	.zero	200
	.type	data_load_10, @object
	.size	data_load_10, 100
data_load_10:
	.zero	100
	.zero	4
	.type	data_load_1, @object
	.size	data_load_1, 200
data_load_1:
	.zero	200
	.type	data_mask, @object
	.size	data_mask, 100
data_mask:
	.zero	100
	.zero	4
	.type	data_store_vreg_memory_72, @object
	.size	data_store_vreg_memory_72, 400
data_store_vreg_memory_72:
	.zero	400
	.type	data_store_vreg_memory_63, @object
	.size	data_store_vreg_memory_63, 400
data_store_vreg_memory_63:
	.zero	400
	.type	data_store_vreg_memory_33, @object
	.size	data_store_vreg_memory_33, 400
data_store_vreg_memory_33:
	.zero	400
	.type	data_store_vreg_memory_28, @object
	.size	data_store_vreg_memory_28, 200
data_store_vreg_memory_28:
	.zero	200
	.type	data_store_vreg_memory_21, @object
	.size	data_store_vreg_memory_21, 400
data_store_vreg_memory_21:
	.zero	400
	.type	data_store_vreg_6, @object
	.size	data_store_vreg_6, 800
data_store_vreg_6:
	.zero	800
	.type	data_store_vreg_42, @object
	.size	data_store_vreg_42, 200
data_store_vreg_42:
	.zero	200
	.type	data_store_vreg_41, @object
	.size	data_store_vreg_41, 100
data_store_vreg_41:
	.zero	100
	.zero	4
	.type	data_store_vreg_40, @object
	.size	data_store_vreg_40, 200
data_store_vreg_40:
	.zero	200
	.type	data_store_vreg_39, @object
	.size	data_store_vreg_39, 200
data_store_vreg_39:
	.zero	200
	.type	data_store_vreg_38, @object
	.size	data_store_vreg_38, 800
data_store_vreg_38:
	.zero	800
	.type	data_store_vreg_37, @object
	.size	data_store_vreg_37, 200
data_store_vreg_37:
	.zero	200
	.type	data_store_vreg_32, @object
	.size	data_store_vreg_32, 800
data_store_vreg_32:
	.zero	800
	.type	data_store_vreg_28, @object
	.size	data_store_vreg_28, 400
data_store_vreg_28:
	.zero	400
	.type	data_store_vreg_22, @object
	.size	data_store_vreg_22, 200
data_store_vreg_22:
	.zero	200
	.type	data_store_vreg_2, @object
	.size	data_store_vreg_2, 200
data_store_vreg_2:
	.zero	200
	.type	data_store_vreg_15, @object
	.size	data_store_vreg_15, 400
data_store_vreg_15:
	.zero	400
	.type	data_store_vreg_0, @object
	.size	data_store_vreg_0, 400
data_store_vreg_0:
	.zero	400
	.type	data_load_79, @object
	.size	data_load_79, 100
data_load_79:
	.zero	100
	.zero	4
	.type	data_load_78, @object
	.size	data_load_78, 100
data_load_78:
	.zero	100
	.zero	4
	.type	data_load_75, @object
	.size	data_load_75, 200
data_load_75:
	.zero	200
	.type	data_load_74, @object
	.size	data_load_74, 400
data_load_74:
	.zero	400
	.type	data_load_73, @object
	.size	data_load_73, 400
data_load_73:
	.zero	400
	.type	data_load_72, @object
	.size	data_load_72, 400
data_load_72:
	.zero	400
	.type	data_load_71, @object
	.size	data_load_71, 200
data_load_71:
	.zero	200
	.type	data_load_70, @object
	.size	data_load_70, 200
data_load_70:
	.zero	200
	.type	data_load_7, @object
	.size	data_load_7, 100
data_load_7:
	.zero	100
	.zero	4
	.type	data_load_66, @object
	.size	data_load_66, 100
data_load_66:
	.zero	100
	.zero	4
	.type	data_load_62, @object
	.size	data_load_62, 400
data_load_62:
	.zero	400
	.type	data_load_60, @object
	.size	data_load_60, 100
data_load_60:
	.zero	100
	.zero	4
	.type	data_load_52, @object
	.size	data_load_52, 200
data_load_52:
	.zero	200
	.type	data_load_5, @object
	.size	data_load_5, 200
data_load_5:
	.zero	200
	.type	data_load_43, @object
	.size	data_load_43, 800
data_load_43:
	.zero	800
	.type	data_load_42, @object
	.size	data_load_42, 800
data_load_42:
	.zero	800
	.type	data_load_13, @object
	.size	data_load_13, 200
data_load_13:
	.zero	200
	.type	data_load_0, @object
	.size	data_load_0, 800
data_load_0:
	.zero	800
	.ident	"GCC: () 15.0.0 20241117 (experimental)"
	.section	.note.GNU-stack,"",@progbits
