//-------------------------------------------------
//               Ch12_03.cpp
//-------------------------------------------------

#include <iostream>
#include <cstdint>

using namespace std;

extern "C" bool CompareSumA_(int32_t a, int32_t b, int32_t c, int32_t* sum);
extern "C" bool CompareSumB_(int64_t a, int64_t b, int64_t c, int64_t* sum);
extern "C" bool CompareSumC_(int32_t a, int32_t b, int32_t c, int32_t* sum);

template <typename T>
void PrintResult(const char* msg, T a, T b, T c, T sum, bool result)
{
    const char nl = '\n';
    const char* sep = " | ";

    cout << msg << nl;
    cout << "a = " << a << sep;
    cout << "b = " << b << sep;
    cout << "c = " << c << sep;
    cout << "sum = " << sum << sep;
    cout << "result = " << boolalpha << result << nl;
    cout << nl;
}

void CompareSumA(void)
{
    bool result;
    int32_t a, b, c, sum;

    a = 10; b = 20; c = 30;
    result = CompareSumA_(a, b, c, &sum);
    PrintResult("CompareSumA_ (sum >= 100) - Test #1", a, b, c, sum, result);

    a = 100; b = -200; c = 400;
    result = CompareSumA_(a, b, c, &sum);
    PrintResult("CompareSumA_ (sum >= 100) - Test #2", a, b, c, sum, result);
}

void CompareSumB(void)
{
    bool result;
    int64_t a, b, c, sum;

    a = 10; b = 20; c = 30;
    result = CompareSumB_(a, b, c, &sum);
    PrintResult("CompareSumB_ (sum > 0) - Test #1", a, b, c, sum, result);

    a = 100; b = -200; c = 50;
    result = CompareSumB_(a, b, c, &sum);
    PrintResult("CompareSumB_ (sum > 0) - Test #2", a, b, c, sum, result);
}

void CompareSumC(void)
{
    bool result;
    int32_t a, b, c, sum;

    a = 0x7ffffff0; b = 5; c = 10;
    result = CompareSumC_(a, b, c, &sum);
    PrintResult("CompareSumC_ (overflow?) - Test #1", a, b, c, sum, result);

    a = 0x7ffffff0; b = 5; c = 11;
    result = CompareSumC_(a, b, c, &sum);
    PrintResult("CompareSumC_ (overflow?) - Test #2", a, b, c, sum, result);

    a = 0x7ffffff0; b = 100; c = 200;
    result = CompareSumC_(a, b, c, &sum);
    PrintResult("CompareSumC_ (overflow?) - Test #3", a, b, c, sum, result);

    a = 0x8000000f; b = -5; c = -10;
    result = CompareSumC_(a, b, c, &sum);
    PrintResult("CompareSumC_ (overflow?) - Test #4", a, b, c, sum, result);
}

int main(int argc, char** argv)
{
    CompareSumA();
    CompareSumB();
    CompareSumC();
}
