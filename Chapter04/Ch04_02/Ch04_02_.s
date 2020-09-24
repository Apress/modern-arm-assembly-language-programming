//-------------------------------------------------
//               Ch04_02_.s
//-------------------------------------------------

// extern "C" int32_t CalcZ_(int32_t* z const int8_t* x, const int16_t* y, int32_t n);

            .text
            .global CalcZ_
CalcZ_:     push {r4-r9}

            mov r4,#0                           // sum = 0
            cmp r3,#0
            ble Done                            // jump if n <= 0

            ldr r5,=g_Val1
            ldr r5,[r5]                         // r5 = g_Val1

            ldr r6,=g_Val2
            ldr r6,[r6]                         // r6 = g_Val2

// Main processing loop
Loop1:      ldrsb r7,[r1],#1                    // r7 = x[i]
            ldrsh r8,[r2],#2                    // r8 = y[i]

            cmp r7,#0                           // is x[i] < 0?

            mullt r9,r8,r5                      // temp = y[i] * g_Val1
                                                // (if x[i] < 0)

            mulge r9,r8,r6                      // temp = y[i] * g_Val2
                                                // (if x[i] >= 0)

            add r4,r4,r9                        // sum += temp
            str r9,[r0],#4                      // save result z[i]

            subs r3,#1                          // n -= 1
            bne Loop1                           // repeat until done

Done:       mov r0,r4                           // r0 = final sum
            pop {r4-r9}
            bx lr
