/*

	File: CS16_Main

	You only need to include this file to use these

*/

// Framework inclues
#include "..\..\Framework\Core.h"

// Game includes
#include "CS16_Structs.h"
#include "CS16_Misc.h"


class CS16Main
{
public:
	CS16Main();
	~CS16Main();

public:
	CMemoryScanner* MemoryScanner = NULL;
	UI_Window* SettingsWindow = NULL;
};