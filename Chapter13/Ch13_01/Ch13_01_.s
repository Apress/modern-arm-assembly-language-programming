//-------------------------------------------------
//               Ch13_01_.s
//-------------------------------------------------

// Constants for temperature conversion functions
                .text
r4_ScaleFtoC:   .single 0.55555556              // 5 / 9
r4_ScaleCtoF:   .single 1.8                     // 9 / 5
r4_32p0:        .single 32.0

// extern "C" float ConvertFtoC_(float deg_f);

            .global ConvertFtoC_
ConvertFtoC_:

// Convert deg_f to Celsius
            ldr s1,r4_32p0                      // s1 = 32
            ldr s2,r4_ScaleFtoC                 // s2 = 5 / 9
            fsub s3,s0,s1                       // s3 = deg_f - 32
            fmul s0,s3,s2                       // s0 = (deg_f - 32) * 5 / 9
            ret

// extern "C" float ConvertCtoF_(float deg_c);

            .global ConvertCtoF_
ConvertCtoF_:

// Convert deg_c to Fahrenheit
            ldr s1,r4_32p0                      // s1 = 32
            ldr s2,r4_ScaleCtoF                 // s2 = 9 / 5
            fmul s3,s0,s2                       // s3 = deg_c * 9 / 5
            fadd s0,s3,s1                       // s3 = deg_c * 9 / 5 + 32
            ret
