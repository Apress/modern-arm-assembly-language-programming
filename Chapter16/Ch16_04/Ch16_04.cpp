//------------------------------------------------
//               Ch16_04.cpp
//------------------------------------------------

#include <iostream>
#include <cmath>
#include "Ch16_04.h"
#include "MatrixF32.h"

using namespace std;

bool Mat4x4InvF32(MatrixF32& m_inv, const MatrixF32& m, float epsilon)
{
    // The intermediate matrices below are declared static for benchmarking purposes.
    static const size_t nrows = 4;
    static const size_t ncols = 4;
    static MatrixF32 m2(nrows, ncols);
    static MatrixF32 m3(nrows, ncols);
    static MatrixF32 m4(nrows, ncols);
    static MatrixF32 I(nrows, ncols, true);
    static MatrixF32 tempA(nrows, ncols);
    static MatrixF32 tempB(nrows, ncols);
    static MatrixF32 tempC(nrows, ncols);
    static MatrixF32 tempD(nrows, ncols);

    MatrixF32::Mul4x4(m2, m, m);
    MatrixF32::Mul4x4(m3, m2, m);
    MatrixF32::Mul4x4(m4, m3, m);

    float t1 = m.Trace4x4();
    float t2 = m2.Trace4x4();
    float t3 = m3.Trace4x4();
    float t4 = m4.Trace4x4();

    float c1 = -t1;
    float c2 = -1.0 / 2.0 * (c1 * t1 + t2);
    float c3 = -1.0 / 3.0 * (c2 * t1 + c1 * t2 + t3);
    float c4 = -1.0 / 4.0 * (c3 * t1 + c2 * t2 + c1 * t3 + t4);

    // Make sure matrix is not singular
    bool is_singular = (fabs(c4) < epsilon);

    if (!is_singular)
    {
        // Calculate = -1.0 / c4 * (m3 + c1 * m2 + c2 * m + c3 * I)
        MatrixF32::MulScalar(tempA, I, c3);
        MatrixF32::MulScalar(tempB, m, c2);
        MatrixF32::MulScalar(tempC, m2, c1);
        MatrixF32::Add(tempD, tempA, tempB);
        MatrixF32::Add(tempD, tempD, tempC);
        MatrixF32::Add(tempD, tempD, m3);
        MatrixF32::MulScalar(m_inv, tempD, -1.0 / c4);
    }

    return is_singular;
}

void RunMat4x4InvF32(const MatrixF32& m, const char* msg)
{
    const char nl = '\n';
    cout << "---------- " << msg << " ----------- \n";
    cout << "\nTest Matrix\n";
    cout << m << nl;

    const float epsilon = c_Epsilon;
    const size_t nrows = m.GetNumRows();
    const size_t ncols = m.GetNumCols();
    MatrixF32 m_inv_a(nrows, ncols);
    MatrixF32 m_ver_a(nrows, ncols);
    MatrixF32 m_inv_b(nrows, ncols);
    MatrixF32 m_ver_b(nrows, ncols);

    for (int i = 0; i <= 1; i++)
    {
        string fn;
        bool is_singular;
        MatrixF32 m_inv(nrows, ncols);
        MatrixF32 m_ver(nrows, ncols);
 
        if (i == 0)
        {
            fn = "Mat4x4InvF32";
            is_singular = Mat4x4InvF32(m_inv, m, epsilon);

            if (!is_singular)
                MatrixF32::Mul(m_ver, m_inv, m);
        }
        else
        {
            fn = "Mat4x4InvF32_";
            is_singular = Mat4x4InvF32_(m_inv.Data(), m.Data(), epsilon);

            if (!is_singular)
                MatrixF32::Mul(m_ver, m_inv, m);
        }

        if (is_singular)
            cout << fn << " - Test matrix is singular\n";
        else
        {
            cout << fn << " - Inverse Matrix\n";
            cout << m_inv << nl;

            // RoundToI() used for display purposes, can be removed.
            cout << fn << " - Verify Matrix\n";
            m_ver.RoundToI(epsilon);
            cout << m_ver << nl;
        }
    }
}

int main()
{
    // Test Matrix #1 - Non-Singular
    MatrixF32 m1(4, 4);
    const float m1_row0[] = { 2, 7, 3, 4 };
    const float m1_row1[] = { 5, 9, 6, 4.75 };
    const float m1_row2[] = { 6.5, 3, 4, 10 };
    const float m1_row3[] = { 7, 5.25, 8.125, 6 };
    m1.SetRow(0, m1_row0);
    m1.SetRow(1, m1_row1);
    m1.SetRow(2, m1_row2);
    m1.SetRow(3, m1_row3);

    // Test Matrix #2 - Non-Singular
    MatrixF32 m2(4, 4);
    const float m2_row0[] = { 0.5, 12, 17.25, 4 };
    const float m2_row1[] = { 5, 2, 6.75, 8 };
    const float m2_row2[] = { 13.125, 1, 3, 9.75 };
    const float m2_row3[] = { 16, 1.625, 7, 0.25 };
    m2.SetRow(0, m2_row0);
    m2.SetRow(1, m2_row1);
    m2.SetRow(2, m2_row2);
    m2.SetRow(3, m2_row3);

    // Test Matrix #3 - Singular
    MatrixF32 m3(4, 4);
    const float m3_row0[] = { 2, 0, 0, 1 };
    const float m3_row1[] = { 0, 4, 5, 0 };
    const float m3_row2[] = { 0, 0, 0, 7 };
    const float m3_row3[] = { 0, 0, 0, 6 };
    m3.SetRow(0, m3_row0);
    m3.SetRow(1, m3_row1);
    m3.SetRow(2, m3_row2);
    m3.SetRow(3, m3_row3);

    RunMat4x4InvF32(m1, "Test Case #1");
    RunMat4x4InvF32(m2, "Test Case #2");
    RunMat4x4InvF32(m3, "Test Case #3");

    Mat4x4InvF32_BM(m1);
    return 0;
}
