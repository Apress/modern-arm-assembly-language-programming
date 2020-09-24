//-------------------------------------------------
//               Ch09_01.cpp
//-------------------------------------------------

#include <iostream>
#include "Vec128.h"

using namespace std;

extern "C" void PackedMathF32_(Vec128 x[7], const Vec128& a, const Vec128& b);

void PackedMathF32(void)
{
    Vec128 x[7], a, b;
    const char nl = '\n';

    a.m_F32[0] = 36.0;              b.m_F32[0] = -0.125;
    a.m_F32[1] = 0.03125;           b.m_F32[1] = 64.0;
    a.m_F32[2] = 2.0;               b.m_F32[2] = -0.0625;
    a.m_F32[3] = -42.0;             b.m_F32[3] = 13.75;

    PackedMathF32_(x, a, b);

    cout << ("\nResults for PackedMathF32_\n");
    cout << "a:       " << a.ToStringF32() << nl;
    cout << "b:       " << b.ToStringF32() << nl;
    cout << nl;
    cout << "vadd:    " << x[0].ToStringF32() << nl;
    cout << "vsub:    " << x[1].ToStringF32() << nl;
    cout << "vmul:    " << x[2].ToStringF32() << nl;
    cout << "vabs(a): " << x[3].ToStringF32() << nl;
    cout << "vneg(b): " << x[4].ToStringF32() << nl;
    cout << "vminnm:  " << x[5].ToStringF32() << nl;
    cout << "vmaxnm:  " << x[6].ToStringF32() << nl;
}

int main()
{
    PackedMathF32();
    return 0;
}
