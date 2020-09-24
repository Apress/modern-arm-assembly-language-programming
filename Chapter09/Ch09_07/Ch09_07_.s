//-------------------------------------------------
//               Ch09_07_.s
//-------------------------------------------------

// Macro Mat4x4MulF32
//
// Input:   q0:q3       matrix m_src1
//          q8:q11      matrix m_src2
//
// Output:  q12:q15     m_src1 * m_src2
//
// Note:    registers q0:q3 and q8:q11 are not modified.

            .macro Mat4x4MulF32

// Calc row 0
            vmul.f32 q12,q8,d0[0]
            vmla.f32 q12,q9,d0[1]
            vmla.f32 q12,q10,d1[0]
            vmla.f32 q12,q11,d1[1]

// Calc row 1
            vmul.f32 q13,q8,d2[0]
            vmla.f32 q13,q9,d2[1]
            vmla.f32 q13,q10,d3[0]
            vmla.f32 q13,q11,d3[1]

// Calc row 2
            vmul.f32 q14,q8,d4[0]
            vmla.f32 q14,q9,d4[1]
            vmla.f32 q14,q10,d5[0]
            vmla.f32 q14,q11,d5[1]

// Calc row 3
            vmul.f32 q15,q8,d6[0]
            vmla.f32 q15,q9,d6[1]
            vmla.f32 q15,q10,d7[0]
            vmla.f32 q15,q11,d7[1]
            .endm

// extern "C" void Mat4x4MulF32_(float* m_des, const float* m_src1, const float* m_src2);

            .global Mat4x4MulF32_
Mat4x4MulF32_:
            vldm r1,{q0-q3}                     // q0:q3 = m_src1
            vldm r2,{q8-q11}                    // q8:q11 = m_src2

            Mat4x4MulF32                        // calc m_src1 * m_src2

            vstm r0,{q12-q15}                   // save result to m_des
            bx lr
