//-------------------------------------------------
//               Ch09_02.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <limits>
#include "Vec128.h"

using namespace std;

extern "C" void PackedCompareF32_(Vec128 x[8], const Vec128& a, const Vec128& b);

const char* c_CmpStr[8] =
{
    "EQ", "NE", "LT", "LE", "GT", "GE", "LT0", "GT0"
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

    cout << "\nResults for PackedCompareF32\n";
    cout << "a:  " << a.ToStringF32() << nl;
    cout << "b:  " << b.ToStringF32() << nl;
    cout << nl;

    for (int j = 0; j < 8; j++)
    {
        string s = string(c_CmpStr[j]) + ":";
        cout << left << setw(4) << s << x[j].ToStringX32() << nl;
    }
}

int main()
{
    PackedCompareF32();
    return 0;
}
