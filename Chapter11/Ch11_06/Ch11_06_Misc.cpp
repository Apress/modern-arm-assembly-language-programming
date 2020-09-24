//-------------------------------------------------
//               Ch11_06_Misc.cpp
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <bitset>
#include <string>
#include <cstdint>

using namespace std;

string ToHexString(unsigned int a)
{
    ostringstream oss;

    oss << setfill('0');
    oss << "0x" << hex << setw(8) << a;
    return oss.str();
}

string ToBitString(unsigned int a)
{
    bitset<32> bs {a};
    size_t n = bs.size();
    stringstream oss;

    for (size_t i = 0; i < n; i++)
    {
        oss << bs[n - 1 - i];

        if ((i + 1) % 4 == 0)
            oss << ' ';
    }

    return oss.str();
}

void PrintResult(const char* msg, const uint32_t* x, uint32_t a, size_t n, int count)
{
    const char nl = '\n';
    string s1[] { "asr #2", "lsl #4", "lsr #5", "ror #3" }; 
    string s2[] { "asr", "lsl", "lsr", "ror" }; 

    if (count < 0)
        cout << nl << msg << nl;
    else
        cout << nl << msg << " - count = " << count << nl;

    cout << "a:    " << ToHexString(a);
    cout << " | " << ToBitString(a) << nl;

    for (size_t i = 0; i < n; i++)
    {
        cout << "x[" << i << "]: " << ToHexString(x[i]);
        cout << " | " << ToBitString(x[i]);
        cout << " | ";

        if (count < 0)
            cout << s1[i] << nl;
        else
            cout << s2[i] << nl;
    }
}
