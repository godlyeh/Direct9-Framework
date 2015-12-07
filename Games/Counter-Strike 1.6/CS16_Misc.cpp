/*

	File: CS16_Misc

	Used for offsets, settings etc

*/
#include "CS16_Main.h"

void CS16OffsetInfo::InitOffsets()
{
	// Create new settings handler
	OffsetSettings = new CSettings("CS16_Offsets");
	PatternScanner = new CPatternScanner(g_Core->Process->Handle, MemoryScanner);

	// Copy offset strings
	strcpy_s(s_gEngfuncs, "B? 00 00 00 00 F3 A5 74 00 5?");
	//strcpy_s(s_gStudio, "B? 00 00 00 00 C7 00 00 00 00 00");
	strcpy_s(s_gPlayerMove, "A? 00 00 00 00 85 D? 0F 95 C1");
	strcpy_s(s_Entity, "8? 0D 00 00 00 00 8D 04 40");
	strcpy_s(s_MaxEntity, "3B 05 00 00 00 00 7D 17");
	strcpy_s(s_TeamInfo, "66 C7 86 00 00 00 00 00 00 EB 26");
	strcpy_s(s_LocalIndex, "8B 0D 00 00 00 00 8D 14 80 8B C1");
	strcpy_s(s_MapName, "B? 00 00 00 00 7D 05");
	strcpy_s(s_CameraMatrix, "8D B? 00 00 00 00 C7 07 00 00 00 00");

	// Register offsets
	CLog::Log(eLogType::HIGH, "Registering offset settings");
	OffsetSettings->Register("gEngfuncs", &s_gEngfuncs, eCoreVariableType::VAR_STRING);
	//OffsetSettings->Register("gStudio", &s_gStudio, eCoreVariableType::VAR_STRING);
	OffsetSettings->Register("gPlayerMove", &s_gPlayerMove, eCoreVariableType::VAR_STRING);
	OffsetSettings->Register("Entity", &s_Entity, eCoreVariableType::VAR_STRING);
	OffsetSettings->Register("MaxEntity", &s_MaxEntity, eCoreVariableType::VAR_STRING);
	OffsetSettings->Register("TeamInfo", &s_TeamInfo, eCoreVariableType::VAR_STRING);
	OffsetSettings->Register("LocalIndex", &s_LocalIndex, eCoreVariableType::VAR_STRING);
	OffsetSettings->Register("MapName", &s_MapName, eCoreVariableType::VAR_STRING);
	OffsetSettings->Register("CameraMatrix", &s_CameraMatrix, eCoreVariableType::VAR_STRING);
	CLog::Log(eLogType::HIGH, " Done");

	// Load offsets
	//OffsetSettings->LoadAllSettings();
	OffsetSettings->Save("Offsets");
}

void CS16OffsetInfo::RetrieveOffsets()
{
	// Wait for hw and client dlls to load
	CLog::Log("Waiting for game dlls");
	while (!g_Core->Process->GetModuleInfo("hw.dll", false, &dllHW));
	while (!g_Core->Process->GetModuleInfo("client.dll", false, &dllClient));
	CLog::Log(" HW [Base: 0x%p] [Size: 0x%p]", dllHW.modBaseAddr, dllHW.modBaseSize);
	CLog::Log(" Client [Base: 0x%p] [Size: 0x%p]", dllClient.modBaseAddr, dllClient.modBaseSize);

	// Register offsets
	CLog::Log("Registering offsets");
	PatternScanner->RegisterPattern(&gEngfuncs, &dllClient, s_gEngfuncs);
	//PatternScanner->RegisterPattern(&gStudio, &dllClient, s_gStudio);
	PatternScanner->RegisterPattern(&gPlayerMove, &dllClient, s_gPlayerMove);
	PatternScanner->RegisterPattern(&TeamInfo, &dllClient, s_TeamInfo);

	PatternScanner->RegisterPattern(&MaxEntity, &dllHW, s_MaxEntity);
	PatternScanner->RegisterPattern(&Entity, &dllHW, s_Entity);
	PatternScanner->RegisterPattern(&LocalIndex, &dllHW, s_LocalIndex);
	PatternScanner->RegisterPattern(&MapName, &dllHW, s_MapName);
	PatternScanner->RegisterPattern(&CameraMatrix, &dllHW, s_CameraMatrix);
	CLog::Log(" Done");

	// Retrieve offsets
	CLog::Log("Performing game scan");
	PatternScanner->Scan();
	CLog::Log(" Done");

	// Log
	CLog::Log("Game Offsets:");
	CLog::Log(" > gEngfuncs: 0x%p", gEngfuncs);
	//CLog::Log(" > gStudio: 0x%p", gStudio);
	CLog::Log(" > gPlayerMove: 0x%p", gPlayerMove);
	CLog::Log(" > MaxEntity: 0x%p", MaxEntity);
	CLog::Log(" > Entity: 0x%p", Entity);
	CLog::Log(" > TeamInfo: 0x%p", TeamInfo);
	CLog::Log(" > LocalIndex: 0x%p", LocalIndex);
	CLog::Log(" > MapName: 0x%p", MapName);
	CLog::Log(" > Camera Matrix: 0x%p", CameraMatrix);
}