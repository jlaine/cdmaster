#if !defined(AFX_MESSAGEDLG_H__579E79C8_56E6_492F_9D68_DD57B0FEB410__INCLUDED_)
#define AFX_MESSAGEDLG_H__579E79C8_56E6_492F_9D68_DD57B0FEB410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessageDlg dialog

class CMessageDlg : public CDialog
{
// Construction
public:
	CMessageDlg(CWnd* pParent = NULL, CString sPrompt = "");   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMessageDlg)
	enum { IDD = IDD_MESSAGEDLG_DIALOG };
	CString	m_sMessage;
	CString	m_sPrompt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMessageDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEDLG_H__579E79C8_56E6_492F_9D68_DD57B0FEB410__INCLUDED_)
