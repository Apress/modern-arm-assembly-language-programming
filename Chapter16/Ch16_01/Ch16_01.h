//------------------------------------------------
//               Ch16_01.h
//------------------------------------------------

#pragma once

// Ch16_01_Misc.cpp
extern void CreateSignal(float* x, int n, int kernel_size, unsigned int seed);
extern void PadSignal(float* x2, int n2, const float* x1, int n1, int ks2);

// Ch16_01.cpp
extern unsigned int g_RngSeedVal;
extern bool ConvolveKsN(float* y, const float* x, int num_pts, const float* kernel, int kernel_size);
extern bool ConvolveKs5(float* y, const float* x, int num_pts, const float* kernel, int kernel_size);

// Ch16_01_.s
extern "C" bool ConvolveKsN_(float* y, const float* x, int num_pts, const float* kernel, int kernel_size);
extern "C" bool ConvolveKs5_(float* y, const float* x, int num_pts, const float* kernel, int kernel_size);

// Ch16_01_BM.cpp
extern void Convolve_BM(void);
