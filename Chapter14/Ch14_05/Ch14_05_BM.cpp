//------------------------------------------------
//               Ch14_05_BM.cpp
//------------------------------------------------

#include <iostream>
#include <string>
#include "Ch14_05.h"
#include "AlignedMem.h"
#include "BmThreadTimer.h"
#include "OS.h"

using namespace std;

void ClipPixels_BM(void)
{
    cout << "\nRunning benchmark function ClipPixels_BM - please wait\n";

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

    const size_t num_it = 500;
    const size_t num_alg = 3;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        ClipPixelsCpp(&cd1);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        ClipPixelsA_(&cd2);
        bmtt.Stop(i, 1);

        bmtt.Start(i, 2);
        ClipPixelsB_(&cd3);
        bmtt.Stop(i, 2);
    }

    string fn = bmtt.BuildCsvFilenameString("Ch14_05_ClipPixels_BM");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    cout << "Benchmark times save to file " << fn << '\n';
}
