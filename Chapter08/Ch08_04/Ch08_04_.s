//-------------------------------------------------
//               Ch08_04_.s
//-------------------------------------------------

// extern "C" bool CalcMinMaxU8_(uint8_t* x_min, uint8_t* x_max, const uint8_t* x, size_t n);

            .text
            .global CalcMinMaxU8_
CalcMinMaxU8_:
// Prologue
            push {r4-r6,lr}

// Validate arguments
            cmp r3,#0
            beq InvalidArg                      // jump if n == 0

            tst r2,#0x0f
            bne InvalidArg                      // jump if x not 16b aligned

// Initialize
            vmov q2.i8,#255
            vmov q3.i8,#255                     // q2:q3 = packed minimums

            vmov q8.i8,#0
            vmov q9.i8,#0                       // q8:q9 = packed maximums

// Main processing loop
            cmp r3,#32
            blo SkipLoop1                       // jump if n < 32

Loop1:      vldm r2!,{q0,q1}                    // load block of 32 pixels

            vmin.u8 q2,q2,q0
            vmin.u8 q3,q3,q1                    // update pixel minimums

            vmax.u8 q8,q8,q0
            vmax.u8 q9,q9,q1                    // update pixel maximums

            sub r3,#32                          // n -= 32
            cmp r3,#32
            bhs Loop1                           // jump if n >= 32

// Reduce packed minimums and maximums to scalar values
SkipLoop1:  vmin.u8 q2,q2,q3                    // q2 = pixel minimums (16)
            vmin.u8 d6,d4,d5                    // d6 = pixel minimums (8)
            vpmin.u8 d7,d6,d6                   // d7 = pixel minimums (4)
            vpmin.u8 d20,d7,d7                  // d20 = pixel minimums (2)                  
            vpmin.u8 d21,d20,d20                // d21[0] = pixel minimum
            vmov.u8 r4,d21[0]

            vmax.u8 q2,q8,q9                    // q2 = pixel maximums (16)
            vmax.u8 d6,d4,d5                    // d6 = pixel maximums (8)
            vpmax.u8 d7,d6,d6                   // d7 = pixel maximums (4)
            vpmax.u8 d20,d7,d7                  // d20 = pixel maximums (2)
            vpmax.u8 d21,d20,d20                // d21[0] = pixel maximum
            vmov.u8 r5,d21[0]

// Process final pixels
            cmp r3,#0
            beq SaveMinMax                      // jump if n == 0

Loop2:      ldrb r6,[r2],#1                     // r6 = pixel value
            cmp r6,r4
            movlo r4,r6                         // update pixel minimum
            cmp r6,r5
            movhi r5,r6                         // update pixel maximum
            subs r3,#1
            bne Loop2                           // repeat until done

// Save results
SaveMinMax: strb r4,[r0]                        // save minimum to x_min
            strb r5,[r1]                        // save maximum to x_max
            mov r0,#1                           // set success return code

// Epilogue
Done:       pop {r4-r6,pc}

InvalidArg: mov r0,#0                           // set error return code
            b Done
