//------------------------------------------------
//               Ch03_03.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

extern "C" void LocalVarsA_(int a, int b, int c, int d, int e, int f,
    int* g, int* h);

void LocalVarsA(int a, int b, int c, int d, int e, int f, int* g, int* h)
{
    int temp0 = a + b + c;
    int temp1 = d + e + f;
    int temp2 = a + c + e;
    int temp3 = b + d + f;

    *g = temp0 * temp1;
    *h = temp2 * temp3;
}

void PrintResult(const char* msg, int a, int b, int c, int d, int e,
    int f, int g1, int g2, int h1, int h2)
{
    const char nl = '\n';
    const char* sep = " | ";
    const size_t w = 8;

    cout << msg << nl;
    cout << "a =  " << setw(w) << a << sep;
    cout << "b =  " << setw(w) << b << sep;
    cout << "c =  " << setw(w) << c << nl;
    cout << "d =  " << setw(w) << d << sep;
    cout << "e =  " << setw(w) << e << sep;
    cout << "f =  " << setw(w) << f << nl;
    cout << "g1 = " << setw(w) << g1 << sep;
    cout << "g2 = " << setw(w) << g2 << nl;
    cout << "h1 = " << setw(w) << h1 << sep;
    cout << "h2 = " << setw(w) << h2 << nl;

    if (g1 != g2 || h1 != h2)
        cout << "Compare Error!\n";
    cout << nl;
}

int main(int argc, char** argv)
{
    int a, b, c, d, e, f, g1, g2, h1, h2;

    // Test Case #1
    a = 10; b = -20; c = 30; d = -40; e = -50; f = -60;
    LocalVarsA(a, b, c, d, e, f, &g1, &h1);
    LocalVarsA_(a, b, c, d, e, f, &g2, &h2);

    PrintResult("Test Case #1", a, b, c, d, e, f,
        g1, g2, h1, h2);

    // Test Case #2
    a = 100; b = -200; c = 300; d = -400; e = -500; f = -600;
    LocalVarsA(a, b, c, d, e, f, &g1, &h1);
    LocalVarsA_(a, b, c, d, e, f, &g2, &h2);

    PrintResult("Test Case #2", a, b, c, d, e, f,
        g1, g2, h1, h2);

    return 0;
}
