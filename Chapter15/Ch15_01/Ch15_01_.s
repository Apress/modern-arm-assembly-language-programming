//-------------------------------------------------
//               Ch15_01_.s
//-------------------------------------------------

// extern "C" void PackedMathF32_(Vec128 x[9], const Vec128& a, const Vec128& b);

            .text
            .global PackedMathF32_
PackedMathF32_:
            ld1 {v0.4s},[x1]                    // v0 = a
            ld1 {v1.4s},[x2]                    // v1 = b

            fadd v2.4s,v0.4s,v1.4s              // v2 = a + b
            st1 {v2.4s},[x0],16                 // save result to x[0]

            fsub v2.4s,v0.4s,v1.4s              // v2 = a - b
            st1 {v2.4s},[x0],16                 // save result to x[1]

            fmul v2.4s,v0.4s,v1.4s              // v2 = a * b
            st1 {v2.4s},[x0],16                 // save result to x[2]

            fdiv v2.4s,v0.4s,v1.4s              // v2 = a / b
            st1 {v2.4s},[x0],16                 // save result to x[3]

            fabs v2.4s,v0.4s                    // v2 = abs(a)
            st1 {v2.4s},[x0],16                 // save result to x[4]

            fneg v2.4s,v1.4s                    // v2 = -b
            st1 {v2.4s},[x0],16                 // save result to x[5]

            fminnm v2.4s,v0.4s,v1.4s            // v2 = min(a, b)
            st1 {v2.4s},[x0],16                 // save result to x[6]

            fmaxnm v2.4s,v0.4s,v1.4s            // v2 = max(a, b)
            st1 {v2.4s},[x0],16                 // save result to x[7]

            fsqrt v2.4s,v0.4s                   // v2 = sqrt(a)
            st1 {v2.4s},[x0],16                 // save result to x[8]
            ret

// extern "C" void PackedMathF64_(Vec128 x[9], const Vec128& a, const Vec128& b);

            .global PackedMathF64_
PackedMathF64_:
            ld1 {v0.2d},[x1]                    // v0 = a
            ld1 {v1.2d},[x2]                    // v1 = b

            fadd v2.2d,v0.2d,v1.2d              // v2 = a + b
            st1 {v2.2d},[x0],16                 // save result to x[0]

            fsub v2.2d,v0.2d,v1.2d              // v2 = a - b
            st1 {v2.2d},[x0],16                 // save result to x[1]

            fmul v2.2d,v0.2d,v1.2d              // v2 = a * b
            st1 {v2.2d},[x0],16                 // save result to x[2]

            fdiv v2.2d,v0.2d,v1.2d              // v2 = a / b
            st1 {v2.2d},[x0],16                 // save result to x[3]

            fabs v2.2d,v0.2d                    // v2 = abs(a)
            st1 {v2.2d},[x0],16                 // save result to x[4]

            fneg v2.2d,v1.2d                    // v2 = -b
            st1 {v2.2d},[x0],16                 // save result to x[5]

            fminnm v2.2d,v0.2d,v1.2d            // v2 = min(a, b)
            st1 {v2.2d},[x0],16                 // save result to x[6]

            fmaxnm v2.2d,v0.2d,v1.2d            // v2 = max(a, b)
            st1 {v2.2d},[x0],16                 // save result to x[7]

            fsqrt v2.2d,v0.2d                   // v2 = sqrt(a)
            st1 {v2.2d},[x0],16                 // save result to x[8]
            ret
