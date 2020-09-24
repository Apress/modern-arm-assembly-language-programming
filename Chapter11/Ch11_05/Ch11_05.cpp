//-------------------------------------------------
//               Ch11_05.cpp
//-------------------------------------------------

#include <iostream>
#include <cstdint>

using namespace std;

extern "C" void MoveA_(int32_t& a0, int32_t& a1, int32_t& a2, int32_t& a3);
extern "C" void MoveB_(int64_t& b0, int64_t& b1, int64_t& b2, int64_t& b3);
extern "C" void MoveC_(int32_t& c0, int32_t& c1);
extern "C" void MoveD_(int64_t& d0, int64_t& d1, int64_t& d2);

int main(int argc, char** argv)
{
    const char nl = '\n';

    int32_t a0, a1, a2, a3;
    MoveA_(a0, a1, a2, a3);
    cout << "\nResults for MoveA_" << nl;
    cout << "a0 = " << a0 << nl;
    cout << "a1 = " << a1 << nl;
    cout << "a2 = " << a2 << nl;
    cout << "a3 = " << a3 << nl;

    int64_t b0, b1, b2, b3;
    MoveB_(b0, b1, b2, b3);
    cout << "\nResults for MoveB_" << nl;
    cout << "b0 = " << b0 << nl;
    cout << "b1 = " << b1 << nl;
    cout << "b2 = " << b2 << nl;
    cout << "b3 = " << b3 << nl;

    int32_t c0, c1;
    MoveC_(c0, c1);
    cout << "\nResults for MoveC_" << nl;
    cout << "c0 = " << c0 << nl;
    cout << "c1 = " << c1 << nl;

    int64_t d0, d1, d2;
    MoveD_(d0, d1, d2);
    cout << "\nResults for MoveD_" << nl;
    cout << "d0 = " << d0 << nl;
    cout << "d1 = " << d1 << nl;
    cout << "d2 = " << d2 << nl;

    return 0;
}
