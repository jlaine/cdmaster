#if !defined(COMMON_H__INCLUDED_)
#define COMMON_H__INCLUDED_


//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------

#include <math.h>
#include "Defs.h"

void GenGoldCodes(int pCodes[KEY_LENGTH][KEY_LENGTH]); 

void WriteHalfSine(BYTE* buffer, int coeff);
void WriteHalfSine(short* buffer, int coeff);

double CalcCorrel(BYTE* buffer1, BYTE* buffer2, double prod_ampli1, double ampli2, DWORD nhsines=1);
double CalcCorrel(short* buffer1, short* buffer2, double prod_ampli1, double ampli2, DWORD nhsines=1);

void SetString(CWnd* pWnd, int nWID, int nSID);

#endif