//------------------------------------------------
//               Ch03_03_.s
//------------------------------------------------

// extern "C" void LocalVarsA_(int a, int b, int c, int d, int e, int f, int* g, int* h)

            .equ ARG_E,32                       // sp offset for e
            .equ ARG_F,36                       // sp offset for f
            .equ ARG_G,40                       // sp offset for g
            .equ ARG_H,44                       // sp offset for h

            .equ TEMP0,0                        // sp offset for temp0
            .equ TEMP1,4                        // sp offset for temp1
            .equ TEMP2,8                        // sp offset for temp2
            .equ TEMP3,12                       // sp offset for temp3

            .text
            .global LocalVarsA_
LocalVarsA_:

// Function prologue
            push {r4-r7}                        // save non-volatile regs
            sub sp,#16                          // allocate local var space

// Load e, f, g, and h from stack
            ldr r4,[sp,#ARG_E]                  // r4 = e
            ldr r5,[sp,#ARG_F]                  // r5 = f
            ldr r6,[sp,#ARG_G]                  // r6 = g (pointer)
            ldr r7,[sp,#ARG_H]                  // r7 = h (pointer)

// Calculate and save temp0, temp1, temp2, and temp3
            add r12,r0,r1
            add r12,r12,r2                      // r12 = a + b + c
            str r12,[sp,#TEMP0]                 // save temp0 on stack

            add r12,r3,r4
            add r12,r12,r5                      // r12 = d + e + f
            str r12,[sp,#TEMP1]                 // save temp1 on stack

            add r12,r0,r2
            add r12,r12,r4                      // r12 = a + c + e
            str r12,[sp,#TEMP2]                 // save temp2 on stack

            add r12,r1,r3
            add r12,r12,r5                      // r12 = b + d + f
            str r12,[sp,#TEMP3]                 // save temp3 on stack

// Calculate and save g and h
            ldr r0,[sp,#TEMP0]
            ldr r1,[sp,#TEMP1]
            mul r0,r0,r1                        // calculate temp0 * temp1
            str r0,[r6]                         // save g

            ldr r0,[sp,#TEMP2]
            ldr r1,[sp,#TEMP3]
            mul r0,r0,r1                        // calculate temp2 * temp3
            str r0,[r7]                         // save h

// Function epilogue
            add sp,#16                          // release local var space
            pop {r4-r7}                         // restore non-volatile regs
            bx lr
