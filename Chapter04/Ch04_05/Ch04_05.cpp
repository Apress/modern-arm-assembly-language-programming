//-------------------------------------------------
//               Ch04_05.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

extern "C" void ReverseArrayA_(int* y, const int* x, int n);
extern "C" void ReverseArrayB_(int* x, int n);

void Init(int* x, int n, unsigned int seed)
{
    uniform_int_distribution<> d {1, 1000};
    mt19937 rng {seed};

    for (int i = 0; i < n; i++)
        x[i] = d(rng);
}

void PrintArray(const char* msg, const int* x, int n)
{
    const char nl = '\n';

    cout << nl << msg << nl;

    for (int i = 0; i < n; i++)
    {
        cout << setw(5) << x[i];

        if ((i + 1) % 10 == 0)
            cout << nl;
    }
    cout << nl;
}

void ReverseArrayA(void)
{
    const int n = 25;
    int x[n], y[n];

    Init(x, n, 32);
    PrintArray("ReverseArrayA - original array x", x, n);
    ReverseArrayA_(y, x, n);
    PrintArray("ReverseArrayA - reversed array y", y, n);
}

void ReverseArrayB(void)
{
    const int n = 25;
    int x[n];

    Init(x, n, 32);
    PrintArray("ReverseArrayB - array x before reversal", x, n);
    ReverseArrayB_(x, n);
    PrintArray("ReverseArrayB - array x after reversal", x, n);
}

int main()
{
    ReverseArrayA();
    ReverseArrayB();
    return 0;
}
