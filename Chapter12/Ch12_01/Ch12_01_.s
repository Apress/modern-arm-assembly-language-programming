//-------------------------------------------------
//               Ch12_01_.s
//-------------------------------------------------

// extern "C" int64_t SumCubes_(uint8_t a, int16_t b, int32_t c, int64_t d,
//    int8_t e, int16_t f, uint8_t g, uint16_t h, int32_t i, int8_t j);

            .equ ARG_I,0                       // stack offset for arg i
            .equ ARG_J,8                       // stack offset for arg j

            .text
            .global SumCubes_
SumCubes_:
            ldrsw x8,[SP,ARG_I]                 // x8 = i (sign-extended)
            ldrsb x9,[SP,ARG_J]                 // x9 = j (sign-extended)

            and w0,w0,0xff                      // zero-extend a to 64 bits
            mul x10,x0,x0                       // x10 = a * a
            mul x10,x10,x0                      // x10 = a * a * a

            sxth x1,w1                          // sign-extend b to 64 bits
            mul x11,x1,x1                       // x11 = b * b
            madd x10,x11,x1,x10                 // x10 += b * b * b

            sxtw x2,w2                          // sign-extend c to 64 bits
            mul x11,x2,x2                       // x11 = c * c (64 bits)
            madd x10,x11,x2,x10                 // x10 += c * c * c

            mul x11,x3,x3                       // x11 = d * d
            madd x10,x11,x3,x10                 // x10 += d * d * d

            sxtb x4,w4                          // sign-extend e to 64 bits
            mul x11,x4,x4                       // x11 = e * e
            madd x10,x11,x4,x10                 // x10 += e * e * e

            sxth x5,w5                          // sign-extend f to 64 bits
            mul x11,x5,x5                       // x11 = f * f
            madd x10,x11,x5,x10                 // x10 += f * f * f

            and w6,w6,0xff                      // zero-extend g to 64 bits
            mul x11,x6,x6                       // x11 = g * g
            madd x10,x11,x6,x10                 // x10 += g * g * g

            uxth x7,w7                          // zero-extend h to 64 bits
            mul x11,x7,x7                       // x11 = h * h
            madd x10,x11,x7,x10                 // x10 += h * h * h

            mul x11,x8,x8                       // x11 = i * i
            madd x10,x11,x8,x10                 // x10 += i * i * i

            mul x11,x9,x9                       // x11 = j * j
            madd x0,x11,x9,x10                  // x0 = final result
            ret
