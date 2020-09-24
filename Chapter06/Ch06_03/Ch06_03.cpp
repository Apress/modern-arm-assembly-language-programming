//-------------------------------------------------
//               Ch06_03.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>

using namespace std;

extern "C" double CalcDist_(double x1, double y1, double z1, double x2, double y2, double z2);

void Init(double* x, double* y, double* z, size_t n, unsigned int seed)
{
    uniform_int_distribution<> ui_dist {1, 100};
    mt19937 rng {seed};

    for (size_t i = 0; i < n; i++)
    {
        x[i] = ui_dist(rng);
        y[i] = ui_dist(rng);
        z[i] = ui_dist(rng);
    }
}

double CalcDist(double x1, double y1, double z1, double x2, double y2, double z2)
{
    double tx = (x2 - x1) * (x2 - x1);
    double ty = (y2 - y1) * (y2 - y1);
    double tz = (z2 - z1) * (z2 - z1);
    double dist = sqrt(tx + ty + tz);

    return dist;
}

int main()
{
    const size_t n = 20;
    double x1[n], y1[n], z1[n];
    double x2[n], y2[n], z2[n];
    double dist1[n];
    double dist2[n];

    Init(x1, y1, z1, n, 29);
    Init(x2, y2, z2, n, 37);

    for (size_t i = 0; i < n; i++)
    {
        dist1[i] = CalcDist(x1[i], y1[i], z1[i], x2[i], y2[i], z2[i]);
        dist2[i] = CalcDist_(x1[i], y1[i], z1[i], x2[i], y2[i], z2[i]);
    }

    cout << fixed;

    for (size_t i = 0; i < n; i++)
    {
        cout << setw(2) << i << "  ";

        cout << setprecision(0);

        cout << "p1(";
        cout << setw(3) << x1[i] << ",";
        cout << setw(3) << y1[i] << ",";
        cout << setw(3) << z1[i] << ") | ";

        cout << "p2(";
        cout << setw(3) << x2[i] << ",";
        cout << setw(3) << y2[i] << ",";
        cout << setw(3) << z2[i] << ") | ";

        cout << setprecision(4);
        cout << "dist1: " << setw(8) << dist1[i] << " | ";
        cout << "dist2: " << setw(8) << dist2[i] << '\n';
    }
    
    return 0;
}
