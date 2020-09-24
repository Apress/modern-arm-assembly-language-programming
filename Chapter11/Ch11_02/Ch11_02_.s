//-------------------------------------------------
//               Ch11_02_.s
//-------------------------------------------------

// extern "C" int IntegerMulA_(int a, int b);

            .text
            .global IntegerMulA_
IntegerMulA_:

// Calculate a * b and save result
            mul w0,w0,w1                        // a * b (32-bit)
            ret

// extern "C" long IntegerMulB_(long a, long b);

            .global IntegerMulB_
IntegerMulB_:

// Calculate a * b and save result
            mul x0,x0,x1                        // a * b (64-bit)
            ret

// extern "C" long IntegerMulC_(int a, int b);

            .global IntegerMulC_
IntegerMulC_:

// Calculate a * b and save result
            smull x0,w0,w1                      // signed 64-bit
            ret

// extern "C" unsigned long IntegerMulD_(unsigned int a, unsigned int b);

            .global IntegerMulD_
IntegerMulD_:

// Calculate a * b and save result
            umull x0,w0,w1                      // unsigned signed 64-bit
            ret
