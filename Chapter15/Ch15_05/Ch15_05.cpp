//------------------------------------------------
//               Ch15_05.cpp
//------------------------------------------------

#include <iostream>
#include <stdexcept>
#include "Ch15_05.h"
#include "AlignedMem.h"
#include "ImageMatrix.h"

using namespace std;

// Image size limits
size_t g_NumPixelsMin = 16;
size_t g_NumPixelsMax = 256 * 1024 * 1024;

// RGB to grayscale conversion coefficients
float g_Coef[] {0.2126f, 0.7152f, 0.0722f};

bool CompareGsImages(const uint8_t* pb_gs1,const uint8_t* pb_gs2, size_t num_pixels)
{
    for (size_t i = 0; i < num_pixels; i++)
    {
        if (abs((int)pb_gs1[i] - (int)pb_gs2[i]) > 1)
            return false;
    }

    return true;
}

bool ConvertRgbToGsCpp(uint8_t* pb_gs, const RGB32* pb_rgb, size_t num_pixels, const float* coef)
{
    if (num_pixels < g_NumPixelsMin || num_pixels > g_NumPixelsMax)
        return false;

    if (num_pixels % 16 != 0)
        return false;

    if (!AlignedMem::IsAligned(pb_gs, 16))
        return false;
    if (!AlignedMem::IsAligned(pb_rgb, 16))
        return false;

    for (size_t i = 0; i < num_pixels; i++)
    {
        uint8_t r = pb_rgb[i].m_R;
        uint8_t g = pb_rgb[i].m_G;
        uint8_t b = pb_rgb[i].m_B;

        float gs_temp = r * coef[0] + g * coef[1] + b * coef[2] + 0.5f;

        if (gs_temp < 0.0f)
            gs_temp = 0.0f;
        else if (gs_temp > 255.0f)
            gs_temp = 255.0f;

        pb_gs[i] = (uint8_t)gs_temp;
    }

    return true;
}

void ConvertRgbToGs(void)
{
    const char nl = '\n';
    const char* fn_rgb = "../../Data/ImageC.png";
    const char* fn_gs1 = "Ch15_05_ConvertRgbToGs_ImageC_GS1.png";
    const char* fn_gs2 = "Ch15_05_ConvertRgbToGs_ImageC_GS2.png";

    ImageMatrix im_rgb(fn_rgb, PixelType::Rgb32);
    int im_h = im_rgb.GetHeight();
    int im_w = im_rgb.GetWidth();
    size_t num_pixels = im_h * im_w;
    ImageMatrix im_gs1(im_h, im_w, PixelType::Gray8);
    ImageMatrix im_gs2(im_h, im_w, PixelType::Gray8);
    RGB32* pb_rgb = im_rgb.GetPixelBuffer<RGB32>();
    uint8_t* pb_gs1 = im_gs1.GetPixelBuffer<uint8_t>();
    uint8_t* pb_gs2 = im_gs2.GetPixelBuffer<uint8_t>();

    cout << "Results for ConvertRgbToGs\n";
    cout << "Converting RGB image " << fn_rgb << nl;
    cout << "  im_h = " << im_h << " pixels\n";
    cout << "  im_w = " << im_w << " pixels\n";

    // Exercise conversion functions
    bool rc1 = ConvertRgbToGsCpp(pb_gs1, pb_rgb, num_pixels, g_Coef);
    bool rc2 = ConvertRgbToGs_(pb_gs2, pb_rgb, num_pixels, g_Coef);

    if (rc1 && rc2)
    {
        cout << "Saving grayscale image #1 - " << fn_gs1 << nl;
        im_gs1.SaveToPngFile(fn_gs1);

        cout << "Saving grayscale image #2 - " << fn_gs2 << nl;
        im_gs2.SaveToPngFile(fn_gs2);

        if (CompareGsImages(pb_gs1, pb_gs2, num_pixels))
            cout << "Grayscale image compare OK\n";
        else
            cout << "Grayscale image compare failed\n";
    }
    else
        cout << "Invalid return code\n";
}

int main()
{
    try
    {
        ConvertRgbToGs();
        ConvertRgbToGs_BM();
    }

    catch (exception& ex)
    {
        cout << "exception has occurred - " << ex.what() << '\n';
    }

    catch (...)
    {
        cout << "Unexpected exception has occurred\n";
    }

    return 0;
}
