//-------------------------------------------------
//               Ch09_06_.s
//-------------------------------------------------

// Macro Mat4x4TrF32
//
// Description:  This macro transposes a 4x4 matrix of single-precision
//               floating-point values.
//
//  Input Matrix                  Output Matrix
//  ---------------------------------------------------
//  q0    a3 a2 a1 a0             q0    d0 c0 b0 a0
//  q1    b3 b2 b1 b0             q1    d1 c1 b1 a1
//  q2    c3 c2 c1 c0             q2    d2 c2 b2 a2
//  q3    d3 d2 d1 d0             q3    d3 c3 b3 a3

            .macro Mat4x4TrF32

            vtrn.f32 q0,q1                  // q0 = b2 a2 b0 a0 
                                            // q1 = b3 a3 b1 a1

            vtrn.f32 q2,q3                  // q2 = d2 c2 d0 c0
                                            // q3 = d3 c3 d1 c1

            vswp d4,d1                      // q0 = d0 c0 b0 a0
                                            // q2 = d2 c2 b2 a2

            vswp d3,d6                      // q1 = d1 c1 b1 a1
                                            // q3 = d3 c3 b3 a3
            .endm

// extern "C" void Mat4x4TransposeF32a_(float* m_des, const float* m_src)

            .text
            .global Mat4x4TransposeF32a_
Mat4x4TransposeF32a_:

            vldm r1,{q0-q3}                     // load m_src into q0-q3

            Mat4x4TrF32                         // transpose m_src

            vstm r0,{q0-q3}                     // save result to m_des
            bx lr

// extern "C" void Mat4x4TransposeF32b_(float* m_des, const float* m_src)

            .global Mat4x4TransposeF32b_
Mat4x4TransposeF32b_:

            vld4.f32 {d0,d2,d4,d6},[r1]!        // q0:q3 = transpose of m_src
            vld4.f32 {d1,d3,d5,d7},[r1]

            vstm r0,{q0-q3}                     // save result to m_des
            bx lr
