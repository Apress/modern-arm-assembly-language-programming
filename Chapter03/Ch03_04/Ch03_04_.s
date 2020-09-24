//------------------------------------------------
//               Ch03_04_.s
//------------------------------------------------

// extern "C" void LocalVarsB_(int a, int b, int c, int d, int e, int f, int* g, int* h)

            .equ ARG_E,24                       // fp offset for e
            .equ ARG_F,28                       // fp offset for f
            .equ ARG_G,32                       // fp offset for g
            .equ ARG_H,36                       // fp offset for h

            .equ TEMP0,-16                      // fp offset for temp0
            .equ TEMP1,-12                      // fp offset for temp1
            .equ TEMP2,-8                       // fp offset for temp2
            .equ TEMP3,-4                       // fp offset for temp3

            .text
            .global LocalVarsB_
LocalVarsB_:

// Function prologue
            push {r4-r7,fp,lr}                  // save NV regs, fp, lr
            mov fp,sp                           // initialize fp
            sub sp,#16                          // allocate local var space

// Load e, f, g, and h from stack
            ldr r4,[fp,#ARG_E]                  // r4 = e
            ldr r5,[fp,#ARG_F]                  // r5 = f
            ldr r6,[fp,#ARG_G]                  // r6 = g (pointer)
            ldr r7,[fp,#ARG_H]                  // r7 = h (pointer)

// Calculate and save temp0, temp1, temp2, and temp3
            add lr,r0,r1
            add lr,lr,r2                        // lr = a + b + c
            str lr,[fp,#TEMP0]                  // save temp0 on stack

            add lr,r3,r4
            add lr,lr,r5                        // lr = d + e + f
            str lr,[fp,#TEMP1]                  // save temp1 on stack

            add lr,r0,r2
            add lr,lr,r4                        // lr = a + c + e
            str lr,[fp,#TEMP2]                  // save temp2 on stack

            add lr,r1,r3
            add lr,lr,r5                        // lr = b + d + f
            str lr,[fp,#TEMP3]                  // save temp3 on stack

// Calculate and save g and h
            ldr r0,[fp,#TEMP0]
            ldr r1,[fp,#TEMP1]
            mul r0,r0,r1                        // calculate temp0 * temp1
            str r0,[r6]                         // save g

            ldr r0,[fp,#TEMP2]
            ldr r1,[fp,#TEMP3]
            mul r0,r0,r1                        // calculate temp2 * temp3
            str r0,[r7]                         // save h

// Function epilogue
            add sp,#16                          // release local var space
            pop {r4-r7,fp,pc}                   // restore NV regs and return
