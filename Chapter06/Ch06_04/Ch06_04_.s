//-------------------------------------------------
//               Ch06_04_.s
//-------------------------------------------------

// extern "C" void CompareF32_(bool* results, float a, float b);
            .text
            .global CompareF32_

CompareF32_:
            vcmpe.f32 s0,s1                 // compare F32 values a and b
            vmrs APSR_nzcv,fpscr            // move compare results

            mov r1,#0
            movvs r1,#1                     // r1 = 1 if unordered
            strb r1,[r0,#0]                 // save result

            mov r1,#0
            movlo r1,#1                     // r1 = 1 if a < b
            strb r1,[r0,#1]                 // save result

            mov r1,#0
            movls r1,#1                     // r1 = 1 if a <= b
            strb r1,[r0,#2]                 // save result

            mov r1,#0
            moveq r1,#1                     // r1 = 1 if a == b
            strb r1,[r0,#3]                 // save result

            mov r1,#0
            movne r1,#1                     // r1 = 1 if a != b
            strb r1,[r0,#4]                 // save result

            mov r1,#0
            movgt r1,#1                     // r1 = 1 if a > b
            strb r1,[r0,#5]                 // save result

            mov r1,#0
            movge r1,#1                     // r1 = 1 if a >= b
            strb r1,[r0,#6]                 // save result

            bx lr
