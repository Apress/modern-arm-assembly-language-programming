//-------------------------------------------------
//               Ch16_01_.s
//-------------------------------------------------

// extern "C" bool ConvolveKsN_(float* y, const float* x, int num_pts, const float* kernel, int kernel_size);

            .text
            .global ConvolveKsN_
ConvolveKsN_:

// Validate arguments
            tst w4,0x01
            b.eq InvalidArg1                    // jump if kernel_size is even

            ldr x5,=g_KernelSizeMin
            ldr w5,[x5]
            cmp w4,w5
            b.lt InvalidArg1                    // jump if kernel_size too small

            ldr x5,=g_KernelSizeMax
            ldr w5,[x5]
            cmp w4,w5
            b.gt InvalidArg1                    // jump if kernel_size too big

            ldr x5,=g_NumPtsMin
            ldr w5,[x5]
            cmp w2,w5
            b.lt InvalidArg1                    // jump if num_pts too small

            ldr x5,=g_NumPtsMax
            ldr w5,[x5]
            cmp w2,w5
            b.gt InvalidArg1                    // jump if num_pts too big

            tst w2,0x0f
            b.ne InvalidArg1                    // jump if num_pts % 16 != 0

// Initialize
            sxtw x2,w2                          // sign-extend num_pts
            sxtw x4,w4                          // sign-extend kernel_size

            lsr x5,x4,1                         // ks2 = kernel_size / 2
            add x1,x1,x5,lsl 2                  // x += ks2 (first data point)
            mov x6,0                            // i = 0

// Processing loops
Loop1a:     movi v0.4s,0                        // packed loop sums = 0.0
            neg x7,x5                           // k = -ks2

Loop2a:     sub x8,x6,x7                        // x8 = i - k
            add x9,x1,x8,lsl 2                  // x9 = ptr to x[i-k]
            ld1 {v1.4s},[x9]                    // v1 = x[i-k:i-k+3]

            add x10,x7,x5                       // x10 = k + ks2
            add x11,x3,x10,lsl 2                // x11 = ptr to kernel[k+ks2]
            ld1r {v2.4s},[x11]                  // v2 = packed kernel[k+ks2]

            add x7,x7,1                         // k += 1
            cmp x7,x5                           // is k > ks2?

            fmla v0.4s,v1.4s,v2.4s              // x[i-k:i-k+3] * kernel[k+ks2]

            b.le Loop2a                         // jump if k <= ks2

            st1 {v0.4s},[x0],16                 // save y[i:i+3]

            add x6,x6,4                         // i += 4
            cmp x6,x2
            b.lt Loop1a                         // jump if i < num_pts

            mov w0,1                            // set success return code
            ret

InvalidArg1:
            mov w0,0                            // set error return code
            ret

// extern "C" bool ConvolveKs5_(float* y, const float* x, int num_pts, const float* kernel, int kernel_size);

            .global ConvolveKs5_
ConvolveKs5_:

// Validate arguments
            cmp w4,5
            b.ne InvalidArg2                    // jump if kernel_size != 5

            ldr x5,=g_NumPtsMin
            ldr w5,[x5]
            cmp w2,w5
            b.lt InvalidArg2                    // jump if num_pts too small

            ldr x5,=g_NumPtsMax
            ldr w5,[x5]
            cmp w2,w5
            b.gt InvalidArg2                    // jump if num_pts too big

            tst w2,0x0f
            b.ne InvalidArg2                    // jump if num_pts % 16 != 0

// Initialize
            sxtw x2,w2                          // sign-extend num_pts
            sxtw x4,w4                          // sign-extend kernel_size

            ld1r {v0.4s},[x3],4                 // v0 = packed kernel[0]
            ld1r {v1.4s},[x3],4                 // v1 = packed kernel[1]
            ld1r {v2.4s},[x3],4                 // v2 = packed kernel[2]
            ld1r {v3.4s},[x3],4                 // v3 = packed kernel[3]
            ld1r {v4.4s},[x3]                   // v4 = packed kernel[4]

            add x1,x1,8                         // x1 ptr first x[] data point
            mov x5,0                            // i = 0
            mov x6,-4                           // offset to next x[]

// Processing loop
Loop1b:     add x7,x5,2                         // j = i + ks2
            add x8,x1,x7,lsl 2                  // x8 = ptr to x[j]
            add x5,x5,4                         // i += 4
            cmp x5,x2                           // is i >= num_pts?

            ld1 {v16.4s},[x8],x6                // v16 = x[j:j+3]
            fmul v5.4s,v16.4s,v0.4s             // x[j:j+3] * kernel[0]

            ld1 {v17.4s},[x8],x6                // v17 = x[j-1:j+2]
            fmla v5.4s,v17.4s,v1.4s             // x[j-1:j+2] * kernel[1]

            ld1 {v18.4s},[x8],x6                // v18 = x[j-2:j+1]
            fmla v5.4s,v18.4s,v2.4s             // x[j-2:j+1] * kernel[2]

            ld1 {v19.4s},[x8],x6                // v19 = x[j-3:j]
            fmla v5.4s,v19.4s,v3.4s             // x[j-3:j] * kernel[3]

            ld1 {v20.4s},[x8],x6                // v19 = x[j-4:j-1]
            fmla v5.4s,v20.4s,v4.4s             // x[j-4:j-1] * kernel[4]

            st1 {v5.4s},[x0],16                 // save y[i:i+3]
            b.lt Loop1b                         // jump if i >= num_pts

            mov w0,1                            // set success return code
            ret

InvalidArg2:
            mov w0,0                            // set error return code
            ret
