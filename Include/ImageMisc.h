//-------------------------------------------------
//               ImageMisc.h
//-------------------------------------------------

#pragma once

struct RGB32
{
    // Do not change order of elements below
    uint8_t m_R;
    uint8_t m_G;
    uint8_t m_B;
    uint8_t m_A;
};

enum class PixelType : unsigned int
{
    Undefined,
    Gray8,
    Rgb32
};

enum class Channel : unsigned int
{
    // Do not change order of R, G, B, A
    R, G, B, A,
    None
};
