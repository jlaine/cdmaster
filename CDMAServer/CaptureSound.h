#if !defined(_CAPTURESOUND_H__)
#define _CAPTURESOUND_H__

#include "resource.h"		// main symbols

#include <dxerr8.h>
#include <mmreg.h>
#include <dsound.h>
#include "../common/Defs.h"

//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------
HRESULT InitCaptureDevice( HWND hDlg, GUID* pDeviceGuid,LPLPDIRECTSOUNDCAPTURE pDSCapture );
HRESULT FreeDirectSound();

INT_PTR CALLBACK DSoundEnumCallback( GUID* pGUID, LPSTR strDesc, LPSTR strDrvName,
                                     VOID* pContext );

HRESULT CreateCaptureBuffer( LPDIRECTSOUNDCAPTURE lpDirectSound, LPDIRECTSOUNDCAPTUREBUFFER *lplpDsb);
//HRESULT InitNotifications();
//HRESULT StartOrStopRecord( BOOL bStartRecording );
//HRESULT RecordCapturedData();


#endif