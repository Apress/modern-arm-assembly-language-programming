//-------------------------------------------------
//               Ch06_07.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <random>

using namespace std;

extern "C" bool CalcTrace_(double* trace, const double* x, int nrows, int ncols);

void Init(double* x, int nrows, int ncols)
{
    unsigned int seed = 47;
    uniform_int_distribution<> d {1, 1000};
    mt19937 rng {seed};

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
            x[i * ncols + j] = (double)d(rng);
    }
}

bool CalcTrace(double* trace, const double* x, int nrows, int ncols)
{
    if (nrows != ncols || nrows <= 0)
        return false;

    double sum = 0.0;

    for (int i = 0; i < nrows; i++)
        sum += x[i * ncols + i];

    *trace = sum;
    return true;
}

int main()
{
    const char nl = '\n';
    const int nrows = 11;
    const int ncols = 11;
    double x[nrows][ncols];
    double trace1, trace2;
    string dashes(72, '-');

    Init(&x[0][0], nrows, ncols);

    CalcTrace(&trace1, &x[0][0], nrows, ncols);
    CalcTrace_(&trace2, &x[0][0], nrows, ncols);

    cout << "\nTest Matrix\n";
    cout << dashes << nl;

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
            cout << setw(5) << x[i][j] << ' ';

        cout << nl;
    }

    cout << "\ntrace1 = " << trace1 << nl;
    cout << "trace2 = " << trace2 << nl;

    return 0;
}
