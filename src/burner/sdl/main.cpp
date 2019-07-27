/* ----------------
 * Retry using SDL2
 * Jul 2019 CF
 * -----------------*/

#include "burner.h"

int nAppVirtualFps = 0;

#undef main

int main(int argc, char *argv[])
{
   int returnCode = 0;
   
	BurnLibInit();

	switch (argc)
	{
      case 2:
      {
         uint32_t GameIdx = 0;
         returnCode = BurnDrvGetDriverIndex(argv[1], &GameIdx);
         if (0 == returnCode)
         {
            DrvInit(GameIdx, 0);

            //RunMessageLoop();

            DrvExit();
            MediaExit();
         }
      }
      break;
      
      default:
         printf ("Usage: fbnsdl <romname>\n   ie: fbnsdl uopoko\n Note: no extension.\n\n");
      break;
	}

	BurnLibExit();
	
	return returnCode;
}

/* const */ TCHAR* ANSIToTCHAR(const char* pszInString, TCHAR* pszOutString, int nOutSize)
{
#if defined (UNICODE)
	static TCHAR szStringBuffer[1024];

	TCHAR* pszBuffer = pszOutString ? pszOutString : szStringBuffer;
	int nBufferSize  = pszOutString ? nOutSize * 2 : sizeof(szStringBuffer);

	if (MultiByteToWideChar(CP_ACP, 0, pszInString, -1, pszBuffer, nBufferSize)) {
		return pszBuffer;
	}

	return NULL;
#else
	if (pszOutString) {
		_tcscpy(pszOutString, pszInString);
		return pszOutString;
	}

	return (TCHAR*)pszInString;
#endif
}


/* const */ char* TCHARToANSI(const TCHAR* pszInString, char* pszOutString, int nOutSize)
{
#if defined (UNICODE)
	static char szStringBuffer[1024];
	memset(szStringBuffer, 0, sizeof(szStringBuffer));

	char* pszBuffer = pszOutString ? pszOutString : szStringBuffer;
	int nBufferSize = pszOutString ? nOutSize * 2 : sizeof(szStringBuffer);

	if (WideCharToMultiByte(CP_ACP, 0, pszInString, -1, pszBuffer, nBufferSize, NULL, NULL)) {
		return pszBuffer;
	}

	return NULL;
#else
	if (pszOutString) {
		strcpy(pszOutString, pszInString);
		return pszOutString;
	}

	return (char*)pszInString;
#endif
}

bool bAlwaysProcessKeyboardInput=0;

bool AppProcessKeyboardInput()
{
	return true;
}

