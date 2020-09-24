//-------------------------------------------------
//               Ch12_05_.s
//-------------------------------------------------

// extern "C" int CalcArraySumA_(const int* x, int n);

            .text
            .global CalcArraySumA_
CalcArraySumA_:

            mov w2,0                            // sum = 0
            cmp w1,w0                           // is n <= 0?
            b.le DoneA                          // jump if n <= 0

LoopA:      ldr w3,[x0],4                       // w3 = x[i]
            add w2,w2,w3                        // sum += x[i]

            subs w1,w1,1                        // n -= 1
            b.ne LoopA                          // jump if more data

DoneA:      mov w0,w2                           // w0 = final sum
            ret

// extern "C" uint64_t CalcArraySumB_(const uint64_t* x, uint32_t n);

            .global CalcArraySumB_
CalcArraySumB_:

            mov x2,0                            // sum = 0
            cmp w1,0                            // is n == 0?
            b.eq DoneB                          // jump if n == 0

            mov w3,0                            // i = 0

LoopB:      ldr x4,[x0,w3,uxtw 3]               // r5 = x[i]
            add x2,x2,x4                        // sum += x[i]

            add w3,w3,1                         // i += 1
            cmp w3,w1                           // is i == n?
            b.ne LoopB                          // jump if more data

DoneB:      mov x0,x2
            ret
