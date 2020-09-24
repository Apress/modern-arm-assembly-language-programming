//-------------------------------------------------
//               Ch15_06_.s
//-------------------------------------------------

// extern "C" void Mat4x4MulF32_(float* m_des, const float* m_src1, const float* m_src2);

            .text
            .global Mat4x4MulF32_
Mat4x4MulF32_:

// Load m_src1 into v0:v3
            ld1 {v0.4s-v3.4s},[x1]

// Load m_src2 into v4:v7
            ld1 {v4.4s-v7.4s},[x2]

// Row 0
            fmul v16.4s,v4.4s,v0.s[0]
            fmla v16.4s,v5.4s,v0.s[1]
            fmla v16.4s,v6.4s,v0.s[2]
            fmla v16.4s,v7.4s,v0.s[3]
            st1 {v16.4s},[x0],16

// Row 1
            fmul v17.4s,v4.4s,v1.s[0]
            fmla v17.4s,v5.4s,v1.s[1]
            fmla v17.4s,v6.4s,v1.s[2]
            fmla v17.4s,v7.4s,v1.s[3]
            st1 {v17.4s},[x0],16

// Row 2
            fmul v18.4s,v4.4s,v2.s[0]
            fmla v18.4s,v5.4s,v2.s[1]
            fmla v18.4s,v6.4s,v2.s[2]
            fmla v18.4s,v7.4s,v2.s[3]
            st1 {v18.4s},[x0],16

// Row 3
            fmul v19.4s,v4.4s,v3.s[0]
            fmla v19.4s,v5.4s,v3.s[1]
            fmla v19.4s,v6.4s,v3.s[2]
            fmla v19.4s,v7.4s,v3.s[3]
            st1 {v19.4s},[x0]
            ret

// extern "C" void Mat4x4MulF64_(double* m_des, const double* m_src1, const double* m_src2);

            .global Mat4x4MulF64_
Mat4x4MulF64_:

// Load m_src1 into v0:v7
            ld1 {v0.4s-v3.4s},[x1],64
            ld1 {v4.4s-v7.4s},[x1]

// Load m_src2 into v16:v23
            ld1 {v16.4s-v19.4s},[x2],64
            ld1 {v20.4s-v23.4s},[x2]

// Row 0
            fmul v24.2d,v16.2d,v0.d[0]          // cols 0 & 1
            fmla v24.2d,v18.2d,v0.d[1]
            fmla v24.2d,v20.2d,v1.d[0]
            fmla v24.2d,v22.2d,v1.d[1]

            fmul v25.2d,v17.2d,v0.d[0]          // cols 2 & 3
            fmla v25.2d,v19.2d,v0.d[1]
            fmla v25.2d,v21.2d,v1.d[0]
            fmla v25.2d,v23.2d,v1.d[1]
            st1 {v24.2d,v25.2d},[x0],32

// Row 1
            fmul v24.2d,v16.2d,v2.d[0]          // cols 0 & 1
            fmla v24.2d,v18.2d,v2.d[1]
            fmla v24.2d,v20.2d,v3.d[0]
            fmla v24.2d,v22.2d,v3.d[1]

            fmul v25.2d,v17.2d,v2.d[0]          // cols 2 & 3
            fmla v25.2d,v19.2d,v2.d[1]
            fmla v25.2d,v21.2d,v3.d[0]
            fmla v25.2d,v23.2d,v3.d[1]
            st1 {v24.2d,v25.2d},[x0],32

// Row 2
            fmul v24.2d,v16.2d,v4.d[0]          // cols 0 & 1
            fmla v24.2d,v18.2d,v4.d[1]
            fmla v24.2d,v20.2d,v5.d[0]
            fmla v24.2d,v22.2d,v5.d[1]

            fmul v25.2d,v17.2d,v4.d[0]          // cols 2 & 3
            fmla v25.2d,v19.2d,v4.d[1]
            fmla v25.2d,v21.2d,v5.d[0]
            fmla v25.2d,v23.2d,v5.d[1]
            st1 {v24.2d,v25.2d},[x0],32

// Row 3
            fmul v24.2d,v16.2d,v6.d[0]          // cols 0 & 1
            fmla v24.2d,v18.2d,v6.d[1]
            fmla v24.2d,v20.2d,v7.d[0]
            fmla v24.2d,v22.2d,v7.d[1]

            fmul v25.2d,v17.2d,v6.d[0]          // cols 2 & 3
            fmla v25.2d,v19.2d,v6.d[1]
            fmla v25.2d,v21.2d,v7.d[0]
            fmla v25.2d,v23.2d,v7.d[1]
            st1 {v24.2d,v25.2d},[x0]
            ret
