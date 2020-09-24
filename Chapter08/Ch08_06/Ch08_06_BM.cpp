//------------------------------------------------
//               Ch08_06_BM.cpp
//------------------------------------------------

#include <iostream>
#include <string>
#include "Ch08_06.h"
#include "AlignedMem.h"
#include "BmThreadTimer.h"
#include "ImageMatrix.h"
#include "OS.h"

using namespace std;

void Threshold_BM(void)
{
    cout << "\nRunning benchmark function Threshold_BM - please wait\n";

    const char* fn_src = "../../Data/ImageA.png";

    ImageMatrix im_src(fn_src, PixelType::Gray8, Channel::G);
    int im_h = im_src.GetHeight();
    int im_w = im_src.GetWidth();
    ImageMatrix im_mask1(im_h, im_w, PixelType::Gray8);
    ImageMatrix im_mask2(im_h, im_w, PixelType::Gray8);
    ITD itd1, itd2;

    itd1.PbSrc = im_src.GetPixelBuffer<uint8_t>();
    itd1.PbMask = im_mask1.GetPixelBuffer<uint8_t>();
    itd1.NumPixels = im_src.GetNumPixels();
    itd1.Threshold = c_TestThreshold;

    itd2.PbSrc = im_src.GetPixelBuffer<uint8_t>();
    itd2.PbMask = im_mask2.GetPixelBuffer<uint8_t>();
    itd2.NumPixels = im_src.GetNumPixels();
    itd2.Threshold = c_TestThreshold;

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        ThresholdImage(&itd1);
        CalcMeanMaskedPixels(&itd1);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        ThresholdImage_(&itd2);
        CalcMeanMaskedPixels_(&itd2);
        bmtt.Stop(i, 1);
    }

    string fn = bmtt.BuildCsvFilenameString("Ch08_06_Threshold_BM");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    cout << "Benchmark times save to file " << fn << '\n';
}
