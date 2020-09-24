//-------------------------------------------------
//               Ch09_04_.s
//-------------------------------------------------

// extern "C" bool CalcArrayMinMaxF32__(float* min_val, float* max_val, const float* x, size_t n);

            .global CalcArrayMinMaxF32_
CalcArrayMinMaxF32_:
            push {r4,lr}

// Verify arguments
            cmp r3,#0
            beq InvalidArg                      // jump if n == 0
            tst r2,#0x0f
            bne InvalidArg                      // jump if x not aligned

// Initialize
            ldr r4,=g_MinValInit
            vldr s0,[r4]
            vdup.f32 q11,d0[0]                  // q11 = packed minimums
            ldr r4,=g_MaxValInit
            vldr s0,[r4]
            vdup.f32 q12,d0[0]                  // q12 = packed maximums

// Main processing loop
            cmp r3,#16
            blo SkipLoop1                       // skip loop if n < 16

Loop1:      vldm.f32 r2!,{q0-q3}                // load next 16 x values

            vminnm.f32 q8,q0,q1                 // update packed minimums
            vminnm.f32 q9,q2,q3
            vminnm.f32 q11,q11,q8
            vminnm.f32 q11,q11,q9

            vmaxnm.f32 q8,q0,q1                 // update packed maximums
            vmaxnm.f32 q9,q2,q3
            vmaxnm.f32 q12,q12,q8
            vmaxnm.f32 q12,q12,q9

            sub r3,#16                          // n -= 16
            cmp r3,#16
            bhs Loop1                           // repeat if n >= 16

// Reduce packed minimums and maximums to scalar values
SkipLoop1:  vminnm.f32 d0,d22,d23               // q11 overlaps d22:d23
            vminnm.f32 s0,s0,s1                 // s0 = min value
            vmaxnm.f32 d1,d24,d25               // q12 overlaps d24:d25
            vmaxnm.f32 s1,s2,s3                 // s1 = max value

// Process final values
            cmp r3,#0
            beq SaveResults

Loop2:      vldm.f32 r2!,{s2}                   // load next v value
            vminnm.f32 s0,s0,s2                 // update min value
            vmaxnm.f32 s1,s1,s2                 // update max value

            subs r3,#1                          // n -= 1
            bne Loop2                           // repeat until done

// Save final min & max values
SaveResults:
            vstr.f32 s0,[r0]                    // save min value
            vstr.f32 s1,[r1]                    // save max value
            mov r0,#1                           // set success return code

Done:       pop {r4,pc}

InvalidArg: mov r0,#0                           // set invalid arg return code
            b Done
