//-------------------------------------------------
//               Ch14_06_.s
//-------------------------------------------------

            .include "Ch14_06_Macros_.inc"

// extern "C" bool CalcImageStats_(ImageStats& im_stats);

            .equ m_PixelBuffer,0
            .equ m_NumPixels,8
            .equ m_PixelSum,16
            .equ m_PixelSumSquares,24
            .equ m_PixelMean,32
            .equ m_PixelSd,40

            .text
            .global CalcImageStats_
CalcImageStats_:

// Load and validate values in im_stats struct
            mov x7,x0
            ldr x0,[x7,m_PixelBuffer]
            tst x0,0x0f                         // jump if m_PixelBuffer
            b.ne InvalidArg                     // not 16b aligned

            ldr x1,[x7,m_NumPixels]             // x1 = m_NumPixels
            cbz x1,InvalidArg                   // jump if m_NumPixels == 0

            tst x1,0x3f                         // jump if
            b.ne InvalidArg                     // m_NumPixels% 64 != 0

// Initialize
            eor v18.16b,v18.16b,v18.16b         // pixel_sum
            eor v19.16b,v19.16b,v19.16b         // pixel_sum_squares
            mov x2,x1                           // num_pixels = m_NumPixels

// Main processing loop
Loop1:      eor v16.16b,v16.16b,v16.16b         // loop_pixel_sum
            eor v17.16b,v17.16b,v17.16b         // loop_pixel_sum_squares

            ld1 {v0.16b-v3.16b},[x0],64         // load next pixel block

            UpdateSums v0
            UpdateSums v1
            UpdateSums v2
            UpdateSums v3

            uxtl v4.2d,v16.2s                   // extend
            uxtl2 v5.2d,v16.4s                  // loop_pixel_sum

            add v18.2d,v18.2d,v4.2d             // update pixel_sum
            add v18.2d,v18.2d,v5.2d

            uxtl v4.2d,v17.2s                   // extend
            uxtl2 v5.2d,v17.4s                  // loop_pixel_sum_squares

            add v19.2d,v19.2d,v4.2d             // update pixel_sum_squares
            add v19.2d,v19.2d,v5.2d

            subs x2,x2,64                       // num_pixels -= 64
            b.ne Loop1

// Reduce packed m_PixelSum and m_PixelSumSquares to scalar values
            addp v0.2d,v18.2d,v18.2d            
            mov x4,v0.d[0]
            str x4,[x7,m_PixelSum]
            
            addp v1.2d,v19.2d,v19.2d
            mov x5,v1.d[0]
            str x5,[x7,m_PixelSumSquares]

// Calculate mean and standard deviation
            ucvtf d0,x1                         // d0 = n
            sub x1,x1,1
            ucvtf d1,x1                         // d1 = n - 1
            ucvtf d2,x4                         // d2 = m_PixelSum
            ucvtf d3,x5                         // d3 = m_PixelSumSquares

            fdiv d4,d2,d0                       // d4 = m_PixelMean
            str d4,[x7,m_PixelMean]             // save m_PixelMean
     
            fmul d4,d0,d3                       // d4 = n * m_PixelSumSquares
            fmul d5,d2,d2                       // d5 = m_PixelSum ** 2
            fsub d6,d4,d5                       // d6 = variance numerator
            fmul d7,d0,d1                       // d7 = variance denominator
            fdiv d0,d6,d7                       // d0 = variance
            fsqrt d1,d0                         // d1 = m_PixelSd
            str d1,[x7,m_PixelSd]               // save m_PixelSd

            mov w0,1                            // set success return code
            ret

InvalidArg: mov w0,0                            // set error return code
            ret
