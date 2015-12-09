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
	MemoryScanner->Read(CS16Offset->PlayerInfo, PlayerInfo, sizeof(cs16_player_info_t) * CS16_MAX_CLIENTS);

	// Fix vars
	LocalIndex += 1;

	// Handle model array
	MemoryScanner->Read(CS16Offset->gModels, ModelArray, sizeof(DWORD) * CS16_MAX_MODELS);

	// Map string
	if (strstr(MapName, ".bsp"))
	{
		*(strrchr(MapName, '.')) = 0;
		strcpy_s(MapName, strrchr(MapName, '/') + 1);
	}
}

void CS16EngineInfo::ReadGameInfo()
{
	// Read game
	MemoryScanner->Read(CS16Offset->Entity, Entity, sizeof(cs16_cl_entity_t) * MaxEntity);
	MemoryScanner->Read(CS16Offset->CameraMatrix, CameraMatrix, sizeof(CameraMatrix));

	GetModelByIndex(&Entity[LocalIndex]);
}

cs16_cl_entity_t* CS16EngineInfo::GetLocalPlayer()
{
	return &Entity[LocalIndex];
}

cs16_cl_entity_t* CS16EngineInfo::GetEntityByIndex(int Index)
{
	return &Entity[Index];
}

cs16_player_info_t* CS16EngineInfo::GetLocalPlayerInfo()
{
	return &PlayerInfo[LocalIndex];
}

cs16_player_info_t* CS16EngineInfo::GetPlayerInfoByIndex(int Index)
{
	return &PlayerInfo[Index];
}

cs16_model_t* CS16EngineInfo::GetModelByIndex(int Index)
{
	// Fill model addr list
	DWORD TmpModel = 0;
	static cs16_model_t* RetModel = new cs16_model_t; ZeroMemory(RetModel, sizeof(cs16_model_t));
	MemoryScanner->Read(ModelArray[Index], RetModel, sizeof(cs16_model_t));
	if (RetModel)
		return RetModel;

	return NULL;
}

cs16_model_t* CS16EngineInfo::GetModelByIndex(cs16_cl_entity_t *pEntity)
{
	for (int i = 0; i < CS16_MAX_MODELS; ++i)
	{
		if (pEntity->model == ModelArray[i])
			return GetModelByIndex(i);
	}

	return NULL;
}

bool CS16EngineInfo::WorldToScreen(float* WorldPos, float* Out)
{
	Out[0] = (CameraMatrix[0][0] * WorldPos[0]) + (CameraMatrix[1][0] * WorldPos[1]) + (CameraMatrix[2][0] * WorldPos[2]) + CameraMatrix[3][0];
	Out[1] = (CameraMatrix[0][1] * WorldPos[0]) + (CameraMatrix[1][1] * WorldPos[1]) + (CameraMatrix[2][1] * WorldPos[2]) + CameraMatrix[3][1];
	Out[2] = (CameraMatrix[0][3] * WorldPos[0]) + (CameraMatrix[1][3] * WorldPos[1]) + (CameraMatrix[2][3] * WorldPos[2]) + CameraMatrix[3][3];

	float ZDelta = 1.0f / Out[2];

	if (Out[2] != 0.0f)
	{
		(Out[0] *= ZDelta) = (Out[0] + 1.0f) * (g_Core->ScreenInfo.Width / 2);
		(Out[1] *= ZDelta) = (-Out[1] + 1.0f) * (g_Core->ScreenInfo.Height / 2);
		g_Core->Render->CompensateRenderLag(&Out[0], &Out[1]);
	}

	return ZDelta > 0.0f;
}

void CS16EngineInfo::VectorLine(float* From, float* To, float lw, COLOR32 Color)
{
	Vec3 ScreenSrc, ScreenDest;
	if (!WorldToScreen(From, ScreenSrc) || !WorldToScreen(To, ScreenDest))
		return;

	g_Core->Render->Line(ScreenSrc[0], ScreenSrc[1], ScreenDest[0], ScreenDest[1], lw, Color);
}

void CS16EngineInfo::Line3DBox(Vec3 WorldPos, Vec3 Mins, Vec3 Maxs, float* Angles, float lw, COLOR32 Color)
{
	Vec3 vF, vR, vU;
	VecMath->AngleVectors(Angles, vF, vR, vU);

	float flForward = Maxs.y;
	float flBack = Mins.y;
	float flRight = Maxs.x;
	float flLeft = Mins.x;
	float flUp = Maxs.z;
	float flDown = Mins.z;

	flForward += 15.0f;
	flBack -= 5.0f;
	flRight += 5.0f;
	flLeft -= 5.0f;
	flUp -= 5.0f;
	flDown -= 2.0f;

	Vec3 vUFLeft = WorldPos + vU * flUp + vF * flForward + vR*flLeft; // vUFLeft = Top left front
	Vec3 vUFRight = WorldPos + vU * flUp + vF * flForward + vR*flRight; // vUFRight = Top right front
	Vec3 vUBLeft = WorldPos + vU * flUp + vF * flBack + vR * flLeft; // vUBLeft = Top left back
	Vec3 vUBRight = WorldPos + vU * flUp + vF * flBack + vR * flRight; // vUBRight = Top right back

	Vec3 vBFLeft = WorldPos + vU * flDown + vF *flForward + vR*flLeft; // vBFLeft = Bottom left front
	Vec3 vBFRight = WorldPos + vU * flDown + vF *flForward + vR*flRight; // vBFRight = Bottom right front
	Vec3 vBBLeft = WorldPos + vU * flDown + vF *flBack + vR*flLeft; // vBBLeft = Bottom left back
	Vec3 vBBRight = WorldPos + vU * flDown + vF *flBack + vR*flRight; // vBBRight = Bottom right back

	//Top Box
	VectorLine(vUBLeft, vUBRight, lw, Color); // Back left -> Back right
	VectorLine(vUBRight, vUFRight, lw, Color); // Back right -> Front right
	VectorLine(vUFRight, vUFLeft, lw, Color); // Front right -> Front left
	VectorLine(vUFLeft, vUBLeft, lw, Color); // Front left -> Back right

	//Mid Box
	VectorLine(vUBLeft, vBBLeft, lw, Color); // Top left -> Bottom left
	VectorLine(vUBRight, vBBRight, lw, Color); // Top right -> Bottom right
	VectorLine(vUFRight, vBFRight, lw, Color); // Top right -> Bottom right
	VectorLine(vUFLeft, vBFLeft, lw, Color); // Top left -> Bottom left

	//Bottom Box
	VectorLine(vBBLeft, vBBRight, lw, Color); // Back left -> Back right
	VectorLine(vBBRight, vBFRight, lw, Color); // Back right -> Front right
	VectorLine(vBFRight, vBFLeft, lw, Color); // Front right -> Front left
	VectorLine(vBFLeft, vBBLeft, lw, Color); // Front left -> Back right
}