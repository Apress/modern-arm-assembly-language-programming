//-------------------------------------------------
//               Ch12_05.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdint>

using namespace std;

extern "C" int CalcArraySumA_(const int* x, int n);
extern "C" uint64_t CalcArraySumB_(const uint64_t* x, uint32_t n);

int CalcArraySumA(const int* x, int n)
{
    int sum = 0;

    for (int i = 0; i < n; i++)
        sum += *x++;

    return sum;
}

uint64_t CalcArraySumB(const uint64_t* x, uint32_t n)
{
    uint64_t sum = 0;

    for (uint32_t i = 0; i < n; i++)
        sum += x[i];

    return sum;
}

void ArraySumA(void)
{
    const char nl = '\n';
    int x[] {3, 17, -13, 25, -2, 9, -6, 12, 88, -19, 9, 35};
    int n = sizeof(x) / sizeof(int);

    cout << "Results for ArraySumA" << nl;

    for (int i = 0; i < n; i++)
        cout << "x[" << i << "] = " << x[i] << nl;

    int sum1 = CalcArraySumA(x, n);
    int sum2 = CalcArraySumA_(x, n);

    cout << "sum1 = " << sum1 << " | sum2 = " << sum2 << nl << nl;
}

void ArraySumB(void)
{
    const char nl = '\n';
    uint64_t x[] = {0x10000000, 0x20000000, 0x30000000, 0x40000000,
                    0x50000000, 0x60000000, 0x70000000, 0x80000000,
                    0x90000000, 0xA0000000, 0xB0000000, 0xC0000000,
                    0xD0000000, 0xE0000000, 0xF0000000};
    uint32_t n = sizeof(x) / sizeof(uint64_t);

    cout << "Results for ArraySumB" << nl;

    for (uint32_t i = 0; i < n; i++)
        cout << "x[" << i << "] = " << x[i] << nl;

    uint64_t sum1 = CalcArraySumB(x, n);
    uint64_t sum2 = CalcArraySumB_(x, n);

    cout << "sum1 = " << sum1 << " | sum2 = " << sum2 << nl << nl;
}

int main()
{
    ArraySumA();
    ArraySumB();
    return 0;
}
