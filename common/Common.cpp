// Common.cpp: common functions
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Common.h"
#include "OGold.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// generates the Gold codes
void GenGoldCodes(int pCodes[KEY_LENGTH][KEY_LENGTH]) {
	unsigned long poly0;
	unsigned long poly1;
	unsigned user;
	unsigned b;
	COGold pn;

	unsigned offset; 

	switch (DEG) {
	case 3:
		poly0 = 10;
		poly1 = 0;
		break;
	case 4:
		poly0 = 18;
		poly1 = 0;
		break;
	case 5:
		poly0 = 36;
		poly1 = 0;
		break;		
	}
  
	for (user = 0; user < KEY_LENGTH; user++) {

        pn.Create( DEG, poly0, poly1, user);
        for ( offset = 0; offset < KEY_LENGTH; offset++ ) {
                b = pn.GetNext();
				pCodes[user][offset] = 2*b-1;
        }
	}
}


//8bit writes a half-sine to a byte buffer
void WriteHalfSine(BYTE* buffer, int coeff) {
	const float cf = 3.1415927f/HSINE_POINTS;
	float ampli = float(HSINE_AMPLI * coeff);
	
	int zero = 1 << 7;

	for(int i = 0; i < HSINE_POINTS; i++) {
		buffer[i] = BYTE(ampli*sin(i*cf)+zero);
	}
}

//16bit writes a half-sine to a uint buffer
void WriteHalfSine(short* buffer, int coeff) {
	const float cf = 3.1415927f/HSINE_POINTS;
	float ampli = float(HSINE_AMPLI * coeff);

	for(int i = 0; i < HSINE_POINTS; i++) {
		buffer[i]=WORD(ampli*sin(i*cf));
	}

}


// calculates the correlation between two signals
double CalcCorrel(BYTE* buffer1, BYTE* buffer2, double ampli1, double ampli2, DWORD n /*=1*/)
{
	double correl = 0;
	DWORD dwPos = 0;

	for (dwPos = 0; dwPos < n*KEY_LENGTH*HSINE_POINTS; dwPos++) {
		correl += ((buffer1[dwPos]-128)/ampli1) * ((buffer2[dwPos]-128)/ampli2);
	}

	correl = correl / HSINE_POINTS / KEY_LENGTH *2 / n ;
	return correl;
}

// calculates the correlation between two signals
double CalcCorrel(short* buffer1, short* buffer2, double ampli1, double ampli2, DWORD n /*=1*/)
{
	double correl = 0;
	DWORD dwPos = 0;

	for (dwPos = 0; dwPos < n*KEY_LENGTH*HSINE_POINTS; dwPos++) {
		correl += (buffer1[dwPos]/ampli1) * (buffer2[dwPos]/ampli2);
	}

	correl = correl / HSINE_POINTS / KEY_LENGTH *2 / n ;
	return correl;
}

// sets an item's string after reading it from resources
void SetString(CWnd* pWnd, int nWID, int nSID)
{
	CString sTemp;
	sTemp.LoadString(nSID);
	pWnd->SetDlgItemText(nWID, sTemp);
}

