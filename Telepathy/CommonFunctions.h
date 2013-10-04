#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>

//  Forward declarations:
BOOL GetProcessList( );
BOOL ListProcessModules( DWORD );
BOOL ListProcessThreads( DWORD );
void printError( TCHAR* );