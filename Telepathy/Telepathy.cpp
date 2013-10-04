// Telepathy.cpp : main project file.
#include "stdafx.h"
#include "frmMain.h"

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")

using namespace Telepathy;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it	
	Application::Run(gcnew frmMain());
	return 0;
}

// Function to Inject Remote DLLs
void InjectDLL(DWORD PID, char* szLibPath)
{
    // INIT LOCAL VARIABLES        
    void* pLibRemote;    
	hKernel32 = GetModuleHandle(L"kernel32");
	HANDLE pLoadLibrary = GetProcAddress(hKernel32, "LoadLibraryA");
    
    // GET ProcessID    
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);	

    // Allocate remote memory
    pLibRemote = VirtualAllocEx(hProcess, NULL, MAX_PATH, 
                                MEM_COMMIT, PAGE_READWRITE);
    
    // Write szLibPath on allocated memory
    WriteProcessMemory(hProcess, pLibRemote, (void*)szLibPath,
                       MAX_PATH, NULL);
    
    // Load lib into the remote process (CreateRemoteThread + LoadLibrary)
    hThread = CreateRemoteThread(hProcess, NULL, 0, 
                                 (LPTHREAD_START_ROUTINE) pLoadLibrary,
                                 pLibRemote, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);                                                                   
    
    // Get handle of the loaded module
    GetExitCodeThread(hThread, &hLibModule);
    
    // Clean up                 
    CloseHandle(hThread);
    VirtualFreeEx(hProcess, pLibRemote, 0, MEM_RELEASE);
}

// Function to Eject the DLL loaded
void EjectDLL()
{
     HANDLE hThread;
     HANDLE pFreeLibrary = GetProcAddress(hKernel32, "FreeLibrary");
     
     // Unload lib from target process (CreateRemoteThread + FreeLibrary)
     hThread = CreateRemoteThread(hProcess, NULL, 0,
                                  (LPTHREAD_START_ROUTINE) pFreeLibrary,
                                  (void*)hLibModule, 0, NULL);
     WaitForSingleObject(hThread, INFINITE);                                                      
     
     // Clean up
     CloseHandle(hThread);
}

// Function to call any function by name in any DLL
DWORD CallFunctionByName(char* dllname, char* funcname, void* params, DWORD size, BOOL remotecopy)
{
    void* pTemp = NULL;
    void* pTmp = NULL;
    DWORD pFunction;     
    DWORD ret;  
    void* pParams = params;
    
    // Get the function address
    pTemp = LoadLibraryA(dllname);
    pFunction = (DWORD)GetProcAddress((HMODULE)pTemp, funcname);
    FreeLibrary((HMODULE)pTemp);    
    
	// Call the function
	if (pFunction)
		ret = CallFunction((pFunction + hLibModule - (DWORD)pTemp), params, size, remotecopy);

	// Return value
	return ret;
}


DWORD CallFunction(DWORD address, void* params, DWORD size, BOOL remotecopy)
{
	HANDLE hThread;
    void* pTemp = NULL;
    void* pTmp = NULL;
    DWORD ret;  
    void* pParams = params;
        
    // Check params
    if ((remotecopy) && (size > 0))
    {        
        // Allocate remote memory
        pTmp = VirtualAllocEx(hProcess, NULL, size, MEM_COMMIT, PAGE_READWRITE);
        
        // Write szLibPath on allocated memory
        WriteProcessMemory(hProcess, pTmp, (void*)pParams, size, NULL); 
        
        pParams = pTmp;
    } 
    
    // Call the function
    hThread = CreateRemoteThread(hProcess, NULL, 0, 
                                 (LPTHREAD_START_ROUTINE) (address),
                                 pParams, 0, NULL);
    WaitForSingleObject(hThread, INFINITE);                                                                   
    GetExitCodeThread(hThread, &ret);        
    
    // Clean up
    CloseHandle(hThread);    
    if (pTmp != NULL) 
        VirtualFreeEx(hProcess, pTmp, 0, MEM_RELEASE);

    // Return value
	return ret;
}

// Read remote string and show it
void ReadRemoteString( DWORD PID, DWORD pointer, char* ret, DWORD size )
{        
    DWORD readed = 0;
    
    // Initialize buffers
    memset(ret, 0, size);           
    
	// Open process
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);

    // Read the memory
    ReadProcessMemory(hProcess, (void*)pointer, ret, size, &readed); 
}

// MessageBox Hidden
void ShowHiddenMsgBox()
{
	DWORD base = (DWORD)GetModuleHandle(NULL);
	System::Windows::Forms::MessageBox::Show(
		"Test from hidden function", 
		"Hidden MsgBox", 
		System::Windows::Forms::MessageBoxButtons::OK);
}

int GetRemoteCalls( DWORD PID, int* calls )
{
	// Internal variables
	DWORD base = 0x00401000;
	DWORD sectionsize = 0x10000;
	DWORD OPCODE = 0xE8; // ASM CALL       
	DWORD pointer;
	DWORD readed = 0;
	LPMODULEINFO lpmod = new MODULEINFO();
	int ret = 0;
	BOOL ok = FALSE;
	
	// REMOTE VALUES
	BYTE rop = 0x00;
	DWORD address = 0x00;

	// Open process	
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	if ((int)hProcess == 0) 
		return -1;  

	// Set EntryPoint	
	ok = GetModuleInformation(hProcess, 0, lpmod, sizeof(*lpmod));
	if (ok)
	{
		base = ((DWORD)lpmod->EntryPoint & 0xFFFF0000) + 0x1000;		
		sectionsize = lpmod->SizeOfImage;
	}


	// Read the memory
	for (pointer = base; pointer <= base+sectionsize; pointer++)
	{
		ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(pointer), reinterpret_cast<LPVOID>(&rop), 1, &readed); 
		if (rop == OPCODE)
		{
			ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(pointer+1), reinterpret_cast<LPVOID>(&address), 4, &readed); 			
			address += pointer + 5;
			if ((address >= base) && (address <= base + sectionsize))
			{
				*calls = address;
				calls++;
				ret++;
			}
		}
	}

	// return size of calls
	return ret;
}