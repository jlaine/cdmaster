// CDMAClient.h : main header file for the CDMACLIENT application
//

#if !defined(AFX_CDMACLIENT_H__D7CDABF5_4D07_4038_B041_8EF993DD1F55__INCLUDED_)
#define AFX_CDMACLIENT_H__D7CDABF5_4D07_4038_B041_8EF993DD1F55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCDMAClientApp:
// See CDMAClient.cpp for the implementation of this class
//

class CCDMAClientApp : public CWinApp
{
public:
	CCDMAClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDMAClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCDMAClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDMACLIENT_H__D7CDABF5_4D07_4038_B041_8EF993DD1F55__INCLUDED_)
