//-------------------------------------------------
//               Ch15_05_Macros_.inc
//-------------------------------------------------

// Macro U8toF32 (uses v3 and v7 as temp registers)
            .macro U8toF32 Vd0,Vd1,Vd2,Vd3,Vs
            uxtl  v3.8h, \Vs\().8b              // promote to U16
            uxtl2 v7.8h, \Vs\().16b

            uxtl  \Vd0\().4s, v3.4h             // promote to U32
            uxtl2 \Vd1\().4s, v3.8h
            ucvtf \Vd0\().4s, \Vd0\().4s        // convert to F32  
            ucvtf \Vd1\().4s, \Vd1\().4s

            uxtl  \Vd2\().4s, v7.4h             // promote to U32
            uxtl2 \Vd3\().4s, v7.8h
            ucvtf \Vd2\().4s, \Vd2\().4s        // convert to F32
            ucvtf \Vd3\().4s, \Vd3\().4s
            .endm

// Macro F32toU8
            .macro F32toU8 Vd,Vs0,Vs1,Vs2,Vs3
            fcvtnu \Vs0\().4s, \Vs0\().4s       // convert F32 to U32
            fcvtnu \Vs1\().4s, \Vs1\().4s
            uqxtn v0.4h, \Vs0\().4s             // convert to U16
            uqxtn2 v0.8h, \Vs1\().4s

            fcvtnu \Vs2\().4s, \Vs2\().4s       // convert F32 to U32
            fcvtnu \Vs3\().4s, \Vs3\().4s
            uqxtn v1.4h, \Vs2\().4s             // convert to U16
            uqxtn2 v1.8h, \Vs3\().4s

            uqxtn \Vd\().8b, v0.8h              // convert to U8
            uqxtn2 \Vd\().16b, v1.8h
            .endm

// Macro MulCoef
            .macro MulCoef Vs0,Vs1,Vs2,Vs3,Vcoef
            fmul \Vs0\().4s, \Vs0\().4s, \Vcoef\().4s
            fmul \Vs1\().4s, \Vs1\().4s, \Vcoef\().4s
            fmul \Vs2\().4s, \Vs2\().4s, \Vcoef\().4s
            fmul \Vs3\().4s, \Vs3\().4s, \Vcoef\().4s
            .endm

// Macro SumRGB (uses v7 as temp register)
            .macro SumRGB Vr, Vg, Vb, Vc
            fadd \Vr\().4s, \Vr\().4s, \Vg\().4s
            fadd v7.4s, \Vb\().4s, \Vc\().4s
            fadd \Vr\().4s, \Vr\().4s, V7.4s
            .endm
