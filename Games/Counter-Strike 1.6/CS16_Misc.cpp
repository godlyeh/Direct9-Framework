/*

	File: CS16_Misc

	Used for offsets, settings etc

*/
#include "CS16_Main.h"

void CS16Offset::InitOffsets(CMemoryScanner *MemScanner)
{
	// Create new settings handler
	OffsetSettings = new CSettings("CS16_Offsets");
	PatternScanner = new CPatternScanner(g_Core->Process->Handle, MemScanner);

	// Copy offset strings
	strcpy_s(s_gEngfuncs, "B? 00 00 00 00 F3 A5 74 00 5?");
	strcpy_s(s_gStudio, "B? 00 00 00 00 C7 00 00 00 00 00");
	strcpy_s(s_gPlayerMove, "A? 00 00 00 00 85 D? 0F 95 C1");

	// Register offsets
	CLog::Log(eLogType::HIGH, "Registering offset settings");
	OffsetSettings->Register("gEngfuncs", &s_gEngfuncs, eCoreVariableType::VAR_STRING);
	OffsetSettings->Register("gStudio", &s_gStudio, eCoreVariableType::VAR_STRING);
	OffsetSettings->Register("gPlayerMove", &s_gPlayerMove, eCoreVariableType::VAR_STRING);
	CLog::Log(eLogType::HIGH, " Done");

	// Load offsets
	//OffsetSettings->LoadAllSettings();
	OffsetSettings->Save("Offsets");
}

void CS16Offset::RetrieveOffsets()
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
	PatternScanner->RegisterPattern(&gStudio, &dllClient, s_gStudio);
	PatternScanner->RegisterPattern(&gPlayerMove, &dllClient, s_gPlayerMove);
	CLog::Log(" Done");

	// Retrieve offsets
	CLog::Log("Performing game scan");
	PatternScanner->Scan();
	CLog::Log(" Done");

	// Log
	CLog::Log("Game Offsets:");
	CLog::Log(" > gEngfuncs: 0x%p", gEngfuncs);
	CLog::Log(" > gStudio: 0x%p", gStudio);
	CLog::Log(" > gPlayerMove: 0x%p", gPlayerMove);
}