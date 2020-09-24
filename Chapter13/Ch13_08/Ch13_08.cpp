//------------------------------------------------
//               Ch13_08.cpp
//------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

extern "C" void CalcBSA_(double bsa[3], double ht, double wt);

void CalcBSA(double bsa[3], double ht, double wt)
{
    bsa[0] = 0.007184 * pow(ht, 0.725) * pow(wt, 0.425);
    bsa[1] = 0.0235 * pow(ht, 0.42246) * pow(wt, 0.51456);
    bsa[2] = sqrt(ht * wt / 3600.0);
}

int main()
{
    const int n = 6;
    const double ht[n] = { 150, 160, 170, 180, 190, 200 };
    const double wt[n] = { 50.0, 60.0, 70.0, 80.0, 90.0, 100.0 };

    cout << "---------- Body Surface Area Results ----------\n";
    cout << fixed;

    for (int i = 0; i < n; i++)
    {
        cout << setprecision(1);
        cout << "height: " << setw(6) << ht[i] << " cm\n";
        cout << "weight: " << setw(6) << wt[i] << " kg\n";

        double bsa1[3], bsa2[3];

        CalcBSA(bsa1, ht[i], wt[i]);
        CalcBSA_(bsa2, ht[i], wt[i]);

        for (int j = 0; j < 3; j++)
        {
            cout << setprecision(6);
            cout << "bsa1[" << j << "]: " << setw(10) << bsa1[j];
            cout << " | ";
            cout << "bsa2[" << j << "]: " << setw(10) << bsa2[j];
            cout << " (sq. m)\n";
        }

        cout << '\n';
    }

    return 0;
}
