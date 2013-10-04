#ifndef _DLL_H_
#define _DLL_H_

#if BUILDING_DLL
# define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
# define DLLIMPORT __declspec (dllimport)
#endif /* Not BUILDING_DLL */

#include <windows.h>

DLLIMPORT char* HelloWorld1 (char*);
DLLIMPORT DWORD HelloWorld2 (char*);


#endif /* _DLL_H_ */
