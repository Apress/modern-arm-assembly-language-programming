//-------------------------------------------------
//               Ch06_06_.s
//-------------------------------------------------

            .text
r8_zero:    .double 0.0

// extern "C" bool CalcMeanStdev_(double* mean, double* stdev, const double* x, int n);

            .global CalcMeanStdev_
CalcMeanStdev_:
            push {r4,r5}

            cmp r3,#2                           // is n < 2?
            blt InvalidArg                      // jump if n < 2

// Calculate mean
            vldr.f64 d0,r8_zero                 // sum1 = 0.0
            vmov d4,d0                          // sum2 = 0.0

            mov r4,#0                           // i = 0
            mov r5,r2                           // r5 = ptr to x

Loop1:      vldmia r5!,{d1}                     // d1 = x[i]
            vadd.f64 d0,d0,d1                   // sum1 += x[i]

            add r4,#1                           // i += 1
            cmp r4,r3
            blt Loop1                           // jump if i < n

            vmov s4,r3                          // s4 = n
            vcvt.f64.s32 d1,s4                  // d1 = n as double
            vdiv.f64 d2,d0,d1                   // d2 = sum1 / n (mean)
            vstr.f64 d2,[r0]                    // save mean

// Calculate standard deviation
            mov r4,#0                           // i = 0
            mov r5,r2                           // r5 = ptr to x

Loop2:      vldmia r5!,{d1}                     // d1 = x[i]
            vsub.f64 d3,d1,d2                   // d3 = x[i] - mean
            vfma.f64 d4,d3,d3                   // sum2 += (x[i] - mean) ** 2

            add r4,#1                           // i += 1
            cmp r4,r3
            blt Loop2                           // jump if i < n

            sub r3,#1                           // r3 = n - 1
            vmov s2,r3
            vcvt.f64.s32 d1,s2                  // d1 = n - 1 as double

            vdiv.f64 d2,d4,d1                   // d2 = sum2 / (n - 1)
            vsqrt.f64 d3,d2                     // d3 = stdev
            vstr.f64 d3,[r1]                    // save stdev

            mov r0,#1                           // set success return code

Done:       pop {r4,r5}
            bx lr

InvalidArg: mov r0,#0                           // set error return code
            b Done
