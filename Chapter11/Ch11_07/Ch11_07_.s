//-------------------------------------------------
//               Ch11_07_.s
//-------------------------------------------------

// extern "C" void BitwiseOpsA_(uint32_t* x, uint32_t a, uint32_t b);

            .text
            .global BitwiseOpsA_
BitwiseOpsA_:

// Perform various bitwise logical operations
            and w3,w1,w2                        // a AND b
            str w3,[x0]

            orr w3,w1,w2                        // a OR b
            str w3,[x0,4]

            eor w3,w1,w2                        // a EOR b
            str w3,[x0,8]
            ret

// extern "C" void BitwiseOpsB_(uint32_t* x, uint32_t a);

            .global BitwiseOpsB_
BitwiseOpsB_:

            and w2,w1,0x0000ff00                // a AND 0x0000ff00
            str w2,[x0]

            orr w2,w1,0x00ff0000                // a OR 0x00ff0000
            str w2,[x0,4]

            eor w2,w1,0xff000000                // a EOR 0xff000000
            str w2,[x0,8]

//          and w2,w1,0xcc00ff00                // invalid imm. operand
            mov w2,0xff00
            movk w2,0xcc00,lsl 16               // w2 = 0xcc00ff00
            and w2,w1,w2                        // a AND 0xcc00ff00
            str w2,[x0,12]
            ret
