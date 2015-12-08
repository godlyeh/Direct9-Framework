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

	bool ContainsBitwise;
	bool RetrieveAddress;
	MODULEENTRY32 Module;
	FDWORD *Offset;
}CorePattern;

class CPatternScanner
{
public:
	CPatternScanner(HANDLE ProcessHandle, CMemoryScanner *MemScanner);
	~CPatternScanner();

public:
	bool __fastcall CompareBytes(CorePattern *Pattern, BYTE *ByteArray);
	bool FoundAllOffsetsInModule(MODULEENTRY32 *me32);

public:
	void Scan();
	void SetupPattern(MODULEENTRY32* Module, PCoreString Pattern, CorePattern* PatternOut, ePatternScanType Type);
	void RegisterPattern(FDWORD* Offset, MODULEENTRY32* Module, PCoreString BytePattern, bool GetAddress = true, ePatternScanType Type = ePatternScanType::SCAN_BYTES);
	FDWORD FindPattern(MODULEENTRY32* Module, PCoreString Pattern, ePatternScanType Type = ePatternScanType::SCAN_BYTES, FDWORD* Out = NULL);

private:
	HANDLE Handle;
	CMemoryScanner *MemoryScanner;

	std::vector<CorePattern> Patterns;
	std::vector<MODULEENTRY32> FilesToScan;
};