//-------------------------------------------------
//               GetSetRm_.s
//-------------------------------------------------

// Example functions to get/set AArch64 FP rounding mode
//
// rm = 0       Round to nearest
// rm = 1       Round to plus infinity
// rm = 2       Round to minus infinity
// rm = 3       Round to zero       

// extern "C" Rm GetRm_(void);

            .text
            .global GetRm_
GetRm_:     mrs x0,fpcr                         // x0 = fpcr
            lsr x1,x0,22
            and x0,x1,3                         // rounding mode in bits 1:0
            ret

// extern "C" void SetRm_(uint64_t rm);

            .global SetRm_
SetRm_:     mrs x1,fpcr                         // x1 = fpcr
            bfi x1,x0,22,2                      // insert new rounding mode
            msr fpcr,x1                         // save updated fpcr
            ret
