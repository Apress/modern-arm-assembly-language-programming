//-------------------------------------------------
//               Ch08_03_.s
//-------------------------------------------------

// extern "C" bool PackedMulA_(Vec128 x[4], const Vec128& a, const Vec128& b, int16_t c);

            .text
            .global PackedMulA_
PackedMulA_:
            vldm r1,{q0}                    // q0 = a
            vldm r2,{q1}                    // q1 = b

            vmov s14,r3                     // s14 = c
            vmul.i16 q2,q0,d7[0]            // q2 = a * c (scalar mul)
            vstm r0!,{q2}                   // save result to x[0]

            vmul.i16 q2,q0,q1               // q2 = a * b (vector 16-bit)
            vstm r0!,{q2}                   // save result to x[1]

            vmull.s16 q2,d0,d2              // q2 = a[0:3] * b[0:3] (32-bit)
            vstm r0!,{q2}                   // save result to x[2] 
            vmull.s16 q2,d1,d3              // q2 = a[4:7] * b[4:7] (32-bit)
            vstm r0,{q2}                    // save result to x[3] 

            bx lr
