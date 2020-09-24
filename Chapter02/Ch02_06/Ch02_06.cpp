//------------------------------------------------
//               Ch02_06.cpp
//------------------------------------------------

#include <iostream>

using namespace std;

// Ch02_06_.s
extern "C" void MoveRegA_(unsigned int a, unsigned int* b);
extern "C" void MoveRegB_(unsigned int a, unsigned int* b, unsigned int count);

// Ch02_06_Misc.cpp
extern void PrintResultA(const char* msg, unsigned int a, const unsigned int* b, size_t n);
extern void PrintResultB(const char* msg, unsigned int a, const unsigned int* b, size_t n, size_t count);

int main(int argc, char** argv)
{
    // Exercise function MoveRegA_
    const size_t n = 5;

    unsigned int a1 = 0x12345678;
    unsigned int b1[5];
    MoveRegA_(a1, b1);
    PrintResultA("MoveRegA_ Test Case #1", a1, b1, n);

    unsigned int a2 = 0xfedcba91;
    unsigned int b2[n];
    MoveRegA_(a2, b2);
    PrintResultA("MoveRegA_ Test Case #2", a2, b2, n);
    cout << "\n";

    // Exercise function MoveRegB_
    const size_t nn = 4;
    const size_t count = 8;

    unsigned int a3 = 0x12345678;
    unsigned int b3[nn];
    MoveRegB_(a3, b3, count);
    PrintResultB("MoveRegB_ Test Case #1", a3, b3, nn, count);

    unsigned int a4 = 0xfedcba91;
    unsigned int b4[nn];
    MoveRegB_(a4, b4, count);
    PrintResultB("MoveRegB_ Test Case #2", a4, b4, nn, count);

    return 0;
}
