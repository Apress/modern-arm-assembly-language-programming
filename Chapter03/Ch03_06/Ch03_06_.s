//------------------------------------------------
//               Ch03_06_.s
//------------------------------------------------

// extern "C" void CalcSum_(int n, int* sum1, int* sum2);

            .equ SAVE_N,0                        // offset for save of n
            .equ SAVE_SUM1,4                     // offset for save of sum1
            .equ SAVE_SUM2,8                     // offset for save of sum2

            .equ ARG_N_MIN,1                    // argument n minimum value
            .equ ARG_N_MAX,1023                 // argument n maximum value

            .text
            .global CalcSum_
CalcSum_:

// Function prologue
            push {lr}                           // save lr
            sub sp,#12                          // allocate local var space

// Save arguments to stack
            str r0,[sp,#SAVE_N]                 // save arg n
            str r1,[sp,#SAVE_SUM1]              // save arg sum1
            str r2,[sp,#SAVE_SUM2]              // save arg sum2

// Set sum1 and sum2 to zero
            mov r3,#0
            str r3,[r1]                         // sum1 = 0
            str r3,[r2]                         // sum2 = 0

// Verify n >= ARG_N_MIN && n <= ARG_N_MAX
            cmp r0,#ARG_N_MIN
            blt Done                            // jump if n < ARG_N_MIN
            mov r3,#ARG_N_MAX
            cmp r0,r3
            bgt Done                            // jump if n > ARG_N_MAX

// Calculate sum1
            bl CalcSum1_
            ldr r1,[sp,#SAVE_SUM1]
            str r0,[r1]                         // save sum1

// Calculate sum2
            ldr r0,[sp,#SAVE_N]
            bl CalcSum2_
            ldr r1,[sp,#SAVE_SUM2]
            str r0,[r1]                         // save sum2

// Function epilogue
Done:       add sp,#12                          // release local var space
            pop {pc}                            // return

// int static CalcSum1_(int n);

CalcSum1_:

// Calculate sum1 using for-loop
            mov r1,#1                           // i = 1
            mov r2,#0                           // sum = 0

Loop1:      mla r2,r1,r1,r2                     // sum += i * i
            add r1,#1                           // i += 1

            cmp r1,r0
            ble Loop1                           // jump if i <= n

            mov r0,r2                           // r0 = final sum1
            bx lr

// int CalcSum2_(int n);

CalcSum2_:

// Calculate sum2 = (n * (n + 1) * (2 * n + 1)) / 6
            add r1,r0,#1                        // r1 = n + 1
            mul r2,r0,r1                        // r2 = n * (n + 1)

            lsl r3,r0,#1                        // r3 = 2 * n
            add r3,#1                           // r3 = 2 * n + 1
            mul r3,r3,r2                        // r3 = dividend

            mov r1,#6                           // r1 = divisor
            sdiv r0,r3,r1                       // r0 = final sum2
            bx lr
