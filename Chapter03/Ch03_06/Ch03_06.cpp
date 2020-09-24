//------------------------------------------------
//               Ch03_06.cpp
//------------------------------------------------

#include <iostream>

using namespace std;

const int c_ArgnMin = 1;
const int c_ArgnMax = 1023;

// Ch03_06_.s
extern "C" void CalcSum_(int n, int* sum1, int* sum2);

// Ch03_06_Misc.cpp
extern void PrintResult(const char* msg, int n, int sum1_cpp,
    int sum1_asm, int sum2_cpp, int sum2_asm);

static int CalcSum1(int n)
{
    int sum = 0;

    for (int i = 1; i <= n; i++)
        sum += i * i;
    return sum;
}

static int CalcSum2(int n)
{
    int sum = (n * (n + 1) * (2 * n + 1)) / 6;
    return sum;
}

void CalcSum(int n, int* sum1, int* sum2)
{
    *sum1 = *sum2 = 0;

    if (n < c_ArgnMin || n > c_ArgnMax)
        return;

    *sum1 = CalcSum1(n);
    *sum2 = CalcSum2(n);
    return;
}

int main(int argc, char** argv)
{
    int n;
    int sum1_cpp, sum1_asm;
    int sum2_cpp, sum2_asm;

    n = 3;
    CalcSum(n, &sum1_cpp, &sum2_cpp);
    CalcSum_(n, &sum1_asm, &sum2_asm);
    PrintResult("CalcSum - Test Case #1",
        n, sum1_cpp, sum1_asm, sum2_cpp, sum2_asm);

    n = 7;
    CalcSum(n, &sum1_cpp, &sum2_cpp);
    CalcSum_(n, &sum1_asm, &sum2_asm);
    PrintResult("CalcSum - Test Case #2",
        n, sum1_cpp, sum1_asm, sum2_cpp, sum2_asm);

    n = 17;
    CalcSum(n, &sum1_cpp, &sum2_cpp);
    CalcSum_(n, &sum1_asm, &sum2_asm);
    PrintResult("CalcSum - Test Case #3",
        n, sum1_cpp, sum1_asm, sum2_cpp, sum2_asm);

    n = 40;
    CalcSum(n, &sum1_cpp, &sum2_cpp);
    CalcSum_(n, &sum1_asm, &sum2_asm);
    PrintResult("CalcSum - Test Case #4",
        n, sum1_cpp, sum1_asm, sum2_cpp, sum2_asm);

    return 0;
}
