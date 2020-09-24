//-------------------------------------------------
//               Ch06_05.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

enum RmOp
{
    // Values below correspond to RMode field in FPSCR
    Nearest = 0, PlusInf = 1, MinusInf = 2, Zero = 3
};

// Miscellaneous values
const string c_RmOpStrings[] = {"Nearest", "PlusInf", "MinusInf", "Zero"};
const RmOp c_RmOpVals[] = {RmOp::Nearest, RmOp::PlusInf, RmOp::MinusInf, RmOp::Zero};
const size_t c_NumRmOps = sizeof(c_RmOpVals) / sizeof (RmOp);

// Assembly language functions defined in Ch06_05_.s
extern "C" RmOp GetRm_(void);
extern "C" void SetRm_(RmOp rm_op);
extern "C" int ConvertA_(double a);
extern "C" double ConvertB_(int a, unsigned int b);
extern "C" float ConvertC_(double a, float b, double c, float d);

void TestConvertA(void)
{
    const char nl = '\n';
    const size_t n = 4;
    double a[n] = {M_PI, M_SQRT2 + 0.5, -M_E, -M_SQRT2};

    cout << fixed << setprecision(8);
    cout << "\n----------Results for TestConvertA ----------\n";

    for (size_t i = 0; i < n; i++)
    {
        cout << "Test case #" << i << " using value " << a[i] << nl;

        for (size_t j = 0; j < c_NumRmOps; j++)
        {
            RmOp rm_old = GetRm_();
            RmOp rm_new = c_RmOpVals[j];

            SetRm_(rm_new);
            int b = ConvertA_(a[i]);
            SetRm_(rm_old);
    
            cout << left << setw(10) << c_RmOpStrings[j];
            cout << b << nl;
        }

        cout << nl;
    }
}

void TestConvertB(void)
{
    const char nl = '\n';
    const size_t n = 4;
    int a[n] = {1, -2, 3, -4};
    unsigned int b[n] = {100, 200, 300, 400};

    cout << fixed << setprecision(2);
    cout << "\n----------Results for TestConvertB ----------\n";

    for (size_t i = 0; i < n; i++)
    {
        double c = ConvertB_(a[i], b[i]);

        cout << "a: " << setw(6) << a[i] << " ";
        cout << "b: " << setw(6) << b[i] << " ";
        cout << "c: " << setw(6) << c << nl;
    }
}

void TestConvertC(void)
{
    const char nl = '\n';
    double a = 2.5, c = 4.0;
    float b = 1.5f, d = 20.0f;

    float e = ConvertC_(a, b, c, d);

    cout << fixed << setprecision(4);
    cout << "\n----------Results for TestConvertC ----------\n";
    cout << "a: " << a << nl << "b: " << b << nl << "c: " << c << nl;
    cout << "d: " << d << nl << "e: " << e << nl;
}

int main(void)
{
    TestConvertA();
    TestConvertB();
    TestConvertC();
    return 0;
}
