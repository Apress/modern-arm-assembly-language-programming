//------------------------------------------------
//               Ch08_04.h
//------------------------------------------------

#pragma once
#include <cstdint>

// Ch08_04.cpp
extern void Init(uint8_t* x, uint32_t n, unsigned int seed);
extern bool CalcMinMaxU8(uint8_t* x_min, uint8_t* x_max, const uint8_t* x, uint32_t n);

// Ch08_04_BM.cpp
extern void MinMaxU8_BM(void);

// Ch08_04_.s
extern "C" bool CalcMinMaxU8_(uint8_t* x_min, uint8_t* x_max, const uint8_t* x, uint32_t n);

// Common constants
const uint32_t c_NumElements = 16 * 1024 * 1024 + 7;
const unsigned int c_RngSeedVal = 23;
