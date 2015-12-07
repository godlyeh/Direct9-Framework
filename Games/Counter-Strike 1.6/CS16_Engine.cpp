/*

	File: CS16_Engine

	Used for cs16 engine handling

*/
#include "CS16_Main.h"

void CS16EngineInfo::ReadGameInfoSlow()
{
	// Read game
	MemoryScanner->Read(CS16Offset->MaxEntity, &MaxEntity, sizeof(int));
	MemoryScanner->Read(CS16Offset->LocalIndex, &LocalIndex, sizeof(int));
	MemoryScanner->Read(CS16Offset->MapName, &MapName, sizeof(MapName));
	MemoryScanner->Read(CS16Offset->TeamInfo, TeamInfo, sizeof(cs16_teaminfo_t) * CS16_MAX_CLIENTS);
	
	// Fix vars
	LocalIndex += 1;
	*(strrchr(MapName, '.')) = 0;
	strcpy_s(MapName, strrchr(MapName, '/') + 1);
}

void CS16EngineInfo::ReadGameInfo()
{
	// Read game
	MemoryScanner->Read(CS16Offset->Entity, Entity, sizeof(cs16_cl_entity_t) * MaxEntity);
	MemoryScanner->Read(CS16Offset->CameraMatrix, CameraMatrix, sizeof(CameraMatrix));
}

bool CS16EngineInfo::WorldToScreen(float *WorldPos, float *Out)
{
	Out[0] = (CameraMatrix[0][0] * WorldPos[0]) + (CameraMatrix[1][0] * WorldPos[1]) + (CameraMatrix[2][0] * WorldPos[2]) + CameraMatrix[3][0];
	Out[1] = (CameraMatrix[0][1] * WorldPos[0]) + (CameraMatrix[1][1] * WorldPos[1]) + (CameraMatrix[2][1] * WorldPos[2]) + CameraMatrix[3][1];
	Out[2] = (CameraMatrix[0][3] * WorldPos[0]) + (CameraMatrix[1][3] * WorldPos[1]) + (CameraMatrix[2][3] * WorldPos[2]) + CameraMatrix[3][3];

	float ZDelta = 1.0f / Out[2];

	if (Out[2] != 0.0f)
	{
		(Out[0] *= ZDelta) = (Out[0] + 1.0f) * (g_Core->ScreenInfo.Width / 2);
		(Out[1] *= ZDelta) = (-Out[1] + 1.0f) * (g_Core->ScreenInfo.Height / 2);
	}

	return ZDelta > 0.0f;
}