//-------------------------------------------------
//               Ch12_04.cpp
//-------------------------------------------------

#include <iostream>
#include <cstdint>

using namespace std;

const int64_t g_ArgnMin = 1;
const int64_t g_ArgnMax = 1023;

extern "C" void SumSquares_(int64_t n, int64_t* sum_a, int64_t* sum_b);

int64_t SumSquaresA(int64_t n)
{
    int64_t sum = 0;

    for (int i = 1; i <= n; i++)
        sum += i * i;

    return sum;
}

int64_t SumSquaresB(int64_t n)
{
    int64_t sum = (n * (n + 1) * (2 * n + 1)) / 6;

    return sum;
}

void SumSquares(int64_t n, int64_t* sum_a, int64_t* sum_b)
{
    *sum_a = *sum_b = 0;

    if (n < g_ArgnMin || n > g_ArgnMax)
        return;

    *sum_a = SumSquaresA(n);
    *sum_b = SumSquaresB(n);
}

void PrintResult(const char* msg, int64_t n, int64_t sum_a1, int64_t sum_a2, int64_t sum_b1, int64_t sum_b2)
{
    const char nl = '\n';
    const char* sep = " | ";

    cout << nl << msg << nl;
    cout << "n = " << n << nl;
    cout << "sum_a1 = " << sum_a1 << sep << "sum_a2 = " << sum_a2 << nl;
    cout << "sum_b1 = " << sum_b1 << sep << "sum_b2 = " << sum_b2 << nl;

    if (sum_a1 != sum_a2 || sum_a1 != sum_b1 || sum_a1 != sum_b2)
        cout << "Compare error!\n";
}

int main(int argc, char** argv)
{
    int64_t n, sum_a1, sum_a2, sum_b1, sum_b2;

    n = 3;
    SumSquares(n, &sum_a1, &sum_b1);
    SumSquares_(n, &sum_a2, &sum_b2);
    PrintResult("SumSquares - Test #1", n, sum_a1, sum_a2, sum_b1, sum_b2);

    n = 42;
    SumSquares(n, &sum_a1, &sum_b1);
    SumSquares_(n, &sum_a2, &sum_b2);
    PrintResult("SumSquares - Test #2", n, sum_a1, sum_a2, sum_b1, sum_b2);

    n = 1023;
    SumSquares(n, &sum_a1, &sum_b1);
    SumSquares_(n, &sum_a2, &sum_b2);
    PrintResult("SumSquares - Test #3", n, sum_a1, sum_a2, sum_b1, sum_b2);

    return 0;
}
