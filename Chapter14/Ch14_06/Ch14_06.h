//------------------------------------------------
//               Ch14_06.h
//------------------------------------------------

#pragma once
#include <cstdint>

struct ImageStats
{
    uint8_t* m_PixelBuffer;
    uint64_t m_NumPixels;
    uint64_t m_PixelSum;
    uint64_t m_PixelSumSquares;
    double m_PixelMean;
    double m_PixelSd;
};

// Ch14_06.cpp
extern bool CalcImageStatsCpp(ImageStats& im_stats);

// Ch14_06_.asm
extern "C" bool CalcImageStats_(ImageStats& im_stats);

// Ch04_06_BM.cpp
extern void CalcImageStats_BM(void);
