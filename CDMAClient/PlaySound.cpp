//----------------------------------------------------------------------------
// File: PlaySound.cpp
//
// Desc: The CaptureSound sample shows how to use DirectSoundCapture to capture 
//       sound into a wave file 
//
// Copyright (c) 1999-2000 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------


#include "stdafx.h"
#include "PlaySound.h"
//#include <windows.h>
//#include <basetsd.h>
//#include <commdlg.h>
//#include <mmreg.h>

//#include <dsound.h>
#include "resource.h"
#include <math.h>
//#include "DSUtil.h"



//-----------------------------------------------------------------------------
// Name: InitPlayDevice()
// Desc: Initilizes DirectSound
//-----------------------------------------------------------------------------
HRESULT InitPlayDevice( HWND hDlg, GUID* pDeviceGuid, LPLPDIRECTSOUND pDSPlay )
{
    HRESULT hr;

    // Initialize COM
    if( FAILED( hr = CoInitialize(NULL) ) )
        return DXTRACE_ERR( TEXT("CoInitialize"), hr );


    // Create IDirectSound using the preferred playback device
    if( FAILED( hr = DirectSoundCreate( pDeviceGuid, pDSPlay, NULL ) ) )
        return DXTRACE_ERR( TEXT("DirectSoundCaptureCreate"), hr );
	
    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: DSoundEnumCallback()
// Desc: Enumeration callback called by DirectSoundEnumerate
//-----------------------------------------------------------------------------
INT_PTR CALLBACK DSoundEnumCallback( GUID* pGUID, LPSTR strDesc, LPSTR strDrvName,
                                  VOID* pContext )
{
    // Set aside static storage space for 20 audio drivers
    static GUID  AudioDriverGUIDs[20];
    static DWORD dwAudioDriverIndex = 0;

    GUID* pTemp  = NULL;

    if( pGUID )
    {
        if( dwAudioDriverIndex >= 20 )
            return TRUE;

        pTemp = &AudioDriverGUIDs[dwAudioDriverIndex++];
        memcpy( pTemp, pGUID, sizeof(GUID) );
    }

    HWND hSoundDeviceCombo = (HWND)pContext;

    // Add the string to the combo box
    SendMessage( hSoundDeviceCombo, CB_ADDSTRING, 
                 0, (LPARAM) (LPCTSTR) strDesc );

    // Get the index of the string in the combo box
    INT nIndex = (INT)SendMessage( hSoundDeviceCombo, CB_FINDSTRING, 
                                   0, (LPARAM) (LPCTSTR) strDesc );

    // Set the item data to a pointer to the static guid stored in AudioDriverGUIDs
    SendMessage( hSoundDeviceCombo, CB_SETITEMDATA, 
                 nIndex, (LPARAM) pTemp );

    return TRUE;
}


BOOL CreatePlayBuffer( 
        LPDIRECTSOUND lpDirectSound, 
        LPDIRECTSOUNDBUFFER *lplpDsb) 
{ 
    WAVEFORMATEX wfx; 
    DSBUFFERDESC dsbdesc; 
    HRESULT hr; 
 
    // Set up wave format structure. 
    wfx.wFormatTag = WAVE_FORMAT_PCM; 
    wfx.nChannels = 1; 
    wfx.nSamplesPerSec = SND_RATE; 
    wfx.nBlockAlign = SND_BITS / 8; 
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign; 
    wfx.wBitsPerSample = SND_BITS; 
 
    // Set up DSBUFFERDESC structure. 
    memset(&dsbdesc, 0, sizeof(DSBUFFERDESC)); 
    dsbdesc.dwSize = sizeof(DSBUFFERDESC); 
	dsbdesc.dwFlags = 0; 
    
	// dimensionne le buffer pour recevoir : 
	// 1 sec silence + taille de message maximale + l'entete
    dsbdesc.dwBufferBytes = 1*wfx.nAvgBytesPerSec + SND_BUFF_MSG + SND_BUFF_HDR; 
    dsbdesc.lpwfxFormat = &wfx; 

    // Create buffer. 
    hr = lpDirectSound->CreateSoundBuffer(&dsbdesc, lplpDsb, NULL); 
    if SUCCEEDED(hr) 
    { 
        // Valid interface is in *lplpDsb. 
        return TRUE; 
    } 
    else 
    { 
        // Failed. 
        *lplpDsb = NULL; 
        return FALSE; 
    } 
}

