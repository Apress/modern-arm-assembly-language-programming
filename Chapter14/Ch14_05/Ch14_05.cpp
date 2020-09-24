//------------------------------------------------
//               Ch14_05.cpp
//------------------------------------------------

#include <iostream>
#include <random>
#include <memory.h>
#include "Ch14_05.h"
#include "AlignedMem.h"

using namespace std;

void Init(uint8_t* x, uint64_t n, unsigned int seed)
{
    uniform_int_distribution<> ui_dist {0, 255};
    default_random_engine rng {seed};

    for (size_t i = 0; i < n; i++)
        x[i] = (uint8_t)ui_dist(rng);
}

bool ClipPixelsCpp(ClipData* cd)
{
    uint8_t* src = cd->m_Src;
    uint8_t* des = cd->m_Des;
    uint64_t num_pixels = cd->m_NumPixels;

    if (num_pixels == 0 || (num_pixels % 64) != 0)
        return false;

    if (!AlignedMem::IsAligned(src, 16))
        return false;
    if (!AlignedMem::IsAligned(des, 16))
        return false;

    uint64_t num_clipped_pixels = 0;
    uint8_t thresh_lo = cd->m_ThreshLo;
    uint8_t thresh_hi = cd->m_ThreshHi;

    for (uint64_t i = 0; i < num_pixels; i++)
    {
        uint8_t pixel = src[i];

        if (pixel < thresh_lo)
        {
            des[i] = thresh_lo;
            num_clipped_pixels++;
        }
        else if (pixel > thresh_hi)
        {
            des[i] = thresh_hi;
            num_clipped_pixels++;
        }
        else
            des[i] = src[i];
    }

    cd->m_NumClippedPixels = num_clipped_pixels;
    return true;
}

void ClipPixels(void)
{
    const char nl = '\n';

    AlignedArray<uint8_t> src(c_NumPixels, 16);
    AlignedArray<uint8_t> des1(c_NumPixels, 16);
    AlignedArray<uint8_t> des2(c_NumPixels, 16);
    AlignedArray<uint8_t> des3(c_NumPixels, 16);

    Init(src.Data(), c_NumPixels, c_Seed);

    ClipData cd1;
    cd1.m_Src = src.Data();
    cd1.m_Des = des1.Data();
    cd1.m_NumPixels = c_NumPixels;
    cd1.m_NumClippedPixels = c_NumPixels + 1;
    cd1.m_ThreshLo = c_ThreshLo;
    cd1.m_ThreshHi = c_ThreshHi;

    ClipData cd2;
    cd2.m_Src = src.Data();
    cd2.m_Des = des2.Data();
    cd2.m_NumPixels = c_NumPixels;
    cd2.m_NumClippedPixels = c_NumPixels + 1;
    cd2.m_ThreshLo = c_ThreshLo;
    cd2.m_ThreshHi = c_ThreshHi;

    ClipData cd3;
    cd3.m_Src = src.Data();
    cd3.m_Des = des3.Data();
    cd3.m_NumPixels = c_NumPixels;
    cd3.m_NumClippedPixels = c_NumPixels + 1;
    cd3.m_ThreshLo = c_ThreshLo;
    cd3.m_ThreshHi = c_ThreshHi;

    bool rc1 = ClipPixelsCpp(&cd1);
    bool rc2 = ClipPixelsA_(&cd2);
    bool rc3 = ClipPixelsB_(&cd3);

    cout << "\nResults for ClipPixels\n";
    cout << "  rc1:                     " << boolalpha << rc1 << nl;
    cout << "  rc2:                     " << boolalpha << rc2 << nl;
    cout << "  rc3:                     " << boolalpha << rc3 << nl;
    cout << "  cd1.m_NumPixels1:        " << cd1.m_NumPixels << nl;    
    cout << "  cd2.m_NumPixels2:        " << cd2.m_NumPixels << nl;
    cout << "  cd3.m_NumPixels3:        " << cd3.m_NumPixels << nl;
    cout << "  cd1.m_NumClippedPixels1: " << cd1.m_NumClippedPixels << nl;
    cout << "  cd2.m_NumClippedPixels2: " << cd2.m_NumClippedPixels << nl;
    cout << "  cd3.m_NumClippedPixels3: " << cd3.m_NumClippedPixels << nl;

    if (cd1.m_NumClippedPixels != cd2.m_NumClippedPixels)
        cout << "  NumClippedPixels compare error\n";
    if (cd1.m_NumClippedPixels != cd2.m_NumClippedPixels)
        cout << "  NumClippedPixels compare error\n";

    if (memcmp(des1.Data(), des2.Data(), c_NumPixels) != 0)
        cout << "  Pixel buffer memory compare error\n";
    if (memcmp(des1.Data(), des3.Data(), c_NumPixels) != 0)
        cout << "  Pixel buffer memory compare error\n";
}

int main(void)
{
//    PrintClipDataStructOffsets();
    ClipPixels();
    ClipPixels_BM();
    return 0;
}
