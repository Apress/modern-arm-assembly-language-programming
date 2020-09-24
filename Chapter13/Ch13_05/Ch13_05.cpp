//-------------------------------------------------
//               Ch13_05.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

extern "C" double ConvertA_(float a, int b, unsigned int c, long long d, unsigned long long e);
extern "C" int ConvertB_(int* x, const char** msg_strings, double a);

void ConvertA(void)
{
    const char nl = '\n';
    float a = 10.125f;
    int b = -20;
    unsigned int c = 30;
    long long d = -40;
    unsigned long long e = 50;

    double x = ConvertA_(a, b, c, d, e);

    cout << fixed << setprecision(6);
    cout << "\n----------Results for TestConvertA ----------\n";
    cout << "a: " << a << nl;
    cout << "b: " << b << nl;
    cout << "c: " << c << nl;
    cout << "d: " << d << nl;
    cout << "e: " << e << nl;
    cout << "x: " << x << nl;
}

void ConvertB(void)
{
    const char nl = '\n';
    const size_t n = 4;
    double a[n] = {M_PI, M_SQRT2 + 0.5, -M_E, -M_SQRT2};

    cout << fixed << setprecision(8);
    cout << "\n----------Results for TestConvertB ----------\n";

    for (size_t i = 0; i < n; i++)
    {
        const size_t m = 4;
        int x[m];
        const char* msg_strings[m];

        cout << "Test case #" << i << " using value " << a[i] << nl;
        ConvertB_(x, msg_strings, a[i]);

        for (size_t j = 0; j < m; j++)
            cout << "  " << setw(4) << x[j] << " - " << msg_strings[j] << nl;
        cout << nl;
    }
}

int main(void)
{
    ConvertA();
    ConvertB();
    return 0;
}
