//------------------------------------------------
//               Ch08_05.h
//------------------------------------------------

#pragma once
#include <cstdint>

// Ch08_05.cpp
extern void Init(uint8_t* x, size_t n, unsigned int seed);
extern bool CalcMeanU8(uint32_t* sum_x, double* mean, const uint8_t* x, uint32_t n);

// Ch08_05_BM.cpp
extern void MeanU8_BM(void);

// Ch08_05_.s
extern "C" bool CalcMeanU8_(uint32_t* sum_x, double* mean, const uint8_t* x, uint32_t n);

// Common constants
const uint32_t c_NumElements = 8 * 1024 * 1024 + 19;
const uint32_t c_NumElementsMax = 16 * 1024 * 1024;
const unsigned int c_RngSeedVal = 29;
