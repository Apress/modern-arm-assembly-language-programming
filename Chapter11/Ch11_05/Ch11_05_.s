//-------------------------------------------------
//               Ch11_05_.s
//-------------------------------------------------

// extern "C" MoveA_(int32_t& a0, int32_t& a1, int32_t& a2, int32_t& a3);

            .text
            .global MoveA_
MoveA_:     mov w7,1000                         // w7 = 1000
            str w7,[x0]

            mov w7,65536000                     // w7 = 65536000
            str w7,[x1]

            movz w7,1000,lsl 16                 // w7 = 65536000
            str w7,[x2]

            mov w7,-131072                      // w7 = -131027
            str w7,[x3]
            ret

// extern "C" MoveB_(int64_t& b0, int64_t& b1, int64_t& b2, int64_t& b3);

            .global MoveB_
MoveB_:     mov x7,131072000                    // x7 = 131072000
            str x7,[x0]

            movz x7,2000,lsl 16                 // x7 = 131072000
            str x7,[x1]

            mov x7,429496729600                 // x7 = 429496729600
            str x7,[x2]

            movz x7,100,lsl 32                  // x7 = 429496729600
            str x7,[x3]
            ret

// extern "C" void MoveC_(int32_t& c0, int32_t& c1);

            .equ VAL1,2000000
            .equ VAL1_LO16,(VAL1 & 0xffff)
            .equ VAL1_HI16,((VAL1 & 0xffff0000) >> 16)

            .global MoveC_
MoveC_:
//          mov w7,VAL1                         // invalid value

            mov w7,VAL1_LO16                    // w7 = 33920
            movk w7,VAL1_HI16,lsl 16            // w7 = 2000000
            str w7,[x0]

            ldr w7,=VAL1                        // w7 = 2000000
            str w7,[x1]
            ret

// extern "C" void MoveD_(int64_t& d0, int64_t& d1, int64_t& d2);

            .equ VAL2,-1000000000000000
            .equ VAL2_00,(VAL2 & 0xffff)
            .equ VAL2_16,(VAL2 & 0xffff0000) >> 16
            .equ VAL2_32,(VAL2 & 0xffff00000000) >> 32
            .equ VAL2_48,(VAL2 & 0xffff000000000000) >> 48

            .equ VAL3,0x100000064               // (2**32 + 100)
            .equ VAL3_00,(VAL3 & 0xffff)
            .equ VAL3_32,(VAL3 & 0xffff00000000) >> 32

            .global MoveD_
MoveD_:
//          mov x7,VAL2                         // invalid value

            mov x7,VAL2_00
            movk x7,VAL2_16,lsl 16
            movk x7,VAL2_32,lsl 32
            movk x7,VAL2_48,lsl 48              // x7 = VAL2
            str x7,[x0]

            ldr x7,=VAL2                        // x7 = VAL2
            str x7,[x1]

            mov x7,VAL3_00
            movk x7,VAL3_32,lsl 32              // x7 = 0x100000064
            str x7,[x2]
            ret
