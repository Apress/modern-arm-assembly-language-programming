//-------------------------------------------------
//               Ch08_06.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdint>
#include "Ch08_06.h"
#include "AlignedMem.h"
#include "ImageMatrix.h"

using namespace std;

bool ThresholdImage(ITD* itd)
{
    uint8_t* pb_src = itd->PbSrc;
    uint8_t* pb_mask = itd->PbMask;
    uint8_t threshold = itd->Threshold;
    uint32_t num_pixels = itd->NumPixels;

    // Verify pixel count and buffer alignment
    if (!CheckArgs_(pb_src, pb_mask, num_pixels))
        return false;

    // Threshold the image
    for (uint32_t i = 0; i < num_pixels; i++)
        *pb_mask++ = (*pb_src++ > threshold) ? 0xff : 0x00;

    return true;
}

void CalcMeanMaskedPixels(ITD* itd)
{
    uint8_t* pb_src = itd->PbSrc;
    uint8_t* pb_mask = itd->PbMask;
    uint32_t num_pixels = itd->NumPixels;

    // Calculate mean of masked pixels
    uint32_t sum_masked_pixels = 0;
    uint32_t num_masked_pixels = 0;

    for (uint32_t i = 0; i < num_pixels; i++)
    {
        uint8_t mask_val = *pb_mask++;
        num_masked_pixels += mask_val & 1;
        sum_masked_pixels += (*pb_src++ & mask_val);
    }

    itd->NumMaskedPixels = num_masked_pixels;
    itd->SumMaskedPixels = sum_masked_pixels;
    
    if (num_masked_pixels == 0)
        itd->MeanMaskedPixels = -1.0;
    else
        itd->MeanMaskedPixels = (double)sum_masked_pixels / num_masked_pixels;
}

void Threshold(void)
{
    const char nl = '\n';
    const char* fn_src = "../../Data/ImageA.png";
    const char* fn_mask1 = "Ch08_06_ImageA_Mask1.png";
    const char* fn_mask2 = "Ch08_06_ImageA_Mask2.png";

    ImageMatrix im_src(fn_src, PixelType::Gray8, Channel::G);
    int im_h = im_src.GetHeight();
    int im_w = im_src.GetWidth();

    ITD itd1;
    ImageMatrix im_mask1(im_h, im_w, PixelType::Gray8);
    itd1.PbSrc = im_src.GetPixelBuffer<uint8_t>();
    itd1.PbMask = im_mask1.GetPixelBuffer<uint8_t>();
    itd1.NumPixels = im_src.GetNumPixels();
    itd1.Threshold = c_TestThreshold;

    ITD itd2;
    ImageMatrix im_mask2(im_h, im_w, PixelType::Gray8);
    itd2.PbSrc = im_src.GetPixelBuffer<uint8_t>();
    itd2.PbMask = im_mask2.GetPixelBuffer<uint8_t>();
    itd2.NumPixels = im_src.GetNumPixels();
    itd2.Threshold = c_TestThreshold;

    // Threshold image
    bool rc1 = ThresholdImage(&itd1);
    bool rc2 = ThresholdImage_(&itd2);

    if (!rc1 || !rc2)
    {
        cout << "\nInvalid return code: ";
        cout << "rc1 = " << rc1 << ", rc2 = " << rc2 << nl;
        return;
    }

    im_mask1.SaveToPngFile(fn_mask1);
    im_mask2.SaveToPngFile(fn_mask2);

    // Calculate mean of masked pixels
    CalcMeanMaskedPixels(&itd1);
    CalcMeanMaskedPixels_(&itd2);

    // Print results
    const int w = 12;
    cout << fixed << setprecision(4);

    cout << "\nResults for Threshold\n\n";
    cout << "                            C++         Armv8-32\n";
    cout << "------------------------------------------------\n";
    cout << "SumMaskedPixels:   ";
    cout << setw(w) << itd1.SumMaskedPixels << "  ";
    cout << setw(w) << itd2.SumMaskedPixels << nl;
    cout << "NumMaskedPixels:   ";
    cout << setw(w) << itd1.NumMaskedPixels << "  ";
    cout << setw(w) << itd2.NumMaskedPixels << nl;
    cout << "MeanMaskedPixels:  ";
    cout << setw(w) << itd1.MeanMaskedPixels << "  ";
    cout << setw(w) << itd2.MeanMaskedPixels << nl;
}

int main()
{
    const char nl = '\n';

    try
    {
        SaveItdEquates();
        Threshold();
        Threshold_BM();
    }

    catch (exception const& ex)
    {
        cout << "Unexpected exception has occurred - " << ex.what() << nl;
    }

    return 0;
}
