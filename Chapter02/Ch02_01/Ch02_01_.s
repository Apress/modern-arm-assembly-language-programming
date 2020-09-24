//------------------------------------------------
//               Ch02_01_.s
//------------------------------------------------

// extern "C" int IntegerAddSub_(int a, int b int c, int d);

            .text
            .global IntegerAddSub_
IntegerAddSub_:

// Calculate a + b + c - d
            add r0,r0,r1                        // r0 = a + b
            add r0,r0,r2                        // r0 = a + b + c
            sub r0,r0,r3                        // r0 = a + b + c - d

            bx lr                               // return to caller
