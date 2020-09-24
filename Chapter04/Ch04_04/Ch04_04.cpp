//-------------------------------------------------
//               Ch04_04.cpp
//-------------------------------------------------

#include <iostream>
#include <random>

using namespace std;

// Ch04_04_.s
extern "C" bool CalcMatrixRowColSums_(int* row_sums, int* col_sums, const int* x, int nrows, int ncols);

// Ch04_04_Misc.cpp
extern void PrintResult(const char* msg, const int* row_sums, const int* col_sums, const int* x, int nrows, int ncols);

void Init(int* x, int nrows, int ncols)
{
    unsigned int seed = 13;
    uniform_int_distribution<> d {1, 200};
    mt19937 rng {seed};

    for (int i = 0; i < nrows * ncols; i++)
        x[i] = d(rng);
}

bool CalcMatrixRowColSums(int* row_sums, int* col_sums, const int* x, int nrows, int ncols)
{
    if (nrows <= 0 || ncols <= 0)
        return false;

    for (int j = 0; j < ncols; j++)
        col_sums[j] = 0;

    for (int i = 0; i < nrows; i++)
    {
        int row_sums_temp = 0;
        int k = i * ncols;

        for (int j = 0; j < ncols; j++)
        {
            int temp = x[k + j];
            row_sums_temp += temp;
            col_sums[j] += temp;
        }

        row_sums[i] = row_sums_temp;
    }

    return true;
}

int main()
{
    const int nrows = 8;
    const int ncols = 6;
    int x[nrows][ncols];

    Init((int*)x, nrows, ncols);

    int row_sums1[nrows], col_sums1[ncols];
    int row_sums2[nrows], col_sums2[ncols];

    const char* msg1 = "Results for CalcMatrixRowColSums";
    const char* msg2 = "Results for CalcMatrixRowColSums_";

    bool rc1 = CalcMatrixRowColSums(row_sums1, col_sums1, (int*)x, nrows, ncols);
    bool rc2 = CalcMatrixRowColSums_(row_sums2, col_sums2, (int*)x, nrows, ncols);

    if (!rc1)
        cout << "\nCalcMatrixRowSums failed\n";
    else
        PrintResult(msg1, row_sums1, col_sums1, (int*)x, nrows, ncols);

    if (!rc2)
        cout << "\nCalcMatrixRowSums_ failed\n";
    else
        PrintResult(msg2, row_sums2, col_sums2, (int*)x, nrows, ncols);

    return 0;
}
