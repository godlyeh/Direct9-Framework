/*

	File: CS16_Misc

	Used for offsets, settings etc

*/

namespace CS16Offset
{
	// Offset Settings
	static CSettings* OffsetSettings = NULL;
	static CPatternScanner* PatternScanner = NULL;

	// Modules
	static MODULEENTRY32 dllHW;
	static MODULEENTRY32 dllClient;

	// Setting offsets
	static CoreOffset gEngfuncs;		static CoreString s_gEngfuncs;
	static CoreOffset gStudio;			static CoreString s_gStudio;
	static CoreOffset gPlayerMove;		static CoreString s_gPlayerMove;

	// Offset settings
	
	// Funcs
	void InitOffsets(CMemoryScanner *MemScanner);
	void RetrieveOffsets();
}