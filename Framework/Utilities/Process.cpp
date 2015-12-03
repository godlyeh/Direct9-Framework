/*

	File: Process

	Used for process handling

*/
#include "..\Core.h"

HWND WndResult = NULL;

BOOL CALLBACK EnumWindowsProcMy(HWND hWnd, LPARAM lParam)
{
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hWnd, &lpdwProcessId);
	if (lpdwProcessId == lParam)
	{
		WndResult = hWnd;
		return FALSE;
	}
	return TRUE;
}

BOOL CProcess::Init(PCoreString ProcessName)
{
	// Perform cleanup before initializing
	CleanUp();

	// Get process id
	CLog::Log(eLogType::HIGH, "> Getting process id");
	Id = Utilities::GetProcessInfo(ProcessName, true);
	if (Id == 0)
	{
		CLog::Log(eLogType::HIGH, " > FAILED");
		return FALSE;
	}
	CLog::Log(eLogType::HIGH, " > SUCCESS [0x%p]", Id);

	// Get process window
	CLog::Log(eLogType::HIGH, "> Getting process window");
	CLog::Log(eLogType::DEBUG, " > Enumerating windows");
	if (EnumWindows(EnumWindowsProcMy, Id) == TRUE)
	{
		CLog::Log(eLogType::DEBUG, "  > FAILED");
		return FALSE;
	}
	HWnd = WndResult;
	WndResult = NULL;
	if (HWnd == NULL)
	{
		CLog::Log(eLogType::HIGH, " > FAILED");
		return FALSE;
	}
	CLog::Log(eLogType::DEBUG, "  > SUCCESS");
	CLog::Log(eLogType::HIGH, " > SUCCESS [0x%p]", HWnd);

	// Get process handle
	CLog::Log(eLogType::HIGH, "> Opening process handle");
	Handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Id);
	if (Handle == INVALID_HANDLE_VALUE)
	{
		CLog::Log(eLogType::HIGH, " > FAILED");
		return FALSE;
	}
	CLog::Log(eLogType::HIGH, " > SUCCESS [0x%p]", Handle);

	strcpy_s(Name, ProcessName);

	return TRUE;
}

void CProcess::CleanUp()
{
	CLog::Log(eLogType::HIGH, "> Performing process cleanup");

	ZeroMemory(&Name, sizeof(Name));

	// Reset handle
	if (Handle != INVALID_HANDLE_VALUE)
	{
		CLog::Log(eLogType::DEBUG, "  > Handle reset");
		Handle = INVALID_HANDLE_VALUE;
	}

	// Reset hwnd
	if (HWnd != NULL)
	{
		CLog::Log(eLogType::DEBUG, "  > Hwnd reset");
		HWnd = NULL;
	}

	// Reset id
	if (Id != 0)
	{
		CLog::Log(eLogType::DEBUG, "  > Id reset");
		Id = 0;
	}

	CLog::Log(eLogType::HIGH, " > Done");
}

MODULEENTRY32* CProcess::GetModuleInfo(PCoreString ModuleName, bool Log, MODULEENTRY32 *me32Out)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, Id);

	if (Log) CLog::Log(eLogType::DEBUG, " > Creating Toolhelp32 Snapshot");
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		if (Log) CLog::Log(eLogType::DEBUG, "  > FAILED");
		return 0;
	}
	if (Log) CLog::Log(eLogType::DEBUG, "  > SUCCESS [0x%p]", hSnapshot);

	static MODULEENTRY32 me32; ZeroMemory(&me32, sizeof(MODULEENTRY32));
	me32.dwSize = sizeof(MODULEENTRY32);

	if (Log) CLog::Log(eLogType::DEBUG, " > Looping through modules");
	Module32First(hSnapshot, &me32);
	while (Module32Next(hSnapshot, &me32))
	{
		if (!_stricmp(ModuleName, me32.szModule))
		{
			if (Log) CLog::Log(eLogType::DEBUG, "  > Found module %s [0x%p]", ModuleName, me32.modBaseSize);
			CloseHandle(hSnapshot);
			if (me32Out) memcpy(me32Out, &me32, sizeof(MODULEENTRY32));
			return &me32;
		}
	}

	if (Log) CLog::Log(eLogType::DEBUG, "  > Could not find %s", ModuleName);
	CloseHandle(hSnapshot);

	return NULL;
}

BOOL CProcess::Running()
{
	DWORD Tmp = NULL;
	GetExitCodeProcess(Handle, &Tmp);
	return (Tmp == STILL_ACTIVE);
}