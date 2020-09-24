//------------------------------------------------
//               Ch08_06.h
//------------------------------------------------

#pragma once
#include <cstdint>

struct ITD
{
    uint8_t* PbSrc;                 // Source image pixel buffer
    uint8_t* PbMask;                // Mask image pixel buffer
    uint32_t NumPixels;             // Number of source image pixels
    uint32_t NumMaskedPixels;       // Number of masked pixels
    uint32_t SumMaskedPixels;       // Sum of masked pixels
    uint8_t Threshold;              // Image threshold value
    double MeanMaskedPixels;        // Mean of masked pixels
};

// Ch08_06.cpp
extern bool ThresholdImage(ITD* itd);
extern void CalcMeanMaskedPixels(ITD* itd);

// Ch08_06_BM.cpp
extern void Threshold_BM(void);

// Ch08_06_.s
extern "C" bool CheckArgs_(const uint8_t* pb_src, const uint8_t* pb_mask, uint32_t num_pixels);
extern "C" bool ThresholdImage_(ITD* itd);
extern "C" void CalcMeanMaskedPixels_(ITD* itd);

// Ch08_06_Misc.cpp
extern void SaveItdEquates(void);

// Miscellaneous constants
const uint8_t c_TestThreshold = 226;

