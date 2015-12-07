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
	FDWORD TeamInfo;		CoreString s_TeamInfo;
	FDWORD LocalIndex;		CoreString s_LocalIndex;
	FDWORD MapName;			CoreString s_MapName;
	FDWORD CameraMatrix;	CoreString s_CameraMatrix;

	// Offset settings
	
	// Funcs
	void InitOffsets();
	void RetrieveOffsets();
};