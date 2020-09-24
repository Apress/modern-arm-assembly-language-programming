//-------------------------------------------------
//               Ch13_02_.s
//-------------------------------------------------

// extern "C" void CalcSphereAreaVolume_(double r, double* sa, double* vol);

            .text
            .global CalcSphereAreaVolume_
CalcSphereAreaVolume_:

// Calculate surface area and volume
            ldr d5,r8_PI                        // d5 = PI
            fmov d6,4.0                         // d6 = 4.0
            fmov d7,3.0                         // d7 = 3.0

            fmul d1,d0,d0                       // d1 = r * r
            fmul d1,d1,d5                       // d1 = r * r * PI
            fmul d1,d1,d6                       // d1 = r * r * PI * 4
            str d1,[x0]                         // save surface area

            fmul d2,d1,d0                       // d2 = sa * r
            fdiv d3,d2,d7                       // d3 = sa * r / 3
            str d3,[x1]                         // save volume
            ret

r8_PI:      .double 3.14159265358979323846
