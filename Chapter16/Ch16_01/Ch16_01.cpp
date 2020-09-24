//------------------------------------------------
//               Ch16_01.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <memory>
#include <fstream>
#include <stdexcept>
#include "Ch16_01.h"
#include "AlignedMem.h"

using namespace std;

// Signal and kernel size limits
int g_NumPtsMin = 16;
int g_NumPtsMax = 16 * 1024 * 1024;
int g_KernelSizeMin = 3;
int g_KernelSizeMax = 15;
unsigned int g_RngSeedVal = 97;

void Convolve(void)
{
    const char nl = '\n';
    const int n1 = 512;
    const float kernel[] { 0.0625f, 0.25f, 0.375f, 0.25f, 0.0625f };
    const int ks = sizeof(kernel) / sizeof(float);
    const int ks2 = ks / 2;
    const int n2 = n1 + ks2 * 2;
    const unsigned int alignment = 16;

    // Create signal array
    AlignedArray<float> x1_aa(n1, alignment);
    AlignedArray<float> x2_aa(n2, alignment);

    float* x1 = x1_aa.Data();
    float* x2 = x2_aa.Data();

    CreateSignal(x1, n1, ks, g_RngSeedVal);
    PadSignal(x2, n2, x1, n1, ks2);

    // Perform convolutions
    AlignedArray<float> y1_aa(n1, alignment);
    AlignedArray<float> y2_aa(n1, alignment);
    AlignedArray<float> y3_aa(n1, alignment);
    AlignedArray<float> y4_aa(n1, alignment);

    float* y1 = y1_aa.Data();
    float* y2 = y2_aa.Data();
    float* y3 = y3_aa.Data();
    float* y4 = y4_aa.Data();

    bool rc1 = ConvolveKsN(y1, x2, n1, kernel, ks);
    bool rc2 = ConvolveKsN_(y2, x2, n1, kernel, ks);
    bool rc3 = ConvolveKs5(y3, x2, n1, kernel, ks);
    bool rc4 = ConvolveKs5_(y4, x2, n1, kernel, ks);

    cout << "Results for Convolve\n";
    cout << "  rc1 = " << boolalpha << rc1 << nl;
    cout << "  rc2 = " << boolalpha << rc2 << nl;
    cout << "  rc3 = " << boolalpha << rc3 << nl;
    cout << "  rc4 = " << boolalpha << rc4 << nl;

    if (!rc1 || !rc2 || !rc3 || !rc4)
        return;

    // Save data
    const char* fn = "Ch16_01_ConvolveResults.csv";
    ofstream ofs(fn);

    if (ofs.bad())
        cout << "File create error - " << fn << nl;
    else
    {
        const char* delim = ", ";

        ofs << fixed << setprecision(7);
        ofs << "i, x1, y1, y2, y3, y4\n";

        for (int i = 0; i < n1; i++)
        {
            ofs << setw(5) << i << delim;
            ofs << setw(10) << x1[i] << delim;
            ofs << setw(10) << y1[i] << delim;
            ofs << setw(10) << y2[i] << delim;
            ofs << setw(10) << y3[i] << delim;
            ofs << setw(10) << y4[i] << nl;
        }

        ofs.close();
        cout << "\nConvolution results saved to file " << fn << nl;
    }
}

bool ConvolveKsN(float* y, const float* x, int num_pts, const float* kernel, int kernel_size)
{
    int ks2 = kernel_size / 2;

    if ((kernel_size & 1) == 0)
        return false;

    if (kernel_size < g_KernelSizeMin || kernel_size > g_KernelSizeMax)
        return false;

    if (num_pts < g_NumPtsMin || num_pts > g_NumPtsMax)
        return false;

    if (num_pts % 16 != 0)
        return false;

    x += ks2;   // x points to first signal point

    for (int i = 0; i < num_pts; i++)
    {
        float sum = 0;

        for (int k = -ks2; k <= ks2; k++)
        {
            float x_val = x[i - k];
            float kernel_val = kernel[k + ks2];

            sum += kernel_val * x_val;
        }

        y[i] = sum;
    }

    return true;
}

bool ConvolveKs5(float* y, const float* x, int num_pts, const float* kernel, int kernel_size)
{
    int ks2 = kernel_size / 2;

    if (kernel_size != 5)
        return false;

    if (num_pts < g_NumPtsMin || num_pts > g_NumPtsMax)
        return false;

    if (num_pts % 16 != 0)
        return false;

    x += ks2;   // x points to first signal point

    for (int i = 0; i < num_pts; i++)
    {
        float sum = 0;
        int j = i + ks2;

        sum += x[j] * kernel[0];
        sum += x[j - 1] * kernel[1];
        sum += x[j - 2] * kernel[2];
        sum += x[j - 3] * kernel[3];
        sum += x[j - 4] * kernel[4];

        y[i] = sum;
    }

    return true;
}


int main()
{
    try
    {
        Convolve();
        Convolve_BM();
    }

    catch (exception& ex)
    {
        cout << "exception has occurred - " << ex.what() << '\n';
    }

    return 0;
}
