//-------------------------------------------------
//               Ch13_04.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

extern "C" void CompareF32_(bool* results, float a, float b);

const char* c_OpStrings[] = {"UO", "LT", "LE", "EQ", "NE", "GT", "GE"};
const size_t c_NumOpStrings = sizeof(c_OpStrings) / sizeof(char*);

const string c_Dashes(72, '-');

template <typename T> void PrintResults(const bool* cmp_results, T a, T b)
{
    cout << "a = " << a << ", ";
    cout << "b = " << b << '\n';

    for (size_t i = 0; i < c_NumOpStrings; i++)
    {
        cout << c_OpStrings[i] << '=';
        cout << boolalpha << left << setw(6) << cmp_results[i] << ' ';
    }

    cout << "\n\n";
}

void CompareF32(void)
{
    const size_t n = 6;
    float a[n] {120.0, 250.0, 300.0, -18.0, -81.0, 42.0};
    float b[n] {130.0, 240.0, 300.0, 32.0, -100.0, 0.0};

    // Set NAN test value
    b[n - 1] = numeric_limits<float>::quiet_NaN();

    cout << "\nResults for CompareF32\n";
    cout << c_Dashes << '\n';

    for (size_t i = 0; i < n; i++)
    {
        bool cmp_results[c_NumOpStrings];

        CompareF32_(cmp_results, a[i], b[i]);
        PrintResults(cmp_results, a[i], b[i]);
    }
}

int main()
{
    CompareF32();
    return 0;
}
