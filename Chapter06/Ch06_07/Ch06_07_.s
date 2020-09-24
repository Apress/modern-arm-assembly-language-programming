//-------------------------------------------------
//               Ch06_07_.s
//-------------------------------------------------

            .text
r8_zero:    .double 0.0

// extern "C" bool CalcTrace_(double* trace, const double* x, int nrows, int ncols);

            .global CalcTrace_
CalcTrace_: push {r4,r5}
            cmp r2,r3
            bne InvalidArg                      // jump if nrows != ncols
            cmp r2,#0
            ble InvalidArg                      // jump if nrows <= 0

// Calculate trace
            vldr.f64 d0,r8_zero                 // sum = 0.0
            mov r4,#0                           // i = 0

Loop1:      mul r5,r4,r3                        // r5 = i * ncols
            add r5,r5,r4                        // r5 = i * ncols + i
            add r5,r1,r5,lsl #3                 // r5 = ptr to x[i][i]

            vldr.f64 d1,[r5]                    // d1 = x[i][i]
            vadd.f64 d0,d0,d1                   // sum += x[i][i]

            add r4,#1                           // i += 1
            cmp r4,r2 
            blt Loop1                           // jump if not done

            vstr.f64 d0,[r0]                    // save trace value

            mov r0,#1                           // set success return code
Done:       pop {r4,r5}
            bx lr

InvalidArg: mov r0,#0                           // set error return code
            b Done
