/*

	File: Logging

	Used for console / file logging.

*/

// Framework includes
#include "..\Core.h"

// Console logging
void CLog::Log(eLogType Type, PCHAR szText, ...)
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
	if (Type > LogLevel) return;

	char szBuffer[1024];
	GET_VA_ARGS(szText, szBuffer);
	if (LogToConsole) printf("%s\n", szBuffer);
}

void CLog::Log(PCHAR szText, ...)
{
	char szBuffer[1024];
	GET_VA_ARGS(szText, szBuffer);
	Log(eLogType::NORMAL, szBuffer);
}

void CLog::LogI(eLogType Type, PCHAR szText, int Value)
{
	if (Type > LogLevel) return;

	if (LogToConsole) printf("%s = %i\n", szText, Value);
}

void CLog::LogI(PCHAR szText, int Value)
{
	LogI(eLogType::NORMAL, szText, Value);
}

void CLog::LogF(eLogType Type, PCHAR szText, float Value)
{
	if (Type > LogLevel) return;
	if (LogToConsole) printf("%s = %f\n", szText, Value);
}

void CLog::LogF(PCHAR szText, float Value) //Float
{
	LogF(eLogType::NORMAL, szText, Value);
}

#ifndef _WIN64
void CLog::LogP(eLogType Type, PCHAR szText, FDWORD Value) //Pointer x86
{
	if (Type > LogLevel) return;
	if (LogToConsole) printf("%s = 0x%X\n", szText, Value);
}
#else
void CLog::LogP(eLogType Type, PCHAR szText, FDWORD Value) //Pointer x64
{
	if (Type > LogLevel) return;
	if (LogToConsole) printf("%s = 0x%p\n", szText, Value);
}
#endif

void CLog::LogP(PCHAR szText, FDWORD Value) //Pointer x64
{
	LogP(eLogType::NORMAL, szText, Value);
}

void CLog::LogX(eLogType Type, PCHAR szText, DWORD Value) //DWORD
{
	if (Type > LogLevel) return;
	if (LogToConsole) printf("%s = %X\n", szText, Value);
}

void CLog::LogX(PCHAR szText, DWORD Value) //DWORD
{
	LogX(eLogType::NORMAL, szText, Value);
}