//-------------------------------------------------
//               Ch16_03_.s
//-------------------------------------------------

// Macro Mat4x4MulVec
//
// Input:   v0 = matrix m column 0
//          v1 = matrix m column 1
//          v2 = matrix m column 2
//          v3 = matrix m column 3 
//          x0 = pointer to vector b
//          x2 = pointer to vector a
//
// Temp registers: v4, v5

            .macro Mat4x4MulVec
            ld1 {v4.4s},[x2],16                 // load vector a[i]

            fmul v5.4s,v0.4s,v4.s[0]            // col[0] * a[i].W
            fmla v5.4s,v1.4s,v4.s[1]            // col[1] * a[i].X
            fmla v5.4s,v2.4s,v4.s[2]            // col[2] * a[i].Y
            fmla v5.4s,v3.4s,v4.s[3]            // col[3] * a[i].Z

            st1 {v5.4s},[x0],16                 // save vector b[i]
            .endm

// extern "C" bool MatVecMulF32_(Vec4x1F32* b, float m[4][4], Vec4x1F32* a, size_t n);

            .text
            .global MatVecMulF32_
MatVecMulF32_:

// Validate arguments and perform required initializations
            cbz x3,InvalidArg                   // jump if n == 0
            tst x3,0x03
            b.ne InvalidArg                     // jump if n % 4 != 0

            tst x0,0x0f
            b.ne InvalidArg                     // jump if b not aligned
            tst x2,0x0f
            b.ne InvalidArg                     // jump if a not aligned

            ld4 {v0.4s-v3.4s},[x1]              // load transpose of m

// Main processing loop
Loop1:      Mat4x4MulVec
            Mat4x4MulVec
            Mat4x4MulVec
            Mat4x4MulVec

            subs x3,x3,4                        // n -= 4
            b.ne Loop1                          // repeat until done

            mov w0,1                            // set success return code
            ret

InvalidArg: mov w0,0                            // set error return code
            ret
