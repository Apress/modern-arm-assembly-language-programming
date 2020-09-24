//-------------------------------------------------
//               Ch14_04_.s
//-------------------------------------------------

// extern "C" bool CalcMinMaxU8_(uint8_t* x_min, uint8_t* x_max, const uint8_t* x, uint64_t n);

            .text
            .global CalcMinMaxU8_
CalcMinMaxU8_:

// Validate arguments
            cmp x3,0
            b.eq InvalidArg                     // jump if n == 0
            tst x2,0x0f
            b.ne InvalidArg                     // jump if x not 16b aligned

// Initialize
            mov w4,255
            dup v2.16b,w4
            mov v3.16b,v2.16b                   // v2:v3 = packed min (32)
            eor v4.16b,v4.16b,v4.16b
            eor v5.16b,v5.16b,v5.16b            // v4:v5 = packed max (32)

            cmp x3,32
            b.lo SkipLoop1                      // jump if n < 32

// Main processing loop
Loop1:      ld1 {v0.16b,v1.16b},[x2],32         // load block of 32 pixels

            umin v2.16b,v2.16b,v0.16b
            umin v3.16b,v3.16b,v1.16b           // update pixel minimums
            umax v4.16b,v4.16b,v0.16b
            umax v5.16b,v5.16b,v1.16b           // update pixel maximums

            sub x3,x3,32                       // n -= 32
            cmp x3,32
            b.cs Loop1                          // jump if n >= 32

// Reduce packed minimums and maximums to scalar values
SkipLoop1:  umin v0.16b,v2.16b,v3.16b
            uminv b1,v0.16b
            umov w4,v1.b[0]                     // w4 = pixel min value

            umax v0.16b,v4.16b,v5.16b
            umaxv b1,v0.16b
            umov w5,v1.b[0]                     // w5 = pixel max value

            cmp x3,0
            b.eq SaveMinMax                     // jump if n == 0

// Process final pixels
Loop2:      ldrb w6,[x2],1                      // w6 = pixel value
            cmp w6,w4
            csel w4,w6,w4,lo                    // update pixel min value
            cmp w6,w5
            csel w5,w6,w5,hi                    // update pixel max value

            subs x3,x3,1                        // n -= 1
            b.ne Loop2                          // repeat until done

// Save results
SaveMinMax: strb w4,[x0]                        // save minimum to x_min
            strb w5,[x1]                        // save maximum to x_max
            mov w0,1                            // set success return code
            ret

InvalidArg: mov w0,0                            // set error return code
            ret
