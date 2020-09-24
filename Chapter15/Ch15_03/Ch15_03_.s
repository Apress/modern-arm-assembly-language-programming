//-------------------------------------------------
//               Ch15_03_.s
//-------------------------------------------------

// The order of values in the following jump table must match the enum
// that's defined in Ch15_03.cpp.
            .text
            .balign 8
CvtTab:     .quad F32_I32, I32_F32
            .quad F64_I64, I64_F64
            .quad F32_U32, U32_F32
            .quad F64_U64, U64_F64
            .quad F32_F64, F64_F32

            .equ NumCvtTab,(. - CvtTab) / 8    // Number of entries in CvtTab

// extern "C" bool PackedConvert_(Vec128& x, const Vec128& a, CvtOp cvt_op, const Vec128* b);

            .global PackedConvert_
PackedConvert_:
            cmp x2,NumCvtTab
            b.hs InvalidArg

            adr x4,CvtTab                       // x4 = points to CvtTab
            add x4,x4,x2,lsl 3                  // x4 = points to table entry
            ldr x4,[x4]                         // x4 = target jump address

            mov x2,x0                           // x2 = ptr to x
            mov w0,1                            // valid cvt_op return code
            br x4                               // jump to target

// ----- Signed conversions -----

// Convert packed F32 <--- I32
F32_I32:    ld1 {v0.4s},[x1]
            scvtf v1.4s,v0.4s                   // signed integer to SPFP
            st1 {v1.4s},[x2]
            ret

// Convert packed I32 <--- F32
I32_F32:    ld1 {v0.4s},[x1]
            fcvtns v1.4s,v0.4s                  // SPFP to signed integer
            st1 {v1.4s},[x2]
            ret

// Convert packed F64 <--- I64
F64_I64:    ld1 {v0.2d},[x1]
            scvtf v1.2d,v0.2d                   // signed integer to DPFP
            st1 {v1.2d},[x2]
            ret

// Convert packed I64 <--- F64
I64_F64:    ld1 {v0.2d},[x1]
            fcvtns v1.2d,v0.2d                  // DPFP to signed integer
            st1 {v1.2d},[x2]
            ret

// ----- Unsigned conversions -----

// Convert packed F32 <--- U32
F32_U32:    ld1 {v0.4s},[x1]
            ucvtf v1.4s,v0.4s                   // unsigned integer to SPFP
            st1 {v1.4s},[x2]
            ret

// Convert packed U32 <--- F32
U32_F32:    ld1 {v0.4s},[x1]
            fcvtnu v1.4s,v0.4s                  // SPFP to unsigned integer
            st1 {v1.4s},[x2]
            ret

// Convert packed F64 <--- U64
F64_U64:    ld1 {v0.2d},[x1]
            ucvtf v1.2d,v0.2d                   // unsigned integer to DPFP
            st1 {v1.2d},[x2]
            ret

// Convert packed U64 <--- F64
U64_F64:    ld1 {v0.2d},[x1]
            fcvtnu v1.2d,v0.2d                  // DPFP to unsigned integer
            st1 {v1.2d},[x2]
            ret

// ----- FP conversions -----

// Convert packed F32 <--- F64
F32_F64:    ld1 {v0.2d},[x1]
            ld1 {v2.2d},[x3]
            fcvtn v1.2s,v0.2d                   // low-order F64 values
            fcvtn2 v1.4s,v2.2d                  // high-order F64 values
            st1 {v1.4s},[x2]
            ret

// Convert packed F64 <--- F32
F64_F32:    ld1 {v0.4s},[x1]
            fcvtl v1.2d,v0.2s                   // low-order F32 values
            fcvtl2 v2.2d,v0.4s                  // high-order F32 values
            st1 {v1.2d,v2.2d},[x2]
            ret

InvalidArg: mov w0,0                            // invalid cvt_op return code
            ret

