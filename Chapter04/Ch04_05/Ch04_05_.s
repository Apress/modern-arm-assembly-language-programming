//-------------------------------------------------
//               Ch04_05_.s
//-------------------------------------------------

// extern "C" void ReverseArrayA_(int* y, const int* x, int n);

            .text
            .global ReverseArrayA_
ReverseArrayA_:
              push {r4-r11}

// Initialize
            add r1,r1,r2,lsl #2
            sub r1,#4                           // r1 points to x[n - 1]
            cmp r2,#4
            blt SkipLoopA                       // jump if n < 4

// Main loop
LoopA:      ldmda r1!,{r4-r7}                   // r4 = *r1
                                                // r5 = *(r1 - 4)
                                                // r6 = *(r1 - 8)
                                                // r7 = *(r1 - 12)
                                                // r1 -= 16

            mov r8,r7                           // reorder elements in
            mov r9,r6                           // r4 - r7 for use with
            mov r10,r5                          // stmia instruction
            mov r11,r4

            stmia r0!,{r8-r11}                  // *r0 = r8
                                                // *(r0 + 4) = r9
                                                // *(r0 + 8) = r10
                                                // *(r0 + 12) = r11
                                                // r0 += 16

            sub r2,#4                           // n -= 4
            cmp r2,#4
            bge LoopA                           // jump if n >= 4 

// Process remaining (0 - 3) array elements
SkipLoopA:  cmp r2,#0
            ble DoneA                           // jump if no more elements

            ldr r4,[r1],#-4                     // load single element from x
            str r4,[r0],#4                      // save element to y
            subs r2,#1                          // n -= 1
            beq DoneA                           // jump if n == 0

            ldr r4,[r1],#-4                     // load single element from x
            str r4,[r0],#4                      // save element to y
            subs r2,#1                          // n -= 1
            beq DoneA                           // jump if n == 0

            ldr r4,[r1]                         // load final element from x
            str r4,[r0]                         // save final element to y

DoneA:      pop {r4-r11}
            bx lr


// extern "C" void ReverseArrayB_(int* x, int n);

            .global ReverseArrayB_
ReverseArrayB_:
            push {r4-r11}

// Initialize
            mov r2,r1                           // r2 = n
            add r1,r0,r2,lsl #2
            sub r1,#4                           // r1 points to x[n - 1]
            cmp r2,#4
            blt SkipLoopB                       // jump if n < 4

LoopB:      ldmia r0,{r4,r5}                    // r4 = *r0, r5 = *(r0 + 4)
            ldmda r1,{r6,r7}                    // r6 = *r1, r7 = *(r1 - 4)

            mov r8,r7                           // reorder elements
            mov r9,r6                           // for use with stmia and
            mov r10,r5                          // stmda instructions
            mov r11,r4

            stmia r0!,{r8,r9}                   // *r0 = r8, *(r0 + 4) = r9, r0 += 8
            stmda r1!,{r10,r11}                 // *r1 = r10, *(r1 - 4) = r11, r1 -= 8

            sub r2,#4                           // n -= 4
            cmp r2,#4
            bge LoopB                           // jump if n >= 4 

// Process remaining (0 - 3) array elements
SkipLoopB:  cmp r2,#1
            ble DoneB                           // jump if done

            ldr r4,[r0]                         // load final element
            ldr r5,[r1]                         // pair into r4:r5

            str r4,[r1]                         // save elements
            str r5,[r0] 

DoneB:      pop {r4-r11}
            bx lr

