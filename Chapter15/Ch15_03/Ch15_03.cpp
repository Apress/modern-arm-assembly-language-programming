//-------------------------------------------------
//               Ch15_03.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include "Vec128.h"

using namespace std;

// The order of values in the following enum must match the jump table
// that's defined in Ch15_03_.s.
enum CvtOp : unsigned int
{
    F32_I32, I32_F32,
    F64_I64, I64_F64,
    F32_U32, U32_F32,
    F64_U64, U64_F64,
    F32_F64, F64_F32
};

extern "C" bool PackedConvert_(Vec128 x[2], const Vec128& a, CvtOp cvt_op, const Vec128* b = nullptr);

void PackedConvertA(void)
{
    const char nl = '\n';
    Vec128 x[2], a;

    // F32_I32
    a.m_I32[0] = 10;
    a.m_I32[1] = -500;
    a.m_I32[2] = 600;
    a.m_I32[3] = -1024;
    PackedConvert_(x, a, CvtOp::F32_I32);
    cout << "\nResults for CvtOp::F32_I32\n";
    cout << "a:    " << a.ToStringI32() << nl;
    cout << "x[0]: " << x[0].ToStringF32() << nl;

    // I32_F32
    a.m_F32[0] = -1.25f;
    a.m_F32[1] = 100.875f;
    a.m_F32[2] = -200.0f;
    a.m_F32[3] = (float)M_PI;
    PackedConvert_(x, a, CvtOp::I32_F32);
    cout << "\nResults for CvtOp::I32_F32\n";
    cout << "a:    " << a.ToStringF32() << nl;
    cout << "x[0]: " << x[0].ToStringI32() << nl;

    // F64_I64
    a.m_I64[0] = 1000;
    a.m_I64[1] = -500000000000;
    PackedConvert_(x, a, CvtOp::F64_I64);
    cout << "\nResults for CvtOp::F64_I64\n";
    cout << "a:    " << a.ToStringI64() << nl;
    cout << "x[0]: " << x[0].ToStringF64() << nl;

    // I64_F64
    a.m_F64[0] = -122.66666667;
    a.m_F64[1] = 1234567890123.75;
    PackedConvert_(x, a, CvtOp::I64_F64);
    cout << "\nResults for CvtOp::I64_F64\n";
    cout << "a:    " << a.ToStringF64() << nl;
    cout << "x[0]: " << x[0].ToStringI64() << nl;
}

void PackedConvertB(void)
{
    const char nl = '\n';
    Vec128 x[2], a;

    // F32_U32
    a.m_U32[0] = 10;
    a.m_U32[1] = 500;
    a.m_U32[2] = 600;
    a.m_U32[3] = 1024;
    PackedConvert_(x, a, CvtOp::F32_U32);
    cout << "\nResults for CvtOp::F32_U32\n";
    cout << "a:    " << a.ToStringU32() << nl;
    cout << "x[0]: " << x[0].ToStringF32() << nl;

    // U32_F32
    a.m_F32[0] = 1.25f;
    a.m_F32[1] = 100.875f;
    a.m_F32[2] = 200.0f;
    a.m_F32[3] = (float)M_PI;
    PackedConvert_(x, a, CvtOp::U32_F32);
    cout << "\nResults for CvtOp::U32_F32\n";
    cout << "a:    " << a.ToStringF32() << nl;
    cout << "x[0]: " << x[0].ToStringU32() << nl;

    // F64_U64
    a.m_I64[0] = 1000;
    a.m_I64[1] = 420000000000;
    PackedConvert_(x, a, CvtOp::F64_U64);
    cout << "\nResults for CvtOp::F64_U64\n";
    cout << "a:    " << a.ToStringU64() << nl;
    cout << "x[0]: " << x[0].ToStringF64() << nl;

    // U64_F64
    a.m_F64[0] = 698.40;
    a.m_F64[1] = 1234567890123.75;
    PackedConvert_(x, a, CvtOp::U64_F64);
    cout << "\nResults for CvtOp::U64_F64\n";
    cout << "a:    " << a.ToStringF64() << nl;
    cout << "x[0]: " << x[0].ToStringU64() << nl;
}

void PackedConvertC(void)
{
    const char nl = '\n';
    Vec128 x[2], a, b;

    // F32_F64
    a.m_F64[0] = M_PI;
    a.m_F64[1] = M_LOG10E;
    b.m_F64[0] = -M_E;
    b.m_F64[1] = M_LN2;
    PackedConvert_(x, a, CvtOp::F32_F64, &b);
    cout << "\nResults for CvtOp::F32_F64\n";
    cout << "a:    " << a.ToStringF64() << nl;
    cout << "b:    " << b.ToStringF64() << nl;
    cout << "x[0]: " << x[0].ToStringF32() << nl;

    // F64_F32
    a.m_F32[0] = 1.0f / 9.0f;
    a.m_F32[1] = 100.875f;
    a.m_F32[2] = 200.0f;
    a.m_F32[3] = (float)M_SQRT2;
    PackedConvert_(x, a, CvtOp::F64_F32);
    cout << "\nResults for CvtOp::F64_F32\n";
    cout << "a:    " << a.ToStringF32() << nl;
    cout << "x[0]: " << x[0].ToStringF64() << nl;
    cout << "x[1]: " << x[1].ToStringF64() << nl;
}

int main()
{
    PackedConvertA();
    PackedConvertB();
    PackedConvertC();
    return 0;
}

