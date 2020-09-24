//-------------------------------------------------
//               Ch15_07_.s
//-------------------------------------------------

// Macro Mat4x4TraceF32
//
// Input Registers          Other Registers
// ------------------------------------------------
// v0   a3 a2 a1 a0         s4  matrix trace value
// v1   b3 b2 b1 b0         s5  temp register
// v2   c3 c2 c1 c0
// v3   d3 d2 d1 d0

            .macro Mat4x4TraceF32
            mov s4,v0.4s[0]                     // s4 = m[0][0]
            mov s5,v1.4s[1]                     // s5 = m[1][1]
            fadd s4,s4,s5                       // s4 = m[0][0] + m[1][1]

            mov s5,v2.4s[2]                     // s5 = m[2][2]
            fadd s4,s4,s5                       // s4 += m[2][2]

            mov s5,v3.4s[3]                     // s5 = m[3][3]
            fadd s4,s4,s5                       // s5 = += m[3][3]
            .endm

// Macro Mat4x4TraceF64
//
// Input Registers          Other Registers
// ------------------------------------------------
// v1:v0    a3 a2 a1 a0     d16 matrix trace value
// v3:v2    b3 b2 b1 b0     d17 temp register
// v5:v4    c3 c2 c1 c0
// v7:v6    d3 d2 d1 d0

            .macro Mat4x4TraceF64
            mov d16,v0.2d[0]                    // d16 = m[0][0]
            mov d17,v2.2d[1]                    // d17 = m[1][1]
            fadd d16,d16,d17                    // d16 = m[0][0] + m[1][1]

            mov d17,v5.2d[0]                    // d17 = m[2][2]
            fadd d16,d16,d17                    // d16 = m[0][0] + m[1][1]

            mov d17,v7.2d[1]                    // d16 = m[3][3]
            fadd d16,d16,d17                    // d17 = m[0][0] + m[1][1]
            .endm

// Mat4x4TransposeF32
//
//  Input Registers         Output Registers    Temp Registers
// -----------------------------------------------------------
//  v0    a3 a2 a1 a0       v0    d0 c0 b0 a0   v4
//  v1    b3 b2 b1 b0       v1    d1 c1 b1 a1   v5
//  v2    c3 c2 c1 c0       v2    d2 c2 b2 a2   v6
//  v3    d3 d2 d1 d0       v3    d3 c3 b3 a3   v7

            .macro Mat4x4TransposeF32
            trn1 v4.4s,v0.4s,v1.4s              // b2 a2 b0 a0
            trn2 v5.4s,v0.4s,v1.4s              // b3 a3 b1 a1
            trn1 v6.4s,v2.4s,v3.4s              // d2 c2 d0 c0
            trn2 v7.4s,v2.4s,v3.4s              // d3 c3 d1 c1

            trn1 v0.2d,v4.2d,v6.2d              // d0 c0 b0 a0
            trn1 v1.2d,v5.2d,v7.2d              // d1 c1 b1 a1
            trn2 v2.2d,v4.2d,v6.2d              // d2 c2 b2 a2
            trn2 v3.2d,v5.2d,v7.2d              // d3 c3 b3 a3
            .endm

// Mat4x4TransposeF64
//
// Input Registers          Output Registers
// ------------------------------------------------
// v1:v0    a3 a2 a1 a0     v17:v16     d0 c0 b0 a0
// v3:v2    b3 b2 b1 b0     v19:v18     d1 c1 b1 a1
// v5:v4    c3 c2 c1 c0     v21:v20     d2 c2 b2 a2
// v7:v6    d3 d2 d1 d0     v23:v22     d3 c3 b3 a3

            .macro Mat4x4TransposeF64
            trn1 v16.2d,v0.2d,v2.2d             // b0 a0
            trn1 v17.2d,v4.2d,v6.2d             // d0 c0
            trn2 v18.2d,v0.2d,v2.2d             // b1 a1
            trn2 v19.2d,v4.2d,v6.2d             // d1 c1

            trn1 v20.2d,v1.2d,v3.2d             // b2 a2
            trn1 v21.2d,v5.2d,v7.2d             // d2 c2
            trn2 v22.2d,v1.2d,v3.2d             // b3 a3
            trn2 v23.2d,v5.2d,v7.2d             // d3 c3
            .endm

// extern float Mat4x4TraceF32_(const float* m_src1);

            .global Mat4x4TraceF32_
Mat4x4TraceF32_:
            ld1 {v0.4s-v3.4s},[x0]              // v0:v3 = m_src1

            Mat4x4TraceF32                      // calculate trace

            fmov s0,s4
            ret

// extern double Mat4x4TraceF64_(const double* m_src1);

            .global Mat4x4TraceF64_
Mat4x4TraceF64_:
            ld1 {v0.2d-v3.2d},[x0],64           // load m_src1 into
            ld1 {v4.2d-v7.2d},[x0]              // v0:v7

            Mat4x4TraceF64                      // calculate trace

            fmov d0,d16
            ret

// extern void Mat4x4TransposeF32_(float* m_des, const float* m_src1);

            .global Mat4x4TransposeF32_
Mat4x4TransposeF32_:
            ld1 {v0.4s-v3.4s},[x1]              // v0:v3 = m_src1

            Mat4x4TransposeF32                  // transpose m_src1

            st1 {v0.4s-v3.4s},[x0]              // save result to m_des
            ret

// extern void Mat4x4TransposeF64_(float* m_des, const float* m_src1);

            .global Mat4x4TransposeF64_
Mat4x4TransposeF64_:
            ld1 {v0.2d-v3.2d},[x1],64           // v0:v3 = rows 0 and 1
            ld1 {v4.2d-v7.2d},[x1]              // v4:v7 = rows 2 and 3

            Mat4x4TransposeF64                  // transpose m_src1

            st1 {v16.2d-v19.2d},[x0],64         // save rows 0 and 1
            st1 {v20.2d-v23.2d},[x0]            // save rows 2 and 3
            ret
