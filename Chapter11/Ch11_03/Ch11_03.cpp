//-------------------------------------------------
//               Ch11_03.cpp
//-------------------------------------------------

#include <iostream>

using namespace std;

extern "C" void CalcQuoRemA_(int a, int b, int* quo, int* rem);
extern "C" void CalcQuoRemB_(long a, long b, long* quo, long* rem);

template <typename T>
void PrintResult(const char* msg, T a, T b, T quo, T rem)
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
    int a1 = 100, b1 = 7, quo1, rem1;
    CalcQuoRemA_(a1, b1, &quo1, &rem1);
    PrintResult("CalcQuoRemA_", a1, b1, quo1, rem1);

    long a2 = -2000000000, b2 = 11, quo2, rem2;
    CalcQuoRemB_(a2, b2, &quo2, &rem2);
    PrintResult("CalcQuoRemB_", a2, b2, quo2, rem2);
}
