//-------------------------------------------------
//               Ch15_02.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Vec128.h"

using namespace std;

extern "C" void PackedCompareF32_(Vec128 x[8], const Vec128& a, const Vec128& b);
extern "C" void PackedCompareF64_(Vec128 x[8], const Vec128& a, const Vec128& b);

const char* c_CmpStr[8] =
{
    "EQ", "NE", "GT", "GE", "LT", "LE", "a LT0", "b GT0"
};

void PackedCompareF32(void)
{
    const char nl = '\n';
    Vec128 x[8], a, b;

    a.m_F32[0] = 2.0;         b.m_F32[0] = -4.0;
    a.m_F32[1] = 17.0;        b.m_F32[1] = 12.0;
    a.m_F32[2] = -6.0;        b.m_F32[2] = -6.0;
    a.m_F32[3] = 3.0;         b.m_F32[3] = 8.0;

    PackedCompareF32_(x, a, b);

    cout << "\nResults for PackedCompareF32_\n";
    cout << setw(11) << 'a' << ':' << a.ToStringF32() << nl;
    cout << setw(11) << 'b' << ':' << b.ToStringF32() << nl;
    cout << nl;

    for (int j = 0; j < 8; j++)
        cout << setw(11) << c_CmpStr[j] << ':' << x[j].ToStringX32() << nl;
}

void PackedCompareF64(void)
{
    const char nl = '\n';
    Vec128 x[8], a, b;

    a.m_F64[0] = -2.0;        b.m_F64[0] = -4.0;
    a.m_F64[1] = M_SQRT2;     b.m_F64[1] = M_PI;

    PackedCompareF64_(x, a, b);

    cout << "\nResults for PackedCompareF64_\n";
    cout << setw(11) << 'a' << ':' << a.ToStringF64() << nl;
    cout << setw(11) << 'b' << ':' << b.ToStringF64() << nl;
    cout << nl;

    for (int j = 0; j < 8; j++)
        cout << setw(11) << c_CmpStr[j] << ':' << x[j].ToStringX64() << nl;
}

int main()
{
    PackedCompareF32();
    PackedCompareF64();
    return 0;
}
