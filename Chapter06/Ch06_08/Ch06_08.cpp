//-------------------------------------------------
//               Ch06_08.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

extern "C" void RectToPolar_(double* r, double* theta, double x, double y);
extern "C" void PolarToRect_(double* x, double* y, double r, double theta);

int main()
{
    //?? Add a few more test cases?
    const int n = 7;
    const double x1[n] = { 3.0, -4.0, 1.0,  1.0, 1.5, -5.0, -8.0 };
    const double y1[n] = { 4.0,  3.0, 1.0, -1.0, 6.0, -4.0,  9.0 };

    cout << fixed << setprecision(4);

    for (int i = 0; i < n; i++)
    {
        const int w = 9;
        const char nl = '\n';

        double r, theta, x2, y2;

        RectToPolar_(&r, &theta, x1[i], y1[i]);
        PolarToRect_(&x2, &y2, r, theta);

        cout << setw(w) << x1[i] << ", " << setw(w) << y1[i] << " | ";
        cout << setw(w) << r << ", " << setw(w) << theta << " | ";
        cout << setw(w) << x2 << ", " << setw(w) << y2 << nl;
    }

    return 0;
}
