//-------------------------------------------------
//               Ch08_06_Misc.cpp
//-------------------------------------------------

#include <iostream>
#include <fstream>
#include "Ch08_06.h"

using namespace std;

void SaveItdEquates(void)
{
    const char nl = '\n';
    const char* fn = "Ch08_06_ITD_Equates.txt";

    ofstream ofs(fn);

    if (ofs.bad())
        ofs << "File create error - " << fn << nl;
    else
    {
        string s(12, ' ');

        ofs << s << ".equ S_PbSrc," << offsetof(ITD, PbSrc) << nl;
        ofs << s << ".equ S_PbMask," << offsetof(ITD, PbMask) << nl;
        ofs << s << ".equ S_NumPixels," << offsetof(ITD, NumPixels) << nl;
        ofs << s << ".equ S_NumMaskedPixels," << offsetof(ITD, NumMaskedPixels) << nl;
        ofs << s << ".equ S_SumMaskedPixels," << offsetof(ITD, SumMaskedPixels) << nl;
        ofs << s << ".equ S_Threshold," << offsetof(ITD, Threshold) << nl;
        ofs << s << ".equ S_MeanMaskedPixels," << offsetof(ITD, MeanMaskedPixels) << nl;

        ofs.close();
    }
}
