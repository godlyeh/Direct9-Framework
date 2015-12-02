/*

	File: Settings

	Core settings system (shitty, should be improved)

*/
#include "..\..\Core.h"

CSettings::CSettings(PCHAR szFileName)
{
	GetModuleFileName(GetModuleHandle(NULL), Path, MAX_PATH);
	*(strrchr(Path, '\\') + 1) = NULL;
	strcat_s(Path, szFileName);
	strcat_s(Path, ".cfg");
	File = std::fstream(szFileName);
}

CSettings::~CSettings()
{
	if (File.is_open()) File.close();
}

void CSettings::Register(PCHAR Name, PVOID Variable, eCoreVariableType Type, double dMin, double dMax)
{
	CoreVariable Var; ZeroMemory(&Var, sizeof(CoreVariable));
	strcpy_s(Var.Name, Name);
	Var.Variable = Variable;
	Var.Type = Type;
	Var.dMinValue = dMin;
	Var.dMaxValue = dMax;
	if (Var.Type == eCoreVariableType::VAR_INTEGER) Var.iDefault = *(PINT)Variable;
	if (Var.Type == eCoreVariableType::VAR_FLOAT) Var.fDefault = *(PFLOAT)Variable;
	if (Var.Type == eCoreVariableType::VAR_DOUBLE) Var.dDefault = *(PDOUBLE)Variable;
	if (Var.Type == eCoreVariableType::VAR_STRING) strcpy_s(Var.szDefault, (PCHAR)Variable);
	StoredSettings.push_back(Var);
}

void CSettings::Remove(PCHAR Name)
{
	for (int i = 0; i < (int)StoredSettings.size(); ++i)
		if (!_stricmp(StoredSettings[i].Name, Name))
			StoredSettings.erase(StoredSettings.begin() + i);
}

void CSettings::Remove(PVOID Variable)
{
	for (int i = 0; i < (int)StoredSettings.size(); ++i)
		if (StoredSettings[i].Variable == Variable)
			StoredSettings.erase(StoredSettings.begin() + i);
}

CoreVariable* CSettings::GetCoreVariable(PCHAR Name)
{
	for (int i = 0; i < (int)StoredSettings.size(); ++i)
		if (!_stricmp(StoredSettings[i].Name, Name))
			return &StoredSettings[i];

	return NULL;
}

CoreVariable* CSettings::GetCoreVariable(PVOID Variable)
{
	for (int i = 0; i < (int)StoredSettings.size(); ++i)
		if (StoredSettings[i].Variable == Variable)
			return &StoredSettings[i];

	return NULL;
}

void CSettings::BoundVariable(CoreVariable* Var)
{
	if (Var->Type == eCoreVariableType::VAR_STRING)
		return;

	if (Var->Type == eCoreVariableType::VAR_INTEGER)
	{
		if (*(PINT)Var->Variable > (int)Var->dMaxValue) *(PINT)Var->Variable = (int)Var->dMaxValue;
		if (*(PINT)Var->Variable < (int)Var->dMinValue) *(PINT)Var->Variable = (int)Var->dMinValue;
	}
	if (Var->Type == eCoreVariableType::VAR_FLOAT)
	{
		if (*(PFLOAT)Var->Variable > (float)Var->dMaxValue) *(PFLOAT)Var->Variable = (float)Var->dMaxValue;
		if (*(PFLOAT)Var->Variable < (float)Var->dMinValue) *(PFLOAT)Var->Variable = (float)Var->dMinValue;
	}
	if (Var->Type == eCoreVariableType::VAR_DOUBLE)
	{
		if (*(PDOUBLE)Var->Variable > Var->dMaxValue) *(PDOUBLE)Var->Variable = Var->dMaxValue;
		if (*(PDOUBLE)Var->Variable < Var->dMinValue) *(PDOUBLE)Var->Variable = Var->dMinValue;
	}
}

PCHAR CSettings::CreateElementLine(PCHAR Name, bool SubItem = false)
{
	static char szTmp[256]; ZeroMemory(&szTmp, sizeof(szTmp));
	if (SubItem) sprintf_s(szTmp, "    <%s>", Name);
	else sprintf_s(szTmp, "<%s>", Name);
	return szTmp;
}

