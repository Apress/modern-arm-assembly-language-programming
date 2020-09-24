//-------------------------------------------------
//               Ch14_01.cpp
//-------------------------------------------------

#include <iostream>
#include <string>
#include "Vec128.h"

using namespace std;

extern "C" void PackedAddI16_(Vec128 x[2], const Vec128& a, const Vec128& b);
extern "C" void PackedSubI16_(Vec128 x[2], const Vec128& a, const Vec128& b);
extern "C" void PackedAddU16_(Vec128 x[2], const Vec128& a, const Vec128& b);
extern "C" void PackedSubU16_(Vec128 x[2], const Vec128& a, const Vec128& b);

// Signed packed addition and subtraction
void PackedAddI16(void)
{
    Vec128 x[2], a, b;
    const char nl = '\n';

    a.m_I16[0] = 10;          b.m_I16[0] = 100;
    a.m_I16[1] = 200;         b.m_I16[1] = -200;
    a.m_I16[2] = 30;          b.m_I16[2] = 32760;
    a.m_I16[3] = -32766;      b.m_I16[3] = -400;
    a.m_I16[4] = 50;          b.m_I16[4] = 500;
    a.m_I16[5] = 60;          b.m_I16[5] = -600;
    a.m_I16[6] = 32000;       b.m_I16[6] = 1200;
    a.m_I16[7] = -32000;      b.m_I16[7] = -950;

    PackedAddI16_(x, a, b);

    cout << "\nResults for PackedAddI16 - Wraparound Addition\n";
    cout << "a:     " << a.ToStringI16() << nl;
    cout << "b:     " << b.ToStringI16() << nl;
    cout << "x[0]:  " << x[0].ToStringI16() << nl;
    cout << "\nResults for PackedAddI16 - Saturated Addition\n";
    cout << "a:     " << a.ToStringI16() << nl;
    cout << "b:     " << b.ToStringI16() << nl;
    cout << "x[1]:  " << x[1].ToStringI16() << nl;
}

void PackedSubI16(void)
{
    Vec128 x[2], a, b;
    const char nl = '\n';

    a.m_I16[0] = 10;          b.m_I16[0] = 100;
    a.m_I16[1] = 200;         b.m_I16[1] = -200;
    a.m_I16[2] = -30;         b.m_I16[2] = 32760;
    a.m_I16[3] = -32766;      b.m_I16[3] = 400;
    a.m_I16[4] = 50;          b.m_I16[4] = 500;
    a.m_I16[5] = 60;          b.m_I16[5] = -600;
    a.m_I16[6] = 32000;       b.m_I16[6] = 1200;
    a.m_I16[7] = -32000;      b.m_I16[7] = 950;

    PackedSubI16_(x, a, b);

    cout << "\nResults for PackedSubI16 - Wraparound Subtraction\n";
    cout << "a:     " << a.ToStringI16() << nl;
    cout << "b:     " << b.ToStringI16() << nl;
    cout << "x[0]:  " << x[0].ToStringI16() << nl;
    cout << "\nResults for PackedSubI16 - Saturated Subtraction\n";
    cout << "a:     " << a.ToStringI16() << nl;
    cout << "b:     " << b.ToStringI16() << nl;
    cout << "x[1]:  " << x[1].ToStringI16() << nl;
}

// Unsigned packed addition and subtraction
void PackedAddU16(void)
{
    Vec128 x[2], a, b;
    const char nl = '\n';

    a.m_U16[0] = 10;          b.m_U16[0] = 100;
    a.m_U16[1] = 200;         b.m_U16[1] = 200;
    a.m_U16[2] = 300;         b.m_U16[2] = 65530;
    a.m_U16[3] = 32766;       b.m_U16[3] = 40000;
    a.m_U16[4] = 50;          b.m_U16[4] = 500;
    a.m_U16[5] = 20000;       b.m_U16[5] = 25000;
    a.m_U16[6] = 32000;       b.m_U16[6] = 1200;
    a.m_U16[7] = 32000;       b.m_U16[7] = 50000;

    PackedAddU16_(x, a, b);

    cout << "\nResults for PackedAddU16 - Wraparound Addition\n";
    cout << "a:     " << a.ToStringU16() << nl;
    cout << "b:     " << b.ToStringU16() << nl;
    cout << "x[0]:  " << x[0].ToStringU16() << nl;
    cout << "\nResults for PackedAddU16 - Saturated Addition\n";
    cout << "a:     " << a.ToStringU16() << nl;
    cout << "b:     " << b.ToStringU16() << nl;
    cout << "x[1]:  " << x[1].ToStringU16() << nl;
}

void PackedSubU16(void)
{
    Vec128 x[2], a, b;
    const char nl = '\n';

    a.m_U16[0] = 10;          b.m_U16[0] = 100;
    a.m_U16[1] = 200;         b.m_U16[1] = 200;
    a.m_U16[2] = 30;          b.m_U16[2] = 7;
    a.m_U16[3] = 65000;       b.m_U16[3] = 5000;
    a.m_U16[4] = 60;          b.m_U16[4] = 500;
    a.m_U16[5] = 25000;       b.m_U16[5] = 28000;
    a.m_U16[6] = 32000;       b.m_U16[6] = 1200;
    a.m_U16[7] = 1200;        b.m_U16[7] = 950;

    PackedSubU16_(x, a, b);

    cout << "\nResults for PackedSubU16 - Wraparound Subtraction\n";
    cout << "a:     " << a.ToStringU16() << nl;
    cout << "b:     " << b.ToStringU16() << nl;
    cout << "x[0]:  " << x[0].ToStringU16() << nl;
    cout << "\nResults for PackedSubI16 - Saturated Subtraction\n";
    cout << "a:     " << a.ToStringU16() << nl;
    cout << "b:     " << b.ToStringU16() << nl;
    cout << "x[1]:  " << x[1].ToStringU16() << nl;
}

int main()
{
    string sep(75, '-');
    const char nl = '\n';

    PackedAddI16();
    PackedSubI16();
    cout << nl << sep << nl;
    PackedAddU16();
    PackedSubU16();
    return 0;
}
