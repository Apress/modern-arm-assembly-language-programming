//------------------------------------------------
//               Ch16_01_BM.cpp
//------------------------------------------------

#include <iostream>
#include "Ch16_01.h"
#include "AlignedMem.h"
#include "BmThreadTimer.h"
#include "OS.h"

using namespace std;

void Convolve_BM(void)
{
    cout << "\nRunning benchmark function Convolve_BM - please wait\n";

    const int n1 = 2000000;
    const float kernel[] { 0.0625f, 0.25f, 0.375f, 0.25f, 0.0625f };
    const int ks = sizeof(kernel) / sizeof(float);
    const int ks2 = ks / 2;
    const int n2 = n1 + ks2 * 2;
    const unsigned int alignment = 16;

    // Create signal array
    AlignedArray<float> x1_aa(n1, alignment);
    AlignedArray<float> x2_aa(n2, alignment);
    float* x1 = x1_aa.Data();
    float* x2 = x2_aa.Data();

    CreateSignal(x1, n1, ks, g_RngSeedVal);
    PadSignal(x2, n2, x1, n1, ks2);

    AlignedArray<float> y1_aa(n1, alignment);
    AlignedArray<float> y2_aa(n1, alignment);
    AlignedArray<float> y3_aa(n1, alignment);
    AlignedArray<float> y4_aa(n1, alignment);

    float* y1 = y1_aa.Data();
    float* y2 = y2_aa.Data();
    float* y3 = y3_aa.Data();
    float* y4 = y4_aa.Data();

    const size_t num_it = 500;
    const size_t num_alg = 4;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        ConvolveKsN(y1, x2, n1, kernel, ks);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        ConvolveKsN_(y2, x2, n1, kernel, ks);
        bmtt.Stop(i, 1);

        bmtt.Start(i, 2);
        ConvolveKs5(y3, x2, n1, kernel, ks);
        bmtt.Stop(i, 2);

        bmtt.Start(i, 3);
        ConvolveKs5_(y4, x2, n1, kernel, ks);
        bmtt.Stop(i, 3);
    }

    string fn = bmtt.BuildCsvFilenameString("Ch16_01_Convolve_BM");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    cout << "Benchmark times save to file " << fn << '\n';
}
