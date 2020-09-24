//-------------------------------------------------
//               Ch13_01.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

extern "C" float ConvertFtoC_(float deg_f);
extern "C" float ConvertCtoF_(float deg_c);

int main()
{
    const int w = 10;
    float deg_fvals[] = {-459.67f, -40.0f, 0.0f, 32.0f, 72.0f, 98.6f, 212.0f};
    size_t nf = sizeof(deg_fvals) / sizeof(float);

    cout << setprecision(6);

    cout << "\n-------- ConvertFtoC Results --------\n";

    for (size_t i = 0; i < nf; i++)
    {
        float deg_c = ConvertFtoC_(deg_fvals[i]);

        cout << "  i: " << i << "  ";
        cout << "f: " << setw(w) << deg_fvals[i] << "  ";
        cout << "c: " << setw(w) << deg_c << '\n';
    }

    cout << "\n-------- ConvertCtoF Results --------\n";

    float deg_cvals[] = {-273.15f, -40.0f, -17.777778f, 0.0f, 25.0f, 37.0f, 100.0f};
    size_t nc = sizeof(deg_cvals) / sizeof(float);

    for (size_t i = 0; i < nc; i++)
    {
        float deg_f = ConvertCtoF_(deg_cvals[i]);

        cout << "  i: " << i << "  ";
        cout << "c: " << setw(w) << deg_cvals[i] << "  ";
        cout << "f: " << setw(w) << deg_f << '\n';
    }

    return 0;
}

