//-------------------------------------------------
//               Ch11_01.cpp
//-------------------------------------------------

#include <iostream>

using namespace std;

extern "C" int IntegerAddSubA_(int a, int b, int c);
extern "C" long IntegerAddSubB_(long a, long b, long c);

template <typename T>
void PrintResult(const char* msg, T a, T b, T c, T result)
{
    const char nl = '\n';

    cout << msg << nl;
    cout << "a = " << a << nl;
    cout << "b = " << b << nl;
    cout << "c = " << c << nl;
    cout << "result (a + b - c) = " << result << nl;
    cout << nl;
}

int main(int argc, char** argv)
{
    int a1 = 100, b1 = 200, c1 = -50, result1;
    result1 = IntegerAddSubA_(a1, b1, c1);
    PrintResult("IntegerAddSubA_", a1, b1, c1, result1);

    long a2 = 1000, b2 = -2000, c2 = 500, result2;
    result2 = IntegerAddSubB_(a2, b2, c2);
    PrintResult("IntegerAddSubB_", a2, b2, c2, result2);
}
