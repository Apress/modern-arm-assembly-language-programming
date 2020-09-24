//-------------------------------------------------
//               Ch14_03_.s
//-------------------------------------------------

// extern "C" bool PackedMulA_(Vec128 x[4], const Vec128& a, const Vec128& b, int16_t c);

            .text
            .global PackedMulA_
PackedMulA_:
            ld1 {v0.8h},[x1]                    // v0 = a
            ld1 {v1.8h},[x2]                    // v1 = b

            mul v2.8h,v0.8h,v1.8h               // a * b (vector 16-bit)
            st1 {v2.8h},[x0],16                 // save result x[0]

            mov v3.8h[0],w3                     // load c into low 16 bits
            mul v2.8h,v0.8h,v3.8h[0]            // mul elements in a by c
            st1 {v2.8h},[x0],16                 // save result to x[1]

            smull v2.4s,v0.4h,v1.4h             // signed mul long
            smull2 v3.4s,v0.8h,v1.8h
            st1 {v2.4s,v3.4s},[x0]              // results to x[2], x[3]
            ret

