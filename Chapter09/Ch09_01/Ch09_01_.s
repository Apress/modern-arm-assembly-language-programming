//-------------------------------------------------
//               Ch09_01_.s
//-------------------------------------------------

// extern "C" void PackedMathF32_(Vec128 x[7], const Vec128& a, const Vec128& b);

            .text
            .global PackedMathF32_
PackedMathF32_:

// Simple packed floating-point (F32) arithmetic
            vldm.f32 r1,{q0}                    // q0 = a
            vldm.f32 r2,{q1}                    // q1 = b

            vadd.f32 q2,q0,q1                   // q2 = a + b
            vstm r0!,{q2}

            vsub.f32 q2,q0,q1                   // q2 = a - b
            vstm r0!,{q2}

            vmul.f32 q2,q0,q1                   // q2 = a * b
            vstm r0!,{q2}

            vabs.f32 q2,q0                      // q2 = abs(a)
            vstm r0!,{q2}

            vneg.f32 q2,q1                      // q2 = -b
            vstm r0!,{q2}

            vminnm.f32 q2,q0,q1                 // q2 = min(a, b)
            vstm r0!,{q2}

            vmaxnm.f32 q2,q0,q1                 // q2 = max(a, b)
            vstm r0,{q2}
            bx lr
