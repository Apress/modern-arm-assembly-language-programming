//-------------------------------------------------
//               Ch12_06_.s
//-------------------------------------------------

// extern "C" bool CalcMatrixRowColSums_(int64_t* row_sums, int64_t* col_sums,
//    const int64_t* x, int nrows, int ncols);

            .text
            .global CalcMatrixRowColSums_

CalcMatrixRowColSums_:
            cmp w3,0
            b.le Error                          // jump if nrows <= 0
            cmp w4,0
            b.le Error                          // jump if ncols <= 0

// Set col_sums to zero
            mov x5,x1                           // x5 = col_sums
            mov w6,w4                           // w6 = ncols
            mov x7,0
Loop0:      str x7,[x5],8                       // col_sums[j] = 0
            subs w6,w6,1
            b.ne Loop0

// Main processing loops
            mov w5,0                            // i = 0
 
Loop1:      mov w6,0                            // j = 0
            str x6,[x0,w5,sxtw 3]               // row_sums[i] = 0

            mul w7,w5,w4                        // w7 = i * ncols

Loop2:      add w8,w7,w6                        // w8 = i * ncols + j
            ldr x9,[x2,w8,sxtw 3]               // x9 = x[i][j]

// Update row_sums and col_sums using current x[i][j]
            add x10,x0,w5,sxtw 3                // x10 = ptr to row_sums[i]
            ldr x11,[x10]                       // x11 = row_sums[i]
            add x11,x11,x9                      // row_sums[i] += x[i][j]
            str x11,[x10]                       // save updated row_sums[i]

            add x10,x1,w6,sxtw 3                // x10 = ptr to col_sums[j]
            ldr x11,[x10]                       // x11 = col_sums[j]
            add x11,x11,x9                      // col_sums[j] += x[i][j]
            str x11,[x10]                       // save updated col_sums[j]

            add w6,w6,1                         // j += 1
            cmp w6,w4
            b.lt Loop2                          // jump if j < ncols

            add w5,w5,1                         // i += 1
            cmp w5,w3
            b.lt Loop1                          // jump if i < nrows

            mov w0,1                            // set success return code
            ret

Error:      mov w0,0                            // set error return code
            ret
