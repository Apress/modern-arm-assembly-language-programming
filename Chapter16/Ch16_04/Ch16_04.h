//------------------------------------------------
//               Ch16_04.h
//------------------------------------------------

#pragma once

#include "MatrixF32.h"

const float c_Epsilon = 1.0e-5;

// Ch16_04.cpp
extern bool Mat4x4InvF32(MatrixF32& m_inv, const MatrixF32& m, float epsilon);

// Ch16_04_Test.cpp
extern bool TestMat4x4F32(const MatrixF32& m1, const MatrixF32& m2);

// Ch16_04_.s
extern "C" bool Mat4x4InvF32_(float* m_inv, const float* m, float epsilon);

// Ch16_04_Test.s
extern "C" void Mat4x4AddF32_(float* m_des, const float* m_src1, const float* m_src2);
extern "C" void Mat4x4MulF32_(float* m_des, const float* m_src1, const float* m_src2);
extern "C" void Mat4x4MulScalarF32_(float* m_des, const float* m_src1, float sv);
extern "C" float Mat4x4TraceF32_(const float* m_src1);

// Ch16_04_BM.cpp
extern void Mat4x4InvF32_BM(const MatrixF32& m);
