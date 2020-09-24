//-------------------------------------------------
//               Ch13_07_.s
//-------------------------------------------------

// extern "C" bool CalcTrace_(double* trace, const double* x, int nrows, int ncols);

            .text
            .global CalcTrace_
CalcTrace_:
            cmp w2,w3
            b.ne InvalidArg                     // jump if nrows != ncols
            cmp w2,0
            b.le InvalidArg                     // jump if nrows <= 0

// Calculate matrix trace
            movi d0,0                           // sum = 0.0
            mov w4,0                            // i = 0

Loop1:      mul w5,w4,w3                        // w5 = i * ncols
            add w5,w5,w4                        // w5 = i * ncols + i

            ldr d1,[x1,w5,sxtw 3]               // d1 = x[i][i]
            fadd d0,d0,d1                       // sum += x[i][i]

            add w4,w4,1                         // i += 1
            cmp w4,w2
            b.lt Loop1                          // jump if not done

            str d0,[x0]                         // save trace value
            mov w0,1                            // set success return code
            ret

InvalidArg: mov w0,0                            // set error return code
            ret
