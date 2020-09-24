//-------------------------------------------------
//               Ch09_05.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <random>
#include "AlignedMem.h"

using namespace std;

extern "C" bool CalcLeastSquares_(float* m, float* b, const float* x, const float* y, int n, float sums[5]);

float g_LsEpsilon = 1.0e-7;

void Init(float* x, float* y, int n)
{
    normal_distribution<float> dist1 {10.0, 3.0};
    normal_distribution<float> dist2 {0.0, 5.0};
    mt19937 rng {107};

    for (int i = 0; i < n; i++)
    {
        x[i] = dist1(rng);
        y[i] = x[i] + dist2(rng);
    }
}

bool CalcLeastSquares(float* m, float* b, const float* x, const float* y, int n, float sums[5])
{
    if (n < 2)
        return false;

    if (!AlignedMem::IsAligned(x, 16) || !AlignedMem::IsAligned(y, 16))
        return false;

    float sum_x = 0.0, sum_y = 0.0, sum_xx = 0, sum_xy = 0.0;

    for (int i = 0; i < n; i++)
    {
        sum_x += x[i];
        sum_y += y[i];
        sum_xx += x[i] * x[i];
        sum_xy += x[i] * y[i];
    }

    float denom = n * sum_xx - sum_x * sum_x;

    sums[0] = sum_x;
    sums[1] = sum_y;
    sums[2] = sum_xx;
    sums[3] = sum_xy;
    sums[4] = denom;

    if (fabs(denom) >= g_LsEpsilon)
    {
        *m = (n * sum_xy - sum_x * sum_y) / denom;
        *b = (sum_xx * sum_y - sum_x * sum_xy) / denom;
    }
    else
        *m = *b = 0.0;

    return true;
}

int main()
{
    const char nl = '\n';
    const int n = 50;
    AlignedArray<float> x_aa(n, 16);
    AlignedArray<float> y_aa(n, 16);
    float* x = x_aa.Data();
    float* y = y_aa.Data();

    Init(x, y, n);

    float m1 = 0.0, m2 = 0.0;
    float b1 = 0.0, b2 = 0.0;
    float sums1[5], sums2[5];

    bool rc1 = CalcLeastSquares(&m1, &b1, x, y, n, sums1);
    bool rc2 = CalcLeastSquares_(&m2, &b2, x, y, n, sums2);

    size_t w = 14;
    cout << fixed << setprecision(6);

    cout << "\nResults from CalcLeastSquares\n";
    cout << "rc:         " << setw(w) << boolalpha << rc1 << nl;
    cout << "sum_x:      " << setw(w) << sums1[0] << nl;
    cout << "sum_y:      " << setw(w) << sums1[1] << nl;
    cout << "sum_xx:     " << setw(w) << sums1[2] << nl;
    cout << "sum_xy:     " << setw(w) << sums1[3] << nl;
    cout << "denom:      " << setw(w) << sums1[4] << nl;
    cout << "slope:      " << setw(w) << m1 << nl;
    cout << "intercept:  " << setw(w) << b1 << nl;

    cout << "\nResults from CalcLeastSquares_\n";
    cout << "rc:         " << setw(w) << boolalpha << rc2 << nl;
    cout << "sum_x:      " << setw(w) << sums2[0] << nl;
    cout << "sum_y:      " << setw(w) << sums2[1] << nl;
    cout << "sum_xx:     " << setw(w) << sums2[2] << nl;
    cout << "sum_xy:     " << setw(w) << sums2[3] << nl;
    cout << "denom:      " << setw(w) << sums2[4] << nl;
    cout << "slope:      " << setw(w) << m2 << nl;
    cout << "intercept:  " << setw(w) << b2 << nl;

    return 0;
}
