//------------------------------------------------
//               Ch16_03.h
//------------------------------------------------

#pragma once

// Simple 4x1 vector structure
struct Vec4x1F32
{
    float W, X, Y, Z;
};

// Ch16_03.cpp
extern void InitVecArray(Vec4x1F32* a, size_t n);
extern bool MatVecMulF32Cpp(Vec4x1F32* b, float m[4][4], Vec4x1F32* a, size_t n);

// Ch16_03_.asm
extern "C" bool MatVecMulF32_(Vec4x1F32* b, float m[4][4], Vec4x1F32* a, size_t n);

// Ch16_03_BM.cpp
extern void MatVecMulF32_BM(void);

// Constants
const size_t c_Align = 16;
