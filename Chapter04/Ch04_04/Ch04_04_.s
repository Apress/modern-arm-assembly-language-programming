//-------------------------------------------------
//               Ch04_04_.s
//-------------------------------------------------

// extern "C" bool CalcMatrixRowColSums_(int* row_sums, int* col_sums, const int* x, int nrows, int ncols);

            .text
            .global CalcMatrixRowColSums_

            .equ ARG_NCOLS,32

CalcMatrixRowColSums_:
            push {r4-r11}

            cmp r3,#0
            movle r0,#0                         // set error return code
            ble Done                            // jump if nrows <= 0

            ldr r4,[sp,#ARG_NCOLS]
            cmp r4,#0
            movle r0,#0                         // set error return code
            ble Done                            // jump if ncols <= 0

// Set elements of col_sums to zero
            mov r5,r1                           // r5 = col_sums
            mov r6,r4                           // r6 = ncols
            mov r7,#0

Loop0:      str r7,[r5],#4                      // col_sums[j] = 0
            subs r6,#1                          // j -= 1
            bne Loop0                           // jump if j != 0

// Main processing loops
            mov r5,#0                           // i = 0

Loop1:      mov r6,#0                           // j = 0
            mov r12,#0                          // row_sums_temp = 0
            mul r7,r5,r4                        // r7 = i * ncols

Loop2:      add r8,r7,r6                        // r8 = i * ncols + j
            ldr r9,[r2,r8,lsl #2]               // r9 = x[i][j]

// Update row_sums and col_sums using current x[i][j]
            add r12,r12,r9                      // row_sums_temp += x[i][j]

            add r10,r1,r6,lsl #2                // r10 = ptr to col_sums[j]
            ldr r11,[r10]                       // r11 = col_sums[j]
            add r11,r11,r9                      // col_sums[j] += x[i][j]
            str r11,[r10]                       // save col_sums[j]

            add r6,r6,#1                        // j += 1
            cmp r6,r4
            blt Loop2                           // jump if j < ncols

            str r12,[r0],#4                     // save row_sums[i]

            add r5,r5,#1                        // i += 1
            cmp r5,r3
            blt Loop1                           // jump if i < nrows

            mov r0,#1                           // set success return code

Done:       pop {r4-r11}
            bx lr
