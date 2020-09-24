//-------------------------------------------------
//               Ch14_01_.s
//-------------------------------------------------

// extern "C" void PackedAddI16_(Vec128 x[2], const Vec128& a, const Vec128& b);

            .text
            .global PackedAddI16_
PackedAddI16_:
            ldr q0,[x1]                         // q0 = a
            ldr q1,[x2]                         // q1 = b

            add v2.8h,v0.8h,v1.8h               // v2 = a + b (wraparound)
            str q2,[x0]                         // save result to x[0]

            sqadd v3.8h,v0.8h,v1.8h             // v3 = a + b (saturated)
            str q2,[x0,16]                      // save result to x[1]
            ret

// extern "C" void PackedSubI16_(Vec128 x[2], const Vec128& b, const Vec128& c);

            .global PackedSubI16_
PackedSubI16_:
            ldr q0,[x1]                         // q0 = a
            ldr q1,[x2]                         // q1 = b

            sub v2.8h,v0.8h,v1.8h               // v2 = a - b (wraparound)
            str q2,[x0]                         // save result to x[0]

            sqsub v3.8h,v0.8h,v1.8h             // v3 = a - b (saturated)
            str q2,[x0,16]                      // save result to x[1]
            ret

// extern "C" void PackedAddU16_(Vec128 x[2], const Vec128& a, const Vec128& b);

            .global PackedAddU16_
PackedAddU16_:
            ld1 {v0.8h},[x1]                    // v0 = a
            ld1 {v1.8h},[x2]                    // v1 = b

            add v2.8h,v0.8h,v1.8h               // v2 = a + b (wraparound)
            uqadd v3.8h,v0.8h,v1.8h             // v3 = a + b (saturated)

            st1 {v2.8h,v3.8h},[x0]              // save results to x
            ret

// extern "C" void PackedSubU16_(Vec128 x[2], const Vec128& a, const Vec128& b);

            .global PackedSubU16_
PackedSubU16_:
            ld1 {v0.8h},[x1]                    // v0 = a
            ld1 {v1.8h},[x2]                    // v1 = b

            sub v2.8h,v0.8h,v1.8h               // q2 = a - b (wraparound)
            uqsub v3.8h,v0.8h,v1.8h             // q3 = a - b (saturated)

            st1 {v2.8h,v3.8h},[x0]              // save results to x
            ret
