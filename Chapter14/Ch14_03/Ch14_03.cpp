//-------------------------------------------------
//               Ch14_03.cpp
//-------------------------------------------------

#include <iostream>
#include <string>
#include "Vec128.h"

using namespace std;

extern "C" bool PackedMulA_(Vec128* x, const Vec128& a, const Vec128& b, int16_t c);

void PackedMulA(void)
{
    Vec128 x[4], a, b;
    const int16_t c = 5;
    const char nl = '\n';
    string sep(75, '-');

    a.m_I16[0] = 10;        b.m_I16[0] = 6;
    a.m_I16[1] = 7;         b.m_I16[1] = 13;
    a.m_I16[2] = -23;       b.m_I16[2] = -75;
    a.m_I16[3] = 41;        b.m_I16[3] = 9;
    a.m_I16[4] = 6;         b.m_I16[4] = 37;
    a.m_I16[5] = -33;       b.m_I16[5] = 28;
    a.m_I16[6] = 19;        b.m_I16[6] = 56;
    a.m_I16[7] = 16;        b.m_I16[7] = -18;

    PackedMulA_(x, a, b, c);

    cout << "\nPackedMulA_\n";
    cout << sep << nl;

    cout << "a:    " << a.ToStringI16() << nl;
    cout << "b:    " << b.ToStringI16() << nl << nl;
    cout << "x[0]: " << x[0].ToStringI16() << nl << nl;
    cout << "x[1]: " << x[1].ToStringI16() << nl << nl;
    cout << "x[2]: " << x[2].ToStringI32() << nl;
    cout << "x[3]: " << x[3].ToStringI32() << nl;
}

int main(void)
{
    PackedMulA();
    return 0;
}
