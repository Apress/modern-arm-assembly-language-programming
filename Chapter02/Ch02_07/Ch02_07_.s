//------------------------------------------------
//               Ch02_07_.s
//------------------------------------------------

// extern "C" void TestBitOpsA_(unsigned int a, unsigned int b, unsigned int* c);

            .text
            .global TestBitOpsA_
TestBitOpsA_:
            push {r4,r5}

            and r3,r0,r1                        // a AND b
            str r3,[r2]

            orr r4,r0,r1                        // a OR b
            str r4,[r2,#4]

            eor r5,r0,r1                        // a EOR b
            str r5,[r2,#8]

            pop {r4,r5}
            bx lr


.int 100
.long 200
.word - 100

.quad -1000
.octa -2000


// extern "C" void TestBitOpsB_(unsigned int a, unsigned int* b);

            .global TestBitOpsB_
TestBitOpsB_:

            push {r4-r7}

            and r2,r0,#0x0000ff00               // a AND 0x0000ff00
            str r2,[r1]

            orr r3,r0,#0x00ff0000               // a OR 0x00ff0000
            str r3,[r1,#4]

            eor r4,r0,#0xff000000               // a EOR 0xff000000
            str r4,[r1,#8]

// removing comment generates invalid constant after fixup error

//          and r5,r0,#0x00ffff00               // invalid constant

            movw r5,#0xff00
            movt r5,#0x00ff                      // r5 = 0x00ffff00
            and r6,r0,r5                        // a AND 0x00ffff00
            str r6,[r1,#12]

            pop {r4-r7}
            bx lr
