//-------------------------------------------------
//               Ch13_04_.s
//-------------------------------------------------


// extern "C" void CompareF32_(bool* results, float a, float b);
            .text
            .global CompareF32_
CompareF32_:

            fcmpe s0,s1                         // compare a and b, update NZCV

            cset w1,vs                          // w1 = 1 if unordered
            strb w1,[x0,0]                      // save result

            cset w1,mi                          // w1 = 1 if a < b
            strb w1,[x0,1]                      // save result

            cset w1,ls                          // w1 = 1 if a <= b
            strb w1,[x0,2]                      // save result

            cset w1,eq                          // w1 = 1 if a == b
            strb w1,[x0,3]                      // save result

            cset w1,ne                          // w1 = 1 if a != b
            strb w1,[x0,4]                      // save result

            cset w1,gt                          // w1 = 1 if a > b
            strb w1,[x0,5]                      // save result

            cset w1,ge                          // w1 = 1 if a >= b
            strb w1,[x0,6]                      // save result
            ret
