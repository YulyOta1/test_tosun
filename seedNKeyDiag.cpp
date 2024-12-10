//*****************************************************************************
/// @file        seedNKeyXcpWin.c
/// @author      Alex Lunkenheimer (ETAS/PAC-Lr)
/// @responsible author
/// @brief       DLL-Main for Seed'n Key for XCP
/// @history     2002-09-16,Lr: - draft
///              2003-02-07,Lr: - DLL-API using extern "C"
///                             - adapted privileges to XCP-Spec V1.0,Rev22
//*****************************************************************************

//*****************************************************************************
//                               includes
//*****************************************************************************
#include <assert.h>
#include "seedNKeyDiag.h"

//*****************************************************************************
//                               variables
//*****************************************************************************

//*****************************************************************************
//                               prototypes
//*****************************************************************************

//*****************************************************************************
/// @fn   DllMain ... Windows DLL entrance point
//*****************************************************************************
KEYGEN_API GenerateKeyEx(
	const unsigned char* ipSeedArray,              /* Array for the seed [in] */
	unsigned int iSeedArraySize,                   /* Length of the array for the seed [in] */
	const unsigned int iSecurityLevel,             /* Security level [in] */
	const char* ipVariant,                         /* Name of the active variant [in] */
	unsigned char* iopKeyArray,                    /* Array for the key [in, out] */
	unsigned int iMaxKeyArraySize,                 /* Maximum length of the array for the key [in] */
	unsigned int& oActualKeyArraySize)             /* Length of the key [out] */
{
	unsigned char Key[4] = { 0,0,0,0 };
	unsigned char Seed[4];

	Seed[0] = ipSeedArray[0];
	Seed[1] = ipSeedArray[1];
	Seed[2] = ipSeedArray[2];
	Seed[3] = ipSeedArray[3];

	char customer_id = 0x33;

	//begin calculate key from seed------------------------------------------------------------
	switch (iSecurityLevel)
	{
	case 0x01://for security access with Services 0x27 01 ->0x27 02
		break;
	case 0x03://for security access with Services 0x27 03 -> 0x27 04
		break;
	case 0x05://for security access with Services 0x27 05 -> 0x27 06
		break;
	case 0x09://for security access with Services 0x27 09 ->0x27 0A
		break;
	default:break;
	}
	//end calculate key from seed------------------------------------------------------------
	//Copy key to the output buffer 
	//Note: The first byte of the key array will be the first key byte of the bus message
	iopKeyArray[0] = ipSeedArray[0] ^ customer_id;
	iopKeyArray[1] = (~ipSeedArray[1]) ^ customer_id;
	iopKeyArray[2] = ipSeedArray[2] + customer_id;
	iopKeyArray[3] = ~(ipSeedArray[3] + customer_id + iSecurityLevel);
	//setting length of key
	oActualKeyArraySize = 4;
	return KGRE_Ok;
}

KEYGEN_API ASAP1A_CCP_ComputeKeyFromSeed(unsigned char* ipSeedArray,          /* Array for the seed [in] */
	UINT16 iSeedArraySize,               /* Length of the array for the seed [in] */
	unsigned char* opKey,                /* Array for the key [in, out] */
	UINT16 maxSizeKey,                   /* Maximum length of the array for the key [in] */
	UINT16* opSizeKey)                    /* Length of the key [out] */
{
	*opSizeKey = 4;
	return KGRE_Ok;
}

KEYGEN_API SeedAndKey_Type2(UINT32 ASeed, UINT32* AKey)
{
	return KGRE_Ok;
}

KEYGEN_API SeedAndKey_Type3(void* ASeed, void* AKey)
{
	return KGRE_Ok;
}
