//------------------------------------------------
//               Ch15_06.h
//------------------------------------------------

// Ch15_06.cpp
extern void Mat4x4MulF32(float* m_des, const float* m_src1, const float* m_src2);
extern void Mat4x4MulF64(double* m_des, const double* m_src1, const double* m_src2);

// Ch15_06_.s
extern "C" void Mat4x4MulF32_(float* m_des, const float* m_src1, const float* m_src2);
extern "C" void Mat4x4MulF64_(double* m_des, const double* m_src1, const double* m_src2);

// Ch15_06_BM.cpp
extern void Mat4x4MulF32_BM(void);
extern void Mat4x4MulF64_BM(void);

