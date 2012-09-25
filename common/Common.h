#ifndef COMMON_H
#define COMMON_H

//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "Defs.h"

void GenGoldCodes(int pCodes[KEY_LENGTH][KEY_LENGTH]); 

void WriteHalfSine(uint8_t* buffer, int coeff);
void WriteHalfSine(int16_t* buffer, int coeff);

double CalcCorrel(uint8_t* buffer1, uint8_t* buffer2, double prod_ampli1, double ampli2, size_t nhsines=1);
double CalcCorrel(int16_t* buffer1, int16_t* buffer2, double prod_ampli1, double ampli2, size_t nhsines=1);

#if 0
void SetString(CWnd* pWnd, int nWID, int nSID);
#endif

#endif
