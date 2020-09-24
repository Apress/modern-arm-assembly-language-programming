//-------------------------------------------------
//               Ch15_07.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include "MatrixF32.h"
#include "MatrixF64.h"

using namespace std;

extern "C" float Mat4x4TraceF32_(const float* m_src1);
extern "C" double Mat4x4TraceF64_(const double* m_src1);
extern "C" void Mat4x4TransposeF32_(float* m_des, const float* m_src1);
extern "C" void Mat4x4TransposeF64_(double* m_des, const double* m_src1);

void Mat4x4TestF32(MatrixF32& m_src1)
{
    const char nl = '\n';
    const size_t nr = m_src1.GetNumCols();
    const size_t nc = m_src1.GetNumRows();
    MatrixF32 m_des1(nr, nc);
    MatrixF32 m_des2(nr, nc);

    MatrixF32::Transpose(m_des1, m_src1);
    Mat4x4TransposeF32_(m_des2.Data(), m_src1.Data());

    cout << fixed << setprecision(1);

    m_src1.SetOstream(12, "  ");
    m_des1.SetOstream(12, "  ");
    m_des2.SetOstream(12, "  ");

    cout << "\nResults for Mat4x4TestF32\n";
    cout << "Matrix m_src1\n" << m_src1 << nl;
    cout << "Matrix m_des1 (transpose of m_src1)\n" << m_des1 << nl;
    cout << "Matrix m_des2 (transpose of m_src1)\n" << m_des2 << nl;

    if (m_des1 != m_des2)
        cout << "\nMatrix transpose compare failed\n";

    float m_trace1 = m_src1.Trace();
    float m_trace2 = Mat4x4TraceF32_(m_src1.Data());
    cout << "m_trace1 = " << m_trace1 << nl;
    cout << "m_trace2 = " << m_trace2 << nl;

    if (m_trace1 != m_trace2)
        cout << "\nMatrix trace compare failed\n";
}

void Mat4x4TestF64(MatrixF64& m_src1)
{
    const char nl = '\n';
    const size_t nr = m_src1.GetNumCols();
    const size_t nc = m_src1.GetNumRows();
    MatrixF64 m_des1(nr, nc);
    MatrixF64 m_des2(nr, nc);

    MatrixF64::Transpose(m_des1, m_src1);
    Mat4x4TransposeF64_(m_des2.Data(), m_src1.Data());

    cout << fixed << setprecision(1);

    m_src1.SetOstream(12, "  ");
    m_des1.SetOstream(12, "  ");
    m_des2.SetOstream(12, "  ");

    cout << "\nResults for Mat4x4TestF64\n";
    cout << "Matrix m_src1\n" << m_src1 << nl;
    cout << "Matrix m_des1 (transpose of m_src1)\n" << m_des1 << nl;
    cout << "Matrix m_des2 (transpose of m_src1)\n" << m_des2 << nl;

    if (m_des1 != m_des2)
        cout << "\nMatrix transpose compare failed\n";

    float m_trace1 = m_src1.Trace();
    float m_trace2 = Mat4x4TraceF64_(m_src1.Data());
    cout << "m_trace1 = " << m_trace1 << nl;
    cout << "m_trace2 = " << m_trace2 << nl;

    if (m_trace1 != m_trace2)
        cout << "\nMatrix trace compare failed\n";
}

void Mat4x4TestF32(void)
{
    const size_t nr = 4;
    const size_t nc = 4;
    MatrixF32 m_src1(nr ,nc);

    const float src1_row0[] = { 10, 11, 12, 13 };
    const float src1_row1[] = { 20, 21, 22, 23 };
    const float src1_row2[] = { 30, 31, 32, 33 };
    const float src1_row3[] = { 40, 41, 42, 43 };

    m_src1.SetRow(0, src1_row0);
    m_src1.SetRow(1, src1_row1);
    m_src1.SetRow(2, src1_row2);
    m_src1.SetRow(3, src1_row3);

    Mat4x4TestF32(m_src1);
}

void Mat4x4TestF64(void)
{
    const size_t nr = 4;
    const size_t nc = 4;
    MatrixF64 m_src1(nr ,nc);

    const double src1_row0[] = { 100, 110, 120, 130 };
    const double src1_row1[] = { 200, 210, 220, 230 };
    const double src1_row2[] = { 300, 310, 320, 330 };
    const double src1_row3[] = { 400, 410, 420, 430 };

    m_src1.SetRow(0, src1_row0);
    m_src1.SetRow(1, src1_row1);
    m_src1.SetRow(2, src1_row2);
    m_src1.SetRow(3, src1_row3);

    Mat4x4TestF64(m_src1);
}

int main()
{
    Mat4x4TestF32();
    Mat4x4TestF64();
    return 0;
}
