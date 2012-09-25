// CDMAServerDlg.h : header file
//

#if !defined(AFX_CDMASERVERDLG_H__CF5DD08F_70D1_409D_A679_8F5ADD558E3E__INCLUDED_)
#define AFX_CDMASERVERDLG_H__CF5DD08F_70D1_409D_A679_8F5ADD558E3E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CaptureSound.h"

#define CHECK_RECORD 1
/////////////////////////////////////////////////////////////////////////////
// CCDMAServerDlg dialog

class CCDMAServerDlg : public CDialog
{
// Construction
public:
	UINT m_nTimer;
	void SetStatus(int nSID);
	CCDMAServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCDMAServerDlg)
	enum { IDD = IDD_CDMASERVER_DIALOG };
	CProgressCtrl	m_prgProgress;
	CButton	m_btnReceive;
	CButton	m_btnDemux;
	CString	m_sStatus;
	BOOL	m_bFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDMAServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// MEMBER VARIABLES
	HICON m_hIcon;

	LPDIRECTSOUNDCAPTURE m_pDSCapture;
	LPDIRECTSOUNDCAPTUREBUFFER m_pDSBuffer;

	int m_nCodes[KEY_LENGTH][KEY_LENGTH];
	//8bit
	//BYTE m_nModCodes[KEY_LENGTH][KEY_LENGTH][HSINE_POINTS];
	//16bit
	short m_nModCodes[KEY_LENGTH][KEY_LENGTH][HSINE_POINTS];

	// MEMBER FUNCTIONS
	void GenCodes();


	// Generated message map functions
	//{{AFX_MSG(CCDMAServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnReceiveButton();
	virtual void OnOK();
	afx_msg void OnDemuxButton();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDMASERVERDLG_H__CF5DD08F_70D1_409D_A679_8F5ADD558E3E__INCLUDED_)
