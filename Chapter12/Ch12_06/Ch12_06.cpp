//-------------------------------------------------
//               Ch12_06.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <random>

using namespace std;

extern "C" bool CalcMatrixRowColSums_(int64_t* row_sums, int64_t* col_sums, const int64_t* x, int nrows, int ncols);

void Init(int64_t* x, int nrows, int ncols)
{
    unsigned int seed = 13;
    uniform_int_distribution<> d {1, 200};
    mt19937 rng {seed};

    for (int i = 0; i < nrows * ncols; i++)
        x[i] = d(rng);
}

void PrintResult(const char* msg, const int64_t* row_sums, const int64_t* col_sums, const int64_t* x, int nrows, int ncols)
{
    const int w = 6;
    const char nl = '\n';

    cout << msg;
    cout << "-----------------------------------------\n";

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

bool CalcMatrixRowColSums(int64_t* row_sums, int64_t* col_sums, const int64_t* x, int nrows, int ncols)
{
    bool rc = false;

    if (nrows > 0 && ncols > 0)
    {
        for (int j = 0; j < ncols; j++)
            col_sums[j] = 0;

        for (int i = 0; i < nrows; i++)
        {
            row_sums[i] = 0;
            int k = i * ncols;

            for (int j = 0; j < ncols; j++)
            {
                int64_t temp = x[k + j];
                row_sums[i] += temp;
                col_sums[j] += temp;
            }
        }

        rc = true;
    }

    return rc;
}

int main()
{
    const int nrows = 7;
    const int ncols = 5;
    int64_t x[nrows][ncols];
    int64_t* px = &x[0][0];

    Init(px, nrows, ncols);

    int64_t row_sums1[nrows], col_sums1[ncols];
    int64_t row_sums2[nrows], col_sums2[ncols];

    const char* msg1 = "\nResults using CalcMatrixRowColSums\n";
    const char* msg2 = "\nResults using CalcMatrixRowColSums_\n";

    bool rc1, rc2;
    rc1 = CalcMatrixRowColSums(row_sums1, col_sums1, px, nrows, ncols);
    rc2 = CalcMatrixRowColSums_(row_sums2, col_sums2, px, nrows, ncols);

    if (!rc1)
        cout << "CalcMatrixRowSums failed\n";
    else
        PrintResult(msg1, row_sums1, col_sums1, px, nrows, ncols);

    if (!rc2)
        cout << "CalcMatrixRowSums_ failed\n";
    else
        PrintResult(msg2, row_sums2, col_sums2, px, nrows, ncols);

    return 0;
}
