//-------------------------------------------------
//               Ch14_02_.s
//-------------------------------------------------

// extern "C" bool PackedShiftA_(Vec128* x, const Vec128& a);

            .text
            .global PackedShiftA_
PackedShiftA_:
            ld1 {v0.8h},[x1]                    // v0 = a

            shl v1.8h,v0.8h,4                   // left shift
            sshr v2.8h,v0.8h,2                  // signed right shift
            ushr v3.8h,v0.8h,3                  // unsigned right shift

            st1 {v1.8h,v2.8h,v3.8h},[x0]        // save results to x
            ret

// extern "C" bool PackedShiftB_(Vec128* x, const Vec128& a, const Vec128& b);

            .global PackedShiftB_
PackedShiftB_:
            ld1 {v0.8h},[x1]                    // v0 = a
            ld1 {v1.8h},[x2]                    // v1 = b (shift counts)

            sshl v2.8h,v0.8h,v1.8h              // signed shift
            ushl v3.8h,v0.8h,v1.8h              // unsigned shift

            st1 {v2.8h,v3.8h},[x0]              // save results to x
            ret

// extern "C" bool PackedShiftC_(Vec128* x, const Vec128& a);

            .global PackedShiftC_
PackedShiftC_:
            ld1 {v0.8h},[x1]                    // v0 = a

            sshll v1.4s,v0.4h,4                 // signed left shift (low half)
            sshll2 v2.4s,v0.8h,4                // signed left shift (top half)
            ushll v3.4s,v0.4h,4                 // unsigned left shift (low half)
            ushll2 v4.4s,v0.8h,4                // unsigned left shift (top half)

            st1 {v1.4s,v2.4s,v3.4s,v4.4s},[x0]  // save results to x
            ret
