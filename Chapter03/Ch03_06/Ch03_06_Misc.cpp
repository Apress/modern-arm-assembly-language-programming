//------------------------------------------------
//               Ch03_06_Misc.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

void PrintResult(const char* msg, int n, int sum1_cpp, int sum1_asm,
    int sum2_cpp, int sum2_asm)
{
    const char nl = '\n';
    const char* sep = " | ";
    const size_t w = 6;

    cout << nl << msg << nl;
    cout << "n =        " << setw(w) << n << nl;

    cout << "sum1_cpp = " << setw(w) << sum1_cpp << sep << "sum1_asm = ";
    cout << setw(w) << sum1_asm << nl;

    cout << "sum2_cpp = " << setw(w) << sum2_cpp << sep << "sum2_asm = ";
    cout << setw(w) << sum2_asm << nl;
}
