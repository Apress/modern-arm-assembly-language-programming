//-------------------------------------------------
//               Ch16_02_.s
//-------------------------------------------------

// Macro VecCp
//
// Input:   s0 = a.x, s1 = a.y, s2 = a.z
//          s3 = b.x, s4 = b.y, s5 = b.z
//
// Output:  s19 = c.x, s20 = c.y, s21 = c.z

            .macro VecCp
            fmul s16,s1,s5                      // c.X = a.Y * b.Z - a.Z * b.Y
            fmsub s19,s2,s4,s16

            fmul s17,s2,s3                      // c.Y = a.Z * b.X - a.X * b.Z
            fmsub s20,s0,s5,s17

            fmul s18,s0,s4                      // c.Z = a.X * b.Y - a.Y * b.X
            fmsub s21,s1,s3,s18
            .endm

// Macro VecCp4
//
// Input:   v0 = a.x, v1 = a.y, v2 = a.z
//          v3 = b.x, v4 = b.y, v5 = b.z
//
// Output:  v19 = c.x, v20 = c.y, v21 = c.z

            .macro VecCp4
            fmul v19.4s,v1.4s,v5.4s             // c.X = a.Y * b.Z - a.Z * b.Y
            fmls v19.4s,v2.4s,v4.4s

            fmul v20.4s,v2.4s,v3.4s             // c.Y = a.Z * b.X - a.X * b.Z
            fmls v20.4s,v0.4s,v5.4s

            fmul v21.4s,v0.4s,v4.4s             // c.Z = a.X * b.Y - a.Y * b.X
            fmls v21.4s,v1.4s,v3.4s
            .endm

// Macro VecCp4AOS
//
// Input:   x1 = Vector* a, x2 = Vector* b, x0 = Vector* c

            .macro VecCp4AOS
            ld3 {v0.4s,v1.4s,v2.4s},[x1],48     // load vectors (a)
            ld3 {v3.4s,v4.4s,v5.4s},[x2],48     // load vectors (b)
            VecCp4                              // calc cross products
            st3 {v19.4s,v20.4s,v21.4s},[x0],48  // save vectors (c)
            .endm

// Macro VecCp4SOA
//
// Input:   x7 = float* a.X, x8 = float* a.Y, x9 = float* a.Z
//          x10 = float* b.X, x11 = float* b.Y, x12 = float* b.Z
//          x13 = float* c.X, x14 = float* c.Y, x15 = float* c.Z
 
            .macro VecCp4SOA
            ld1 {v0.4s},[x7],16                 // load a.X components
            ld1 {v1.4s},[x8],16                 // load a.Y components
            ld1 {v2.4s},[x9],16                 // load a.Z components

            ld1 {v3.4s},[x10],16                // load b.X components
            ld1 {v4.4s},[x11],16                // load b.Y components
            ld1 {v5.4s},[x12],16                // load b.Z components

            VecCp4                              // calc cross products

            st1 {v19.4s},[x13],16               // save c.X components
            st1 {v20.4s},[x14],16               // save c.Y components
            st1 {v21.4s},[x15],16               // save c.Z components
            .endm

// extern "C" void CrossProdAOS_(Vector* c, const Vector* a, const Vector* b, size_t n);

            .text
            .global CrossProdAOS_
CrossProdAOS_:
            cmp x3,16
            b.lo SkipLoop1A                     // skip loop if n < 16

// Main processing loop
Loop1A:     VecCp4AOS
            VecCp4AOS
            VecCp4AOS
            VecCp4AOS

            sub x3,x3,16                        // n -= 16
            cmp x3,16                           // is n >= 16?
            b.hs Loop1A                         // jump if n >= 16

SkipLoop1A: cbz x3,DoneA                        // jump if no more vectors

Loop2A:     ldp s0,s1,[x1],8                    // s0,s1,s2 = a.X,a.Y,a.Z
            ldr s2,[x1],4

            ldp s3,s4,[x2],8                    // s3,s4,s5 = b.X,b.Y,b.Z
            ldr s5,[x2],4

            VecCp                               // calc cross product

            stp s19,s20,[x0],8                  // save vector c
            str s21,[x0],4

            subs x3,x3,1                        // n -= 1
            b.ne Loop2A
DoneA:      ret

// extern "C" void CrossProdSOA_(VectorSoA& c, const VectorSoA& a, const VectorSoA& b, size_t n);

            .global CrossProdSOA_
CrossProdSOA_:
            ldp x7,x8,[x1],16                   // x7,x8,x9 = 
            ldr x9,[x1]                         // a.X,a.Y,a.Z

            ldp x10,x11,[x2],16                 // x10,x11,x12 =
            ldr x12,[x2]                        // b.X,b.Y,b.Z

            ldp x13,x14,[x0],16                 // x13,x14,x15 = 
            ldr x15,[x0]                        // c.X,c.Y,c.Z

            cmp x3,16
            b.lo SkipLoop1B                     // skip loop if n < 16

// Main processing loop
Loop1B:     VecCp4SOA
            VecCp4SOA
            VecCp4SOA
            VecCp4SOA

            sub x3,x3,16                        // n -= 16
            cmp x3,16                           // is n >= 16?
            b.hs Loop1B                         // jump if n >= 16

SkipLoop1B: cbz x3,DoneB

Loop2B:     ldr s0,[x7],4                       // s0 = a.X
            ldr s1,[x8],4                       // s1 = a.Y
            ldr s2,[x9],4                       // s2 = a.Z

            ldr s3,[x10],4                      // s3 = a.X
            ldr s4,[x11],4                      // s4 = a.Y
            ldr s5,[x12],4                      // s5 = a.Z

            VecCp                               // calc cross product

            str s19,[x13],4                     // save c.X
            str s20,[x14],4                     // save c.Y
            str s21,[x15],4                     // save c.Z

            subs x3,x3,1                        // n -= 1
            b.ne Loop2B
DoneB:      ret
