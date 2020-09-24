//------------------------------------------------
//               Ch16_03.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include "Ch16_03.h"
#include "AlignedMem.h"

using namespace std;

bool VecCompare(const Vec4x1F32* v1, const Vec4x1F32* v2)
{
    static const float eps = 1.0e-12f;

    bool b0 = (fabs(v1->W - v2->W) <= eps);
    bool b1 = (fabs(v1->X - v2->X) <= eps);
    bool b2 = (fabs(v1->Y - v2->Y) <= eps);
    bool b3 = (fabs(v1->Z - v2->Z) <= eps);

    return b0 && b1 && b2 && b3;
}

void InitVecArray(Vec4x1F32* a, size_t n) 
{
    uniform_int_distribution<> ui_dist {1, 500};
    mt19937 rng {187};

    for (size_t i = 0; i < n; i++)
    {
        a[i].W = (float)ui_dist(rng);
        a[i].X = (float)ui_dist(rng);
        a[i].Y = (float)ui_dist(rng);
        a[i].Z = (float)ui_dist(rng);
    }

    if (n >= 4)
    {
        // Known values for test purposes
        a[0].W =  5; a[0].X =  6; a[0].Y =  7; a[0].Z =  8;
        a[1].W = 15; a[1].X = 16; a[1].Y = 17; a[1].Z = 18;
        a[2].W = 25; a[2].X = 26; a[2].Y = 27; a[2].Z = 28;
        a[3].W = 35; a[3].X = 36; a[3].Y = 37; a[3].Z = 38;
    }
}

bool MatVecMulF32Cpp(Vec4x1F32* b, float m[4][4], Vec4x1F32* a, size_t n)
{
    if (n == 0 || (n % 4) != 0)
        return false;

    if (!AlignedMem::IsAligned(a, c_Align) || !AlignedMem::IsAligned(b, c_Align))
        return false;

    for (size_t i = 0; i < n; i++)
    {
        b[i].W =  m[0][0] * a[i].W + m[0][1] * a[i].X;
        b[i].W += m[0][2] * a[i].Y + m[0][3] * a[i].Z;

        b[i].X =  m[1][0] * a[i].W + m[1][1] * a[i].X;
        b[i].X += m[1][2] * a[i].Y + m[1][3] * a[i].Z;

        b[i].Y =  m[2][0] * a[i].W + m[2][1] * a[i].X;
        b[i].Y += m[2][2] * a[i].Y + m[2][3] * a[i].Z;

        b[i].Z =  m[3][0] * a[i].W + m[3][1] * a[i].X;
        b[i].Z += m[3][2] * a[i].Y + m[3][3] * a[i].Z;
    }

    return true;
}

void MatVecMulF32(void)
{
    const char nl = '\n';
    const size_t num_vec = 8;

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

    bool rc1 = MatVecMulF32Cpp(b1, m, a, num_vec);
    bool rc2 = MatVecMulF32_(b2, m, a, num_vec);

    cout << "Results for MatVecMulF32\n";

    if (!rc1 || !rc2)
    {
        cout << "Invalid return code\n";
        cout << "  rc1 = " << boolalpha << rc1 << nl;
        cout << "  rc2 = " << boolalpha << rc2 << nl;
        return;
    }

    const unsigned int w = 8;
    cout << fixed << setprecision(1);

    for (size_t i = 0; i < num_vec; i++)
    {
        cout << "Test case #" << i << '\n';

        cout << "b1: ";
        cout << "  " << setw(w) << b1[i].W << ' ';
        cout << "  " << setw(w) << b1[i].X << ' ';
        cout << "  " << setw(w) << b1[i].Y << ' ';
        cout << "  " << setw(w) << b1[i].Z << nl;

        cout << "b2: ";
        cout << "  " << setw(w) << b2[i].W << ' ';
        cout << "  " << setw(w) << b2[i].X << ' ';
        cout << "  " << setw(w) << b2[i].Y << ' ';
        cout << "  " << setw(w) << b2[i].Z << nl;

        if (!VecCompare(&b1[i], &b2[i]))
        {
            cout << "Error - vector compare failed\n";
            return;
        }
    }
}

int main()
{
    MatVecMulF32();
    MatVecMulF32_BM();
    return 0;
}
