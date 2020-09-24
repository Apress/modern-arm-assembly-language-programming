//------------------------------------------------
//               Ch16_04_BM.cpp
//------------------------------------------------

#include <iostream>
#include "Ch16_04.h"
#include "MatrixF32.h"
#include "BmThreadTimer.h"
#include "OS.h"

using namespace std;

void Mat4x4InvF32_BM(const MatrixF32& m)
{
    cout << "\nRunning benchmark function Mat4x4InvF32_BM - please wait\n";

    const float epsilon = c_Epsilon;
    MatrixF32 m_inv0(m.GetNumRows(), m.GetNumCols());
    MatrixF32 m_inv1(m.GetNumRows(), m.GetNumCols());

    const size_t num_it = 500;
    const size_t num_alg = 2;
    const size_t num_ops = 100000;

    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        for (size_t j = 0; j < num_ops; j++)
            Mat4x4InvF32(m_inv0, m, epsilon);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        for (size_t j = 0; j < num_ops; j++)
            Mat4x4InvF32_(m_inv1.Data(), m.Data(), epsilon);
        bmtt.Stop(i, 1);
    }

    string fn = bmtt.BuildCsvFilenameString("Ch16_04_Mat4x4InvF32_BM");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    cout << "Benchmark times save to file " << fn << '\n';
}
