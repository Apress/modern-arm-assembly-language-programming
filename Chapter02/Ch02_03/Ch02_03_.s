//------------------------------------------------
//               Ch02_03_.s
//------------------------------------------------

// extern "C" void CalcQuoRem_(const int* a, const int* b, int* quo, int* rem);

            .text
            .global CalcQuoRem_
CalcQuoRem_:

// Save non-volatile registers
            push {r4,r5}                            // save r4 and r5 on stack

// Load a and b
            ldr r4,[r0]                             // r4 = a (dividend)
            ldr r5,[r1]                             // r5 = b (divisor)

// Calculate quotient and remainder
            sdiv r0,r4,r5                           // r0 = quotient
            str r0,[r2]                             // save quotient

            mul r1,r0,r5                            // r1 = quotient * b
            sub r2,r4,r1                            // r2 = a - quotient * b
            str r2,[r3]                             // save remainder

// Restore non-volatile registers and return
            pop {r4,r5}                             // restore r4 & r5
            bx lr                                   // return to caller
