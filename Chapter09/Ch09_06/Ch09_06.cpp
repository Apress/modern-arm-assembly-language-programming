//-------------------------------------------------
//               Ch09_06.cpp
//-------------------------------------------------

#include <iostream>
#include "MatrixF32.h"

using namespace std;

extern "C" void Mat4x4TransposeF32a_(float* m_des, const float* m_src);
extern "C" void Mat4x4TransposeF32b_(float* m_des, const float* m_src);

void Mat4x4TransposeF32(MatrixF32& m_src)
{
    const char nl = '\n';
    const size_t nr = 4;
    const size_t nc = 4;
    MatrixF32 m_des1(nr ,nc);
    MatrixF32 m_des2(nr ,nc);
    MatrixF32 m_des3(nr ,nc);

    MatrixF32::Transpose(m_des1, m_src);
    Mat4x4TransposeF32a_(m_des2.Data(), m_src.Data());
    Mat4x4TransposeF32b_(m_des3.Data(), m_src.Data());

    cout << fixed << setprecision(1);
    m_src.SetOstream(12, "  ");
    m_des1.SetOstream(12, "  ");
    m_des2.SetOstream(12, "  ");
    m_des3.SetOstream(12, "  ");

    cout << "Results for Mat4x4TransposeF32\n";
    cout << "Matrix m_src \n" << m_src << nl;
    cout << "Matrix m_des1\n" << m_des1 << nl;
    cout << "Matrix m_des2\n" << m_des2 << nl;
    cout << "Matrix m_des3\n" << m_des3 << nl;

    if (m_des1 != m_des2 || m_des1 != m_des3)
        cout << "\nMatrix compare failed - Mat4x4TransposeF32\n";
}

int main()
{
    const size_t nr = 4;
    const size_t nc = 4;
    MatrixF32 m_src(nr ,nc);

    const float src_row0[] = {  2,  5,  7,  8 };
    const float src_row1[] = { 11, 14, 16, 19 };
    const float src_row2[] = { 24, 21, 25, 28 };
    const float src_row3[] = { 31, 34, 36, 39 };

    m_src.SetRow(0, src_row0);
    m_src.SetRow(1, src_row1);
    m_src.SetRow(2, src_row2);
    m_src.SetRow(3, src_row3);

    Mat4x4TransposeF32(m_src);
    return 0;
}
