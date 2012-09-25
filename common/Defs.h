#if !defined(DEFS_H__INCLUDED)
#define DEFS_H__INCLUDED_

//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------


#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }


#define DEG				4
#define KEY_LENGTH		16
#define USERS			16

#define HSINE_POINTS	6			// points par demi-periode de la sinusoide

////////// 8bit ////////
//#define HSINE_AMPLI		127/USERS	// amplitude de la sinusoide
						    			// pour 1 utilisateur

//////////16bit ////////
#define HSINE_AMPLI		32767/USERS	// amplitude de la sinusoide
						    			// pour 1 utilisateur


#define MSG_MAXLEN		2304		// taille max du message en octets

#define HDR_LEN			8*KEY_LENGTH// taille max du message en "chips"
#define MARGIN_LEN		4*SND_RATE

#define SND_RATE		44100		// frequence d'echantillonage
#define SND_BITS		16			// bits par echantillon
#define SND_SYNC		1	
#define SND_BUFF_MSG	(8* MSG_MAXLEN * KEY_LENGTH * HSINE_POINTS * (SND_BITS / 8))
#define SND_BUFF_HDR	(HDR_LEN * HSINE_POINTS * (SND_BITS / 8))
#define SND_BUFF_MARGIN (MARGIN_LEN * (SND_BITS / 8))

#endif