void CSettings::Save(PCHAR SettingsName)
{
	if (File.is_open())
		File.close();

	File.open(Path, std::fstream::out);
	
	// Add element name
	File << CreateElementLine(SettingsName) << "\n";

	// Add elements
	for (int i = 0; i < (int)StoredSettings.size(); ++i)
	{
		char szValue[256]; ZeroMemory(&szValue, sizeof(szValue));
		char szDefaultValue[256]; ZeroMemory(&szValue, sizeof(szValue));
		CoreVariable *Var = &StoredSettings[i];

		if (Var->Type == eCoreVariableType::VAR_INTEGER) sprintf_s(szValue, "%i", *(PINT)Var->Variable);
		if (Var->Type == eCoreVariableType::VAR_FLOAT) sprintf_s(szValue, "%.2f", *(PFLOAT)Var->Variable);
		if (Var->Type == eCoreVariableType::VAR_DOUBLE) sprintf_s(szValue, "%.2f", *(PDOUBLE)Var->Variable);
		if (Var->Type == eCoreVariableType::VAR_STRING) strcpy_s(szValue, (PCHAR)Var->Variable);

		if (Var->Type == eCoreVariableType::VAR_INTEGER) sprintf_s(szDefaultValue, "%i", Var->iDefault);
		if (Var->Type == eCoreVariableType::VAR_FLOAT) sprintf_s(szDefaultValue, "%.2f", Var->fDefault);
		if (Var->Type == eCoreVariableType::VAR_DOUBLE) sprintf_s(szDefaultValue, "%.2f", Var->dDefault);
		if (Var->Type == eCoreVariableType::VAR_STRING) strcpy_s(szDefaultValue, Var->szDefault);

		File << CreateElementLine(Var->Name, true) << " <Type = " << szCoreVariableType[Var->Type] << "> <Value = " << szValue << "> <Default: " << szDefaultValue << ">\n";
	}

	// Add end of element name
	File << CreateElementLine(SettingsName) << "\n";

	File.close();
}

void CSettings::LoadRawData(std::vector<std::string>* RawData)
{
	if (File.is_open())
		File.close();

	File.open(Path, std::fstream::in);

	std::string Line;
	while (std::getline(File, Line))
		RawData->push_back(Line);

	File.close();
}

std::string CSettings::GetElementData(PCHAR Element, std::string RawData)
{
	char szTmp[64];
	sprintf_s(szTmp, "<%s", Element);
	std::string RawValue = RawData.substr(RawData.find(szTmp) + 1);
	RawValue = RawValue.substr(0, RawValue.find('>'));
	if (RawValue.find("= "))
		RawValue = strrchr(RawValue.c_str(), '=') + 2;
	else
		RawValue = strrchr(RawValue.c_str(), '=') + 1;

	return RawValue;
}

eCoreVariableType CSettings::GetElementDataType(PCHAR TypeName)
{
	for (int i = 0; i <= sizeof(eCoreVariableType); ++i)
		if (!_stricmp(TypeName, szCoreVariableType[i]))
			return (eCoreVariableType)i;

	return (eCoreVariableType)0;
}

CoreVariable* CSettings::LoadSetting(PCHAR Name)
{
	CoreVariable *Var = GetCoreVariable(Name);
	if (Var == NULL)
		return NULL;

	std::vector<std::string> RawData;
	LoadRawData(&RawData);

	for (int i = 0; i < (int)RawData.size(); ++i)
	{
		if (strstr(RawData[i].c_str(), Name))
		{
			eCoreVariableType VarType = GetElementDataType((PCHAR)GetElementData("Type", RawData[i]).c_str());
			std::string VarValue = GetElementData("Value", RawData[i]);

			if (VarType == eCoreVariableType::VAR_INTEGER)
			{
				if (VarValue.find_first_not_of("0123456789") != EOF)
					*(PINT)Var->Variable = Var->iDefault;
				else
					*(PINT)Var->Variable = atoi(VarValue.c_str());
			}
			if (VarValue.find_first_not_of("1234567890.") == EOF)
			{
				if (VarType == eCoreVariableType::VAR_FLOAT) *(PFLOAT)Var->Variable = (float)atof(VarValue.c_str());
				if (VarType == eCoreVariableType::VAR_DOUBLE) *(PDOUBLE)Var->Variable = atof(VarValue.c_str());
			}
			else
			{
				if (VarType == eCoreVariableType::VAR_FLOAT) *(PFLOAT)Var->Variable = Var->fDefault;
				if (VarType == eCoreVariableType::VAR_DOUBLE) *(PDOUBLE)Var->Variable = Var->dDefault;
			}

			if (VarType == eCoreVariableType::VAR_STRING) strcpy_s((PCHAR)Var->Variable, VarValue.size() + 1, VarValue.c_str());

			BoundVariable(Var);
		}
	}

	return Var;
}

void CSettings::LoadAllSettings()
{
	for (int i = 0; i < (int)StoredSettings.size(); ++i)
		memcpy(&StoredSettings[i], LoadSetting(StoredSettings[i].Name), sizeof(CoreVariable));
}