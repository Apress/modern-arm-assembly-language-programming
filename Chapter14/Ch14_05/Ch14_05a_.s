//-------------------------------------------------
//               Ch14_05a_.s
//-------------------------------------------------

            .include "Ch14_05_Macros_.inc"

// extern "C" bool ClipPixels_(ClipData* cd);

            .equ m_Des,0
            .equ m_Src,8
            .equ m_NumPixels,16
            .equ m_NumClippedPixels,24
            .equ m_ThreshLo,32
            .equ m_ThreshHi,33

            .equ NPPI,64                        // num pixels per iteration

            .text
            .global ClipPixelsA_
ClipPixelsA_:
// Load elements from structure
            mov x7,x0                           // x7 = cd
            ldr x0,[x7,m_Des]
            ldr x1,[x7,m_Src]
            ldr x2,[x7,m_NumPixels]
            ldrb w3,[x7,m_ThreshLo]
            ldrb w4,[x7,m_ThreshHi]

// Validate structure values
            cmp x2,0
            b.eq InvalidArg                     // m_NumPixels == 0
            tst x2,0x3f
            b.ne InvalidArg                     // m_NumPixels % 64 != 0

            tst x0,0x0f
            b.ne InvalidArg                     // m_Des not 16b aligned
            tst x1,0x0f
            b.ne InvalidArg                     // m_Src not 16b aligned

// Initialize
            dup v16.16b,w3                      // v16 = packed m_ThreshLo
            dup v17.16b,w4                      // v17 = packed m_ThreshHi
            movi v18.16b,0x01                   // v18 = packed 0x01
            mov x8,0                            // num_clipped_pixels = 0

// Main processing loop
Loop1:      ld1 {v4.16b-v7.16b},[x1],NPPI       // load pixel block

            ClipPix v4                          // clip pixels in v4
            ClipPix v5                          // clip pixels in v5
            ClipPix v6                          // clip pixels in v6
            ClipPix v7                          // clip pixels in v7

            st1 {v4.16b-v7.16b},[x0],NPPI       // save clipped pix

            subs x2,x2,NPPI                     // num_pixels -= NPPI
            b.ne Loop1

            str x8,[x7,m_NumClippedPixels]      // save m_NumClippedPixels
            mov w0,1                            // set success return code
            ret

            mov w0,1
            ret

InvalidArg: mov w0,0                            // set error return code
            ret
