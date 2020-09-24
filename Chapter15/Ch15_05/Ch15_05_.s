//-------------------------------------------------
//               Ch15_05_.s
//-------------------------------------------------

            .include "Ch15_05_Macros_.inc"

// extern "C" bool ConvertRgbToGs_(uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float* coef);

            .text
            .global ConvertRgbToGs_
ConvertRgbToGs_:

// Validate arguments
            ldr x4,=g_NumPixelsMin              // make sure num_pixels
            ldr x4,[x4]                         // is >= g_NumPixelsMin
            cmp x2,x4
            b.lo InvalidArg

            ldr x4,=g_NumPixelsMax              // make sure num_pixels
            ldr x4,[x4]                         // is <= g_NumPixelsMax
            cmp x2,x4
            b.hi InvalidArg

            tst x2,0x0f                         // num_pixels must be even
            b.ne InvalidArg                     // multiple of 16

            tst x0,0x0f                         // make sure both
            b.ne InvalidArg                     // pixel buffers are
            tst x1,0x0f                         // aligned to a 16-byte
            b.ne InvalidArg                     // boundary

// Initialize constants - all registers contain packed SPFP elements
// v4 = coef[0] v5 = coef[1], v6 = coef[2], v29 = 0.5

            ld3r {v4.4s,v5.4s,v6.4s},[x3]       // load packed coefficients
            fmov v29.4s,0.5                     // load packed 0.5

// Main processing loop
Loop1:      ld4 {v0.16b,v1.16b,v2.16b,v3.16b},[x1],64   // load 16 RGB32

            U8toF32 v16,v17,v18,v19,v0          // convert red pixels
            U8toF32 v20,v21,v22,v23,v1          // convert green pixels
            U8toF32 v24,v25,v26,v27,v2          // convert blue pixels

            MulCoef v16,v17,v18,v19,v4          // red pixels * coef[0]
            MulCoef v20,v21,v22,v23,v5          // green pixels * coef[1]
            MulCoef v24,v25,v26,v27,v6          // blue pixels * coef[2]

            SumRGB v16,v20,v24,v29              // sum r, g, b channels
            SumRGB v17,v21,v25,v29              // registers v16:19
            SumRGB v18,v22,v26,v29              // contain grayscale
            SumRGB v19,v23,v27,v29              // pixel values as F32

            F32toU8 v2,v16,v17,v18,v19          // convert back to U8
            st1 {v2.16b},[x0],16                // save 16 GS pixels

            subs x2,x2,16                       // n -= 16
            b.ne Loop1

            mov w0,1                            // set success return code
            ret

InvalidArg: mov w0,0                            // set error return code
            ret
