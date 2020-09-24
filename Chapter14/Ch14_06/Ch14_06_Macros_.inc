//-------------------------------------------------
//               Ch14_06_Macros_.inc
//-------------------------------------------------

// Macro UpdateSums
//
// Input:           Vreg - image pixel block
//
// Data registers:  v16 - loop_packed pixel_sum
//                  v17 - loop_packed pixel_sum_squares
//
// Temp registers:  v4, v5, v6, v7
//

            .macro UpdateSums Vreg
// Update loop_pixel_sum
            uxtl v4.8h,\Vreg\().8b                  // zero-extend pixel
            uxtl2 v5.8h,\Vreg\().16b                // values to halfwords
            add v4.8h,v4.8h,v5.8h                   // temp pixel_sum

            uxtl v5.4s,v4.4h                        // zero-extend loop
            uxtl2 v6.4s,v4.8h                       // pixel_sum to words
            add v7.4s,v5.4s,v6.4s                   // update 
            add v16.4s,v16.4s,v7.4s                 // loop_pixel_sum

// Update loop_pixel_sum_squares
            umull v4.8h,\Vreg\().8b,\Vreg\().8b     // temp pixel_sum_squares (lo)
            uxtl v5.4s,v4.4h                        // zero-extend to words
            uxtl2 v6.4s,v4.8h
            add v7.4s,v5.4s,v6.4s                   // update loop
            add v17.4s,v17.4s,v7.4s                 // loop_pixel_sum_squares

            umull2 v4.8h,\Vreg\().16b,\Vreg\().16b  // temp pixel_sum_squares (hi)
            uxtl v5.4s,v4.4h                        // zero-extend to words
            uxtl2 v6.4s,v4.8h
            add v7.4s,v5.4s,v6.4s                   // update
            add v17.4s,v17.4s,v7.4s                 // loop_pixel_sum_squares
            .endm

