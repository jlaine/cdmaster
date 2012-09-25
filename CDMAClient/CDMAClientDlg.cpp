// CDMAClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CDMAClient.h"
#include "CDMAClientDlg.h"
#include "DeviceDlg.h"
#include "MessageDlg.h"
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
// CCDMAClientDlg dialog

CCDMAClientDlg::CCDMAClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCDMAClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCDMAClientDlg)
	m_bFile = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pMux = NULL;
	m_pDSPlay = NULL;
	m_pDSBuffer = NULL;
}

void CCDMAClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCDMAClientDlg)
	DDX_Control(pDX, IDC_DUMPMESSAGE_BUTTON, m_btnDumpmessage);
	DDX_Control(pDX, IDC_DUMPCODE_BUTTON, m_btnDumpcode);
	DDX_Control(pDX, IDC_SEND_BUTTON, m_btnSend);
	DDX_Control(pDX, IDC_MUX_BUTTON, m_btnMux);
	DDX_Check(pDX, IDC_FILE, m_bFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCDMAClientDlg, CDialog)
	//{{AFX_MSG_MAP(CCDMAClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MUX_BUTTON, OnMuxButton)
	ON_BN_CLICKED(IDC_SEND_BUTTON, OnSendButton)
	ON_BN_CLICKED(IDC_DUMPCODE_BUTTON, OnDumpcodeButton)
	ON_BN_CLICKED(IDC_DUMPMESSAGE_BUTTON, OnDumpmessageButton)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDMAClientDlg message handlers

BOOL CCDMAClientDlg::OnInitDialog()
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
	SetString(this, IDC_MUX_FRM, IDS_MUX_FRM);
	SetString(this, IDC_DUMP_FRM, IDS_DUMP_FRM);
	SetString(this, IDC_MUX_BUTTON, IDS_MUX);
	SetString(this, IDC_SEND_BUTTON, IDS_SEND);
	SetString(this, IDC_DUMPCODE_BUTTON, IDS_DUMPCODE);
	SetString(this, IDC_DUMPMESSAGE_BUTTON, IDS_DUMPMESSAGE);
	SetString(this, IDOK, IDS_QUIT);


///////////////////////////////////////////////////
///     Device selection and DirectSound init

	GUID guidDevice;
	int nResponse;
	CDeviceDlg* dlg = NULL;
		
	dlg = new CDeviceDlg(NULL, &guidDevice);
	nResponse = dlg->DoModal();
	SAFE_DELETE(dlg);

	if (nResponse != IDOK)
		return FALSE;

	if (!InitDirectSound(guidDevice))
		return FALSE;
	
///////////////////////////////////////////////////
///            Generate codes
	GenCodes();
	
///////////////////////////////////////////////////
///            Enable appropriate buttons
	m_btnMux.EnableWindow(true);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCDMAClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCDMAClientDlg::OnPaint() 
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
HCURSOR CCDMAClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CCDMAClientDlg::InitDirectSound(GUID guidDevice)
{
	HRESULT hr;

	// Init playback device
    SAFE_RELEASE( m_pDSPlay );
	if( FAILED( hr = InitPlayDevice( m_hWnd, &guidDevice, &m_pDSPlay ) ) )
    {
		AfxMessageBox( "Error initializing DirectSound." );
		return FALSE;
    }
	
	if( FAILED( hr = m_pDSPlay->SetCooperativeLevel(this->m_hWnd, DSSCL_NORMAL) ) )
	{
		AfxMessageBox("Error initializing playback device.");
		return FALSE;
	}
	
	// Init playback buffer
	SAFE_RELEASE( m_pDSBuffer );
	if (!CreatePlayBuffer(m_pDSPlay, &m_pDSBuffer)) {
		AfxMessageBox("Error creating playback buffer.");
		return FALSE;
	}

	return TRUE;
}



