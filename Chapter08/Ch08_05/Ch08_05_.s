//-------------------------------------------------
//               Ch08_05_.s
//-------------------------------------------------

// extern "C" bool CalcMeanU8_(uint32_t* sum_x, double* mean, const uint8_t* x, uint32_t n);

            .text
            .global CalcMeanU8_

CalcMeanU8_:
// Prologue
            push {r4-r6,lr}
            vpush {q4-q6}

// Validate arguments
            cmp r3,#0
            beq InvalidArg                      // jump if n == 0

            ldr r4,=g_NumElementsMax
            ldr r5,[r4]
            cmp r3,r5                           // n > g_NumElementsMax?
            bhi InvalidArg                      // jump if yes

            tst r2,#0x0f
            bne InvalidArg                      // jump if x not 16b aligned            

// Initialize
            mov r6,r3                           // save n for later
            veor q6,q6,q6                       // set packed sums to zero

// Main processing loop
            cmp r3,#32
            blo SkipLoop1                       // jump if n < 32

Loop1:      vldm r2!,{q0,q1}                    // q0:q1 = 32 pixels

            vaddl.u8 q2,d0,d1                   // zero-extend to h-words
            vaddl.u8 q3,d2,d3                   // and sum

            vaddl.u16 q4,d4,d5                  // zero-extend to words
            vaddl.u16 q5,d6,d7                  // and sum

            vadd.u32 q6,q6,q4                   // update packed sums
            vadd.u32 q6,q6,q5

            sub r3,#32
            cmp r3,#32
            bhs Loop1                           // jump if n >= 32

SkipLoop1:  vpadd.u32 d0,d12,d13                // reduce packed uint32
            vpadd.u32 d1,d0,d0                  // sums to scalar
            vmov r4,d1[0]                       // r4 = current sum

// Process final array elements
            cmp r3,#0                           // more pixels to process?
            beq CalcMean                        // jump if no

Loop2:      ldrb r5,[r2],#1                     // r5 = pixel value
            add r4,r4,r5                        // sum += pixel value
            subs r3,#1
            bne Loop2                           // jump if n > 0

CalcMean:   str r4,[r0]                         // save sum

            vmov s0,r4
            vcvt.f64.u32 d1,s0                  // d1 = sum as double
            vmov s0,r6
            vcvt.f64.u32 d2,s0                  // d2 = n as double

            vdiv.f64 d3,d1,d2                   // calculate mean
            vstr.f64 d3,[r1]                    // save mean

            mov r0,#1                           // set success return code

// Epilogue
Done:       vpop {q4-q6}
            pop {r4-r6,pc}

InvalidArg: mov r0,#0                           // set error return code
            b Done
