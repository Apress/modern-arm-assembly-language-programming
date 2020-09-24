//-------------------------------------------------
//               Ch14_05_Misc.cpp
//-------------------------------------------------

#include <iostream>
#include "Ch14_05.h"

using namespace std;

void PrintClipDataStructOffsets(void)
{
    const char nl = '\n';

    cout << "offsetof(ClipData.m_Src) =              " << offsetof(ClipData, m_Src) << nl;
    cout << "offsetof(ClipData.m_Des) =              " << offsetof(ClipData, m_Des) << nl;
    cout << "offsetof(ClipData.m_NumPixels) =        " << offsetof(ClipData, m_NumPixels) << nl;
    cout << "offsetof(ClipData.m_NumClippedPixels) = " << offsetof(ClipData, m_NumClippedPixels) << nl;
    cout << "offsetof(ClipData.m_ThreshLo) =         " << offsetof(ClipData, m_ThreshLo) << nl;
    cout << "offsetof(ClipData.m_ThreshHi) =         " << offsetof(ClipData, m_ThreshHi) << nl;
}
