//-------------------------------------------------
//               Ch06_08_.s
//-------------------------------------------------

// extern "C" void RectToPolar_(double* r, double* theta, double x, double y);

                .text
r8_RadToDeg:    .double 57.2957795131
r8_DegToRad:    .double 0.0174532925

            .global RectToPolar_
RectToPolar_:
// Prologue
            push {r4,lr}

            mov r4,r1                           // save theta for later

// Calculate r
            vmul.f64 d2,d0,d0                   // d2 = x * x
            vfma.f64 d2,d1,d1                   // d2 = x * x + y * y
            vsqrt.f64 d3,d2                     // d3 = r
            vstr.f64 d3,[r0]                    // save r

// Calculate theta
            vmov d2,d1
            vmov d1,d0                          // d1 = x
            vmov d0,d2                          // d0 = y
            bl atan2                            // calc arctan(y / x)
            vldr d1,r8_RadToDeg
            vmul.f64 d2,d0,d1                   // d2 = theta in degrees
            vstr.f64 d2,[r4]                    // save theta

// Epilogue
            pop {r4,pc}

// extern "C" void PolarToRect_(double* x, double* y, double r, double theta);

            .global PolarToRect_
PolarToRect_:
// Prologue
            push {r4-r6,lr}
            vpush {d8,d9}

// Save r, x, and y for later use
            vmov d8,d0                          // d8 = r
            mov r4,r0                           // r4 = x
            mov r5,r1                           // r5 = y

// Calculate x
            vldr d2,r8_DegToRad
            vmul.f64 d0,d1,d2                   // d0 = theta in radians
            vmov.f64 d9,d0                      // save theta for later
            bl cos                              // calc cos(theta)
            vmul.f64 d1,d8,d0                   // d1 = r * cos(theta)
            vstr.f64 d1,[r4]                    // save x

// Calculate y
            vmov.f64 d0,d9                      // d0 = theta in radians
            bl sin                              // calc sin(theta)
            vmul.f64 d1,d8,d0                   // d1 = r * sin(theta)
            vstr.f64 d1,[r5]                    // save y

// Epilogue
            vpop {d8,d9}
            pop {r4-r6,pc}
