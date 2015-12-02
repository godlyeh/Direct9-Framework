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
	void Log(eLogType Type, PCHAR szText, ...);
	void Log(PCHAR szText, ...);
	void LogI(eLogType Type, PCHAR szText, int Value);
	void LogI(PCHAR szText, int Value);
	void LogF(eLogType Type, PCHAR szText, float Value);
	void LogF(PCHAR szText, float Value);
	void LogX(eLogType Type, PCHAR szText, DWORD Value);
	void LogX(PCHAR szText, DWORD Value);
	void LogP(eLogType Type, PCHAR szText, FDWORD Value);
	void LogP(PCHAR szText, FDWORD Value);
}

namespace Utilities // Framework utilities
{
	DWORD GetProcessInfo(PCHAR ProcessName, bool Log = false, PROCESSENTRY32 *pe32Out = NULL);
	void GetWindowInformation(HWND hWnd, LPSCREENINFO pScreenInfo);
	void RemoveSpaces(PCHAR Text, PCHAR Out);
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
	BOOL Init(PCHAR ProcessName);
	void CleanUp();
	BOOL Running();
	MODULEENTRY32* GetModuleInfo(PCHAR ModuleName, bool Log = false, MODULEENTRY32 *me32Out = NULL);
};