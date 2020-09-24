//-------------------------------------------------
//               Ch11_07.cpp
//-------------------------------------------------

#include <iostream>
#include <cstdint>

using namespace std;

// Ch11_07_Misc.cpp
extern void PrintResultA(const char* msg, const uint32_t* x, uint32_t a, uint32_t b, size_t n);
extern void PrintResultB(const char* msg, const uint32_t* x, uint32_t a, size_t n);

// Ch11_07_.s
extern "C" void BitwiseOpsA_(uint32_t* x, uint32_t a, uint32_t b);
extern "C" void BitwiseOpsB_(uint32_t* x, uint32_t a);

void BitwiseOpsA(void)
{
    const size_t n = 3;
    uint32_t a, b, x[n];

    a = 0x12345678;
    b = 0xaa55aa55;
    BitwiseOpsA_(x, a, b);
    PrintResultA("BitwiseOpsA_ Test #1", x, a, b, n);

    a = 0x12345678;
    b = 0x00ffc384;
    BitwiseOpsA_(x, a, b);
    PrintResultA("BitwiseOpsA_ Test #2", x, a, b, n);
}

void BitwiseOpsB(void)
{
    const size_t n = 4;
    uint32_t a, x[n];

    a = 0x12345678;
    BitwiseOpsB_(x, a);
    PrintResultB("BitwiseOpsB_ Test #1", x, a, n);

    a = 0xaa55aa55;
    BitwiseOpsB_(x, a);
    PrintResultB("BitwiseOpsB_ Test #2", x, a, n);
}

int main(int argc, char** argv)
{
    BitwiseOpsA();
    cout << "\n";
    BitwiseOpsB();
    return 0;
}

