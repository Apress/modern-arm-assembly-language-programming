//-------------------------------------------------
//               Ch09_02_.s
//-------------------------------------------------

// extern "C" void PackedCompareF32_(Vec128 x[8], const Vec128& a, const Vec128& b);

            .text
            .global PackedCompareF32_
PackedCompareF32_:

// Simple packed floating-point (F32) compare operations
            vldm.f32 r1,{q0}                    // q0 = a
            vldm.f32 r2,{q1}                    // q1 = b

            vceq.f32 q2,q0,q1                   // packed a == b
            vstm r0!,{q2}

            vmvn.u32 q2,q2                      // packed a != b
            vstm r0!,{q2}

            vclt.f32 q2,q0,q1                   // packed a < b
            vstm r0!,{q2}

            vcle.f32 q2,q0,q1                   // packed a <= b
            vstm r0!,{q2}

            vcgt.f32 q2,q0,q1                   // packed a > b
            vstm r0!,{q2}

            vcge.f32 q2,q0,q1                   // packed a >= b
            vstm r0!,{q2}

            vclt.f32 q2,q0,#0                   // packed a < 0
            vstm r0!,{q2}

            vcgt.f32 q2,q0,#0                   // packed a > 0
            vstm r0,{q2}
            bx lr
