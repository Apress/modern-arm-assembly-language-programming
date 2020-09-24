//------------------------------------------------
//               Ch02_04_.s
//------------------------------------------------

            .data
Foo:        .word 100, 200, 300, 400

// extern "C" void TestLDR_(void);

            .text
            .global TestLDR_

TestLDR_:   ldr r1,=Foo                         // r1 = address of Foo

            ldr r2,[r1]                         // r2 = Foo[0]
            ldr r3,[r1,#4]                      // r3 = Foo[1]

            add r0,r2,r3                        // r0 = Foo[0] + Foo[1]

            ldr r2,[r1,#8]                      // r2 = Foo[2]
            add r0,r0,r2                        // r0 += Foo[2]

            ldr r2,[r1,#12]                     // r2 = Foo[3]
            add r0,r0,r2                        // r0 += Foo[3]

            bx lr                               // return to caller
