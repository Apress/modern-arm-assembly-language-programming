//-------------------------------------------------
//
//-------------------------------------------------

//!! DOUBLE CHECK ROT/SHIFT INSTRUCTION TEXT STRINGS WITH CODE IN T06_.S

#include <iostream>
#include <iomanip>
#include <bitset>
#include <string>

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

void PrintResultA(const char* msg, unsigned int a, const unsigned int* b, size_t n)
{
    const char nl = '\n';
    string s[] { "asr #2", "lsl #4", "lsr #5", "ror #3", "rrx" }; 

    cout << nl << msg << nl;

    cout << "a:    " << ToHexString(a);
    cout << " | " << ToBitString(a) << nl;

    for (size_t i = 0; i < n; i++)
    {
        cout << "b[" << i << "]: " << ToHexString(b[i]);
        cout << " | " << ToBitString(b[i]);
        cout << " | " << s[i] << nl;
    }
}

void PrintResultB(const char* msg, unsigned int a, const unsigned int* b, size_t n, size_t count)
{
    const char nl = '\n';
    string s[] { "asr", "lsl", "lsr", "ror" }; 

    cout << nl << msg << " - count = " << count << nl;

    cout << "a:    " << ToHexString(a);
    cout << " | " << ToBitString(a) << nl;

    for (size_t i = 0; i < n; i++)
    {
        cout << "b[" << i << "]: " << ToHexString(b[i]);
        cout << " | " << ToBitString(b[i]);
        cout << " | " << s[i] << nl;
    }
}
