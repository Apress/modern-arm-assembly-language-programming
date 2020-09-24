//------------------------------------------------
//               Ch15_05.h
//------------------------------------------------

#pragma once
#include <cstdint>
#include "ImageMatrix.h"

// Ch15_05.cpp
extern float g_Coef[];
extern bool ConvertRgbToGsCpp(uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float* coef);

// Ch15_05_.s
extern "C" bool ConvertRgbToGs_(uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float* coef);

// Ch15_05_BM.cpp
extern void ConvertRgbToGs_BM(void);
