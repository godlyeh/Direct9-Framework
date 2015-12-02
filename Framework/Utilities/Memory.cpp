/*

	File: Memory

	Used for memory handling

*/
#include "..\Core.h"

CMemoryScanner::CMemoryScanner(HANDLE ProcessHandle)
{
	Handle = ProcessHandle;
}

LPVOID CMemoryScanner::Read(FDWORD Address, LPVOID lpBuffer, SIZE_T Length)
{
	ReadProcessMemory(Handle, (LPCVOID)Address, lpBuffer, Length, NULL);
	return lpBuffer;
}