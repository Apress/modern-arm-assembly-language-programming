//-------------------------------------------------
//               Ch08_02.cpp
//-------------------------------------------------

#include <iostream>
#include "Vec128.h"

using namespace std;

extern "C" bool PackedShiftA_(Vec128* x, const Vec128& a);
extern "C" bool PackedShiftB_(Vec128* x, const Vec128& a, const Vec128& b);
extern "C" bool PackedShiftC_(Vec128* x, const Vec128& a, const Vec128& b);

void PackedShiftA(void)
{
    const char nl = '\n';
    Vec128 x[2], a;

    a.m_U16[0] = 0x1234;
    a.m_U16[1] = 0xFF9B;
    a.m_U16[2] = 0x00CC;
    a.m_U16[3] = 0xBD98;
    a.m_U16[4] = 0x00FF;
    a.m_U16[5] = 0xAAAA;
    a.m_U16[6] = 0x0F0F;
    a.m_U16[7] = 0x0065;

    PackedShiftA_(x, a);
    cout << "\nPackedShiftA_ (vshl.u16, vshr.u16, immediate)\n";
    cout << "a:    " << a.ToStringX16() << nl;
    cout << "x[0]: " << x[0].ToStringX16() << nl;
    cout << "x[1]: " << x[1].ToStringX16() << nl;
}

void PackedShiftB(void)
{
    const char nl = '\n';
    Vec128 x, a, b;

    a.m_U16[0] = 0x1234;    b.m_I16[0] = 3;
    a.m_U16[1] = 0xFF9B;    b.m_I16[1] = -4;
    a.m_U16[2] = 0x00CC;    b.m_I16[2] = 2;
    a.m_U16[3] = 0xBD98;    b.m_I16[3] = -6;
    a.m_U16[4] = 0x00FF;    b.m_I16[4] = 7;
    a.m_U16[5] = 0xAAAA;    b.m_I16[5] = 1;
    a.m_U16[6] = 0x0F0F;    b.m_I16[6] = -2;
    a.m_U16[7] = 0x0065;    b.m_I16[7] = 5;

    PackedShiftB_(&x, a, b);
    cout << "\nPackedShiftB_ (vshl.u16, register)\n";
    cout << "a:    " << a.ToStringX16() << nl;
    cout << "b:    " << b.ToStringI16() << nl;
    cout << "x:    " << x.ToStringX16() << nl;
}

void PackedShiftC(void)
{
    const char nl = '\n';
    Vec128 x[3], a, b;

    a.m_I16[0] = 4660;      b.m_I16[0] = 4;
    a.m_I16[1] = -105;      b.m_I16[1] = -2;
    a.m_I16[2] = 204;       b.m_I16[2] = 3;
    a.m_I16[3] = -17000;    b.m_I16[3] = 2;
    a.m_I16[4] = 255;       b.m_I16[4] = 4;
    a.m_I16[5] = -21846;    b.m_I16[5] = -1;
    a.m_I16[6] = 3855;      b.m_I16[6] = 8;
    a.m_I16[7] = 101;       b.m_I16[7] = -3;

    PackedShiftC_(x, a, b);
    cout << "\nPackedShiftC_ (vshl.s16, vqshl.s16, vrshl.s16)\n";
    cout << "a:    " << a.ToStringI16() << nl;
    cout << "b:    " << b.ToStringI16() << nl;
    cout << "x[0]: " << x[0].ToStringI16() << nl;
    cout << "x[1]: " << x[1].ToStringI16() << nl;
    cout << "x[2]: " << x[2].ToStringI16() << nl;
}

int main(void)
{
    const char nl = '\n';
    string sep(75, '-');

    PackedShiftA();
    cout << '\n' << sep << nl;
    PackedShiftB();
    cout << '\n' << sep << nl;
    PackedShiftC();
    return 0;
}
