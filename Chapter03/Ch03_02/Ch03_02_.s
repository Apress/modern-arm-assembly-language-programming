//------------------------------------------------
//               Ch03_02_.s
//------------------------------------------------

// extern "C" int SumCubes_(unsigned char a, short b, int c, int d,
//    signed char e, short f, unsigned char g, unsigned short h, int i);

            .equ ARG_E, 8                       // stack offset for e
            .equ ARG_F, 12                      // stack offset for f
            .equ ARG_G, 16                      // stack offset for g
            .equ ARG_H, 20                      // stack offset for h
            .equ ARG_I, 24                      // stack offset for i

            .text
            .global SumCubes_
SumCubes_:  push {r4,r5}

            mul r4,r0,r0                        // r4 = a * a
            mul r0,r4,r0                        // r0 = a * a * a

            mul r4,r1,r1                        // r4 = b * b
            mla r0,r4,r1,r0                     // r0 += b * b * b

            mul r4,r2,r2                        // r4 = c * c
            mla r0,r4,r2,r0                     // r0 += c * c * c

            mul r4,r3,r3                        // r4 = d * d
            mla r0,r4,r3,r0                     // r0 += d * d * d

            ldrsb r1,[sp,#ARG_E]                // r1 = e (sign-extended)
            mul r4,r1,r1                        // r4 = e * e
            mla r0,r4,r1,r0                     // r0 += e * e * e

            ldrsh r1,[sp,#ARG_F]                // r1 = f (sign-extended)
            mul r4,r1,r1                        // r4 = f * f
            mla r0,r4,r1,r0                     // r0 += f * f * f

            ldrb r1,[sp,#ARG_G]                 // r1 = g (zero-extended)
            mul r4,r1,r1                        // r4 = g * g
            mla r0,r4,r1,r0                     // r0 += g * g * g

            ldrh r1,[sp,#ARG_H]                 // r1 = h (zero-extended)
            mul r4,r1,r1                        // r4 = h * h
            mla r0,r4,r1,r0                     // r0 += h * h * h

            ldr r1,[sp,#ARG_I]                  // r1 = i
            mul r4,r1,r1                        // r4 = i * i
            mla r0,r4,r1,r0                     // r0 += i * i * i

            pop {r4,r5}
            bx lr
