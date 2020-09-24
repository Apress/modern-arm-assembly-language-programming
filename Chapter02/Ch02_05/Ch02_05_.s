//------------------------------------------------
//               Ch02_05_.s
//------------------------------------------------

// extern "C" int MoveImmA_(void);

            .text
            .global MoveImmA_
MoveImmA_:

// Move immediate examples using unsigned integers
            mov r0,#25                          // r0 = 25
            mov r1,#1000                        // r1 = 1000

            mov r2,#1001                        // movw r2,#1001
            mov r3,#50000                       // movw r3,#50000
            bx lr

// extern "C" int MoveImmB_(void);

            .global MoveImmB_
MoveImmB_:

// Move immediate example - 32-bit unsigned integers
            mov r0,#260096                      // r0 = 260096

// Move immediate example - invalid constant after fixup error

//          mov r1,#260097                      // invalid constant

// Alternative move immediate examples 
            movw r1,#0xf801
            movt r1,#0x0003                     // r1 = 260097

            movw r2,#(260097 & 0xffff)
            movt r2,#(260097 >> 16)             // r2 = 260097

            ldr r3,=#260097                     // r3 = 260097
            bx lr


// extern "C" int MoveImmC_(void);

            .global MoveImmC_
MoveImmC_:

// Move immediate examples - negative numbers
            mov r0,#-57                         // mvn r0,#56
            mov r1,#-6401                       // mvn r1,#6400

// Move immediate example - invalid constant after fixup error

//          mov r1,#-1000                       // invalid constant

// Alternative move immediate examples 
            movw r0,#0xfc18
            movt r0,#0xffff                     // r0 = -1000

            movw r1,#(-1000 & 0xffff)
            movt r1,#(-1000 >> 16)              // r1 = -1000

            ldr r2,=#-1000                      // r2 = -1000

            mvn r3,#1000
            add r3,#1                           // r3 = -1000
            bx lr
