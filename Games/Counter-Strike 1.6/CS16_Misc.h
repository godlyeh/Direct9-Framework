/*

	File: CS16_Misc

	Used for offsets, settings etc

*/

class CS16OffsetInfo
{
public:
	// Offset Settings
	CSettings* OffsetSettings = NULL;
	CPatternScanner* PatternScanner = NULL;

	// Modules
	MODULEENTRY32 dllHW;
	MODULEENTRY32 dllClient;

	// Setting offsets
	FDWORD gEngfuncs;		CoreString s_gEngfuncs;
	FDWORD gStudio;			CoreString s_gStudio;
	FDWORD gPlayerMove;		CoreString s_gPlayerMove;
	FDWORD MaxEntity;		CoreString s_MaxEntity;
	FDWORD Entity;			CoreString s_Entity;

	// Offset settings
	
	// Funcs
	void InitOffsets(CMemoryScanner *MemScanner);
	void RetrieveOffsets();
};