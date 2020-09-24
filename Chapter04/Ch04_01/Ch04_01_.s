//-------------------------------------------------
//               Ch04_01_.s
//-------------------------------------------------

// extern "C" int CalcSumA_(const int* x, int n);

            .text
            .global CalcSumA_
CalcSumA_:
            mov r2,#0                           // sum = 0

            cmp r1,#0                           // is n <= 0?
            ble DoneA                           // jump if n <= 0

LoopA:      ldr r3,[r0],#4                      // r3 = *r0; r0 += 4
            add r2,r2,r3                        // add current x to sum
            subs r1,r1,#1                       // n -= 1
            bne LoopA                           // jump if more data

DoneA:      mov r0,r2                           // r0 = final sum
            bx lr


// extern "C" uint64_t CalcSumB_(const uint32_t* x, uint32_t n);

            .global CalcSumB_
CalcSumB_:
            push {r4,r5}

            mov r2,#0
            mov r3,#0                           // sum (r2:r3) = 0
            cmp r1,#0                           // is n == 0?
            beq DoneB                           // jump if n == 0

            mov r4,#0                           // i = 0

LoopB:      ldr r5,[r0,r4,lsl #2]               // r5 = x[i]

            adds r2,r2,r5
            adc r3,r3,#0                        // sum += x[i]

            add r4,#1                           // i += 1
            cmp r4,r1                           // is i == n?
            bne LoopB                           // jump if more data

DoneB:      mov r0,r2
            mov r1,r3                           // r0:r1 = final 64-bit sum

            pop {r4,r5}
            bx lr
