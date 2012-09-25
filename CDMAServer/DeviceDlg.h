#if !defined(AFX_DEVICEDLG_H__2E7E1878_9B31_45E5_AF71_F23F366A85F5__INCLUDED_)
#define AFX_DEVICEDLG_H__2E7E1878_9B31_45E5_AF71_F23F366A85F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DeviceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDeviceDlg dialog

class CDeviceDlg : public CDialog
{
// Construction
public:
	CDeviceDlg(CWnd* pParent = NULL, GUID* pguidDevice = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDeviceDlg)
	enum { IDD = IDD_DEVICEDLG_DIALOG };
	CComboBox	m_cmbDevice;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeviceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	GUID* m_pguidDevice;

	// Generated message map functions
	//{{AFX_MSG(CDeviceDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVICEDLG_H__2E7E1878_9B31_45E5_AF71_F23F366A85F5__INCLUDED_)
