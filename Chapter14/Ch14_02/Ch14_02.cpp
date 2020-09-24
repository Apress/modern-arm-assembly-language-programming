//-------------------------------------------------
//               Ch14_02.cpp
//-------------------------------------------------

#include <iostream>
#include "Vec128.h"

using namespace std;

extern "C" bool PackedShiftA_(Vec128* x, const Vec128& a);
extern "C" bool PackedShiftB_(Vec128* x, const Vec128& a, const Vec128& b);
extern "C" bool PackedShiftC_(Vec128* x, const Vec128& a);

void PackedShiftA(void)
{
    Vec128 x[3], a;
    const char nl = '\n';

    a.m_U16[0] = 0x1234;
    a.m_U16[1] = 0xFF9B;
    a.m_U16[2] = 0x00CC;
    a.m_U16[3] = 0xBD98;
    a.m_U16[4] = 0x00FF;
    a.m_U16[5] = 0xAAAA;
    a.m_U16[6] = 0x0F0F;
    a.m_U16[7] = 0x0065;

    PackedShiftA_(x, a);
    cout << "\nPackedShiftA_ (shl 4, sshr 2, ushr 3)\n";
    cout << "a:    " << a.ToStringX16() << nl;
    cout << "x[0]: " << x[0].ToStringX16() << nl;
    cout << "x[1]: " << x[1].ToStringX16() << nl;
    cout << "x[2]: " << x[2].ToStringX16() << nl;
}

void PackedShiftB(void)
{
    Vec128 x[2], a, b;
    const char nl = '\n';

    a.m_U16[0] = 0x1234;    b.m_I16[0] = 3;
    a.m_U16[1] = 0xFF9B;    b.m_I16[1] = -4;
    a.m_U16[2] = 0x00CC;    b.m_I16[2] = 2;
    a.m_U16[3] = 0xBD98;    b.m_I16[3] = -6;
    a.m_U16[4] = 0x00FF;    b.m_I16[4] = 7;
    a.m_U16[5] = 0xAAAA;    b.m_I16[5] = 1;
    a.m_U16[6] = 0x0F0F;    b.m_I16[6] = -2;
    a.m_U16[7] = 0x0065;    b.m_I16[7] = 5;

    PackedShiftB_(x, a, b);
    cout << "\nPackedShiftB_ (sshl, ushl)\n";
    cout << "a:    " << a.ToStringX16() << nl;
    cout << "b:    " << b.ToStringI16() << nl;
    cout << "x[0]: " << x[0].ToStringX16() << nl;
    cout << "x[1]: " << x[1].ToStringX16() << nl;
}

void PackedShiftC(void)
{
    Vec128 x[4], a;
    const char nl = '\n';

    a.m_U16[0] = 0x1234;
    a.m_U16[1] = 0xFF9B;
    a.m_U16[2] = 0x00CC;
    a.m_U16[3] = 0xEA98;
    a.m_U16[4] = 0x00FF;
    a.m_U16[5] = 0xAAAA;
    a.m_U16[6] = 0x0F0F;
    a.m_U16[7] = 0x0065;

    PackedShiftC_(x, a);
    cout << "\nPackedShiftC_ (sshll 4, sshll2 4, ushll 4, ushll2 4)\n";
    cout << "a:    " << a.ToStringX16() << nl;
    cout << "x[0]: " << x[0].ToStringX32() << nl;
    cout << "x[1]: " << x[1].ToStringX32() << nl;
    cout << "x[2]: " << x[2].ToStringX32() << nl;
    cout << "x[3]: " << x[3].ToStringX32() << nl;
}

int main(void)
{
    string sep(75, '-');

    PackedShiftA();
    cout << '\n' << sep << '\n';
    PackedShiftB();
    cout << '\n' << sep << '\n';
    PackedShiftC();
    return 0;
}

