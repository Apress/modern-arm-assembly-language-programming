//-------------------------------------------------
//               Ch09_05_.s
//-------------------------------------------------

// extern "C" bool CalcLeastSquares_(double* m, double* b, const double* x, const double* y, int n, float sums[5]);

            .equ ARG_N,8                        // stack offset for n
            .equ ARG_SUMS,12                    // stack offset for sums

            .text
            .global CalcLeastSquares_
CalcLeastSquares_:
            push {r4,lr}

// Validate arguments
            ldr r4,[sp,#ARG_N]                  // r4 = n
            cmp r4,#2
            blt InvalidArg                      // jump if n < 2
            tst r2,#0x0f
            bne InvalidArg                      // jump if x not aligned
            tst r3,#0x0f
            bne InvalidArg                      // jump if y not aligned

// Initialize
            veor q12,q12,q12                    // sum_x = 0
            veor q13,q13,q13                    // sum_y = 0
            veor q14,q14,q14                    // sum_xx = 0
            veor q15,q15,q15                    // sum_xy = 0

// Main processing loop
            cmp r4,#8
            blt SkipLoop1                       // jump if n < 8

Loop1:      vldm r2!,{q0,q1}                    // q0:q1 = 8 x values
            vldm r3!,{q2,q3}                    // q2:q3 = 8 y values

            vadd.f32 q12,q12,q0                 // update sum_x
            vadd.f32 q12,q12,q1 

            vadd.f32 q13,q13,q2                 // update sum_y
            vadd.f32 q13,q13,q3

            vfma.f32 q14,q0,q0                  // update sum_xx
            vfma.f32 q14,q1,q1

            vfma.f32 q15,q0,q2                  // update sum_xy
            vfma.f32 q15,q1,q3

            sub r4,#8                           // n -= 8
            cmp r4,#8
            bhs Loop1                           // repeat if n >= 8

// Reduce packed variables to scalar values
SkipLoop1:  vpadd.f32 d0,d24,d25
            vpadd.f32 d0,d0,d0                  // s0 = sum_x

            vpadd.f32 d1,d26,d27
            vpadd.f32 d1,d1,d1                  // s2 = sum_y

            vpadd.f32 d2,d28,d29
            vpadd.f32 d2,d2,d2                  // s4 = sum_xx

            vpadd.f32 d3,d30,d31
            vpadd.f32 d3,d3,d3                  // s6 = sum_xy

            cmp r4,#0
            beq SkipLoop2

// Process final values in x & y arrays
Loop2:      vldm r2!,{s8}                       // s8 = x[i]
            vldm r3!,{s9}                       // s9 = y[i]
            vadd.f32 s0,s0,s8                   // sum_x += x[i]
            vadd.f32 s2,s2,s9                   // sum_y += y[i]
            vfma.f32 s4,s8,s8                   // sum_xx += x[i] * x[i]
            vfma.f32 s6,s8,s9                   // sum_xy += x[i] * y[i]
            subs r4,#1                          // n -= 1
            bne Loop2

// Compute denominator and make sure it's valid
// denom = n * sum_xx - sum_x * sum_x
SkipLoop2:  ldr r4,[sp,#ARG_N]                  // r4 = n
            vmov s8,r4
            vcvt.f32.s32 s8,s8                  // s8 = n (F32)
            vmul.f32 s9,s8,s4                   // s9 = n * sum_xx
            vfms.f32 s9,s0,s0                   // s9 -= sum_x * sum_x

            vabs.f32 s10,s9                     // s10 = abs(denom)
            ldr r4,=g_LsEpsilon
            vldr s11,[r4]                       // s11 = g_LsEpsilon
            vcmp.f32 s10,s11                    // denom < g_LsEpsilon?
            vmrs APSR_nzcv,fpscr
            blo InvalidDen                      // jump if true

// Save sum values
            ldr r4,[sp,#ARG_SUMS]
            vstr s0,[r4,#0]                     // save sum_x
            vstr s2,[r4,#4]                     // save sum_y
            vstr s4,[r4,#8]                     // save sum_xx
            vstr s6,[r4,#12]                    // save sum_xy
            vstr s9,[r4,#16]                    // save denom

// Compute and save slope
// slope = (n * sum_xy - sum_x * sum_y) / denom
            vmul.f32 s10,s8,s6                  // s10 = n * sum_xy
            vfms.f32 s10,s0,s2                  // s10 -= sum_x * xum_y
            vdiv.f32 s11,s10,s9                 // s11 = slope
            vstr s11,[r0]                       // save slope

// Compute and save intercept
// intercept = (sum_xx * sum_y - sum_x * sum_xy) / denom
            vmul.f32 s10,s4,s2                  // s10 = sum_xx * sum_y
            vfms.f32 s10,s0,s6                  // s10 -= sum_x * sum_xy
            vdiv.f32 s11,s10,s9                 // s11 = intercept
            vstr s11,[r1]                       // save intercept

            mov r0,#1                           // set valid arg return code

Done:       pop {r4,pc}

InvalidArg: mov r0,#0                           // set invalid arg return code
            b Done

// Invalid denominator detected, set m and b to 0.0
InvalidDen: veor d0,d0                          // s0 = 0.0
            vstr s0,[r0]                        // slope = 0.0
            vstr s0,[r1]                        // intercept = 0.0
            mov r0,#1                           // set valid arg code
            b Done
