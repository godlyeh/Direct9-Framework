/*

	File: ByteScan

	Used for byte scanning

*/

enum ePatternScanType : int
{
	SCAN_BYTES = 0,
	SCAN_STRING = 1
};

typedef struct
{
	CoreString szPattern;
	BYTE *bPattern;
	DWORD dwLength;
	ePatternScanType ScanType;

	MODULEENTRY32 Module;
	CoreOffset *Offset;
}CorePattern;

class CPatternScanner
{
public:
	CPatternScanner(HANDLE ProcessHandle, CMemoryScanner *MemScanner);
	~CPatternScanner();

public:
	bool __fastcall CompareBytes(CorePattern *Pattern, BYTE *ByteArray);

public:
	void Scan();
	void SetupPattern(MODULEENTRY32* Module, PCHAR Pattern, CorePattern* PatternOut, ePatternScanType Type);
	void RegisterPattern(CoreOffset* Offset, MODULEENTRY32* Module, PCHAR BytePattern, ePatternScanType Type = ePatternScanType::SCAN_BYTES);
	FDWORD FindPattern(MODULEENTRY32* Module, PCHAR Pattern, ePatternScanType Type = ePatternScanType::SCAN_BYTES, CoreOffset* Out = NULL);

private:
	HANDLE Handle;
	CMemoryScanner *MemoryScanner;

	std::vector<CorePattern> Patterns;
	std::vector<MODULEENTRY32> FilesToScan;
};