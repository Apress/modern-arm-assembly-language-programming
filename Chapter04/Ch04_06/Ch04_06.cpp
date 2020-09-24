//-------------------------------------------------
//               Ch04_06.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cstddef>

using namespace std;

struct TestStruct
{
    int8_t ValA;
    int8_t ValB;
    int32_t ValC;
    int16_t ValD;
    int32_t ValE;
    uint8_t ValF;
    uint16_t ValG;
};

extern "C" int32_t CalcTestStructSum_(const TestStruct* ts);

void PrintTestStructOffsets(void)
{
    const char nl = '\n';

    cout << "offsetof(ts.ValA) = " << offsetof(TestStruct, ValA) << nl;
    cout << "offsetof(ts.ValB) = " << offsetof(TestStruct, ValB) << nl;
    cout << "offsetof(ts.ValC) = " << offsetof(TestStruct, ValC) << nl;
    cout << "offsetof(ts.ValD) = " << offsetof(TestStruct, ValD) << nl;
    cout << "offsetof(ts.ValE) = " << offsetof(TestStruct, ValE) << nl;
    cout << "offsetof(ts.ValF) = " << offsetof(TestStruct, ValF) << nl;
    cout << "offsetof(ts.ValG) = " << offsetof(TestStruct, ValG) << nl;
}

int32_t CalcTestStructSum(const TestStruct* ts)
{
    int32_t temp1 = ts->ValA + ts->ValB + ts->ValC + ts->ValD;
    int32_t temp2 = ts->ValE + ts->ValF + ts->ValG;

    return temp1 + temp2;
}

int main()
{
    const char nl = '\n';
    PrintTestStructOffsets();

    TestStruct ts;
    ts.ValA = -100;
    ts.ValB = 75;
    ts.ValC = 1000000;
    ts.ValD = -3000;
    ts.ValE = 400000;
    ts.ValF = 200;
    ts.ValG = 50000;

    int32_t sum1 = CalcTestStructSum(&ts);
    int32_t sum2 = CalcTestStructSum_(&ts);

    cout << nl << "Results for CalcTestStructSum" << nl;
    cout << "ts1.ValA = " << (int)ts.ValA << nl;
    cout << "ts1.ValB = " << (int)ts.ValB << nl;
    cout << "ts1.ValC = " << ts.ValC << nl;
    cout << "ts1.ValD = " << ts.ValD << nl;
    cout << "ts1.ValE = " << ts.ValE << nl;
    cout << "ts1.ValF = " << (int)ts.ValF << nl;
    cout << "ts1.ValG = " << ts.ValG << nl;
    cout << "sum1 =     " << sum1 << nl;
    cout << "sum2 =     " << sum2 << nl;

    if (sum1 != sum2)
        cout << "Compare error!" << nl;

    return 0;
}
