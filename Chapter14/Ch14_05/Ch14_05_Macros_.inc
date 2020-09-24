//-------------------------------------------------
//               Ch14_05_Macros_.inc
//-------------------------------------------------

// Macro ClipPix
//
// Input:           Vreg - original source pixels
//
// Output:          Vreg - clipped pixels
//
// Data registers:  v16 - packed m_ThreshLo
//                  v17 - packed m_ThreshHi
//                  v18 - packed 0x01
//                  x8 - num_clipped_pixels
//
// Temp registers:  v0, v1, v2, v3, x9

            .macro ClipPix Vreg
            umax v0.16b,\Vreg\().16b,v16.16b    // clip to thresh_lo
            umin v1.16b,v0.16b,v17.16b          // clip to thresh_hi

            cmeq v2.16b,v1.16b,\Vreg\().16b     // compare clipped to original
            not v2.16b,v2.16b
            and v3.16b,v2.16b,v18.16b           // clipped if lane = 0x01
            addv b3,v3.16b                      // b3 = num clipped pixels

            umov w9,v3.b[0]
            add x8,x8,x9                        // num_clipped_pixels += x9
            mov \Vreg\().16b,v1.16b             // save clipped pixels
            .endm
