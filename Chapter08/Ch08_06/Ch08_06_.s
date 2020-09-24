//-------------------------------------------------
//               Ch08_06_.s
//-------------------------------------------------

// struct ITD offset equates
            .equ S_PbSrc,0
            .equ S_PbMask,4
            .equ S_NumPixels,8
            .equ S_NumMaskedPixels,12
            .equ S_SumMaskedPixels,16
            .equ S_Threshold,20
            .equ S_MeanMaskedPixels,24

// Miscellaneous equates
            .equ NumPixelMax,16777216

// extern "C" bool CheckArgs_(const uint8_t* pb_src, const uint8_t* pb_mask, uint32_t num_pixels);

            .text
            .global CheckArgs_
CheckArgs_:

// Check pb_mask and pb_src for proper alignment
            tst r0,#0x0f
            bne InvalidArgA                     // pb_src not 16b aligned
            tst r1,#0x0f
            bne InvalidArgA                     // pb_mask not 16b aligned

// Check num_pixels for valid size
            cmp r2,#0
            beq InvalidArgA                     // jump if num_pixels == 0
            mov r3,#NumPixelMax
            cmp r2,r3
            bhi InvalidArgA                     // jump if num_pixels too big

            tst r2,#0x3f                        // make sure num_pixels is  
            bne InvalidArgA                     // integral multiple of 64

            mov r0,#1                           // set success return code
            bx lr

InvalidArgA:
            mov r0,#0                           // set error return code
            bx lr

// extern "C" bool ThresholdImage_(ITD* itd);

            .global ThresholdImage_
ThresholdImage_:
            push {r4,lr}

// Validate args
            mov r4,r0                           // r4 points to ITD struct
            ldr r0,[r4,#S_PbSrc]                // r0 = PbSrc
            ldr r1,[r4,#S_PbMask]               // r1 = PbMask
            ldr r2,[r4,#S_NumPixels]            // r2 = NumPixels
            bl CheckArgs_
            cmp r0,#0
            beq InvalidArgB                     // jump if arg check failed

// Initialize
            ldr r0,[r4,#S_PbSrc]                // r0 = PbSrc
            ldr r1,[r4,#S_PbMask]               // r1 = PbMask
            ldr r2,[r4,#S_NumPixels]            // r2 = NumPixels
            ldrb r3,[r4,#S_Threshold]           // r3 = threshold value
            vdup.u8 q8,r3                       // q8 = packed threshold

// Threshold image
Loop1B:     vldm r0!,{q0-q3}                     // q0:q3 = 64 pixels

            vcgt.u8 q12,q0,q8                    // compare pixels
            vcgt.u8 q13,q1,q8                    // to specfied threshold
            vcgt.u8 q14,q2,q8
            vcgt.u8 q15,q3,q8

            vstm r1!,{q12-q15}                  // save mask result

            subs r2,#64                         // n -= 64
            bne Loop1B                          // jump if more pixels

            mov r0,#1                           // set success return code
DoneB:
            pop {r4,pc}

InvalidArgB:
            mov r0,#0                           // set error return code
            b DoneB

// extern "C" void CalcMeanMaskedPixels_(ITD* itd);

            .global CalcMeanMaskedPixels_
CalcMeanMaskedPixels_:
            push {r4,lr}

// Initialize
            mov r4,r0                           // r4 points to IDT struct
            ldr r0,[r4,#S_PbSrc]                // r0 = PbSrc
            ldr r1,[r4,#S_PbMask]               // r1 = PbMask
            ldr r2,[r4,#S_NumPixels]            // r2 = NumPixels

            veor.u32 q8,q8,q8                   // q8 = num_masked_pixels
            veor.u32 q9,q9,q9                   // q9 = sum_mask_pixels
            vmov.u8 q10,#0x01                   // q10 = packed 0x01

// Calculate packed num_mask_pixels and sum_masked_pixels
Loop1C:     vldm r0!,{q0}                       // q0 = 16 pixels
            vldm r1!,{q1}                       // q1 = 16 mask pixels

            vand.u8 q2,q1,q10                   // q2 = 0x00 or 0x01
            vaddl.u8 q3,d4,d5                   // sum pixel counts
            vaddl.u16 q11,d6,d7                 // sum pixel counts
            vadd.u32 q8,q8,q11                  // update num_masked_pixels

            vand.u8 q2,q1,q0                    // q2 = 0x00 or pixel val
            vaddl.u8 q3,d4,d5                   // sum pixel intensities
            vaddl.u16 q11,d6,d7                 // sum pixel intensities
            vadd.u32 q9,q9,q11                  // update sum_masked_pixels

            subs r2,#16
            bne Loop1C

// Calculate final NumMaskedPixels and SumMaskedPixels
            vpadd.u32 d0,d16,d17
            vpadd.u32 d1,d0,d0
            vmov r0,d1[0]
            str r0,[r4,#S_NumMaskedPixels]

            vpadd.u32 d0,d18,d19
            vpadd.u32 d1,d0,d0
            vmov r1,d1[0]
            str r1,[r4,#S_SumMaskedPixels]

// Calculate MeanMaskedPixels
            cmp r0,#0                           // NumMaskedPixels == 0?
            vmov s0,r1                          // s0 = SumMaskedPixels
            vmov s1,r0                          // s1 = NumMaskedPixels
            vcvt.f64.u32 d1,s0
            vcvt.f64.u32 d2,s1

            vmoveq.f64 d0,#-1.0                 // if NumMaskedPixels == 0
            vdivne.f64 d0,d1,d2                 // calc mean or use -1.0

            vstr.f64 d0,[r4,#S_MeanMaskedPixels]  // save MeanMaskedPixels
            pop {r4,pc}
