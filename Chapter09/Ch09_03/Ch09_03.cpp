//-------------------------------------------------
//               Ch09_03.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Vec128.h"

using namespace std;

// The values enum CvtOp must match the jump table
// that's defined in Ch09_03_.s.
enum CvtOp : unsigned int
{
    F32_I32 = 0, I32_F32 = 1, F32_U32 = 2, U32_F32 = 3
};

extern "C" bool PackedConvertF32_(Vec128& x, const Vec128& a, CvtOp cvt_op);

void PackedConvertF32(void)
{
    const char nl = '\n';
    bool rc;
    Vec128 x, a;

    // F32_I32
    a.m_I32[0] = 10;
    a.m_I32[1] = -500;
    a.m_I32[2] = 600;
    a.m_I32[3] = -1024;
    rc = PackedConvertF32_(x, a, CvtOp::F32_I32);
    cout << "\nResults for CvtOp::F32_I32\n";
    cout << "rc: " << boolalpha << rc << nl;
    cout << "a:  " << a.ToStringI32() << nl;
    cout << "b:  " << x.ToStringF32() << nl;

    // I32_F32
    a.m_F32[0] = -1.25;
    a.m_F32[1] = 100.875;
    a.m_F32[2] = -200.0;
    a.m_F32[3] = (float)M_PI;
    rc = PackedConvertF32_(x, a, CvtOp::I32_F32);
    cout << "\nResults for CvtOp::I32_F32\n";
    cout << "rc: " << boolalpha << rc << nl;
    cout << "a:  " << a.ToStringF32() << nl;
    cout << "b:  " << x.ToStringI32() << nl;

    // F32_U32
    a.m_U32[0] = 10;
    a.m_U32[1] = 40000;
    a.m_U32[2] = 600;
    a.m_U32[3] = 200000;
    rc = PackedConvertF32_(x, a, CvtOp::F32_U32);
    cout << "\nResults for CvtOp::F32_U32\n";
    cout << "rc: " << boolalpha << rc << nl;
    cout << "a:  " << a.ToStringU32() << nl;
    cout << "b:  " << x.ToStringF32() << nl;

    // U32_F32
    a.m_F32[0] = 10.0f;
    a.m_F32[1] = 0.625;
    a.m_F32[2] = (float)M_SQRT2;
    a.m_F32[3] = 400.75;
    rc = PackedConvertF32_(x, a, CvtOp::U32_F32);
    cout << "\nResults for CvtOp::U32_F32\n";
    cout << "rc: " << boolalpha << rc << nl;
    cout << "a:  " << a.ToStringF32() << nl;
    cout << "b:  " << x.ToStringU32() << nl;
}

int main()
{
    PackedConvertF32();
    return 0;
}
