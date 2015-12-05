/*

	File: UtilCore

	Used for utilities such as logging, memory editing etc...

*/

enum eLogType : int
{
	NONE = 0,
	NORMAL = 1,
	HIGH = 2,
	DEBUG = 3
};

static char szLogType[][16]
{
	"NONE",
	"NORMAL",
	"HIGH",
	"DEBUG"
};

namespace CLog // Console logging
{
	// Variables
	static bool LogToConsole = true;
	static bool LogToFile = false;
	static eLogType LogLevel = eLogType::DEBUG;

	// Funcs
	void Log(eLogType Type, PCoreString szText, ...);
	void Log(PCoreString szText, ...);
	void LogI(eLogType Type, PCoreString szText, int Value);
	void LogI(PCoreString szText, int Value);
	void LogF(eLogType Type, PCoreString szText, float Value);
	void LogF(PCoreString szText, float Value);
	void LogX(eLogType Type, PCoreString szText, DWORD Value);
	void LogX(PCoreString szText, DWORD Value);
	void LogP(eLogType Type, PCoreString szText, FDWORD Value);
	void LogP(PCoreString szText, FDWORD Value);
}

namespace Utilities // Framework utilities
{
	DWORD GetProcessInfo(PCoreString ProcessName, bool Log = false, PROCESSENTRY32 *pe32Out = NULL);
	void GetWindowInformation(HWND hWnd, LPSCREENINFO pScreenInfo);
	void RemoveSpaces(PCoreString Text, PCoreString Out);
	PCHAR GetStringWithArgs(PCoreString Text, ...);
}

class CMemoryScanner // Memory handling
{
public:
	CMemoryScanner(HANDLE ProcessHandle);
	~CMemoryScanner();

	LPVOID Read(FDWORD Address, LPVOID lpBuffer, SIZE_T Length);

private:
	HANDLE Handle = INVALID_HANDLE_VALUE;
};

class CProcess // Process handling
{
public:
	// Variables
	CoreString Name;
	HANDLE Handle = INVALID_HANDLE_VALUE;
	HWND HWnd = NULL;
	DWORD Id = 0;
	
	// Funcs
	BOOL Init(PCoreString ProcessName);
	void CleanUp();
	BOOL Running();
	MODULEENTRY32* GetModuleInfo(PCoreString ModuleName, bool Log = false, MODULEENTRY32 *me32Out = NULL);
};