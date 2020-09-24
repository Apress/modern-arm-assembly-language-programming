//-------------------------------------------------
//               Ch11_06.cpp
//-------------------------------------------------

#include <iostream>
#include <cstdint>

using namespace std;

// Ch11_06_Misc.cpp
extern void PrintResult(const char* msg, const uint32_t* x, uint32_t a,
    size_t n, int count = -1);

// Ch11_06_.s
extern "C" void ShiftA_(uint32_t* x, uint32_t a);
extern "C" void ShiftB_(uint32_t* x, uint32_t a, uint32_t count);

void ShiftA(void)
{
    const size_t n = 4;

    uint32_t a = 0xC1234561;
    uint32_t x[4];
    ShiftA_(x, a);
    PrintResult("ShiftA_", x, a, n);
}

void ShiftB(void)
{
    const size_t n = 4;

    uint32_t a = 0xC1234561;
    uint32_t x[4];
    uint32_t count = 8;
    ShiftB_(x, a, count);
    PrintResult("ShiftB_", x, a, n, (int)count);
}

int main(int argc, char** argv)
{
    ShiftA();
    ShiftB();
    return 0;
}
