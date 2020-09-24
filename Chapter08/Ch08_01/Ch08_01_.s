//-------------------------------------------------
//               Ch08_01_.s
//-------------------------------------------------

// extern "C" void PackedAddI16_(Vec128 x[2], const Vec128& a, const Vec128& b);

            .text
            .global PackedAddI16_
PackedAddI16_:

            vldm r1,{q0}                        // q0 = a
            vldm r2,{q1}                        // q1 = b

            vadd.i16 q2,q0,q1                   // q2 = a + b (wraparound)
            vqadd.s16 q3,q0,q1                  // q3 = a + b (saturated)

            vstm r0,{q2,q3}                     // save result to x
            bx lr

// extern "C" void PackedSubI16_(Vec128 x[2], const Vec128& b, const Vec128& c);

            .global PackedSubI16_
PackedSubI16_:

            vldm r1,{q0}                        // q0 = a
            vldm r2,{q1}                        // q1 = b

            vsub.i16 q2,q0,q1                   // q2 = a - b (wraparound)
            vqsub.s16 q3,q0,q1                  // q3 = a - b (saturated)

            vstm r0,{q2,q3}                     // save result to x
            bx lr

// extern "C" void PackedAddU16_(Vec128 x[2], const Vec128& a, const Vec128& b);

            .global PackedAddU16_
PackedAddU16_:

            vldm r1,{q0}                        // q0 = a
            vldm r2,{q1}                        // q1 = b

            vadd.i16 q2,q0,q1                   // q2 = a + b (wraparound)
            vqadd.u16 q3,q0,q1                  // q3 = a + b (saturated)

            vstm r0,{q2,q3}                     // save result to x
            bx lr

// extern "C" void PackedSubU16_(Vec128 x[2], const Vec128& a, const Vec128& b);

            .global PackedSubU16_
PackedSubU16_:

            vldm r1,{q0}                        // q0 = a
            vldm r2,{q1}                        // q1 = b

            vsub.i16 q2,q0,q1                   // q2 = a - b (wraparound)
            vqsub.u16 q3,q0,q1                  // q3 = a - b (saturated)

            vstm r0,{q2,q3}                     // save result to x
            bx lr
