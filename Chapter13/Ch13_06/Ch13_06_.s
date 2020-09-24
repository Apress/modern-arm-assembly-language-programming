//-------------------------------------------------
//               Ch13_06_.s
//-------------------------------------------------

// extern "C" bool CalcMeanStdev_(double* mean, double* stdev, const double* x, int n);

            .text
            .global CalcMeanStdev_
CalcMeanStdev_:
            cmp w3,2                            // is n < 2?
            b.lt InvalidArg                     // jump if n < 2

// Calculate mean
            movi d0,0                           // sum1 = 0.0
            movi d4,0                           // sum2 = 0.0
            mov w4,0                            // i = 0
            mov x5,x2                           // x5 = ptr to x

Loop1:      ldr d1,[x5],8                       // d1 = x[i]
            fadd d0,d0,d1                       // sum1 += x[i]
            add w4,w4,1                         // i += 1
            cmp w4,w3
            b.lt Loop1                          // jump if i < n

            scvtf d1,w3                         // d1 = n as double
            fdiv d2,d0,d1                       // d2 = sum1 / n (mean)
            str d2,[x0]                         // save mean

// Calculate standard deviation
            mov w4,0                            // i = 0
            mov x5,x2                           // x5 = ptr to x

Loop2:      ldr d1,[x5],8                       // d1 = x[i]
            fsub d3,d1,d2                       // d3 = x[i] - mean
            fmadd d4,d3,d3,d4                   // sum2 += (x[i] - mean)**2

            add w4,w4,1                         // i += 1
            cmp w4,w3
            b.lt Loop2                          // jump if i < n

            sub w3,w3,1                         // w3 = n - 1
            scvtf d1,w3                         // d1 = n - 1 as double

            fdiv d2,d4,d1                       // d2 = sum2 / (n - 1)
            fsqrt d3,d2                         // d3 = stdev

            str d3,[x1]                         // save stdev
            mov w0,1                            // set success return code
            ret

InvalidArg: mov w0,0                            // set error return code
            ret
