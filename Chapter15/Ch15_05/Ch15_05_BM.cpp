//------------------------------------------------
//               Ch15_05_BM.cpp
//------------------------------------------------

#include <iostream>
#include "Ch15_05.h"
#include "BmThreadTimer.h"
#include "OS.h"

using namespace std;

void ConvertRgbToGs_BM(void)
{
    cout << "\nRunning benchmark function ConvertRgbToGs_BM - please wait\n";

    const char* fn_rgb = "../../Data/ImageC.png";

    ImageMatrix im_rgb(fn_rgb, PixelType::Rgb32);
    int im_h = im_rgb.GetHeight();
    int im_w = im_rgb.GetWidth();
    size_t num_pixels = im_h * im_w;
    ImageMatrix im_gs1(im_h, im_w, PixelType::Gray8);
    ImageMatrix im_gs2(im_h, im_w, PixelType::Gray8);
    RGB32* pb_rgb = im_rgb.GetPixelBuffer<RGB32>();
    uint8_t* pb_gs1 = im_gs1.GetPixelBuffer<uint8_t>();
    uint8_t* pb_gs2 = im_gs2.GetPixelBuffer<uint8_t>();

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        ConvertRgbToGsCpp(pb_gs1, pb_rgb, num_pixels, g_Coef);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        ConvertRgbToGs_(pb_gs2, pb_rgb, num_pixels, g_Coef);
        bmtt.Stop(i, 1);
    }

    string fn = bmtt.BuildCsvFilenameString("Ch15_05_ConvertRgbToGs_BM");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    cout << "Benchmark times save to file " << fn << '\n';
}
