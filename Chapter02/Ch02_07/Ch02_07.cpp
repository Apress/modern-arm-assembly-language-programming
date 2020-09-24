//------------------------------------------------
//               Ch02_07.cpp
//------------------------------------------------

#include <iostream>

using namespace std;

// Ch02_07_.s
extern "C" void TestBitOpsA_(unsigned int a, unsigned int b, unsigned int* c);
extern "C" void TestBitOpsB_(unsigned int a, unsigned int* b);

// Ch02_07_Misc.cpp
extern void PrintResultA(const char* msg, unsigned int a, unsigned int b, const unsigned int* c, size_t n);
extern void PrintResultB(const char* msg, unsigned int a, const unsigned int* b, size_t n);

int main(int argc, char** argv)
{
    // Exercise function TestBitOpsA_
    const size_t n = 3;
    unsigned int a1 = 0x12345678;
    unsigned int b1 = 0xaa55aa55;
    unsigned int c1[n];
    TestBitOpsA_(a1, b1, c1);
    PrintResultA("TestBitOpsA_ Test Case #1", a1, b1, c1, n);

    unsigned int a2 = 0x12345678;
    unsigned int b2 = 0x00ffc384;
    unsigned int c2[n];
    TestBitOpsA_(a2, b2, c2);
    PrintResultA("TestBitOpsA_ Test Case #2", a2, b2, c2, n);

    cout << "\n";

    // Exercise function TestBitOpsB_
    const size_t nn = 4;
    unsigned int a3 = 0x12345678;
    unsigned int b3[nn];
    TestBitOpsB_(a3, b3);
    PrintResultB("TestBitOpsB_ Test Case #1", a3, b3, nn);

    unsigned int a4 = 0xaa55aa55;
    unsigned int b4[nn];
    TestBitOpsB_(a4, b4);
    PrintResultB("TestBitOpsB_ Test Case #2", a4, b4, nn);

    return 0;
}
