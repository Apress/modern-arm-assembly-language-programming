//-------------------------------------------------
//               Ch013_05_.s
//-------------------------------------------------

// String table - used in ConvertB_
            .text
Str0:       .asciz "fcvtns - round to nearest"
Str1:       .asciz "fcvtps - round to plus infinity"
Str2:       .asciz "fcvtms - round to minus infinity"
Str3:       .asciz "fcvtzs - round to zero"
            .balign 4

// extern "C" double ConvertA_(float a, int b, unsigned int c, long long d, unsigned long long e);

            .global ConvertA_
ConvertA_:  fcvt d0,s0                          // d0 = a as F64

            scvtf d1,w0                         // d1 = b as F64
            ucvtf d2,w1                         // d2 = c as F64

            scvtf d3,x2                         // d3 = d as F64
            ucvtf d4,x3                         // d4 = e as F64

            fadd d5,d0,d1                       // d5 = a + b
            fadd d6,d2,d3                       // d6 = c + d
            fadd d7,d5,d4                       // d7 = a + b + e
            fadd d0,d6,d7                       // d0 = final sum
            ret

// extern "C" int ConvertB_(int* x, const char** msg_strings, double a);

            .global ConvertB_
ConvertB_:

// Convert a to signed integer using different rounding modes
            fcvtns w2,d0                        // rm = to nearest (even)
            str w2,[x0,0]                       // save result
            adr x2,Str0                         // x2 = address of Str0
            str x2,[x1]                         // save ptr to string S0

            fcvtps w2,d0                        // rm = to plus infinity
            str w2,[x0,4]                       // save result
            adr x2,Str1                         // x2 = address of Str1
            str x2,[x1,8]                       // save ptr to string S1

            fcvtms w2,d0                        // rm = to minus infinity
            str w2,[x0,8]                       // save result
            adr x2,Str2                         // x2 = address of Str2
            str x2,[x1,16]                      // save ptr to string S2

            fcvtzs w2,d0                        // rm = to zero
            str w2,[x0,12]                      // save result
            adr x2,Str3                         // x2 = address of Str3
            str x2,[x1,24]                      // save ptr to string S3
            ret
