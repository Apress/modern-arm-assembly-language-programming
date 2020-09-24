//-------------------------------------------------
//               Ch04_01.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdint>

using namespace std;

extern "C" int CalcSumA_(const int* x, int n);
extern "C" uint64_t CalcSumB_(const uint32_t* x, uint32_t n);

int CalcSumA(const int* x, int n)
{
    int sum = 0;

    for (int i = 0; i < n; i++)
        sum += *x++;

    return sum;
}

uint64_t CalcSumB(const uint32_t* y, uint32_t n)
{
    uint64_t sum = 0;

    for (uint32_t i = 0; i < n; i++)
        sum += y[i];

    return sum;
}

int main()
{
    const char nl = '\n';

    int x[] {3, 17, -13, 25, -2, 9, -6, 12, 88, -19};
    int nx = sizeof(x) / sizeof(int);

    uint32_t y[] = {0x10000000, 0x20000000, 0x40000000, 0x80000000,
                    0x50000000, 0x70000000, 0x90000000, 0xC0000000};
    uint32_t ny = sizeof(y) / sizeof(uint32_t);

    // Calculate sum of elements in array x
    cout << "Results for CalcSumA" << nl;

    for (int i = 0; i < nx; i++)
        cout << "x[" << i << "] = " << x[i] << nl;

    int sum_x1 = CalcSumA(x, nx);
    int sum_x2 = CalcSumA_(x, nx);

    cout << "sum_x1 = " << sum_x1 << nl;
    cout << "sum_x2 = " << sum_x2 << nl << nl;

    // Calculate sum of elements in array y
    cout << "Results for CalcSumB" << nl;

    for (uint32_t i = 0; i < ny; i++)
        cout << "y[" << i << "] = " << y[i] << nl;

    uint64_t sum_y1 = CalcSumB(y, ny);
    uint64_t sum_y2 = CalcSumB_(y, ny);

    cout << "sum_y1 = " << sum_y1 << nl;
    cout << "sum_y2 = " << sum_y2 << nl << nl;

    return 0;
}
