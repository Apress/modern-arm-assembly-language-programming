//-------------------------------------------------
//               Ch12_02_.s
//-------------------------------------------------

// extern "C" void LocalVars_(int32_t a, int32_t b int32_t c, int32_t d,
//  int64_t e, int64_t f, int64_t g, int64_t h, int32_t* x, int64_t* y);

            .equ ARG_X,48                       // sp offset for x
            .equ ARG_Y,56                       // sp offset for y
            .equ TEMP0,0                        // sp offset for temp0
            .equ TEMP1,4                        // sp offset for temp1
            .equ TEMP2,8                        // sp offset for temp2
            .equ TEMP3,16                       // sp offset for temp3

            .equ LOCAL_VAR_SIZE,32              // size of local var space

            .text
            .global LocalVars_
LocalVars_:

// Prologue
            stp x19,x20,[sp,-16]!               // push x19 and x20
            sub sp,sp,LOCAL_VAR_SIZE            // allocate local var space

// Calculate temp0
            add w8,w0,w1                        // w8 = a + b
            add w8,w8,w2                        // w8 = a + b + c
            str w8,[sp,TEMP0]                   // save temp0

// Calculate temp1
            ldr x19,=g_Val1                     // x19 points to g_Val1
            ldr w19,[x19]                       // w19 = g_Val1
            sub w8,w3,w19                       // w8 = d - g_Val1
            str w8,[sp,TEMP1]                   // save temp1

// Calculate temp2
            add x8,x4,x5                        // x8 = e + f
            add x8,x8,x6                        // x8 = e + f + g
            str x8,[sp,TEMP2]                   // save temp2

// Calculate temp3
            ldr x20,=g_Val2                     // x20 points to g_Val2
            ldr x20,[x20]                       // x20 = g_Val2
            sub x8,x7,x20                       // x8 = h - g_Val2
            str x8,[sp,TEMP3]                   // save temp3

// Calculate x
            ldr w0,[sp,TEMP0]                   // w0 = temp0
            ldr w1,[sp,TEMP1]                   // w1 = temp1
            mul w2,w0,w1                        // w2 = temp0 * temp1
            ldr x3,[sp,ARG_X]                   // x3 = x
            str w2,[x3]                         // save x

// Calculate y
            ldr x0,[sp,TEMP2]                   // x0 = temp2
            ldr x1,[sp,TEMP3]                   // x1 = temp3
            mul x2,x0,x1                        // x2 = temp2 * temp3
            ldr x3,[sp,ARG_Y]                   // x3 = y
            str x2,[x3]                         // save y

// Epilogue
            add sp,sp,LOCAL_VAR_SIZE            // release local storage
            ldp x19,x20,[sp],16                 // pop x19 and x20
            ret
