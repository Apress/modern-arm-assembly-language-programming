//------------------------------------------------
//               Ch14_06_BM.cpp
//------------------------------------------------

#include <iostream>
#include "Ch14_06.h"
#include "AlignedMem.h"
#include "BmThreadTimer.h"
#include "ImageMatrix.h"
#include "OS.h"

using namespace std;

void CalcImageStats_BM(void)
{
    cout << "\nRunning benchmark function CalcImageStats_BM - please wait\n";

    const char* image_fn = "../../Data/ImageB.png";

    ImageMatrix im(image_fn, PixelType::Gray8, Channel::G);
    uint64_t num_pixels = im.GetNumPixels();
    uint8_t* pb = im.GetPixelBuffer<uint8_t>();

    ImageStats is1;
    is1.m_PixelBuffer = pb;
    is1.m_NumPixels = num_pixels;

    ImageStats is2;
    is2.m_PixelBuffer = pb;
    is2.m_NumPixels = num_pixels;

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        CalcImageStatsCpp(is1);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        CalcImageStats_(is2);
        bmtt.Stop(i, 1);
    }

    string fn = bmtt.BuildCsvFilenameString("Ch14_06_CalcImageStats_BM");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    cout << "Benchmark times save to file " << fn << '\n';
}
