//-------------------------------------------------
//               Ch12_02.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdint>

using namespace std;

int32_t g_Val1 = 10;
int64_t g_Val2 = -20;

extern "C" void LocalVars_(int32_t a, int32_t b, int32_t c, int32_t d,
  int64_t e, int64_t f, int64_t g, int64_t h, int32_t* x, int64_t* y);

void LocalVars(int32_t a, int32_t b, int32_t c, int32_t d,
  int64_t e, int64_t f, int64_t g, int64_t h, int32_t* x, int64_t* y)
{
    int32_t temp0 = a + b + c;
    int32_t temp1 = d - g_Val1;
    int64_t temp2 = e + f + g;
    int64_t temp3 = h - g_Val2;

    *x = temp0 * temp1;
    *y = temp2 * temp3;
}

void PrintResult(const char* msg, int32_t a, int32_t b, int32_t c, int32_t d,
    int64_t e, int64_t f, int64_t g, int64_t h, int32_t x1, int64_t y1,
    int32_t x2, int64_t y2)
{
    const char nl = '\n';
    const char* sep = " | ";
    const size_t w = 8;

    cout << nl << msg << nl;
    cout << "a =  " << setw(w) << a << sep;
    cout << "b =  " << setw(w) << b << sep;
    cout << "c =  " << setw(w) << c << sep;
    cout << "d =  " << setw(w) << d << nl;
    cout << "e =  " << setw(w) << e << sep;
    cout << "f =  " << setw(w) << f << sep;
    cout << "g =  " << setw(w) << g << sep;
    cout << "h =  " << setw(w) << h << nl;
    cout << "x1 = " << setw(w) << x1 << nl;
    cout << "x2 = " << setw(w) << x2 << nl;
    cout << "y1 = " << setw(w) << y1 << nl;
    cout << "y2 = " << setw(w) << y2 << nl;

    if (x1 != x2 || y1 != y2)
        cout << "Compare error!" << nl;
}

int main(int argc, char** argv)
{
    int32_t a, b, c, d, x1, x2;
    int64_t e, f, g, h, y1, y2;
 
    a = 10; b = -20; c = 30; d = -40;
    e = 50; f = -60, g = 70, h = -80;
    LocalVars(a, b, c, d, e, f, g, h, &x1, &y1);
    LocalVars_(a, b, c, d, e, f, g, h, &x2, &y2);
    PrintResult("LocalVarsA - Test Case #1", a, b, c, d, e, f, g, h, x1, y1, x2, y2);

    a = 100; b = -200; c = 300; d = -400;
    e = 500; f = -600; g = 700; h = -800;
    LocalVars(a, b, c, d, e, f, g, h, &x1, &y1);
    LocalVars_(a, b, c, d, e, f, g, h, &x2, &y2);
    PrintResult("LocalVarsA - Test Case #2", a, b, c, d, e, f, g, h, x1, y1, x2, y2);
}

