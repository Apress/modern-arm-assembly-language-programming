//------------------------------------------------
//               Ch14_06.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <stdexcept>
#include <cmath>
#include "Ch14_06.h"
#include "AlignedMem.h"
#include "ImageMatrix.h"

using namespace std;

bool CalcImageStatsCpp(ImageStats& im_stats)
{
    uint64_t num_pixels = im_stats.m_NumPixels;
    const uint8_t* pb = im_stats.m_PixelBuffer;

    // Perform validation checks
    if (!AlignedMem::IsAligned(pb, 16))
        return false;
    if (num_pixels == 0)
        return false;
    if (num_pixels % 64 != 0)
        return false;

    // Calculate intermediate sums
    uint64_t pixel_sum = 0;
    uint64_t pixel_sum_squares = 0;
 
    for (size_t i = 0; i < num_pixels; i++)
    {
        uint32_t pval = pb[i];

        pixel_sum += pval;
        pixel_sum_squares += pval * pval;
    }

    im_stats.m_PixelSum = pixel_sum;
    im_stats.m_PixelSumSquares = pixel_sum_squares;

    // Calculate mean and standard deviation
    im_stats.m_PixelMean = (double)im_stats.m_PixelSum / im_stats.m_NumPixels;

    double temp0 = (double)im_stats.m_NumPixels * im_stats.m_PixelSumSquares;
    double temp1 = (double)im_stats.m_PixelSum * im_stats.m_PixelSum;
    double var_num = temp0 - temp1;
    double var_den = (double)im_stats.m_NumPixels * (im_stats.m_NumPixels - 1);

    im_stats.m_PixelSd = sqrt(var_num / var_den);
    return true;
}

void CalcImageStats()
{
    const char nl = '\n';
    const char* image_fn = "../../Data/ImageB.png";

    ImageMatrix im(image_fn, PixelType::Gray8, Channel::R);
    uint64_t num_pixels = im.GetNumPixels();
    uint8_t* pb = im.GetPixelBuffer<uint8_t>();

    if (num_pixels % 64 != 0)
    {
        cout << "Error: number of pixels in image " << image_fn << nl;
        cout << "must be an integral multiple of 64.\n";
        return;
    }

    ImageStats is1;
    is1.m_PixelBuffer = pb;
    is1.m_NumPixels = num_pixels;

    ImageStats is2;
    is2.m_PixelBuffer = pb;
    is2.m_NumPixels = num_pixels;

    bool rc1 = CalcImageStatsCpp(is1);
    bool rc2 = CalcImageStats_(is2);

    // Display results
    const char* s = " | ";
    const unsigned int w1 = 22;
    const unsigned int w2 = 12;
    cout << fixed << setprecision(5) << left;
    cout << "\nResults for CalcImageStats - image_fn = " << image_fn << nl;

    if (!rc1 || !rc2)
    {
        cout << "Bad return code\n";
        cout << "  rc1 = " << rc1 << nl;
        cout << "  rc2 = " << rc2 << nl;
        return;
    }

    cout << setw(w1) << "m_NumPixels:";
    cout << setw(w2) << is1.m_NumPixels << s;
    cout << setw(w2) << is2.m_NumPixels << nl;

    cout << setw(w1) << "m_PixelSum:";
    cout << setw(w2) << is1.m_PixelSum << s;
    cout << setw(w2) << is2.m_PixelSum << nl;

    cout << setw(w1) << "m_PixelSumOfSquares:";
    cout << setw(w2) << is1.m_PixelSumSquares << s;
    cout << setw(w2) << is2.m_PixelSumSquares << nl;

    cout << setw(w1) << "m_PixelMean:";
    cout << setw(w2) << is1.m_PixelMean << s;
    cout << setw(w2) << is2.m_PixelMean << nl;
    
    cout << setw(w1) << "m_PixelSd:";
    cout << setw(w2) << is1.m_PixelSd << s;
    cout << setw(w2) << is2.m_PixelSd << nl;
}

int main()
{
    try
    {
        CalcImageStats();
        CalcImageStats_BM();
    }

    catch (exception& ex)
    {
        cout << "exception has occurred - " << ex.what() << '\n';
    }

    return 0;
}
