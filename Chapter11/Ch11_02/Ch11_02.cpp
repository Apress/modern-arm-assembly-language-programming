//-------------------------------------------------
//               Ch11_02.cpp
//-------------------------------------------------

#include <iostream>

using namespace std;

extern "C" int IntegerMulA_(int a, int b);
extern "C" long IntegerMulB_(long a, long b);
extern "C" long IntegerMulC_(int a, int b);
extern "C" unsigned long IntegerMulD_(unsigned int a, unsigned int b);

template <typename T1, typename T2>
void PrintResult(const char* msg, T1 a, T1 b, T2 result)
{
    const char nl = '\n';

    cout << msg << nl;
    cout << "a = " << a << ", b = " << b;
    cout << " result = " << result << nl << nl;
}

int main(int argc, char** argv)
{
    int a1 = 50;
    int b1 = 25;
    int result1 = IntegerMulA_(a1, b1);
    PrintResult("IntegerMulA_", a1, b1, result1);

    long a2 = -3000000000;
    long b2 = 7;
    long result2 = IntegerMulB_(a2, b2);
    PrintResult("IntegerMulB_", a2, b2, result2);

    int a3 = 4000;
    int b3 = 0x80000000;
    long result3 = IntegerMulC_(a3, b3);
    PrintResult("IntegerMulC_", a3, b3, result3);

    unsigned int a4 = 4000;
    unsigned int b4 = 0x80000000;
    unsigned long result4 = IntegerMulD_(a4, b4);
    PrintResult("IntegerMulD_", a4, b4, result4);

    return 0;
}
