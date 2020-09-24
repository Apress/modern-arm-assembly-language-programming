//-------------------------------------------------
//               Ch09_03_.s
//-------------------------------------------------

// The order of entries in CvtTab must match
// the enum CvtOp that's defined in Ch09_03.cpp.

            .text
CvtTab:     .word F32_I32
            .word I32_F32
            .word F32_U32
            .word U32_F32

            .equ NumCvtTab,(. - CvtTab) / 4     // num CvtTab entries

// extern "C" bool PackedConvertF32_(Vec128& x, const Vec128& a, CvtOp cvt_op);

            .global PackedConvertF32_
PackedConvertF32_:
            cmp r2,#NumCvtTab                   // cvt_op >= NumCvtOp?
            bhs InvalidArg                      // jump if yes

            vldm r1,{q0}                        // q0 = a

            adr r3,CvtTab                       // r3 = points to CvtTab
            ldr r3,[r3,r2,lsl #2]               // r3 = target jump address
 
            mov r2,r0                           // r2 = ptr to x
            mov r0,#1                           // valid cvt_op return code
            bx r3                               // jump to target

// Convert packed I32 to packed F32
F32_I32:    vcvt.f32.s32 q1,q0
            vstm r2,{q1} 
            bx lr

// Convert packed F32 to packed I32
I32_F32:    vcvt.s32.f32 q1,q0
            vstm r2,{q1} 
            bx lr

// Convert packed U32 to packed F32
F32_U32:    vcvt.f32.u32 q1,q0
            vstm r2,{q1} 
            bx lr

// Convert packed F32 to packed U32
U32_F32:    vcvt.u32.f32 q1,q0
            vstm r2,{q1} 
            bx lr

InvalidArg: mov r0,#0                           // Invalid cvt_op return code
            bx lr
