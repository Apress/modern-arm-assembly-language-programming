//-------------------------------------------------
//               Ch12_04_.s
//-------------------------------------------------

// static int SumSquaresA_(int64_t n);

            .text
SumSquaresA_:

// Calculate sum of squares using for-loop
            mov x1,1                            // i = 1
            mov x2,0                            // sum = 0

Loop1:      madd x2,x1,x1,x2                    // sum += i * i

            add x1,x1,1                         // i += 1
            cmp x1,x0
            b.le Loop1                          // jump if i <= n

            mov x0,x2                           // x0 = final sum
            ret

// static int SumSquaresB_(int64_t n);

SumSquaresB_:

// Calculate sum = (n * (n + 1) * (2 * n + 1)) / 6
            add x1,x0,1                         // x1 = n + 1
            mul x2,x0,x1                        // x2 = n * (n + 1)

            lsl x3,x0,1                         // r3 = 2 * n
            add x3,x3,1                         // r3 = 2 * n + 1
            mul x3,x3,x2                        // r3 = dividend

            mov x1,6                            // r1 = divisor
            sdiv x0,x3,x1                       // r0 = final sum
            ret

// extern "C" void SumSquares_(int64_t n, int64_t* sum_a, int64_t* sum_b);

            .equ SAVE_N,0                       // offset for save of n
            .equ SAVE_SUM_A,8                   // offset for save of sum_a
            .equ SAVE_SUM_B,16                  // offset for save of sum_b
            .equ SAVE_LR,24                     // offset for save of lr

            .equ ARG_N_MIN,1                    // argument n minimum value
            .equ ARG_N_MAX,1023                 // argument n maximum value

            .equ LOCAL_VAR_SPACE,32             // local variable space

            .global SumSquares_
SumSquares_:
// Function prologue
            sub sp,sp,LOCAL_VAR_SPACE           // allocate local var space

// Save arguments to stack
            str x0,[sp,SAVE_N]                  // save arg n
            str x1,[sp,SAVE_SUM_A]              // save arg sum_a
            str x2,[sp,SAVE_SUM_B]              // save arg sum_b
            str lr,[sp,SAVE_LR]                 // save link register

// Set sum_a and sum_b to zero
            mov x3,0
            str x3,[x1]                         // sum_a = 0
            str x3,[x2]                         // sum_b = 0

// Verify n >= ARG_N_MIN && n <= ARG_N_MAX
            cmp x0,ARG_N_MIN
            b.lt Done                           // jump if n < ARG_N_MIN
            cmp x0,ARG_N_MAX
            b.gt Done                           // jump if n > ARG_N_MAX

// Calculate sum_a
            bl SumSquaresA_                     // call SumSquaresA_
            ldr x1,[sp,SAVE_SUM_A]
            str x0,[x1]                         // save sum_a

// Calculate sum_b
            ldr x0,[sp,SAVE_N]                  // reload arg value n
            bl SumSquaresB_                     // call SumSquaresB_
            ldr x1,[sp,SAVE_SUM_B]
            str x0,[x1]                         // save sum_b

// Restore LR register
            ldr lr,[sp,SAVE_LR]                 // restore link register

// Function epilogue
Done:       add sp,sp,LOCAL_VAR_SPACE           // release local var space
            ret
