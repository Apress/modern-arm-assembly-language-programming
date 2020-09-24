//-------------------------------------------------
//               Ch04_06_.s
//-------------------------------------------------

// extern "C" int32_t CalcTestStructSum_(const TestStruct* ts);

// Offsets for TestStruct
            .equ S_ValA,0                       // int8_t
            .equ S_ValB,1                       // int8_t
            .equ S_ValC,4                       // int32_t
            .equ S_ValD,8                       // int16_t
            .equ S_ValE,12                      // int32_t
            .equ S_ValF,16                      // uint8_t
            .equ S_ValG,18                      // uint16_t

            .text
            .global CalcTestStructSum_
CalcTestStructSum_:

// Sum the elements of TestStruct
            ldrsb r1,[r0,#S_ValA]               // r1 = ValA (sign-extended)
            ldrsb r2,[r0,#S_ValB]               // r2 = ValB (sign-extended)
            add r1,r1,r2

            ldr r2,[r0,#S_ValC]                 // r2 = ValC
            add r1,r1,r2

            ldrsh r2,[r0,#S_ValD]               // r2 = ValD (sign-extended)
            add r1,r1,r2

            ldr r2,[r0,#S_ValE]                 // r2 = ValE
            add r1,r1,r2
            
            ldrb r2,[r0,#S_ValF]                // r2 = ValF (zero-extended)
            add r1,r1,r2

            ldrh r2,[r0,#S_ValG]                // r2 = ValG (zero-extended)
            add r1,r1,r2

            mov r0,r1
            bx lr
