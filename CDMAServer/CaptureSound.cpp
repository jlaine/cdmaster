//----------------------------------------------------------------------------
// File: CaptureSound.cpp
//
// Desc: The CaptureSound sample shows how to use DirectSoundCapture to capture 
//       sound into a wave file 
//
// Copyright (c) 1999-2000 Microsoft Corp. All rights reserved.
//-----------------------------------------------------------------------------


#include "stdafx.h"
#include "CaptureSound.h"
//#include <windows.h>
//#include <basetsd.h>
//#include <commdlg.h>
//#include <mmreg.h>

//#include <dsound.h>
#include "resource.h"
#include <math.h>
//#include "DSUtil.h"



//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
#define NUM_REC_NOTIFICATIONS  16
#define MAX(a,b)        ( (a) > (b) ? (a) : (b) )
/*
LPDIRECTSOUNDNOTIFY        g_pDSNotify          = NULL;
HINSTANCE                  g_hInst              = NULL;
GUID                       g_guidCaptureDevice  = GUID_NULL;
BOOL                       g_bRecording;
WAVEFORMATEX               g_wfxInput;
DSBPOSITIONNOTIFY          g_aPosNotify[ NUM_REC_NOTIFICATIONS + 1 ];  
HANDLE                     g_hNotificationEvent; 
BOOL                       g_abInputFormatSupported[16];
DWORD                      g_dwCaptureBufferSize;
DWORD                      g_dwNextCaptureOffset;
DWORD                      g_dwNotifySize;
//CWaveFile*                  g_pWaveFile;
*/


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


//-----------------------------------------------------------------------------
// Name: InitCaptureDevice()
// Desc: Initilizes DirectSound
//-----------------------------------------------------------------------------
HRESULT InitCaptureDevice( HWND hDlg, GUID* pDeviceGuid, LPLPDIRECTSOUNDCAPTURE pDSCapture )
{
    HRESULT hr;

    // Initialize COM
    if( FAILED( hr = CoInitialize(NULL) ) )
        return DXTRACE_ERR( TEXT("CoInitialize"), hr );


    // Create IDirectSoundCapture using the preferred capture device
    if( FAILED( hr = DirectSoundCaptureCreate( pDeviceGuid, pDSCapture, NULL ) ) )
        return DXTRACE_ERR( TEXT("DirectSoundCaptureCreate"), hr );

    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: CreateCaptureBuffer()
// Desc: Creates a capture buffer and sets the format 
//-----------------------------------------------------------------------------
HRESULT CreateCaptureBuffer( 
		LPDIRECTSOUNDCAPTURE lpDirectSound,
		LPDIRECTSOUNDCAPTUREBUFFER *lplpDsb )
{
    WAVEFORMATEX wfx; 
    DSCBUFFERDESC dscbdesc; 
    HRESULT hr; 
 
    // Set up wave format structure. 
    //memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT)); 
    wfx.wFormatTag = WAVE_FORMAT_PCM; 
    wfx.nChannels = 1; 
    wfx.nSamplesPerSec = SND_RATE; 
    wfx.nBlockAlign = SND_BITS / 8; 
    wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign; 
    wfx.wBitsPerSample = SND_BITS;


	memset(&dscbdesc, 0, sizeof(DSCBUFFERDESC));
    dscbdesc.dwSize = sizeof(DSCBUFFERDESC);
    // dimensionne le buffer pour recevoir SND_RCV_MARGIN secondes + le message + entete
	dscbdesc.dwBufferBytes = SND_BUFF_MARGIN + SND_BUFF_MSG + SND_BUFF_HDR;
    dscbdesc.lpwfxFormat = &wfx; 
	dscbdesc.dwFlags = 0;

    // Create buffer. 
    hr = lpDirectSound->CreateCaptureBuffer(&dscbdesc, lplpDsb, NULL); 
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

    return S_OK;
}



/*

//-----------------------------------------------------------------------------
// Name: FreeDirectSound()
// Desc: Releases DirectSound 
//-----------------------------------------------------------------------------
HRESULT FreeDirectSound()
{
//    SAFE_DELETE( g_pWaveFile );

    // Release DirectSound interfaces
    SAFE_RELEASE( g_pDSNotify );
    SAFE_RELEASE( g_pDSBCapture );
    SAFE_RELEASE( g_pDSCapture ); 

    // Release COM
    CoUninitialize();

    return S_OK;
}

*/



/*

//-----------------------------------------------------------------------------
// Name: StartOrStopRecord()
// Desc: Starts or stops the capture buffer from recording
//-----------------------------------------------------------------------------
HRESULT StartOrStopRecord( BOOL bStartRecording )
{
    HRESULT hr;

    if( bStartRecording )
    {
        // Create a capture buffer, and tell the capture 
        // buffer to start recording   
        if( FAILED( hr = CreateCaptureBuffer( &g_wfxInput ) ) )
            return DXTRACE_ERR( TEXT("CreateCaptureBuffer"), hr );

        if( FAILED( hr = g_pDSBCapture->Start( DSCBSTART_LOOPING ) ) )
            return DXTRACE_ERR( TEXT("Start"), hr );
    }
    else
    {
        // Stop the capture and read any data that 
        // was not caught by a notification
        if( NULL == g_pDSBCapture )
            return S_OK;

        // Stop the buffer, and read any data that was not 
        // caught by a notification
        if( FAILED( hr = g_pDSBCapture->Stop() ) )
            return DXTRACE_ERR( TEXT("Stop"), hr );

        if( FAILED( hr = RecordCapturedData() ) )
            return DXTRACE_ERR( TEXT("RecordCapturedData"), hr );

        // Close the wav file
//        SAFE_DELETE( g_pWaveFile );
    }

    return S_OK;
}

*/


