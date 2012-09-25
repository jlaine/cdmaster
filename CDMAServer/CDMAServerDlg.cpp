// CDMAServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CDMAServer.h"
#include "CDMAServerDlg.h"
#include "DeviceDlg.h"
#include "../common/ogold.h"
#include "../common/common.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDMAServerDlg dialog

CCDMAServerDlg::CCDMAServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCDMAServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCDMAServerDlg)
	m_sStatus = _T("");
	m_bFile = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pDSCapture = NULL;
	m_pDSBuffer = NULL;
}

void CCDMAServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCDMAServerDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_prgProgress);
	DDX_Control(pDX, IDC_RECEIVE_BUTTON, m_btnReceive);
	DDX_Control(pDX, IDC_DEMUX_BUTTON, m_btnDemux);
	DDX_Text(pDX, IDC_STATUS, m_sStatus);
	DDX_Check(pDX, IDC_FILE, m_bFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCDMAServerDlg, CDialog)
	//{{AFX_MSG_MAP(CCDMAServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RECEIVE_BUTTON, OnReceiveButton)
	ON_BN_CLICKED(IDC_DEMUX_BUTTON, OnDemuxButton)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDMAServerDlg message handlers

BOOL CCDMAServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

///////////////////////////////////////////////////
///     set strings
	SetString(this, IDC_DEMUX_BUTTON, IDS_DEMUX);
	SetString(this, IDC_RECEIVE_BUTTON, IDS_RECEIVE);
	SetString(this, IDOK, IDS_QUIT);

	
///////////////////////////////////////////////////
///     Device selection and DirectSound init

	GUID guidDevice;
	int nResponse;
	CDeviceDlg* dlg = NULL;
	HRESULT hr;
	
	dlg = new CDeviceDlg(NULL, &guidDevice);
	nResponse = dlg->DoModal();
	SAFE_DELETE(dlg);

	if (nResponse != IDOK)
		return FALSE;

	// Init DirectSound
	SAFE_RELEASE(m_pDSCapture);
    if( FAILED( hr = InitCaptureDevice( m_hWnd, &guidDevice, &m_pDSCapture ) ) )
    {
		AfxMessageBox( "Error initializing DirectSound." );
		return FALSE;
    }
	
///////////////////////////////////////////////////
///            Generate codes
	GenCodes();

///////////////////////////////////////////////////
///            Enable appropriate buttons
	m_btnReceive.EnableWindow(true);
	SetStatus(IDS_STOP_STATUS);
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CCDMAServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCDMAServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCDMAServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CCDMAServerDlg::GenCodes()
{
	unsigned user;
	unsigned chip;
  
	GenGoldCodes(m_nCodes);

	for (user = 0; user < KEY_LENGTH; user++) {
		for ( chip = 0; chip < KEY_LENGTH; chip++) {
			WriteHalfSine(m_nModCodes[user][chip], m_nCodes[user][chip]*USERS);
		}
	}
}

void CCDMAServerDlg::OnReceiveButton() 
{
	HRESULT hr;
	DWORD dwLength;
	//16bite
	//BYTE* lpvRead;
	LONG* lpvRead;

	// disactivate buttons
	UpdateData(true);
	m_btnReceive.EnableWindow(false);
	m_btnDemux.EnableWindow(false);
	KillTimer(m_nTimer);
	
    // create a fresh buffer
	SAFE_RELEASE(m_pDSBuffer);
	if (!CreateCaptureBuffer(m_pDSCapture, &m_pDSBuffer)) {
		AfxMessageBox("Error creating capture buffer.");
		return;
	}

	// lock buffer
	if ( FAILED( hr= m_pDSBuffer->Lock(
        0,              // Offset at which to start lock.
        0,              // Size of lock; ignored because of flag.
        (void**)(&lpvRead),      // Gets address of first part of lock.
        &dwLength,      // Gets size of first part of lock.
        NULL,           // Address of wraparound not needed. 
        NULL,           // Size of wraparound not needed.
        DSCBLOCK_ENTIREBUFFER ) ) )  // Flag
    {
		AfxMessageBox("Failed to lock buffer");
		return;		
    }

	// erase buffer
	//8bit
	//memset(lpvRead,128,dwLength);
	//16bit
	memset(lpvRead,0,dwLength);
	
	// unlock buffer
	if ( FAILED ( hr = m_pDSBuffer->Unlock(
		lpvRead,        // Address of lock start.
		dwLength,       // Size of lock.
		NULL,           // No wraparound portion.
		0) ) )          // No wraparound size.
	{
		AfxMessageBox("Failed to unlock buffer.");
		return;
	}

	// start recording

	if( FAILED( hr = m_pDSBuffer->Start( 0 ) ) )
	{ 
		AfxMessageBox("Failed to start recording.");
		return;
	}
	
	
	SetStatus(IDS_RECEIVE_STATUS);
	m_prgProgress.SetRange(0,100);
	m_prgProgress.SetPos(0);
	m_nTimer = SetTimer(CHECK_RECORD, 100, 0);
	
	// reactivate buttons.
	m_btnDemux.EnableWindow(true);
	m_btnReceive.EnableWindow(true);
}

