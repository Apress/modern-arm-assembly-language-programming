//------------------------------------------------
//               Ch02_06_.s
//------------------------------------------------

// extern "C" void MoveRegA_(void a, unsigned int* b);

            .text
            .global MoveRegA_
MoveRegA_:
            push {r4-r7}

// Register to register move
            mov r7,r1                           // copy value in r1 to r7

// Register moves with shift/rotate operator
            mov r2,r0,asr #2                    // arithmetic shift right
            mov r3,r0,lsl #4                    // logical shift left
            mov r4,r0,lsr #5                    // logical shift right
            mov r5,r0,ror #3                    // rotate right
            mov r6,r0,rrx                       // rotate right extended

            str r2,[r7]                         // save asr result to b[0]
            str r3,[r7,#4]                      // save lsl result to b[1]
            str r4,[r7,#8]                      // save lsr result to b[2]
            str r5,[r7,#12]                     // save ror result to b[3]
            str r6,[r7,#16]                     // save rrx result to b[4]

            pop {r4-r7}
            bx lr

// extern "C" void MoveRegB_(unsigned int a, unsigned int* b, unsigned int count);

            .global MoveRegB_
MoveRegB_:
            push {r4-r6}

// Register moves with shift/rotate operator
            mov r3,r0,asr r2                    // arithmetic shift right
            mov r4,r0,lsl r2                    // logical shift left
            mov r5,r0,lsr r2                    // logical shift right
            mov r6,r0,ror r2                    // rotate right

            str r3,[r1]                         // save asr result to b[0]
            str r4,[r1,#4]                      // save lsl result to b[1]
            str r5,[r1,#8]                      // save lsr result to b[2]
            str r6,[r1,#12]                     // save ror result to b[3]

            pop {r4-r6}
            bx lr
