//-------------------------------------------------
//               Ch08_02_.s
//-------------------------------------------------

// extern "C" bool PackedShiftA_(Vec128* x, const Vec128& a);

            .text
            .global PackedShiftA_
PackedShiftA_:

            vldm r1,{q0}                        // q0 = a

            vshl.u16 q1,q0,#4                   // vector left shift by 4
            vshr.u16 q2,q0,#2                   // vector right shift by 2

            vstm r0,{q1,q2}                     // save results to x
            bx lr

// extern "C" bool PackedShiftB_(Vec128* x, const Vec128& a, const Vec128& b);

            .global PackedShiftB_
PackedShiftB_:
            vldm r1,{q0}                        // q0 = a
            vldm r2,{q1}                        // q1 = b (shift counts)

            vshl.u16 q2,q0,q1                   // vector shift using counts

            vstm r0,{q2}                        // save result to x
            bx lr

// extern "C" bool PackedShiftC_(Vec128* x, const Vec128& a, const Vec128& b);

            .global PackedShiftC_
PackedShiftC_:
            vpush {q4}

            vldm r1,{q0}                        // q0 = a
            vldm r2,{q1}                        // q1 = b (shift counts)

            vshl.s16 q2,q0,q1                   // vector left shift
            vqshl.s16 q3,q0,q1                  // vector left shift - sat
            vrshl.s16 q4,q0,q1                  // vector left shift - round

            vstm r0,{q2-q4}                     // save result to x

            vpop {q4}
            bx lr
