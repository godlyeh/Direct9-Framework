/*

	ByteScan

	Byte pattern scanning, should be improved. not really

*/
#include "..\..\Core.h"

CPatternScanner::CPatternScanner(HANDLE ProcessHandle, CMemoryScanner* MemScanner)
{
	Handle = ProcessHandle;
	MemoryScanner = MemScanner;
}

bool __fastcall CPatternScanner::CompareBytes(CorePattern* Pattern, BYTE* ByteArray)
{
	for (int i = 0, x = 0; i < (int)Pattern->dwLength; ++i, x += 2)
	{
		if (Pattern->ScanType == ePatternScanType::SCAN_BYTES)
		{
			// Skip unknowns
			if (i != Pattern->dwLength - 1)
			{
				if (Pattern->szPattern[x] == '?' && Pattern->szPattern[x + 1] == '?')
					continue;
				
				if (Pattern->bPattern[i] == 0x00)
					continue;
			}
			

			// Uncertain variables like mov eax, edi can be mov eax, esi next time.
			if (Pattern->szPattern[x] == '?' && (ByteArray[i] & 0xF) != Pattern->bPattern[i])
				break;

			// Uncertain variables like mov eax, edi can be mov eax, esi next time.
			if (Pattern->szPattern[x + 1] == '?' && (ByteArray[i] >> 4) != Pattern->bPattern[i])
				break;

			// Cmp byte
			if (Pattern->szPattern[x] != '?' && Pattern->szPattern[x + 1] != '?' && ByteArray[i] != Pattern->bPattern[i])
				break;

			if (i == Pattern->dwLength - 1)
				return true;
		}

		if (Pattern->ScanType == ePatternScanType::SCAN_STRING)
		{
			if (!memcmp(Pattern->bPattern, ByteArray, Pattern->dwLength + 1))
				return true;
		}
	}

	return false;
}

bool CPatternScanner::FoundAllOffsetsInModule(MODULEENTRY32 *me32)
{
	for (int i = 0; i < (int)Patterns.size(); ++i)
	{
		if (_stricmp(me32->szModule, Patterns[i].Module.szModule))
			continue;

		if (*Patterns[i].Offset == NULL)
			return false;
	}
	return true;
}

void CPatternScanner::Scan()
{
	for (int x = 0; x < (int)FilesToScan.size(); ++x)
	{
		// Read module
		PBYTE GameBytes = new BYTE[FilesToScan[x].modBaseSize];
		MemoryScanner->Read((FDWORD)FilesToScan[x].modBaseAddr, GameBytes, FilesToScan[x].modBaseSize);

		// Scan bytes for our pattern
		for (DWORD i = 0; i < FilesToScan[x].modBaseSize; ++i, ++GameBytes)
		{
			if (FoundAllOffsetsInModule(&FilesToScan[x]))
				break;

			for (int p = 0; p < (int)Patterns.size(); ++p)
			{
				if (*Patterns[p].Offset == NULL && CompareBytes(&Patterns[p], GameBytes))
				{
					*Patterns[p].Offset = (FDWORD)FilesToScan[x].modBaseAddr + i;
					if (Patterns[p].RetrieveAddress)
					{
						FDWORD TmpAddr = 0;
						FDWORD OpcodeLength = oplen(GameBytes);
						if (OpcodeLength == 0x5) TmpAddr = 0x1;
						if (OpcodeLength == 0x6) TmpAddr = 0x2;

						if (TmpAddr)
							MemoryScanner->Read((*Patterns[p].Offset + TmpAddr), Patterns[p].Offset, sizeof(DWORD));
					}
				}
			}
		}
	}
}

void CPatternScanner::SetupPattern(MODULEENTRY32* Module, PCoreString Pattern, CorePattern* PatternOut, ePatternScanType Type)
{
	static CorePattern PatternInfo; ZeroMemory(&PatternInfo, sizeof(CorePattern));
	
	// Copy info
	strcpy_s(PatternInfo.szPattern, Pattern);
	PatternInfo.ScanType = Type;
	if (Module) memcpy(&PatternInfo.Module, Module, sizeof(MODULEENTRY32));

	// Convert to bytes for faster cmps
	if (Type == ePatternScanType::SCAN_BYTES)
	{
		// Remove spaces if byte scan
		Utilities::RemoveSpaces(Pattern, PatternInfo.szPattern);

		PatternInfo.dwLength = (DWORD)strlen(PatternInfo.szPattern) / 2;
		PatternInfo.bPattern = new BYTE[PatternInfo.dwLength];
		for (int i = 0, x = 0; i < (int)PatternInfo.dwLength; ++i, x += 2)
		{
			char szTmp[4];
			if (PatternInfo.szPattern[x] == '?') sprintf_s(szTmp, "%c", PatternInfo.szPattern[x + 1]);
			else sprintf_s(szTmp, "%c%c", PatternInfo.szPattern[x], PatternInfo.szPattern[x + 1]);
			PatternInfo.bPattern[i] = (BYTE)strtoul(szTmp, 0, 16);
		}
	}

	if (Type == ePatternScanType::SCAN_STRING)
	{
		PatternInfo.dwLength = (DWORD)strlen(Pattern);
		PatternInfo.bPattern = new BYTE[PatternInfo.dwLength];
		strcpy_s((PCoreString)PatternInfo.bPattern, PatternInfo.dwLength + 1, Pattern);
	}

	// Copy out
	memcpy(PatternOut, &PatternInfo, sizeof(CorePattern));
}

void CPatternScanner::RegisterPattern(FDWORD* Offset, MODULEENTRY32* Module, PCoreString Pattern, bool GetAddress, ePatternScanType Type)
{
	// Setup byte scan info
	CorePattern PatternInfo;
	SetupPattern(Module, Pattern, &PatternInfo, Type);
	PatternInfo.Offset = Offset;
	PatternInfo.RetrieveAddress = GetAddress;
	Patterns.push_back(PatternInfo);

	// Add file if not already added
	for (int i = 0; i < (int)FilesToScan.size(); ++i)
		if (memcmp(&FilesToScan[i], Module, sizeof(MODULEENTRY32)) == 0)
			return;

	FilesToScan.push_back(*Module);
}

FDWORD CPatternScanner::FindPattern(MODULEENTRY32* Module, PCoreString Pattern, ePatternScanType Type, FDWORD* Out)
{
	// Read module
	PBYTE GameBytes = new BYTE[Module->modBaseSize];
	MemoryScanner->Read((FDWORD)Module->modBaseAddr, GameBytes, Module->modBaseSize);

	CorePattern PatternInfo;
	SetupPattern(Module, Pattern, &PatternInfo, Type);

	for (DWORD i = 0; i < Module->modBaseSize; ++i, ++GameBytes)
	{
		if (CompareBytes(&PatternInfo, GameBytes))
		{
			if (Out) *Out = (FDWORD)(Module->modBaseAddr + i);
			return (FDWORD)Module->modBaseAddr + i;
		}
	}

	return NULL;
}