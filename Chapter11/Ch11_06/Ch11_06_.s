//-------------------------------------------------
//               Ch11_06_.s
//-------------------------------------------------

// extern "C" void ShiftA_(uint32_t* x, uint32_t a);

            .text
            .global ShiftA_
ShiftA_:    asr w2,w1,2                         // arithmetic shift right - 2 bits
            lsl w3,w1,4                         // logical shift left - 4 bits
            lsr w4,w1,5                         // logical shift right - 5 bits
            ror w5,w1,3                         // rotate right - 3 bits

            str w2,[x0]                         // save asr result to x[0]
            str w3,[x0,4]                       // save lsl result to x[1]
            str w4,[x0,8]                       // save lsr result to x[2]
            str w5,[x0,12]                      // save ror result to x[3]
            ret

// extern "C" void ShiftB_(uint32_t* x, uint32_t a, uint32_t count);

            .global ShiftB_
ShiftB_:    asr w3,w1,w2                        // arithmetic shift right
            lsl w4,w1,w2                        // logical shift left
            lsr w5,w1,w2                        // logical shift right
            ror w6,w1,w2                        // rotate right

            str w3,[x0]                         // save asr result to x[0]
            str w4,[x0,4]                       // save lsl result to x[1]
            str w5,[x0,8]                       // save lsr result to x[2]
            str w6,[x0,12]                      // save ror result to x[3]
            ret
