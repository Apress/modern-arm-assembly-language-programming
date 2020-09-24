//-------------------------------------------------
//               Ch16_04_.s
//-------------------------------------------------

            .include "Ch16_04_Macros_.inc"

// Algorithm constants
            .text
r4_n0p333:  .single -0.333333333
            .balign 16
r4_4x4I:    .single 1.0, 0.0, 0.0, 0.0
            .single 0.0, 1.0, 0.0, 0.0
            .single 0.0, 0.0, 1.0, 0.0
            .single 0.0, 0.0, 0.0, 1.0

// extern "C" bool Mat4x4InvF32_(float* m_inv, const float* m, float epsilon);

            .global Mat4x4InvF32_
Mat4x4InvF32_:

// Prologue
            stp d8,d9,[sp,-16]!             // push d8, d9
            stp d10,d11,[sp,-16]!           // push d10, d11
            sub sp,sp,16                    // allocate local space

            str s0,[sp]                     // save epsilon for later

// load m into v0:v3
            ld1 {v0.4s-v3.4s},[x1]          // load  m

// Calculate t1 = trace(m)
            Mat4x4TraceF32 s28, v0,v1,v2,v3, s27       // s28 = t1

// Calculate m2 = m * m and t2 = trace(m2)
            Mat4x4MulF32 v4,v5,v6,v7, v0,v1,v2,v3, v0,v1,v2,v3

            Mat4x4TraceF32 s29, v4,v5,v6,v7, s27       // s29 = t2

// Calculate m3 = m * m * m and t3 = trace(m3)
            Mat4x4MulF32 v16,v17,v18,v19, v4,v5,v6,v7, v0,v1,v2,v3

            Mat4x4TraceF32 s30, v16,v17,v18,v19, s27   // s30 = t3

// Calculate m4 = m * m * m * m and t4 = trace(m4)
            Mat4x4MulF32 v20,v21,v22,v23, v16,v17,v18,v19, v0,v1,v2,v3

            Mat4x4TraceF32 s31, v20,v21,v22,v23, s27   // s31 = t4

// Calculate c1 = -t1
            fneg s8,s28                     // s8 = c1

// Calculate c2 = -1.0 / 2.0 * (c1 * t1 + t2)
            fmul s24,s8,s28                 // c1 * t1
            fadd s24,s24,s29                // c1 * t1 + t2
            fmov s25,-0.5
            fmul s9,s25,s24                 // c2

// Calculate c3 = -1.0 / 3.0 * (c2 * t1 + c1 * t2 + t3)
            fmul s24,s9,s28                 // c2 * t1
            fmul s25,s8,s29                 // c1 * t2
            fadd s25,s25,s30                // c1 * t2 + t3
            fadd s25,s25,s24                // sum of above expressions
            ldr s26,r4_n0p333
            fmul s10,s26,s25                // c3

// Calculate c4 = -1.0 / 4.0 * (c3 * t1 + c2 * t2 + c1 * t3 + t4)
            fmul s24,s10,s28                // c3 * t1
            fmul s25,s9,s29                 // c2 * t2
            fmul s26,s8,s30                 // c1 * t3
            fadd s26,s26,s31                // c1 * t3 + t4
            fadd s27,s24,s25
            fadd s11,s27,s26                // sum of above expressions
            fmov s25,-0.25
            fmul s11,s25,s11                // c4

// Test fabs(c4) < epsilon for singular matrix
            fabs s28,s11                    // s28 = fabs(c4)
            ldr s29,[sp]                    // s29 = epsilon
            fcmp s28,s29                    // is matrix singular?
            cset w3,lo                      // w3 = 1 if singular, else 0
            b.lo Done                       // jump if singular

// Register content summary
//  v0-v3       m               s8  c1
//  v4-v7       m2              s9  c2
//  v16-v19     m3              s10 c3
//  v20-v23     m4              s11 c4

// Calculate = -1.0 / c4 * (m3 + c1 * m2 + c2 * m + c3 * I)
    adr x4,r4_4x4I
    ld1 {v24.4s-v27.4s},[x4]                                   // load I

    Mat4x4MulScalarF32 v24,v25,v26,v27, v24,v25,v26,v27, v10   // c3 * I

    Mat4x4MulScalarF32 v0,v1,v2,v3, v0,v1,v2,v3, v9            // c2 * m

    Mat4x4MulScalarF32 v4,v5,v6,v7, v4,v5,v6,v7, v8            // c1 * m2

    Mat4x4AddF32 v28,v29,v30,v31, v24,v25,v26,v27, v0,v1,v2,v3 // c3 * I + c2 * m

    Mat4x4AddF32 v28,v29,v30,v31, v28,v29,v30,v31, v4,v5,v6,v7 // += c1 * m2

    Mat4x4AddF32 v28,v29,v30,v31, v28,v29,v30,v31, v16,v17,v18,v19  // += m3

    fmov s4,-1.0
    fdiv s4,s4,s11                                          // -1.0 / c4
    Mat4x4MulScalarF32 v0,v1,v2,v3, v28,v29,v30,v31, v4     // inverse
    st1 {v0.4s-v3.4s},[x0]                                  // save m_inv

// Epilogue
Done:       mov w0,w3                       // set return code
            add sp,sp,16                    // release local space
            ldp d10,d11,[sp],16             // pop d10, d11
            ldp d8,d9,[sp],16               // pop d8,d9
            ret
