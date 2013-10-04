/* Replace "dll.h" with the name of your header */
#include "dll.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

DLLIMPORT char* HelloWorld1 (char* txt)
{
    char text[100];    
    memset(text, 0, 100);
    strcat(text, "Hello World from DLL!\n");    
    strcat(text, txt);    
    MessageBox (0, text, "Hi", MB_ICONINFORMATION);
    return "test return";
}

DLLIMPORT DWORD HelloWorld2 (char* txt)
{
    char text[100];    
    memset(text, 0, 100);
    strcat(text, "Hello World from DLL!\n");    
    strcat(text, txt);    
    MessageBox (0, text, "Hi", MB_ICONINFORMATION);
    return 0x666;
}


BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    switch (reason)
    {
      case DLL_PROCESS_ATTACH:
        break;

      case DLL_PROCESS_DETACH:
        break;

      case DLL_THREAD_ATTACH:
        break;

      case DLL_THREAD_DETACH:
        break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}
