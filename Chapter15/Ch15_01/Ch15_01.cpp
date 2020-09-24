//-------------------------------------------------
//               Ch15_01.cpp
//-------------------------------------------------

#include <iostream>
#include <cmath>
#include "Vec128.h"

using namespace std;

extern "C" void PackedMathF32_(Vec128 x[9], const Vec128& a, const Vec128& b);
extern "C" void PackedMathF64_(Vec128 x[9], const Vec128& a, const Vec128& b);

void PackedMathF32(void)
{
    const char nl = '\n';
    Vec128 x[9], a, b;

    a.m_F32[0] = 36.0f;                b.m_F32[0] = -1.0f / 9.0f;
    a.m_F32[1] = 1.0f / 32.0f;         b.m_F32[1] = 64.0f;
    a.m_F32[2] = 2.0f;                 b.m_F32[2] = -0.0625f;
    a.m_F32[3] = 42.0f;                b.m_F32[3] = 8.666667f;

    PackedMathF32_(x, a, b);

    cout << ("\nResults for PackedMathF32_\n");
    cout << "a:        " << a.ToStringF32() << nl;
    cout << "b:        " << b.ToStringF32() << nl;
    cout << nl;
    cout << "fadd:     " << x[0].ToStringF32() << nl;
    cout << "fsub:     " << x[1].ToStringF32() << nl;
    cout << "fmul:     " << x[2].ToStringF32() << nl;
    cout << "fdiv:     " << x[3].ToStringF32() << nl;
    cout << "fabs(a):  " << x[4].ToStringF32() << nl;
    cout << "fneg(b):  " << x[5].ToStringF32() << nl;
    cout << "fminnm:   " << x[6].ToStringF32() << nl;
    cout << "fmaxnm:   " << x[7].ToStringF32() << nl;
    cout << "fsqrt(a): " << x[8].ToStringF32() << nl;
}

void PackedMathF64(void)
{
    const char nl = '\n';
    Vec128 x[9], a, b;

    a.m_F64[0] = 36.0;              b.m_F64[0] = -M_SQRT2;
    a.m_F64[1] = M_PI;              b.m_F64[1] = 2.0;

    PackedMathF64_(x, a, b);

    cout << ("\nResults for PackedMathF64_\n");
    cout << "a:        " << a.ToStringF64() << nl;
    cout << "b:        " << b.ToStringF64() << nl;
    cout << nl;
    cout << "fadd:     " << x[0].ToStringF64() << nl;
    cout << "fsub:     " << x[1].ToStringF64() << nl;
    cout << "fmul:     " << x[2].ToStringF64() << nl;
    cout << "fdiv:     " << x[3].ToStringF64() << nl;
    cout << "fabs(a):  " << x[4].ToStringF64() << nl;
    cout << "fneg(b):  " << x[5].ToStringF64() << nl;
    cout << "fminnm:   " << x[6].ToStringF64() << nl;
    cout << "fmaxnm:   " << x[7].ToStringF64() << nl;
    cout << "fsqrt(a): " << x[8].ToStringF64() << nl;
}

int main()
{
    PackedMathF32();
    PackedMathF64();
    return 0;
}