void CCDMAClientDlg::OnMuxButton() 
{
	CMessageDlg* dlg = NULL;
	unsigned int user, byte, bit, chip;
	int f;

	// disactivate buttons.
	m_btnMux.EnableWindow(false);
	m_btnSend.EnableWindow(false);
	m_btnDumpmessage.EnableWindow(false);

	UpdateData(true);

	if (m_bFile) {
		/////////////////////////////
		///       File input      ///
		/////////////////////////////
		CFile fFile;
		CFileException ex;
		DWORD dwRead;
		TCHAR szError[1024];

			
		if (!fFile.Open("input.txt",CFile::modeRead,&ex)) {

			 ex.GetErrorMessage(szError, 1024);
			 AfxMessageBox(CString("Couldn't open source file: ") + szError);

			 fFile.Close();
			 return;
		}

		for (user = 0; user < USERS; user++) {
			dwRead = fFile.Read(m_pMessage[user],MSG_MAXLEN);
		}
		fFile.Close();
	}
	else
	{
		///////////////////////////////
		///       Dialog input      ///
		///////////////////////////////
		CString sMsgUser,sTemp;
		char buffer[32];
		CString sMessage[USERS];

		sMsgUser.LoadString(IDS_MSG_FROM_USER);
		for (user = 0; user < USERS; user++) {
			sprintf(buffer, sMsgUser, user);
			dlg = new CMessageDlg( this, buffer );
			if (dlg->DoModal() == IDOK) {
				sMessage[user] = dlg->m_sMessage;
			}
			else {
				SAFE_DELETE(dlg);
				m_btnMux.EnableWindow(true);	
				return;
			}
			SAFE_DELETE(dlg);		
		}
		
		sTemp = CString(32, MSG_MAXLEN);
		for (user = 0; user < USERS; user++) {
			sMessage[user] = CString(sMessage[user] + sTemp).Left(MSG_MAXLEN);
			for(byte = 0; byte < MSG_MAXLEN; byte++) {
				m_pMessage[user][byte] = (unsigned char) sMessage[user].GetBuffer(0)[byte];
			}
		}
	}

	// Start mux
	SAFE_DELETE(m_pMux);
	m_pMux = new int[8*KEY_LENGTH*MSG_MAXLEN];

	for (chip = 0; chip < 8*KEY_LENGTH*MSG_MAXLEN; chip++) {
		m_pMux[chip] = 0;
	}

	for (user = 0; user < USERS; user++) {
		//traite le user-ième utilisateur
		
		for (byte = 0; byte < MSG_MAXLEN; byte++) {
			// traite le byte-ième charactère à envoyer
			for (bit = 0; bit < 8; bit++) {
				// traite le bit-ieme bit du charactère en cours
				//f : valeur du bit considéré
				
				f = 2*((m_pMessage[user][byte] & (1 << bit)) >> bit) -1;
				
				for (chip = 0; chip < KEY_LENGTH; chip++) {
					m_pMux[(byte*8+bit)*KEY_LENGTH+chip] += f * m_nCodes[user][chip];
				}
			}
		}
	}


	// reactivate buttons.
	m_btnMux.EnableWindow(true);
	m_btnSend.EnableWindow(true);
	m_btnDumpmessage.EnableWindow(true);
}

void CCDMAClientDlg::OnSendButton() 
{
	DWORD i;
	//8bit
	//BYTE* lpvWrite;
	
	///////////16bit////////
	short* lpvWrite;


	DWORD  dwLength;
	DWORD dwPos; 

	// disactivate buttons.
	m_btnMux.EnableWindow(false);
	m_btnSend.EnableWindow(false);

	// lock playback buffer
	if ( FAILED( m_pDSBuffer->Lock(
        0,							// Offset at which to start lock.
        0,							// Size of lock; ignored because of flag.
        (void**)(&lpvWrite),		// Gets address of first part of lock.
        &dwLength,					// Gets size of first part of lock.
        NULL,						// Address of wraparound not needed. 
        NULL,						// Size of wraparound not needed.
        DSBLOCK_ENTIREBUFFER) ) )	// Flag
    {
		AfxMessageBox("Failed to lock playback buffer.");
		return;
	}
	
	// erase buffer
	////////// 8bit ////////
	//memset(lpvWrite,128,dwLength);

	////////// 16bit ////////
	memset(lpvWrite,0,dwLength);

	// skip 1 sec blank

	dwPos = SND_RATE;

	// write header
	for (i = 0; i < HDR_LEN / 2; i++) {
		WriteHalfSine(lpvWrite+dwPos, (2*(i % 2) - 1) * USERS);
		dwPos += HSINE_POINTS;
	}
	for (i = 0; i < HDR_LEN / 2; i++) {
		WriteHalfSine(lpvWrite+dwPos, (1- 2*(i % 2)) * USERS);
		dwPos += HSINE_POINTS;
	}


	// write message
	for (i = 0; i < 8*KEY_LENGTH*MSG_MAXLEN; i++) {
		WriteHalfSine(lpvWrite+dwPos, m_pMux[i]);
		dwPos += HSINE_POINTS;
	}

	// lock playback buffer
	if ( FAILED (m_pDSBuffer->Unlock(
		lpvWrite,       // Address of lock start.
		dwLength,       // Size of lock.
		NULL,           // No wraparound portion.
		0) ) )          // No wraparound size.
	{
		AfxMessageBox("Failed to unlock playback buffer.");
		return;
	}

	// set playback position to zero
	if ( FAILED (m_pDSBuffer->SetCurrentPosition(0) ) )
	{
		AfxMessageBox("Failed to reset playback buffer position.");
		return;
	}

	// start playing
	if ( FAILED (m_pDSBuffer->Play(0,0,0) ) )
	{
		AfxMessageBox("Failed to play playback buffer.");
		return;
	}
    
	m_nTimer = SetTimer(CHECK_PLAY, 500,0);
}

