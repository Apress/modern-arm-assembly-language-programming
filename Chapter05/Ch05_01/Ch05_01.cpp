//------------------------------------------------
//               Ch05_01.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

union Val
{
    float f;
    unsigned int u;
};

void PrintResult(const char* msg, float a, float b, float c, float d)
{
    const char nl = '\n';
    const size_t w = 8;

    Val v;
    v.f = d;

    cout << fixed << setprecision(8);
    cout << nl << msg << nl;
    cout << "a:           " << setw(w) << a << nl;
    cout << "b:           " << setw(w) << b << nl;
    cout << "c:           " << setw(w) << c << nl;
    cout << scientific << setprecision(8);
    cout << "d (float):   " << setw(w) << d << nl;
    cout << "d (binary):  0x" << hex << setw(8) << v.u << nl;
}

int main(int argc, char** argv)
{
    float a = 0.01;
    float b = 0.001;
    float c = 0.0001;
    float d1 = (a * b) * c;
    float d2 = a * (b * c);

    PrintResult("Results for (a * b) * c", a, b, c, d1);
    PrintResult("Results for a * (b * c)", a, b, c, d2);
}
