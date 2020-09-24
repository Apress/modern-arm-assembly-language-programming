//-------------------------------------------------
//               Ch12_03_.s
//-------------------------------------------------

// extern "C" bool CompareSumA_(int32_t a, int32_t b, int32_t c, int32_t* sum);

            .text
            .global CompareSumA_
CompareSumA_:

// Calculate a + b + c and save sum
            add w0,w0,w1                        // w0 = a + b
            add w0,w0,w2                        // w0 = a + b + c
            str w0,[x3]                         // save sum

// Is sum >= 100?
            cmp w0,100                          // Compare sum and 100
            b.ge SumGE100                       // jump if sum >= 100

            mov w0,#0                           // set return code to false
            ret

SumGE100:   mov w0,#1                           // set return code to true
            ret

// extern "C" bool CompareSumB_(int64_t a, int64_t b, int64_t c, int64_t* sum);

            .global CompareSumB_
CompareSumB_:

// Calculate a + b + c and save sum
            add x0,x0,x1                        // x0 = a + b
            adds x0,x0,x2                       // x0 = a + b + c
            str x0,[x3]                         // save sum
            
            b.gt SumGT0                         // jump if sum > 0

            mov w0,#0                           // set return code to false
            ret

SumGT0:     mov w0,#1                           // set return code to true
            ret

// extern "C" bool CompareSumC_(int32_t a, int32_t b, int32_t c, int32_t* sum);

            .global CompareSumC_
CompareSumC_:
            adds w4,w0,w1                       // w4 = a + b
            cset w5,vs                          // w5 = 1 on overflow

            adds w4,w4,w2                       // w4 = a + b + c
            cset w6,vs                          // w6 = 1 on overflow
            orr w0,w5,w6                        // w0 = 1 on overflow

            str w4,[x3]                         // save sum
            ret
