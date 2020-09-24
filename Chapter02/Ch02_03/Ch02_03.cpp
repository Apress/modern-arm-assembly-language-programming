//------------------------------------------------
//               Ch02_03.cpp
//------------------------------------------------

#include <iostream>

using namespace std;

extern "C" void CalcQuoRem_(const int* a, const int* b, int* quo, int* rem);

void PrintResult(const char* msg, int a, int b, int quo, int rem)
{
    const char nl = '\n';

    cout << msg << nl;
    cout << "a = " << a << nl;
    cout << "b = " << b << nl;
    cout << "quotient = " << quo << nl;
    cout << "remainder = " << rem << nl;
    cout << nl;
}

int main(int argc, char** argv)
{
    int a, b, quo, rem;

    a = 100; b = 7;
    CalcQuoRem_(&a, &b, &quo, &rem);
    PrintResult("Test case #1", a, b, quo, rem);

    a = 200; b = 10;
    CalcQuoRem_(&a, &b, &quo, &rem);
    PrintResult("Test case #2", a, b, quo, rem);

    a = 300; b = -17;
    CalcQuoRem_(&a, &b, &quo, &rem);
    PrintResult("Test case #3", a, b, quo, rem);
}
