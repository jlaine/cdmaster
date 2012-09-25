// DeviceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CDMAClient.h"
#include "DeviceDlg.h"
#include "PlaySound.h"
#include "..\common\common.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeviceDlg dialog


CDeviceDlg::CDeviceDlg(CWnd* pParent /*=NULL*/, GUID* pguidDevice /*=NULL*/)
	: CDialog(CDeviceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeviceDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pguidDevice = pguidDevice;
}


void CDeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeviceDlg)
	DDX_Control(pDX, IDC_DEVICE_COMBO, m_cmbDevice);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeviceDlg, CDialog)
	//{{AFX_MSG_MAP(CDeviceDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeviceDlg message handlers

void CDeviceDlg::OnOK() 
{
	// Get the index of the currently selected devices
    int nDeviceIndex = m_cmbDevice.GetCurSel(); 

	// Get the GUID attached to the combo box item
	GUID* pDeviceGUID = (GUID*) m_cmbDevice.GetItemData(nDeviceIndex);

    // Remember that guid
    if( pDeviceGUID ) 
		*m_pguidDevice = *pDeviceGUID;
	
	CDialog::OnOK();
}

BOOL CDeviceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Load dialog strings
	SetString(this, IDC_OUTPUT_DEVICE, IDS_OUTPUT_DEVICE);

	// Enumerate the playback devices and place them in the combo box
	DirectSoundEnumerate( (LPDSENUMCALLBACK)DSoundEnumCallback,
                                 m_cmbDevice.m_hWnd );

    // Select the first device in the combo box
    m_cmbDevice.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
