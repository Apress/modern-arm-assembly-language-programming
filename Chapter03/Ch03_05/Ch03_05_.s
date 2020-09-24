//------------------------------------------------
//               Ch03_05_.s
//------------------------------------------------

// extern "C" bool CompareSumA_(int a, int b, int c, int* sum);

            .text
            .global CompareSumA_
CompareSumA_:

// Calculate a + b + c and save sum
            add r0,r0,r1                        // r0 = a + b
            add r0,r0,r2                        // r0 = a + b + c
            str r0,[r3]                         // save sum

// Is sum >= 100?
            cmp r0,#100                         // Compare sum and 100
            bge SumGE100                        // jump if sum >= 100

            mov r0,#0                           // set return code to false
            bx lr

SumGE100:   mov r0,#1                           // set return code to true
            bx lr


// extern "C" bool CompareSumB_(int a, int b, int c, int* sum);

            .global CompareSumB_
CompareSumB_:

// Calculate a + b + c and save sum
            add r0,r0,r1                        // r0 = a + b
            adds r0,r0,r2                       // r0 = a + b + c
            str r0,[r3]                         // save sum
            bgt SumGT0                          // jump if sum > 0

            mov r0,#0                           // set return code to false
            bx lr

SumGT0:     mov r0,#1                           // set return code to true
            bx lr

// extern "C" bool CompareSumC_(int a, int b, int c, int* sum);

            .global CompareSumC_
CompareSumC_:

            push {r4,r5}

            mov r4,r0                           // r4 = a
            mov r0,#0                           // r0 = 0 (no overflow)

            adds r4,r4,r1                       // r4 = a + b
            orrvs r0,#1                         // r0 = 1 if overflow

            adds r5,r4,r2                       // r5 = a + b + c
            orrvs r0,#1                         // r0 = 1 if overflow

            str r5,[r3]                         // save sum

            pop {r4,r5}
            bx lr
