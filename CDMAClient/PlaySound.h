#if !defined(_PLAYSOUND_H__)
#define _PLAYSOUND_H__

#include "resource.h"		// main symbols

#include <dxerr8.h>
#include <mmreg.h>
#include <dsound.h>
#include "../common/defs.h"

//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------
HRESULT InitPlayDevice( HWND hDlg, GUID* pDeviceGuid, LPLPDIRECTSOUND pDSPlay );

INT_PTR CALLBACK DSoundEnumCallback( GUID* pGUID, LPSTR strDesc, LPSTR strDrvName,
                                     VOID* pContext );

CreatePlayBuffer( LPDIRECTSOUND lpDirectSound, LPDIRECTSOUNDBUFFER *lplpDsb);

#endif