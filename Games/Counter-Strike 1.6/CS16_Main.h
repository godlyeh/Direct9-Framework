/*

	File: CS16_Main

	You only need to include this file to use these

*/

// Framework inclues
#include "..\..\Framework\Core.h"

// Game includes
#include "CS16_Structs.h"

#include "CS16_DVars.h"
#include "CS16_ESP.h"
#include "CS16_Misc.h"
#include "CS16_Engine.h"


class CS16Main
{
public:
	CS16Main();
	~CS16Main();
};

extern CS16EngineInfo* CS16Engine;
extern CS16OffsetInfo* CS16Offset;
extern CS16DVars* CS16DVar;