//-------------------------------------------------
//               Ch06_02_.s
//-------------------------------------------------

            .text
r8_PI:      .double 3.14159265358979323846

// extern "C" void CalcSphereAreaVolume_(double r, double* sa, double* vol);

            .global CalcSphereAreaVolume_
CalcSphereAreaVolume_:

// Calculate sphere surface area and volume
            vldr.f64 d5,r8_PI                   // d5 = PI
            vmov.f64 d6,#4.0                    // d6 = 4.0
            vmov.f64 d7,#3.0                    // d7 = 3.0

            vmul.f64 d1,d0,d0                   // d1 = r * r
            vmul.f64 d1,d1,d5                   // d1 = r * r * PI
            vmul.f64 d1,d1,d6                   // d1 = r * r * PI * 4
            vstr.f64 d1,[r0]                    // save surface area

            vmul.f64 d2,d1,d0                   // d2 = sa * r
            vdiv.f64 d3,d2,d7                   // d3 = sa * r / 3
            vstr.f64 d3,[r1]                    // save volume
            bx lr

