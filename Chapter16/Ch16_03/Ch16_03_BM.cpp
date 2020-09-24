//------------------------------------------------
//               Ch16_03_BM.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch16_03.h"
#include "AlignedMem.h"
#include "BmThreadTimer.h"
#include "OS.h"

using namespace std;

void MatVecMulF32_BM(void)
{
    cout << "\nRunning benchmark function MatVecMulF32_BM - please wait\n";

    const size_t num_vec = 1000000;

    alignas(c_Align) float m[4][4]
    {
       10.0, 11.0, 12.0, 13.0,
       20.0, 21.0, 22.0, 23.0,
       30.0, 31.0, 32.0, 33.0,
       40.0, 41.0, 42.0, 43.0
    };

    AlignedArray<Vec4x1F32> a_aa(num_vec, c_Align);
    AlignedArray<Vec4x1F32> b1_aa(num_vec, c_Align);
    AlignedArray<Vec4x1F32> b2_aa(num_vec, c_Align);

    Vec4x1F32* a = a_aa.Data();
    Vec4x1F32* b1 = b1_aa.Data();
    Vec4x1F32* b2 = b2_aa.Data();

    InitVecArray(a, num_vec);

    const size_t num_it = 500;
    const size_t num_alg = 2;
    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        MatVecMulF32Cpp(b1, m, a, num_vec);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        MatVecMulF32_(b2, m, a, num_vec);
        bmtt.Stop(i, 1);
    }

    string fn = bmtt.BuildCsvFilenameString("Ch16_03_MatVecMulF32_BM");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    cout << "Benchmark times save to file " << fn << '\n';
}
