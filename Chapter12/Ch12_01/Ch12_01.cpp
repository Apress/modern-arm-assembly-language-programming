//-------------------------------------------------
//               Ch12_01.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdint>

using namespace std;

extern "C" int64_t SumCubes_(uint8_t a, int16_t b, int32_t c, int64_t d,
        int8_t e, int16_t f, uint8_t g, uint16_t h, int32_t i, int8_t j);

void PrintResult(const char* msg, int a, int b, int c, int64_t d, int e,
        int f, int g, int h, int i, int j, int64_t sum1, int64_t sum2)
{
    const char nl = '\n';
    const char* sep = " | ";
    const size_t w = 6;

    cout << msg << nl;
    cout << "a = " << setw(w) << a << sep;
    cout << "b = " << setw(w) << b << sep;
    cout << "c = " << setw(w) << c << sep;
    cout << "d = " << setw(w) << d << sep;
    cout << "e = " << setw(w) << e << nl;
    cout << "f = " << setw(w) << f << sep;
    cout << "g = " << setw(w) << g << sep;
    cout << "h = " << setw(w) << h << sep;
    cout << "i = " << setw(w) << i << sep;
    cout << "j = " << setw(w) << j << nl;
    cout << "sum1 = " << setw(w) << sum1 << nl;
    cout << "sum2 = " << setw(w) << sum2 << nl;

    if (sum1 != sum2)
        cout << "Compare error!\n";

    cout << nl;
}

int64_t SumCubes(uint8_t a, int16_t b, int32_t c, int64_t d,
        int8_t e, int16_t f, uint8_t g, uint16_t h, int32_t i, int8_t j)
{
    int64_t aa = (int64_t)a * a * a;
    int64_t bb = (int64_t)b * b * b;
    int64_t cc = (int64_t)c * c * c;
    int64_t dd = d * d * d;
    int64_t ee = (int64_t)e * e * e;
    int64_t ff = (int64_t)f * f * f;
    int64_t gg = (int64_t)g * g * g;
    int64_t hh = (int64_t)h * h * h;
    int64_t ii = (int64_t)i * i * i;
    int64_t jj = (int64_t)j * j * j;

    return aa + bb + cc + dd + ee + ff + gg + hh + ii + jj;
}

int main(int argc, char** argv)
{
    uint8_t a, g;
    int16_t b, f;
    int32_t c, i;
    int64_t d, sum1, sum2;
    int8_t e, j;
    uint16_t short h;
 
    a = 10; b = -20; c = 30; d = -40;
    e = -50; f = -60; g = 70, h = 80, i = -90, j = 100;
    sum1 = SumCubes(a, b, c, d, e, f, g, h, i, j);
    sum2 = SumCubes_(a, b, c, d, e, f, g, h, i, j);
    PrintResult("SumCubes - Test #1", a, b, c, d, e, f, g, h, i, j, sum1, sum2);

    a = 10; b = -20; c = -30; d = 40;
    e = -50; f = 60; g = 70, h = 80, i = 90, j = -100;
    sum1 = SumCubes(a, b, c, d, e, f, g, h, i, j);
    sum2 = SumCubes_(a, b, c, d, e, f, g, h, i, j);
    PrintResult("SumCubes - Test #2", a, b, c, d, e, f, g, h, i, j, sum1, sum2);

    a = -100; b = 200; c = 300; d = 400;
    e = 50; f = -600; g = 70, h = 800, i = -900, j = -25;
    sum1 = SumCubes(a, b, c, d, e, f, g, h, i, j);
    sum2 = SumCubes_(a, b, c, d, e, f, g, h, i, j);
    PrintResult("SumCubes - Test #3", a, b, c, d, e, f, g, h, i, j, sum1, sum2);
}
