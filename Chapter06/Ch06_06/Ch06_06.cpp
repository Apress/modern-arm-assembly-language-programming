//-------------------------------------------------
//               Ch06_06.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

extern "C" bool CalcMeanStdev_(double* mean, double* stdev, const double* x, int n);

bool CalcMeanStdev(double* mean, double* stdev, const double* x, int n)
{
    if (n < 2)
        return false;

    double sum = 0.0;
    double sum2 = 0.0;

    for (int i = 0; i < n; i++)
        sum += x[i];

    *mean = sum / n;

    for (int i = 0; i < n; i++)
    {
        double temp = x[i] - *mean;
        sum2 += temp * temp;
    }

    *stdev = sqrt(sum2 / (n - 1));
    return true;
}

int main()
{
    const char nl = '\n';
    double x[] = { 10, 2, 33, 19, 41, 24, 75, 37, 18, 97, 14, 71, 88, 92, 7};
    const int n = sizeof(x) / sizeof(double);

    double mean1 = 0.0, stdev1 = 0.0;
    double mean2 = 0.0, stdev2 = 0.0;

    bool rc1 = CalcMeanStdev(&mean1, &stdev1, x, n);
    bool rc2 = CalcMeanStdev_(&mean2, &stdev2, x, n);

    cout << fixed << setprecision(2);

    for (int i = 0; i < n; i++)
    {
        cout << "x[" << setw(2) << i << "] = ";
        cout << setw(6) << x[i] << nl;
    }

    cout << setprecision(6);
        
    cout << nl;
    cout << "rc1 = " << boolalpha << rc1;
    cout << "  mean1 = " << mean1 << "  stdev1 = " << stdev1 << nl;
    cout << "rc2 = " << boolalpha << rc2;
    cout << "  mean2 = " << mean2 << "  stdev2 = " << stdev2 << nl;
}
