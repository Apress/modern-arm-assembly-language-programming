//------------------------------------------------
//               Ch09_07.h
//------------------------------------------------

#pragma once

// Ch09_07_.s
extern "C" void Mat4x4MulF32_(float* m_des, const float* m_src1, const float* m_src2);

// Ch09_07_BM.cpp
extern void Mat4x4MulF32_BM(void);
