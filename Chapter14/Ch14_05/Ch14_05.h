//------------------------------------------------
//               Ch14_05.h
//------------------------------------------------

#pragma once
#include <cstdint>

struct ClipData
{
    uint8_t* m_Des;                 // destination buffer pointer
    uint8_t* m_Src;                 // source buffer pointer
    uint64_t m_NumPixels;           // number of pixels
    uint64_t m_NumClippedPixels;    // number of clipped pixels
    uint8_t m_ThreshLo;             // low threshold
    uint8_t m_ThreshHi;             // high threshold
};

// Ch14_05.cpp
extern void Init(uint8_t* x, uint64_t n, unsigned int seed);
extern bool ClipPixelsCpp(ClipData* cd);

// Ch14_05a_.s
extern "C" bool ClipPixelsA_(ClipData* cd);

// Ch14_05b_.s
extern "C" bool ClipPixelsB_(ClipData* cd);

// Ch14_05_BM.cpp
extern void ClipPixels_BM(void);

// Ch14_05_Misc.cpp
extern void PrintClipDataStructOffsets(void);

// Algorithm constants
const uint8_t c_ThreshLo = 10;
const uint8_t c_ThreshHi = 245;
const uint64_t c_NumPixels = 8 * 1024 * 1024;
const unsigned int c_Seed = 157;
