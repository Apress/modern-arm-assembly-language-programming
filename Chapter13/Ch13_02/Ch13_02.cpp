//-------------------------------------------------
//               Ch13_02.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

extern "C" void CalcSphereAreaVolume_(double r, double* sa, double* vol);

int main(int argc, char** argv)
{
    double r[] = { 0.0, 1.0, 2.0, 3.0, 5.0, 10.0, 20.0, 32.0 };
    size_t num_r = sizeof(r) / sizeof(double);

    cout << setprecision(8);
    cout << "\n--------- Results for CalcSphereAreaVolume -----------\n";

    for (size_t i = 0; i < num_r; i++)
    {
        double sa = -1, vol = -1;

        CalcSphereAreaVolume_(r[i], &sa, &vol);

        cout << "i: " << i << "  ";
        cout << "r: " << setw(6) << r[i] << "  ";
        cout << "sa: " << setw(11) << sa << "  ";
        cout << "vol: " << setw(11) << vol << '\n';
    }

    return 0;
}
