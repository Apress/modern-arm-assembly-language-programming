//------------------------------------------------
//               Ch15_06_BM.cpp
//------------------------------------------------

#include <iostream>
#include "Ch15_06.h"
#include "MatrixF32.h"
#include "MatrixF64.h"

#include "BmThreadTimer.h"
#include "OS.h"

using namespace std;

void Mat4x4MulF32_BM(void)
{
    cout << "\nRunning benchmark function Mat4x4MulF32_BM - please wait\n";

    const size_t num_rows = 4;
    const size_t num_cols = 4;
    MatrixF32 m_src1(num_rows, num_cols);
    MatrixF32 m_src2(num_rows, num_cols);
    MatrixF32 m_des1(num_rows, num_cols);
    MatrixF32 m_des2(num_rows, num_cols);

    const float m_src1_r0[] = { 10, 11, 12, 13 };
    const float m_src1_r1[] = { 14, 15, 16, 17 };
    const float m_src1_r2[] = { 18, 19, 20, 21 };
    const float m_src1_r3[] = { 22, 23, 24, 25 };
    const float m_src2_r0[] = { 0, 1, 2, 3 };
    const float m_src2_r1[] = { 4, 5, 6, 7 };
    const float m_src2_r2[] = { 8, 9, 10, 11 };
    const float m_src2_r3[] = { 12, 13, 14, 15 };

    m_src1.SetRow(0, m_src1_r0);
    m_src1.SetRow(1, m_src1_r1);
    m_src1.SetRow(2, m_src1_r2);
    m_src1.SetRow(3, m_src1_r3);
    m_src2.SetRow(0, m_src2_r0);
    m_src2.SetRow(1, m_src2_r1);
    m_src2.SetRow(2, m_src2_r2);
    m_src2.SetRow(3, m_src2_r3);

    const size_t num_it = 500;
    const size_t num_alg = 2;
    const size_t num_ops = 250000;

    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        for (size_t j = 0; j < num_ops; j++)
            MatrixF32::Mul4x4(m_des1, m_src1, m_src2);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        for (size_t j = 0; j < num_ops; j++)
            Mat4x4MulF32_(m_des2.Data(), m_src1.Data(), m_src2.Data());
        bmtt.Stop(i, 1);
    }

    string fn = bmtt.BuildCsvFilenameString("Ch15_06_Mat4x4MulF32_BM");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    cout << "Benchmark times save to file " << fn << '\n';
}

void Mat4x4MulF64_BM(void)
{
    cout << "\nRunning benchmark function Mat4x4MulF64_BM - please wait\n";

    const size_t num_rows = 4;
    const size_t num_cols = 4;
    MatrixF64 m_src1(num_rows, num_cols);
    MatrixF64 m_src2(num_rows, num_cols);
    MatrixF64 m_des1(num_rows, num_cols);
    MatrixF64 m_des2(num_rows, num_cols);

    const double m_src1_r0[] = { 10, 11, 12, 13 };
    const double m_src1_r1[] = { 14, 15, 16, 17 };
    const double m_src1_r2[] = { 18, 19, 20, 21 };
    const double m_src1_r3[] = { 22, 23, 24, 25 };
    const double m_src2_r0[] = { 0, 1, 2, 3 };
    const double m_src2_r1[] = { 4, 5, 6, 7 };
    const double m_src2_r2[] = { 8, 9, 10, 11 };
    const double m_src2_r3[] = { 12, 13, 14, 15 };

    m_src1.SetRow(0, m_src1_r0);
    m_src1.SetRow(1, m_src1_r1);
    m_src1.SetRow(2, m_src1_r2);
    m_src1.SetRow(3, m_src1_r3);
    m_src2.SetRow(0, m_src2_r0);
    m_src2.SetRow(1, m_src2_r1);
    m_src2.SetRow(2, m_src2_r2);
    m_src2.SetRow(3, m_src2_r3);

    const size_t num_it = 500;
    const size_t num_alg = 2;
    const size_t num_ops = 250000;

    BmThreadTimer bmtt(num_it, num_alg);

    for (size_t i = 0; i < num_it; i++)
    {
        bmtt.Start(i, 0);
        for (size_t j = 0; j < num_ops; j++)
            MatrixF64::Mul4x4(m_des1, m_src1, m_src2);
        bmtt.Stop(i, 0);

        bmtt.Start(i, 1);
        for (size_t j = 0; j < num_ops; j++)
            Mat4x4MulF64_(m_des2.Data(), m_src1.Data(), m_src2.Data());
        bmtt.Stop(i, 1);
    }

    string fn = bmtt.BuildCsvFilenameString("Ch15_06_Mat4x4MulF64_BM");
    bmtt.SaveElapsedTimes(fn, BmThreadTimer::EtUnit::MicroSec, 2);
    cout << "Benchmark times save to file " << fn << '\n';
}

