//------------------------------------------------
//               Ch08_05_BM.cpp
//------------------------------------------------

#include <iostream>
#include "Ch08_05.h"
#include "AlignedMem.h"
#include "BmThreadTimer.h"
#include "OS.h"

using namespace std;

void MeanU8_BM(void)
{
    cout << "\nRunning benchmark function MeanU8_BM - please wait\n";

    uint32_t n = c_NumElements;
    AlignedArray<uint8_t> x_aa(n, 16);
    uint8_t* x = x_aa.Data();

    Init(x, n, c_RngSeedVal);

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        uint32_t sum0, sum1;
        double mean0, mean1;

        bmtt.Start(i, 0);
        CalcMeanU8(&sum0, &mean0, x, n);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        CalcMeanU8_(&sum1, &mean1, x, n);
        bmtt.Stop(i, 1);
    }

    string fn = bmtt.BuildCsvFilenameString("Ch08_05_MeanU8_BM");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    cout << "Benchmark times save to file " << fn << '\n';
}