void CCDMAClientDlg::OnOK() 
{
	SAFE_RELEASE(m_pDSBuffer);
	SAFE_RELEASE(m_pDSPlay);
	
	SAFE_DELETE(m_pMux);
	
	CDialog::OnOK();
}

void CCDMAClientDlg::OnDumpcodeButton() 
{
  unsigned i, offset;

  unsigned pn_size;
  
  CFile fOutput;
  CFileException ex;
  char cBuffer[1024];
  
  TCHAR szError[1024];
  int n;

  pn_size = 1 << DEG;


  // codes are dumped to files codeXX

	for (i = 0; i < pn_size; i++) {
		sprintf(cBuffer, "code%i", i);
		if (!fOutput.Open(cBuffer, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate, &ex)) {
			ex.GetErrorMessage(szError, 1024);
			AfxMessageBox("Couldn't open destination file: " + CString(szError), MB_OK | MB_ICONINFORMATION);
			return;
		}
		       
		for ( offset = 0; offset < pn_size; offset++ ) {
				n = sprintf(cBuffer, "%d.5 %d\n", offset, m_nCodes[i][offset]);
				fOutput.Write(cBuffer, n);
        }
		fOutput.Close();
	}
}

void CCDMAClientDlg::OnDumpmessageButton() 
{
	unsigned int user, byte, bit, chip;

	char cBuffer[1024];
	CFile fOutput;
	CFileException ex;
	TCHAR szError[1024];
	int n,f;
	
	// outputs the users' messages to file
	for (user = 0; user < USERS; user++) {
		//traite le user-ième utilisateur
		
		// ouverture du fichier
		sprintf(cBuffer,"message%i",user);
		if (!fOutput.Open(cBuffer, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate, &ex)) {
			ex.GetErrorMessage(szError, 1024);
			AfxMessageBox("Couldn't open destination file: " + CString(szError), MB_OK | MB_ICONINFORMATION);
			return;
		}

		for (byte = 0; byte < MSG_MAXLEN; byte++) {
			// traite le byte-ième charactère à envoyer
			for (bit = 0; bit < 8; bit++) {
				// traite le bit-ieme bit du charactère en cours
				//f : valeur du bit considéré
				
				f = 2*((m_pMessage[user][byte] & (1 << bit)) >> bit) -1;
				n = sprintf(cBuffer, "%d\n", f);
				fOutput.Write(cBuffer, n);
			}
		}
		fOutput.Close();
	}
	
	
	// outputs the mux result to file
	if (!fOutput.Open("mux", CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate, &ex)) {
		ex.GetErrorMessage(szError, 1024);
		AfxMessageBox("Couldn't open destination file: " + CString(szError), MB_OK | MB_ICONINFORMATION);
		return;
	}

	for(chip = 0; chip < 8*KEY_LENGTH*MSG_MAXLEN; chip++) {
		n = sprintf(cBuffer, "%d\n", m_pMux[chip]);
		fOutput.Write(cBuffer, n);
    }

	fOutput.Close();	
}

	
void CCDMAClientDlg::GenCodes() 
{
	GenGoldCodes(m_nCodes);
	m_btnDumpcode.EnableWindow(true);
}

void CCDMAClientDlg::OnTimer(UINT nIDEvent) 
{
	DWORD dwStatus;
	
	switch (nIDEvent) {
	case CHECK_PLAY:
		m_pDSBuffer->GetStatus(&dwStatus);
		if (!(dwStatus && DSBSTATUS_PLAYING)) {
			KillTimer(m_nTimer);
			// reactivate buttons.
			m_btnMux.EnableWindow(true);
			m_btnSend.EnableWindow(true);

		}
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}
