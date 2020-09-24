//------------------------------------------------
//               Ch14_04_BM.cpp
//------------------------------------------------

#include <iostream>
#include "Ch14_04.h"
#include "AlignedMem.h"
#include "BmThreadTimer.h"
#include "OS.h"

using namespace std;

void MinMaxU8_BM(void)
{
    cout << "\nRunning benchmark function MinMaxU8_BM - please wait\n";

    size_t n = c_NumElements;
    AlignedArray<uint8_t> x_aa(n, 16);
    uint8_t* x = x_aa.Data();

    Init(x, n, c_RngSeedVal);

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        uint8_t x_min0 = 0, x_max0 = 0;
        uint8_t x_min1 = 0, x_max1 = 0;

        bmtt.Start(i, 0);
        CalcMinMaxU8(&x_min0, &x_max0, x, n);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        CalcMinMaxU8_(&x_min1, &x_max1, x, n);
        bmtt.Stop(i, 1);
    }

    string fn = bmtt.BuildCsvFilenameString("Ch14_04_MinMaxU8_BM");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    cout << "Benchmark times save to file " << fn << '\n';
}
