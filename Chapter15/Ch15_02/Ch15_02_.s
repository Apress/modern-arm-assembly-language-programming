//-------------------------------------------------
//               Ch15_02_.s
//-------------------------------------------------

// extern "C" void PackedCompareF32_(Vec128 x[8], const Vec128& a, const Vec128& b);

            .text
            .global PackedCompareF32_
PackedCompareF32_:
            ld1 {v0.4s},[x1]                    // v0 = a
            ld1 {v1.4s},[x2]                    // v1 = b

            fcmeq v2.4s,v0.4s,v1.4s             // packed a == b
            st1 {v2.4s},[x0],16                 // save result to x[0]

            not v2.16b,v2.16b                   // packed a != b
            st1 {v2.4s},[x0],16                 // save result to x[1]

            fcmgt v2.4s,v0.4s,v1.4s             // packed a > b
            st1 {v2.4s},[x0],16                 // save result to x[2]

            fcmge v2.4s,v0.4s,v1.4s             // packed a >= b
            st1 {v2.4s},[x0],16                 // save result to x[3]

            fcmgt v2.4s,v1.4s,v0.4s             // packed a < b
            st1 {v2.4s},[x0],16                 // save result to x[4]

            fcmge v2.4s,v1.4s,v0.4s             // packed a <= b
            st1 {v2.4s},[x0],16                 // save result to x[5]

            fcmlt v2.4s,v0.4s,0.0               // packed a < 0
            st1 {v2.4s},[x0],16                 // save result to x[6]

            fcmgt v2.4s,v1.4s,0.0               // packed b > 0
            st1 {v2.4s},[x0],16                 // save result to x[7]
            ret

// extern "C" void PackedCompareF64_(Vec128 x[8], const Vec128& a, const Vec128& b);

            .global PackedCompareF64_
PackedCompareF64_:
            ld1 {v0.2d},[x1]                    // v0 = a
            ld1 {v1.2d},[x2]                    // v1 = b

            fcmeq v2.2d,v0.2d,v1.2d             // packed a == b
            st1 {v2.2d},[x0],16                 // save result to x[0]

            not v2.16b,v2.16b                   // packed a != b
            st1 {v2.2d},[x0],16                 // save result to x[1]

            fcmgt v2.2d,v0.2d,v1.2d             // packed a > b
            st1 {v2.2d},[x0],16                 // save result to x[2]

            fcmge v2.2d,v0.2d,v1.2d             // packed a >= b
            st1 {v2.2d},[x0],16                 // save result to x[3]

            fcmgt v2.2d,v1.2d,v0.2d             // packed a < b
            st1 {v2.2d},[x0],16                 // save result to x[4]

            fcmge v2.2d,v1.2d,v0.2d             // packed a <= b
            st1 {v2.2d},[x0],16                 // save result to x[5]

            fcmlt v2.2d,v0.2d,0.0               // packed a < 0
            st1 {v2.2d},[x0],16                 // save result to x[6]

            fcmgt v2.2d,v1.2d,0.0               // packed b > 0
            st1 {v2.2d},[x0],16                 // save result to x[7]
            ret
