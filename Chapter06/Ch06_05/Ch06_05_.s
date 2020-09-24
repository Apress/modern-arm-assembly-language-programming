//-------------------------------------------------
//               Ch06_05_.s
//-------------------------------------------------

// extern "C" Rm GetRm_(void);

            .text
            .global GetRm_
GetRm_:     vmrs r1,fpscr                       // r1 = fpscr
            lsr r2,r1,#22
            and r0,r2,#3                        // RMode in bits 1:0
            bx lr

// extern "C" void SetRm_(Rm rm);

            .global SetRm_
SetRm_:     vmrs r1,fpscr                       // r1 = fpscr
            bfi r1,r0,#22,#2                    // insert new RMode bits
            vmsr fpscr,r1                       // save updated fpscr
            bx lr

// extern "C" int ConvertA_(double a);

            .global ConvertA_
ConvertA_:  vcvtr.s32.f64 s0,d0                 // convert a to signed int
            vmov r0,s0                          // copy result to r0
            bx lr

// extern "C" double ConvertB_(int a, unsigned int b);

            .global ConvertB_
ConvertB_:  vmov s0,r0                          // s0 = a
            vcvt.f64.s32 d1,s0                  // convert a to double

            vmov s1,r1                          // s1 = b
            vcvt.f64.u32 d2,s1                  // convert b to double
            
            vadd.f64 d0,d1,d2                   // d0 = a + b
            bx lr

// extern "C" float ConvertC_(double a, float b, double c, float d);

            .global ConvertC_
ConvertC_:  vcvt.f64.f32 d3,s2                  // convert b to double
            vcvt.f64.f32 d4,s3                  // convert d to double

            vadd.f64 d5,d0,d3                   // Perform arithmetic
            vsub.f64 d6,d2,d4                   // using doubles
            vdiv.f64 d7,d5,d6

            vcvt.f32.f64 s0,d7                  // Convert result to float
            bx lr
