/*

	File: Logging

	Used for console / file logging.

*/

// Framework includes
#include "..\Core.h"

// Console logging
void CLog::Log(eLogType Type, PCoreString szText, ...)
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
	if (Type > LogLevel) return;

	char szBuffer[1024];
	GET_VA_ARGS(szText, szBuffer);
	if (LogToConsole) printf("%s\n", szBuffer);
}

void CLog::Log(PCoreString szText, ...)
{
	char szBuffer[1024];
	GET_VA_ARGS(szText, szBuffer);
	Log(eLogType::NORMAL, szBuffer);
}

void CLog::LogI(eLogType Type, PCoreString szText, int Value)
{
	if (Type > LogLevel) return;

	if (LogToConsole) printf("%s = %i\n", szText, Value);
}

void CLog::LogI(PCoreString szText, int Value)
{
	LogI(eLogType::NORMAL, szText, Value);
}

void CLog::LogF(eLogType Type, PCoreString szText, float Value)
{
	if (Type > LogLevel) return;
	if (LogToConsole) printf("%s = %f\n", szText, Value);
}

void CLog::LogF(PCoreString szText, float Value) //Float
{
	LogF(eLogType::NORMAL, szText, Value);
}

#ifndef _WIN64
void CLog::LogP(eLogType Type, PCoreString szText, FDWORD Value) //Pointer x86
{
	if (Type > LogLevel) return;
	if (LogToConsole) printf("%s = 0x%X\n", szText, Value);
}
#else
void CLog::LogP(eLogType Type, PCoreString szText, FDWORD Value) //Pointer x64
{
	if (Type > LogLevel) return;
	if (LogToConsole) printf("%s = 0x%p\n", szText, Value);
}
#endif

void CLog::LogP(PCoreString szText, FDWORD Value) //Pointer x64
{
	LogP(eLogType::NORMAL, szText, Value);
}

void CLog::LogX(eLogType Type, PCoreString szText, DWORD Value) //DWORD
{
	if (Type > LogLevel) return;
	if (LogToConsole) printf("%s = %X\n", szText, Value);
}

void CLog::LogX(PCoreString szText, DWORD Value) //DWORD
{
	LogX(eLogType::NORMAL, szText, Value);
}