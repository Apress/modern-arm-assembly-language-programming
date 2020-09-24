//------------------------------------------------
//               Ch03_05.cpp
//------------------------------------------------

#include <iostream>

using namespace std;

extern "C" bool CompareSumA_(int a, int b, int c, int* sum);
extern "C" bool CompareSumB_(int a, int b, int c, int* sum);
extern "C" bool CompareSumC_(int a, int b, int c, int* sum);

void PrintResult(const char* msg, int a, int b, int c, int sum, bool result)
{
    const char nl = '\n';
    const char* sep = " | ";

    cout << msg << nl;
    cout << "a = " << a << sep;
    cout << "b = " << b << sep;
    cout << "c = " << c << sep;
    cout << "sum = " << sum << sep;
    cout << "result = " << boolalpha << result << nl << nl;
}

void CompareSumA(void)
{
    bool result;
    int a, b, c, sum;

    a = 10; b = 20; c = 30;
    result = CompareSumA_(a, b, c, &sum);
    PrintResult("CompareSumA - Test Case #1", a, b, c, sum, result);

    a = 100; b = -200; c = 400;
    result = CompareSumA_(a, b, c, &sum);
    PrintResult("CompareSumA - Test Case #2", a, b, c, sum, result);

    a = 100; b = -200; c = 200;
    result = CompareSumA_(a, b, c, &sum);
    PrintResult("CompareSumA - Test Case #3", a, b, c, sum, result);
}

void CompareSumB(void)
{
    bool result;
    int a, b, c, sum;

    a = 10; b = 20; c = 30;
    result = CompareSumB_(a, b, c, &sum);
    PrintResult("CompareSumB - Test Case #1", a, b, c, sum, result);

    a = 100; b = -200; c = 50;
    result = CompareSumB_(a, b, c, &sum);
    PrintResult("CompareSumB - Test Case #2", a, b, c, sum, result);

    a = 100; b = -200; c = 100;
    result = CompareSumB_(a, b, c, &sum);
    PrintResult("CompareSumB - Test Case #3", a, b, c, sum, result);
}

void CompareSumC(void)
{
    bool result;
    int a, b, c, sum;

    a = 0x7ffffff0; b = 5; c = 10;
    result = CompareSumC_(a, b, c, &sum);
    PrintResult("CompareSumC - Test Case #1", a, b, c, sum, result);

    a = 0x7ffffff0; b = 5; c = 11;
    result = CompareSumC_(a, b, c, &sum);
    PrintResult("CompareSumC - Test Case #2", a, b, c, sum, result);

    a = 0x7ffffff0; b = 100; c = 200;
    result = CompareSumC_(a, b, c, &sum);
    PrintResult("CompareSumC - Test Case #3", a, b, c, sum, result);

    a = 0x8000000f; b = -5; c = -10;
    result = CompareSumC_(a, b, c, &sum);
    PrintResult("CompareSumC - Test Case #4", a, b, c, sum, result);

    a = 0x8000000f; b = 100; c = -200;
    result = CompareSumC_(a, b, c, &sum);
    PrintResult("CompareSumC - Test Case #5", a, b, c, sum, result);
}

int main(int argc, char** argv)
{
    const char nl = '\n';
    string sep(75, '-');

    CompareSumA();
    cout << sep << nl << nl;
    CompareSumB();
    cout << sep << nl << nl;
    CompareSumC();
}
