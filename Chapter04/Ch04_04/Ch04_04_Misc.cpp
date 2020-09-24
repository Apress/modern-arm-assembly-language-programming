//-------------------------------------------------
//               Ch04_04_Misc.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <random>

using namespace std;

void PrintResult(const char* msg, const int* row_sums, const int* col_sums, const int* x, int nrows, int ncols)
{
    const int w = 6;
    const char nl = '\n';
    const string s(48, '-');

    cout << nl << nl << msg << nl;
    cout << s << nl;

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
            cout << setw(w) << x[i* ncols + j];
        cout << "  " << setw(w) << row_sums[i] << nl;
    }

    cout << nl;

    for (int i = 0; i < ncols; i++)
        cout << setw(w) << col_sums[i];
    cout << nl;
}
