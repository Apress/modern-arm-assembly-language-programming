//-------------------------------------------------
//               Ch11_04.cpp
//-------------------------------------------------

#include <iostream>

using namespace std;

extern "C" int TestLDR1_(unsigned int i, unsigned long j);
extern "C" long TestLDR2_(unsigned int i, unsigned long j);
extern "C" short TestLDR3_(unsigned int i, unsigned long j);

void TestLDR1(void)
{
    const char nl = '\n';
    unsigned int i = 3;
    unsigned long j = 6;

    int test_ldr1 = TestLDR1_(i, j);

    cout << "TestLDR1_(" << i << ", " << j << ") = " << test_ldr1 << nl;
}

void TestLDR2(void)
{
    const char nl = '\n';
    unsigned int i = 2;
    unsigned long j = 7;

    long test_ldr2 = TestLDR2_(i, j);

    cout << "TestLDR2_(" << i << ", " << j << ") = " << test_ldr2 << nl;
}

void TestLDR3(void)
{
    const char nl = '\n';
    unsigned int i = 5;
    unsigned long j = 1;

    short test_ldr3 = TestLDR3_(i, j);

    cout << "TestLDR3_(" << i << ", " << j << ") = " << test_ldr3 << nl;
}

int main(int argc, char** argv)
{
    TestLDR1();
    TestLDR2();
    TestLDR3();
}

