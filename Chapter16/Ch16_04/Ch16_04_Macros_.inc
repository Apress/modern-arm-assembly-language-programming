//-------------------------------------------------
//               Ch16_04_Macros_.inc
//-------------------------------------------------

// Macro Mat4x4AddF32
//
// Input Registers                  Input Registers
// ----------------------------------------------------------
// A0   a3 a2 a1 a0                 B0  w3 w2 w1 w0
// A1   b3 b2 b1 b0                 B1  x3 x2 x1 x0
// A2   c3 c2 c1 c0                 B2  y3 y2 y1 y0
// A3   d3 d2 d1 d0                 B3  z3 z2 z1 z0
//
// Output Registers
// ----------------------------------------------------------
// C0   a3+w3 a2+w2 a1+w1 a0+w0
// C1   b3+x3 b2+x2 b1+x1 b0+x0
// C2   c3+y3 c2+y2 c1+y1 c0+y0
// C3   d3+z3 d2+z2 d1+z1 d0+z0

            .macro Mat4x4AddF32 C0,C1,C2,C3, A0,A1,A2,A3, B0,B1,B2,B3 

            fadd \C0\().4s, \B0\().4s, \A0\().4s    // row 0
            fadd \C1\().4s, \B1\().4s, \A1\().4s    // row 1
            fadd \C2\().4s, \B2\().4s, \A2\().4s    // row 2
            fadd \C3\().4s, \B3\().4s, \A3\().4s    // row 3
            .endm

// Macro Mat4x4MulF32
//
// Input Registers                  Input Registers
// ----------------------------------------------------------
// A0   a3 a2 a1 a0                 B0  w3 w2 w1 w0
// A1   b3 b2 b1 b0                 B1  x3 x2 x1 x0
// A2   c3 c2 c1 c0                 B2  y3 y2 y1 y0
// A3   d3 d2 d1 d0                 B3  z3 z2 z1 z0
// 
// Output Registers
// ----------------------------------------------------------
// C0   row 0 of A * B
// C1   row 1 of A * B
// C2   row 2 of A * B
// C3   row 3 of A * B

            .macro Mat4x4MulF32 C0,C1,C2,C3, A0,A1,A2,A3, B0,B1,B2,B3

            fmul \C0\().4s, \B0\().4s, \A0\().s[0]      // row 0
            fmla \C0\().4s, \B1\().4s, \A0\().s[1]
            fmla \C0\().4s, \B2\().4s, \A0\().s[2]
            fmla \C0\().4s, \B3\().4s, \A0\().s[3]

            fmul \C1\().4s, \B0\().4s, \A1\().s[0]      // row 1
            fmla \C1\().4s, \B1\().4s, \A1\().s[1]
            fmla \C1\().4s, \B2\().4s, \A1\().s[2]
            fmla \C1\().4s, \B3\().4s, \A1\().s[3]

            fmul \C2\().4s, \B0\().4s, \A2\().s[0]      // row 2
            fmla \C2\().4s, \B1\().4s, \A2\().s[1]
            fmla \C2\().4s, \B2\().4s, \A2\().s[2]
            fmla \C2\().4s, \B3\().4s, \A2\().s[3]

            fmul \C3\().4s, \B0\().4s, \A3\().s[0]      // row 3
            fmla \C3\().4s, \B1\().4s, \A3\().s[1]
            fmla \C3\().4s, \B2\().4s, \A3\().s[2]
            fmla \C3\().4s, \B3\().4s, \A3\().s[3]
            .endm

// Macro Mat4x4MulScalarF32
//
// Input Registers              Output Registers
// ----------------------------------------------------------
//  A0  a3 a2 a1 a0             B0  a3*VS a2*VS a1*VS a0*VS
//  A1  b3 b2 b1 b0             B1  b3*VS b2*VS b1*VS b0*VS
//  A2  c3 c2 c1 c0             B2  c3*VS c2*VS c1*VS c0*VS
//  A3  d3 d2 d1 d0             B3  d3*VS d2*VS d1*VS d0*VS
//
//  Other Registers
// ----------------------------------------------------------
//  VS  scalar multiplier

            .macro Mat4x4MulScalarF32 B0,B1,B2,B3, A0,A1,A2,A3, VS

            fmul \B0\().4s, \A0\().4s, \VS\().s[0]  // row 0
            fmul \B1\().4s, \A1\().4s, \VS\().s[0]  // row 1
            fmul \B2\().4s, \A2\().4s, \VS\().s[0]  // row 2
            fmul \B3\().4s, \A3\().4s, \VS\().s[0]  // row 3
            .endm

// Macro Mat4x4TraceF32
//
// Input Registers              Other Registers
// ----------------------------------------------------------
// VA   a3 a2 a1 a0             SA  matrix trace
// VB   b3 b2 b1 b0             SB  temp register
// VC   c3 c2 c1 c0
// VD   d3 d2 d1 d0

            .macro Mat4x4TraceF32 SA, VA, VB, VC, VD, SB

            mov \SA, \VA\().4s[0]               // SA = M[0][0]
            mov \SB, \VB\().4s[1]               // SA = M[1][1]
            fadd \SA, \SA, \SB                  // SA += SB
            mov \SB, \VC\().4s[2]               // SB = M[2][2]
            fadd \SA, \SA, \SB                  // SA += SB
            mov \SB, \VD\().4s[3]               // SB = M[3][3]
            fadd \SA, \SA, \SB                  // SA += SB
            .endm
