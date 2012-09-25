// CDMAClientDlg.h : header file
//

#if !defined(AFX_CDMACLIENTDLG_H__D4B72777_4DE6_44E5_8FBA_021D01CBEAA2__INCLUDED_)
#define AFX_CDMACLIENTDLG_H__D4B72777_4DE6_44E5_8FBA_021D01CBEAA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../common/Defs.h"
#include "../common/Common.h"
#include "PlaySound.h"

#define CHECK_PLAY 1

/////////////////////////////////////////////////////////////////////////////
// CCDMAClientDlg dialog

class CCDMAClientDlg : public CDialog
{
// Construction
public:
	CCDMAClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCDMAClientDlg)
	enum { IDD = IDD_CDMACLIENT_DIALOG };
	CButton	m_btnDumpmessage;
	CButton	m_btnDumpcode;
	CButton	m_btnSend;
	CButton	m_btnMux;
	BOOL	m_bFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDMAClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Members variables
protected:
	HICON m_hIcon;

	LPDIRECTSOUND m_pDSPlay; 
	LPDIRECTSOUNDBUFFER m_pDSBuffer;

	int* m_pMux;

	int m_nCodes[KEY_LENGTH][KEY_LENGTH];
	BYTE m_pMessage[USERS][MSG_MAXLEN];
	UINT m_nTimer;
	
// Implementation
protected:
	int InitDirectSound(GUID guidDevice);
	void GenCodes();

	// Generated message map functions
	//{{AFX_MSG(CCDMAClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMuxButton();
	afx_msg void OnSendButton();
	virtual void OnOK();
	afx_msg void OnDumpcodeButton();
	afx_msg void OnDumpmessageButton();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDMACLIENTDLG_H__D4B72777_4DE6_44E5_8FBA_021D01CBEAA2__INCLUDED_)
