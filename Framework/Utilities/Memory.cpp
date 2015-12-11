/*

	File: Memory

	Used for memory handling

*/
#include "..\Core.h"

CMemoryScanner::CMemoryScanner(HANDLE ProcessHandle)
{
	Handle = ProcessHandle;
}

CMemoryScanner::~CMemoryScanner()
{
	if (Handle != INVALID_HANDLE_VALUE)
		CloseHandle(Handle);
}

LPVOID CMemoryScanner::Read(FDWORD Address, LPVOID lpBuffer, SIZE_T Length)
{
	ReadProcessMemory(Handle, (LPCVOID)Address, lpBuffer, Length, NULL);
	return lpBuffer;
}