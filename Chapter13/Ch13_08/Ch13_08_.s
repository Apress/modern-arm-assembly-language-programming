//-------------------------------------------------
//               Ch13_08_.s
//-------------------------------------------------

// extern "C" void CalcBSA_(double bsa[3], double ht, double wt);

            .text
            .global CalcBSA_
CalcBSA_:   stp lr,x19,[sp,-16]!                // push lr, x19
            stp d12,d13,[sp,-16]!               // push d12, d13
            stp d14,d15,[sp,-16]!               // push d14, d15

            mov x19,x0                          // x19 = bsa array ptr
            fmov d12,d0                         // d12 = height
            fmov d13,d1                         // d13 = weight

// Calculate bsa[0] = 0.007184 * pow(ht, 0.725) * pow(wt, 0.425)
            ldr d1,r8_0p725
            bl pow                              // calc pow(ht,0.725)
            fmov d14,d0                         // save result
            fmov d0,d13                         // d0 = weight
            ldr d1,r8_0p425
            bl pow                              // calc pow(wt,0.425)
            ldr d1,r8_0p007184
            fmul d2,d1,d14                      // 0.007184 * pow(ht,0.725)
            fmul d2,d2,d0                       // d2 *=  pow(wt,0.425)
            str d2,[x19]                        // save bsa[0]

// Calculate bsa[1] = 0.0235 * pow(ht, 0.42246) * pow(wt, 0.51456)
            fmov d0,d12                         // d0 = height
            ldr d1,r8_0p42246
            bl pow                              // calc pow(ht,0.42246)
            fmov d14,d0                         // save result
            fmov d0,d13                         // d0 = weight
            ldr d1,r8_0p51456
            bl pow                              // calc pow(wt,0.51456)
            ldr d1,r8_0p0235
            fmul d2,d1,d14                      // 0.0235 * pow(ht,0.42246)
            fmul d2,d2,d0                       // d2 *= pow(wt,0.51456)
            str d2,[x19,8]                      // save bsa[1]

// Calculate bsa[2] = sqrt(ht * wt / 3600.0)
            fmul d0,d12,d13                     // d0 = ht * wt
            ldr d1,r8_3600p0
            fdiv d2,d0,d1                       // d2 = ht * wt / 3600
            fsqrt d2,d2                         // sqrt(ht * wt / 3600)
            str d2,[x19,16]                     // save bsa[2]

// Restore non-volatile registers & return
            ldp d14,d15,[sp],16                 // pop d14, d15
            ldp d12,d13,[sp],16                 // pop d12, d13
            ldp lr,x19,[sp],16                  // pop lr, x19
            ret

// Constants
                .balign 8
r8_0p007184:    .double 0.007184
r8_0p725:       .double 0.725
r8_0p425:       .double 0.425
r8_0p0235:      .double 0.0235
r8_0p42246:     .double 0.42246
r8_0p51456:     .double 0.51456
r8_3600p0:      .double 3600.0

