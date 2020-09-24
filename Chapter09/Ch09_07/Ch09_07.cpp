//-------------------------------------------------
//               Ch09_07.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include "Ch09_07.h"
#include "MatrixF32.h"

using namespace std;

void Mat4x4MulF32(MatrixF32& m_src1, MatrixF32& m_src2)
{
    const size_t nr = 4;
    const size_t nc = 4;
    MatrixF32 m_des1(nr ,nc);
    MatrixF32 m_des2(nr ,nc);

    MatrixF32::Mul4x4(m_des1, m_src1, m_src2);
    Mat4x4MulF32_(m_des2.Data(), m_src1.Data(), m_src2.Data());

    cout << fixed << setprecision(1);

    m_src1.SetOstream(12, "  ");
    m_src2.SetOstream(12, "  ");
    m_des1.SetOstream(12, "  ");
    m_des2.SetOstream(12, "  ");

    cout << "\nResults for Mat4x4MulF32\n";
    cout << "Matrix m_src1\n" << m_src1 << '\n';
    cout << "Matrix m_src2\n" << m_src2 << '\n';
    cout << "Matrix m_des1\n" << m_des1 << '\n';
    cout << "Matrix m_des2\n" << m_des2 << '\n';

    if (m_des1 != m_des2)
        cout << "\nMatrix compare failed - Mat4x4MulF32\n";
}

int main()
{
    const size_t nr = 4;
    const size_t nc = 4;
    MatrixF32 m_src1(nr ,nc);
    MatrixF32 m_src2(nr ,nc);

    const float src1_row0[] = { 10, 11, 12, 13 };
    const float src1_row1[] = { 20, 21, 22, 23 };
    const float src1_row2[] = { 30, 31, 32, 33 };
    const float src1_row3[] = { 40, 41, 42, 43 };

    const float src2_row0[] = { 100, 101, 102, 103 };
    const float src2_row1[] = { 200, 201, 202, 203 };
    const float src2_row2[] = { 300, 301, 302, 303 };
    const float src2_row3[] = { 400, 401, 402, 403 };

    m_src1.SetRow(0, src1_row0);
    m_src1.SetRow(1, src1_row1);
    m_src1.SetRow(2, src1_row2);
    m_src1.SetRow(3, src1_row3);

    m_src2.SetRow(0, src2_row0);
    m_src2.SetRow(1, src2_row1);
    m_src2.SetRow(2, src2_row2);
    m_src2.SetRow(3, src2_row3);

    Mat4x4MulF32(m_src1, m_src2);
    Mat4x4MulF32_BM();
    return 0;
}
