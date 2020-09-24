//------------------------------------------------
//               Ch02_05.cpp
//------------------------------------------------

#include <iostream>

using namespace std;

extern "C" int MoveImmA_(void);
extern "C" int MoveImmB_(void);
extern "C" int MoveImmC_(void);

int main(int argc, char** argv)
{
    int a = MoveImmA_();
    int b = MoveImmB_();
    int c = MoveImmC_();

    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';
    cout << "c = " << c << '\n';

    return 0;
}
