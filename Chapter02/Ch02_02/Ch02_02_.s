//------------------------------------------------
//               Ch02_02_.s
//------------------------------------------------

// extern "C" int IntegerMulA_(int a, int b);

            .text
            .global IntegerMulA_
IntegerMulA_:

// Calculate a * b and save result
            mul r0,r0,r1                        // calc a * b (32-bit)
            bx lr

// extern "C" long long IntegerMulB_(int a, int b);

            .global IntegerMulB_
IntegerMulB_:

// Calculate a * b and save result
            smull r0,r1,r0,r1                   // calc a * b (signed 64-bit)
            bx lr

// extern "C" unsigned long long IntegerMulC_(unsigned int a, unsigned int b);

            .global IntegerMulC_
IntegerMulC_:

// Calculate a * b and save result
            umull r0,r1,r0,r1                   // calc a * b (unsigned 64-bit)
            bx lr