void CCDMAServerDlg::OnOK() 
{
	SAFE_RELEASE(m_pDSBuffer);
	SAFE_RELEASE(m_pDSCapture);
	
	CDialog::OnOK();
}

void CCDMAServerDlg::OnDemuxButton() 
{
	//8bit
	//BYTE* lpvRead;
	//16bit
	short* lpvRead;

	DWORD dwPos;
	DWORD dwLength, dwMaxPos;
	signed int dwSync,dwSyncBest;
	unsigned byte, user, bit;
	HRESULT hr;
	bool bFound = FALSE;
	double correl, maxcorrel,synccorrel;
	//8bit
	//BYTE pStartBlock[SND_BUFF_HDR];
	//16bit
	short pStartBlock[SND_BUFF_HDR];
	
	BYTE pMessage[USERS][MSG_MAXLEN];
	CString sOutput;
	char cByte;
	int i;
	//status related
	CString sBoxMessage;

	// disactivate buttons
	UpdateData(true);
	m_btnReceive.EnableWindow(false);
	m_btnDemux.EnableWindow(false);

	// stop recording
	if( FAILED( hr= m_pDSBuffer->Stop() ) ) 
	{
		AfxMessageBox("Failed to stop recording.");
		return;
	}

	// lock capture buffer
	if ( FAILED( hr= m_pDSBuffer->Lock(
        0,              // Offset at which to start lock.
        0,              // Size of lock; ignored because of flag.
        (void**)(&lpvRead),      // Gets address of first part of lock.
        &dwLength,      // Gets size of first part of lock.
        NULL,           // Address of wraparound not needed. 
        NULL,           // Size of wraparound not needed.
        DSCBLOCK_ENTIREBUFFER ) ) )  // Flag
    {
		AfxMessageBox("Failed to lock capture buffer.");
		return;
	}
	
	// Generate start block
	dwPos = 0;
	for (i = 0; i < HDR_LEN / 2; i++) {
		WriteHalfSine(pStartBlock+dwPos, (2*(i % 2) -1) * USERS);
		dwPos += HSINE_POINTS;
	}
	for (i = 0; i < HDR_LEN / 2; i++) {
		WriteHalfSine(pStartBlock+dwPos, (1- 2*(i % 2)) * USERS);
		dwPos += HSINE_POINTS;
	}

	maxcorrel = 0;
	dwPos =0;
	
	//// update status
	m_prgProgress.SetPos(0);
	SetStatus(IDS_STATUS_SEARCH);
	/////

	for (dwPos = 0; dwPos  < MARGIN_LEN; dwPos+=SND_SYNC) {
		// parcourt et recherche un maximum de correlation
		correl = CalcCorrel(lpvRead+ dwPos,pStartBlock,HSINE_AMPLI*USERS,HSINE_AMPLI*USERS,8);
 
		if (fabs(correl) > fabs(maxcorrel)) 
		{
			maxcorrel = correl;
			dwMaxPos = dwPos;
		}		
		if (dwPos % (SND_SYNC*256) == 0) {
			m_prgProgress.SetPos(100* dwPos / (MARGIN_LEN));
		}
	}

	dwPos = dwMaxPos;
	
	if (fabs(fabs(maxcorrel)-1) > 0.6) 
	{
		sBoxMessage.LoadString(IDS_SEARCH_NOTFOUND);
		AfxMessageBox(sBoxMessage);
		SetStatus(IDS_STATUS_STOP);
	} 
	else {
		SetStatus(IDS_STATUS_DEMUX);
		m_prgProgress.SetPos(0);

		//sauter les HDR_LEN demi-sinusoides du départ	
		dwPos += HDR_LEN * HSINE_POINTS;
			
		for (byte = 0; byte < MSG_MAXLEN; byte++) {
			m_prgProgress.SetPos(100 * byte  / MSG_MAXLEN);
			/// pour maintenir la synchro
			synccorrel = 0;
			dwSyncBest = 0;
			for (dwSync = -SND_SYNC; dwSync <= SND_SYNC; dwSync++) {
				correl = 0;
				for (bit = 0; bit < 8; bit++) {
					correl += fabs(CalcCorrel(lpvRead+ dwPos + dwSync,m_nModCodes[1][0],maxcorrel*HSINE_AMPLI,HSINE_AMPLI*USERS));
				}
				if (correl > synccorrel)  {
					dwSyncBest = dwSync;
					synccorrel = correl;
				}
			}
			
			dwPos += dwSyncBest;

			for(user = 0; user < USERS; user++) {
				cByte = 0;
				for (bit = 0; bit < 8; bit++) {
					correl = CalcCorrel(lpvRead+ dwPos+bit*HSINE_POINTS*KEY_LENGTH,m_nModCodes[user][0],maxcorrel*HSINE_AMPLI,HSINE_AMPLI*USERS);
					if (fabs(correl - 1)  < fabs(correl + 1)) {
						if (fabs(correl - 1) > 0.35)
						{
							//AfxMessageBox("valeur suspecte : prise comme +1");
						}
						cByte = cByte | (1 << bit);

					}
					else {
						if (fabs(correl+1) > 0.35)
						{
							//AfxMessageBox("valeur suspecte : prise comme -1");
						}
					}			
				}
				// bidouille pour ne pas afficher des characteres speciaux
				// qui sont généralement introduits par un erreur (bruit, saturation)
				//if ((cByte < 32) || (cByte>126)) cByte = 32;
				//
				pMessage[user][byte] = cByte;
			}
			dwPos += 8*HSINE_POINTS*KEY_LENGTH;
		}
			
		if (m_bFile) {
			//////////////////////////////
			///       File output      ///
			//////////////////////////////
			CFile fFile;
			CFileException ex;
				
			if (!fFile.Open("output.txt",CFile::modeCreate | CFile::modeWrite,&ex)) {

				 TCHAR szError[1024];
				 ex.GetErrorMessage(szError, 1024);
				 AfxMessageBox(CString("Couldn't open source file: ") + szError);

				 fFile.Close();
				 return;
			}

			for (user = 0; user < USERS; user++) {
				fFile.Write(pMessage[user],MSG_MAXLEN);
			}
			fFile.Close();
		}
		else {
			//////////////////////////////
			///       Dialog Output    ///
			//////////////////////////////
			
			char buffer[32];

			//prepare le texte à afficher dans la boite de dialogue
			sOutput = "";
			for(user = 0; user < USERS; user++) {
				sOutput = sOutput + "utilisateur " + CString(_ltoa(user, buffer, 10)) + ": "+ CString(pMessage[user]).Left(MSG_MAXLEN) + "\n\n"; 
			}
			AfxMessageBox(sOutput,MB_ICONINFORMATION);
		}
		
		///////////////////////////////

	}		
	
/// common whether detected or not	
	// unlock capture buffer
	if ( FAILED( hr = m_pDSBuffer->Unlock(
			lpvRead,        // Address of lock start.
			dwLength,       // Size of lock.
			NULL,           // No wraparound portion.
			0) ) )          // No wraparound size.
	{
		AfxMessageBox("Failed to unlock capture buffer.");
		return;
	}

	// set status back to stopped
	SetStatus(IDS_STATUS_STOP);

	// reactivate buttons
	m_btnReceive.EnableWindow(true);
	m_btnDemux.EnableWindow(true);
}

void CCDMAServerDlg::SetStatus(int nSID)
{
	m_sStatus.LoadString(nSID);
	UpdateData(false);
}

void CCDMAServerDlg::OnTimer(UINT nIDEvent) 
{
	DWORD dwCapturePos, dwReadPos, dwStatus;
	
	switch (nIDEvent) {
	case CHECK_RECORD:
		
		m_pDSBuffer->GetStatus(&dwStatus);
	
		if (dwStatus && DSCBSTATUS_CAPTURING) {
			m_pDSBuffer->GetCurrentPosition(&dwCapturePos, &dwReadPos);
			m_prgProgress.SetPos(100 * dwReadPos / (SND_BUFF_MSG + SND_BUFF_HDR + SND_BUFF_MARGIN));
		}
		else {
			KillTimer(m_nTimer);
			SetStatus(IDS_STATUS_STOP);
			// reactivate buttons.
		}
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}
