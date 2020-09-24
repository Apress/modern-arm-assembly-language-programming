//-------------------------------------------------
//               Ch04_03.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

extern "C" void CalcMatrixSquares_(int* y, const int* x, int m, int n);

void CalcMatrixSquares(int* y, const int* x, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int kx = j * m + i;
            int ky = i * n + j;
            y[ky] = x[kx] * x[kx];
        }
    }
}

int main()
{
    const int m = 6;
    const int n = 3;
    int y1[m][n], y2[m][n];

    int x[n][m] {{ 1, 2, 3, 4, 5, 6 },
                  { 7, 8, 9, 10, 11, 12 },
                  { 13, 14, 15, 16, 17, 18 }};

    CalcMatrixSquares(&y1[0][0], &x[0][0], m, n);
    CalcMatrixSquares_(&y2[0][0], &x[0][0], m, n);

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << "y1[" << setw(2) << i << "][" << setw(2) << j << "] = ";
            cout << setw(6) << y1[i][j] << ' ' ;

            cout << "y2[" << setw(2) << i << "][" << setw(2) << j << "] = ";
            cout << setw(6) << y2[i][j] << ' ';

            cout << "x[" << setw(2) << j << "][" << setw(2) << i << "] = ";
            cout << setw(6) << x[j][i] << '\n';

            if (y1[i][j] != y2[i][j])
               cout << "Compare failed\n";
        }
    }

    return 0;
}
