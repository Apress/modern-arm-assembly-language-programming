//------------------------------------------------
//               Ch15_04.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include "AlignedMem.h"

using namespace std;

extern "C" bool CalcCorrCoef_(float* rho, float sums[5], const float* x, const float* y, size_t n, float epsilon);

const size_t c_Alignment = 16;

void Init(float* x, float* y, size_t n, unsigned int seed)
{
    uniform_real_distribution<float> dist1 {0.0, 50.0};
    normal_distribution<float> dist2 {25.0, 7.0};
    mt19937 rng {seed};

    for (size_t i = 0; i < n; i++)
    {
        x[i] = round(dist1(rng));
        y[i] = x[i] + round(dist2(rng));
//      cout << setw(10) << x[i] << ", " << setw(10) << y[i] << endl;
    }
}

bool CalcCorrCoef(float* rho, float sums[5], const float* x, const float* y, size_t n, float epsilon)
{
    // Make sure n is valid
    if (n == 0)
        return false;

    // Make sure x and y are properly aligned
    if (!AlignedMem::IsAligned(x, c_Alignment))
        return false;
    if (!AlignedMem::IsAligned(y, c_Alignment))
        return false;

    // Calculate and save sum variables
    float sum_x = 0, sum_y = 0, sum_xx = 0, sum_yy = 0, sum_xy = 0;

    for (size_t i = 0; i < n; i++)
    {
        sum_x += x[i];
        sum_y += y[i];
        sum_xx += x[i] * x[i];
        sum_yy += y[i] * y[i];
        sum_xy += x[i] * y[i];
    }

    sums[0] = sum_x;
    sums[1] = sum_y;
    sums[2] = sum_xx;
    sums[3] = sum_yy;
    sums[4] = sum_xy;

    // Calculate rho
    float rho_num = n * sum_xy - sum_x * sum_y;
    float rho_den = sqrt(n * sum_xx - sum_x * sum_x) * sqrt(n * sum_yy - sum_y * sum_y);

    if (rho_den >= epsilon)
    {
        *rho = rho_num / rho_den;
        return true;
    }
    else
    {
        *rho = 0;
        return false;
    }
}

int main()
{
    const char nl = '\n';
    const size_t n = 103;
    AlignedArray<float> x_aa(n, c_Alignment);
    AlignedArray<float> y_aa(n, c_Alignment);
    float sums1[5], sums2[5];
    float rho1, rho2;
    float epsilon = 1.0e-9;
    float* x = x_aa.Data();
    float* y = y_aa.Data();

    Init(x, y, n, 71);

    bool rc1 = CalcCorrCoef(&rho1, sums1, x, y, n, epsilon);
    bool rc2 = CalcCorrCoef_(&rho2, sums2, x, y, n, epsilon);

    cout << "Results for CalcCorrCoef\n\n";

    if (!rc1 || !rc2)
    {
        cout << "Invalid return code ";
        cout << "rc1 = " << boolalpha << rc1 << ", ";
        cout << "rc2 = " << boolalpha << rc2 << nl;
        return 1;
    }

    int w = 14;
    string sep(w * 3, '-');

    cout << fixed << setprecision(6);
    cout << "Value    " << setw(w) << "C++" << " " << setw(w) << "A64 SIMD" << nl;
    cout << sep << nl;

    cout << setprecision(2);
    cout << "sum_x:   " << setw(w) << sums1[0] << " " << setw(w) << sums2[0] << nl;
    cout << "sum_y:   " << setw(w) << sums1[1] << " " << setw(w) << sums2[1] << nl;
    cout << "sum_xx:  " << setw(w) << sums1[2] << " " << setw(w) << sums2[2] << nl;
    cout << "sum_yy:  " << setw(w) << sums1[3] << " " << setw(w) << sums2[3] << nl;
    cout << "sum_xy:  " << setw(w) << sums1[4] << " " << setw(w) << sums2[4] << nl;
    cout << "rho:     " << setw(w) << rho1 << " " << setw(w) << rho2 << nl;
    return 0;
}
