//-------------------------------------------------
//               Ch08_05.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <random>
#include "Ch08_05.h"
#include "AlignedMem.h"

using namespace std;

uint32_t g_NumElementsMax = c_NumElementsMax;

void Init(uint8_t* x, size_t n, unsigned int seed)
{
    uniform_int_distribution<> ui_dist {0, 255};
    mt19937 rng {seed};

    for (size_t i = 0; i < n; i++)
        x[i] = (uint8_t)ui_dist(rng);
}

bool CalcMeanU8(uint32_t* sum_x, double* mean_x, const uint8_t* x, uint32_t n)
{
    if (n == 0 || n > g_NumElementsMax)
        return false;

    if (!AlignedMem::IsAligned(x, 16))
        return false;

    uint32_t sum_x_temp = 0;

    for (uint32_t i = 0; i < n; i++)
        sum_x_temp += x[i];

    *sum_x = sum_x_temp;
    *mean_x = (double)sum_x_temp / n;
    return true;
}

void MeanU8()
{
    const char nl = '\n';
    const uint32_t n = c_NumElements;
    AlignedArray<uint8_t> x_aa(n, 16);
    uint8_t* x = x_aa.Data();

    Init(x, n, c_RngSeedVal);

    bool rc1, rc2;
    uint32_t sum_x1, sum_x2;
    double mean_x1, mean_x2;

    rc1 = CalcMeanU8(&sum_x1, &mean_x1, x, n);
    rc2 = CalcMeanU8_(&sum_x2, &mean_x2, x, n);

    cout << "\nResults for MeanU8\n";
    cout << fixed << setprecision(4);
    cout << "rc1: " << boolalpha << rc1 << "  ";
    cout << "sum_x1:  " << sum_x1 << "  ";
    cout << "mean_x1: " << mean_x1 << nl;;
    cout << "rc2: " << boolalpha << rc2 << "  ";
    cout << "sum_x2:  " << sum_x2 << "  ";
    cout << "mean_x2: " << mean_x2 << nl;
}

int main()
{
    MeanU8();
    MeanU8_BM();
    return 0;
}
