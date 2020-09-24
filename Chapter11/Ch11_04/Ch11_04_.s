//-------------------------------------------------
//               Ch11_04_.s
//-------------------------------------------------

// Test arrays
            .data
A1:         .word 1, 2, 3, 4, 5, 6, 7, 8
A2:         .quad 10, -20, 30, -40, 50, -60, 70, -80

            .text
A3:         .short 100, 200, -300, 400, 500, -600, 700, 800

// extern "C" int TestLDR1_(unsigned int i, unsigned long j);

            .global TestLDR1_
TestLDR1_:  ldr x2,=A1                              // x2 = ptr to A1

            ldr w3,[x2,w0,uxtw 2]                   // w3 = A1[i]
            ldr w4,[x2,x1,lsl 2]                    // w4 = A1[j]

            add w0,w3,w4                            // w0 = A1[i] + A1[j]
            ret

// extern "C" long TestLDR2_(unsigned int i, unsigned long j);

            .global TestLDR2_
TestLDR2_:  ldr x2,=A2                              // x2 = ptr to A2

            ldr x3,[x2,w0,uxtw 3]                   // x3 = A2[i]
            ldr x4,[x2,x1,lsl 3]                    // x4 = A2[j]

            add x0,x3,x4                            // w0 = A2[i] + A2[j]
            ret

// extern "C" short TestLDR3_(unsigned int i, unsigned long j);

            .global TestLDR3_
TestLDR3_:  adr x2,A3                               // x2 = ptr to A3

            ldrsh w3,[x2,w0,uxtw 1]                 // w3 = A3[i]
            ldrsh w4,[x2,x1,lsl 1]                  // w4 = A3[j]

            add w0,w3,w4                            // w0 = A3[i] + A3[j]
            ret
