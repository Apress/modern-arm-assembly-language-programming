//-------------------------------------------------
//               Ch13_03_.s
//-------------------------------------------------

// extern "C" double CalcDist_(double x1, double y1, double z1, double x2, double y2, double z2);

           .text
            .global CalcDist_
CalcDist_:

// Calculate distance
            fsub d0,d3,d0                       // d0 = x2 - x1
            fmul d0,d0,d0                       // d0 = (x2 - x1) ** 2

            fsub d1,d4,d1                       // d1 = y2 - y1
            fmadd d0,d1,d1,d0                   // d0 += (y2 - y1) ** 2

            fsub d2,d5,d2                       // d2 = z2 - z1
            fmadd d0,d2,d2,d0                   // d0 += (z2 - z1) ** 2

            fsqrt d0,d0                         // d0 = final distance
            ret
