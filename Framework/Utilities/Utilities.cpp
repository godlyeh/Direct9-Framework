/*

	File: Utilities

	Used for making life easier

*/
#include "..\Core.h"

// Get process id through toohelp32 snapshot
DWORD Utilities::GetProcessInfo(PCoreString ProcessName, bool Log, PROCESSENTRY32 *pe32Out)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Log) CLog::Log(eLogType::DEBUG, " > Creating Toolhelp32 Snapshot");
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		if (Log) CLog::Log(eLogType::DEBUG, "  > FAILED");
		return 0;
	}
	if (Log) CLog::Log(eLogType::DEBUG, "  > SUCCESS [0x%p]", hSnapshot);

	static PROCESSENTRY32 pe32; ZeroMemory(&pe32, sizeof(PROCESSENTRY32));
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (Log) CLog::Log(eLogType::DEBUG, " > Looping through processes");
	Process32First(hSnapshot, &pe32);
	while (Process32Next(hSnapshot, &pe32))
	{
		if (!_stricmp(ProcessName, pe32.szExeFile))
		{
			if (Log) CLog::Log(eLogType::DEBUG, "  > Found process %s [0x%p]", ProcessName, pe32.th32ProcessID);
			CloseHandle(hSnapshot);
			if (pe32Out) memcpy(pe32Out, &pe32, sizeof(PROCESSENTRY32));
			return pe32.th32ProcessID;
		}
	}

	if (Log) CLog::Log(eLogType::DEBUG, "  > Could not find %s", ProcessName);
	CloseHandle(hSnapshot);

	return 0;
}

void Utilities::GetWindowInformation(HWND hWnd, LPSCREENINFO pScreenInfo)
{
	if (!pScreenInfo)
		return;

	// Get window info
	WINDOWINFO Info;
	Info.cbSize = sizeof(WINDOWINFO);
	if (GetWindowInfo(hWnd, &Info) == FALSE)
		return;

	// Get screen res
	int ResX = GetSystemMetrics(SM_CXSCREEN);
	int ResY = GetSystemMetrics(SM_CYSCREEN);

	// Get process window info
	SCREENINFO Screen;
	Screen.X = (float)Info.rcClient.left;
	Screen.Y = (float)Info.rcClient.top;
	Screen.Width = Info.rcClient.right - Screen.X;
	Screen.Height = Info.rcClient.bottom - Screen.Y;
	Screen.WindowedFullscreen = !(Info.dwExStyle &WS_EX_TOPMOST) && (Screen.Width == ResX && Screen.Height == ResY);
	Screen.Fullscreen = (Info.dwExStyle &WS_EX_TOPMOST) && (Screen.Width == ResX && Screen.Height == ResY);
	Screen.Minimized = (IsIconic(hWnd) == TRUE);

	memcpy(pScreenInfo, &Screen, sizeof(SCREENINFO));
}

void Utilities::RemoveSpaces(PCoreString Text, PCoreString Out)
{
	std::string RetStr(Text);
	while (RetStr.find(' ') != -1) RetStr.erase(RetStr.find(' '), 1);
	strcpy_s(Out, RetStr.size() + 1, RetStr.c_str());
}

PCHAR Utilities::GetStringWithArgs(PCoreString Text, ...)
{
	static char szBuffer[1024]; ZeroMemory(&szBuffer, sizeof(szBuffer));
	GET_VA_ARGS(Text, szBuffer);
	return szBuffer;
}