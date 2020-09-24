//-------------------------------------------------
//               Ch15_04_.s
//-------------------------------------------------

// Macro UpdateSums
//
// Arguments:   VregX   x values register
//              VregY   y values register               
//
// Registers:   V16.4s  sum_x
//              v17.4s  sum_y
//              v18.4s  sum_xx
//              v19.4s  sum_yy
//              v20.4s  sum_xy

            .macro UpdateSums VregX,VregY
            fadd v16.4s,v16.4s,\VregX\().4s         // update sum_x
            fadd v17.4s,v17.4s,\VregY\().4s         // update sum_y
            fmla v18.4s,\VregX\().4s,\VregX\().4s   // update sum_xx
            fmla v19.4s,\VregY\().4s,\VregY\().4s   // update sum_yy
            fmla v20.4s,\VregX\().4s,\VregY\().4s   // update sum_xy
            .endm

// extern "C" bool CalcCorrCoef_(float* rho, float sums[5], const float* x, const float* y, size_t n, float epsilon);

            .text
            .global CalcCorrCoef_
CalcCorrCoef_:

// Validate arguments
            cbz x4,InvalidArg                   // jump if n == 0
            tst x2,0x0f
            b.ne InvalidArg                     // jump if x not 16 aligned
            tst x3,0x0f
            b.ne InvalidArg                     // jump if y not 16 aligned
            mov x5,x4                           // save n for later

// Initialize
            eor v16.16b,v16.16b,v16.16b         // sum_x = 0
            eor v17.16b,v17.16b,v17.16b         // sum_y = 0
            eor v18.16b,v18.16b,v18.16b         // sum_xx = 0
            eor v19.16b,v19.16b,v19.16b         // sum_yy = 0
            eor v20.16b,v20.16b,v20.16b         // sum_xy = 0

            cmp x4,16
            b.lo SkipLoop1                      // jump if n < 16

// Main processing loop
Loop1:      ld1 {v0.4s,v1.4s,v2.4s,v3.4s},[x2],64   // load 16 x values
            ld1 {v4.4s,v5.4s,v6.4s,v7.4s},[x3],64   // load 16 y values

            UpdateSums v0,v4
            UpdateSums v1,v5
            UpdateSums v2,v6
            UpdateSums v3,v7

            sub x4,x4,16                        // n -= 16
            cmp x4,16
            b.hs Loop1                          // repeat if n >= 16

// Reduce packed sums to scalar values
SkipLoop1:  faddp v16.4s,v16.4s,v16.4s
            faddp v16.4s,v16.4s,v16.4s          // s16 = sum_x

            faddp v17.4s,v17.4s,v17.4s
            faddp v17.4s,v17.4s,v17.4s          // s17 = sum_y

            faddp v18.4s,v18.4s,v18.4s
            faddp v18.4s,v18.4s,v18.4s          // s18 = sum_xx

            faddp v19.4s,v19.4s,v19.4s
            faddp v19.4s,v19.4s,v19.4s          // s19 = sum_yy

            faddp v20.4s,v20.4s,v20.4s
            faddp v20.4s,v20.4s,v20.4s          // s20 = sum_xy


// Update sums with final elements
            cbz x4,SkipLoop2                    // jump if n == 0
Loop2:      ldr s1,[x2],4                       // s0 = x value
            ldr s2,[x3],4                       // s1 = y value

            fadd s16,s16,s1                     // update sum_x
            fadd s17,s17,s2                     // update sum_y
            fmla s18,s1,v1.4s[0]                // update sum_xx
            fmla s19,s2,v2.4s[0]                // update sum_yy
            fmla s20,s1,v2.4s[0]                // update sum_xy

            subs x4,x4,1                        // n -= 1
            b.ne Loop2

// Save sum values to sums[] array
SkipLoop2:  stp s16,s17,[x1],8                  // save sum_x, sum_y
            stp s18,s19,[x1],8                  // save sum_xx, sum_yy
            str s20,[x1]                        // save sum_xy

// Calculate rho numerator
            scvtf s21,x5                        // s21 = n
            fmul s1,s21,s20                     // n * sum_xy
            fmls s1,s16,v17.4s[0]               // n * sum_xy - sum_x * sum_y

// Calculate rho denominator
            fmul s2,s21,s18                     // n * sum_xx
            fmsub s2,s16,s16,s2                 // n * sum_xx - sum_x * sum_x
            fsqrt s2,s2
            fmul s3,s21,v19.4s[0]               // n * sum_yy
            fmsub s3,s17,s17,s3                 // n * sum_yy - sum_y * sum_y
            fsqrt s3,s3
            fmul s4,s2,s3                       // s4 = rho_den

            fcmp s4,s0                          // is rho_den < epsilon?
            b.lo BadRhoDen                      // jump if yes
            fdiv s5,s1,s4                       // s5 = rho
            str s5,[x0]                         // save rho
            mov w0,1                            // set success return code
            ret

BadRhoDen:  eor v5.16b,v5.16b,v5.16b            // set rho to zero
            str s5,[x0]                         // save rho
            mov w0,0                            // set error return code
            ret

InvalidArg: mov w0,0                            // set error return code
            ret

