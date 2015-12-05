/*

	File: Settings

	Core settings system (shitty, should be improved)

*/
#include "..\..\Core.h"

CSettings::CSettings(PCoreString szFileName)
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

void CSettings::Register(PCoreString Name, PVOID Variable, eCoreVariableType Type, double dMin, double dMax)
{
	CoreVariable Var; ZeroMemory(&Var, sizeof(CoreVariable));
	strcpy_s(Var.Name, Name);
	Var.Variable = Variable;
	Var.Type = Type;
	Var.dMinValue = dMin;
	Var.dMaxValue = dMax;

	switch (Var.Type)
	{
	case eCoreVariableType::VAR_INTEGER:
		Var.iDefault = *(PINT)Variable;
		sprintf_s(Var.szDefault, "%i", Var.iDefault);
		break;

	case eCoreVariableType::VAR_BOOL:
		Var.dMinValue = 0;
		Var.dMaxValue = 1; 
		Var.iDefault = *(PINT)Variable;
		sprintf_s(Var.szDefault, "%i", Var.iDefault);
		break;

	case eCoreVariableType::VAR_FLOAT:
		Var.fDefault = *(PFLOAT)Variable;
		sprintf_s(Var.szDefault, "%.2f", Var.fDefault);
		break;

	case eCoreVariableType::VAR_DOUBLE:
		Var.dDefault = *(PDOUBLE)Variable;
		sprintf_s(Var.szDefault, "%.2f", Var.dDefault);
		break;

	case eCoreVariableType::VAR_STRING:
		strcpy_s(Var.szDefault, (PCoreString)Variable);
		sprintf_s(Var.szDefault, "%.2f", Var.fDefault);
		break;
	}

	StoredSettings.push_back(Var);
}

void CSettings::Remove(PCoreString Name)
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

CoreVariable* CSettings::GetCoreVariable(PCoreString Name)
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

	if (Var->dMinValue == 0 && Var->dMaxValue == 0)
		return;

	switch (Var->Type)
	{
	case eCoreVariableType::VAR_INTEGER:
	case eCoreVariableType::VAR_BOOL:
		if (*(PINT)Var->Variable > (int)Var->dMaxValue) *(PINT)Var->Variable = (int)Var->dMaxValue;
		if (*(PINT)Var->Variable < (int)Var->dMinValue) *(PINT)Var->Variable = (int)Var->dMinValue;
		break;

	case eCoreVariableType::VAR_FLOAT:
		if (*(PFLOAT)Var->Variable >(float)Var->dMaxValue) *(PFLOAT)Var->Variable = (float)Var->dMaxValue;
		if (*(PFLOAT)Var->Variable < (float)Var->dMinValue) *(PFLOAT)Var->Variable = (float)Var->dMinValue;
		break;

	case eCoreVariableType::VAR_DOUBLE:
		if (*(PDOUBLE)Var->Variable > Var->dMaxValue) *(PDOUBLE)Var->Variable = Var->dMaxValue;
		if (*(PDOUBLE)Var->Variable < Var->dMinValue) *(PDOUBLE)Var->Variable = Var->dMinValue;
		break;
	}
}

PCoreString CSettings::CreateElementLine(PCoreString Name, bool SubItem = false)
{
	static char szTmp[256]; ZeroMemory(&szTmp, sizeof(szTmp));
	if (SubItem) sprintf_s(szTmp, "    <Name = %s>", Name);
	else sprintf_s(szTmp, "<Name = %s>", Name);
	return szTmp;
}

void CSettings::OutputSetting(CoreVariable *Var, PCHAR szValue, ...)
{
	char szBuffer[1024];
	GET_VA_ARGS(szValue, szBuffer);
	File << CreateElementLine(Var->Name, true) << " <Type = " << szCoreVariableType[Var->Type] << "> <Value = " << szBuffer << ">\n";
}

void CSettings::Save(PCoreString SettingsName)
{
	if (File.is_open())
		File.close();

	File.open(Path, std::fstream::out);
	
	// Add element name
	File << CreateElementLine(SettingsName) << "\n";

	// Add elements
	for (int i = 0; i < (int)StoredSettings.size(); ++i)
	{
		CoreVariable *Var = &StoredSettings[i];

		switch (Var->Type)
		{
		case eCoreVariableType::VAR_BOOL:
		case eCoreVariableType::VAR_INTEGER:
			OutputSetting(Var, "%i", *(PINT)Var->Variable);
			break;

		case eCoreVariableType::VAR_DOUBLE:
		case eCoreVariableType::VAR_FLOAT:
			OutputSetting(Var, "%.2f", *(PFLOAT)Var->Variable);
			break;

		case eCoreVariableType::VAR_STRING:
			OutputSetting(Var, (PCoreString)Var->Variable);
			break;

		case eCoreVariableType::CTRL_COMBOBOX:
			OutputSetting(Var, "%i", ((UI_ComboBox*)Var->Variable)->GetIndex());
			break;
		}

		
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

std::string CSettings::GetElementData(PCoreString Element, std::string RawData)
{
	char szTmp[128];
	sprintf_s(szTmp, "<%s", Element);
	int Pos = RawData.find(szTmp);
	if (Pos == EOF)
		return "UNKNOWN";

	std::string RawValue = RawData.substr(Pos);
	RawValue = RawValue.substr(0, RawValue.find('>'));
	RawValue = RawValue.substr(RawValue.find('=') + 1);
	if (RawValue.c_str()[0] == ' ')
		RawValue = RawValue.substr(1);

	return RawValue;
}

eCoreVariableType CSettings::GetElementDataType(PCoreString TypeName)
{
	for (int i = 0; i <= sizeof(szCoreVariableType); ++i)
	{
		if (!_stricmp(TypeName, szCoreVariableType[i]))
			return (eCoreVariableType)i;
	}

	return (eCoreVariableType)0;
}

CoreVariable* CSettings::LoadSetting(PCoreString Name)
{
	CoreVariable *Var = GetCoreVariable(Name);
	if (Var == NULL)
		return NULL;

	std::vector<std::string> RawData;
	LoadRawData(&RawData);

	for (int i = 0; i < (int)RawData.size(); ++i)
	{
		std::string VarName = GetElementData("Name", RawData[i]);

		if (!_stricmp(VarName.c_str(), Name))
		{
			eCoreVariableType VarType = GetElementDataType((PCoreString)GetElementData("Type", RawData[i]).c_str());
			std::string VarValue = GetElementData("Value", RawData[i]);

			if (VarType == eCoreVariableType::VAR_UNKNOWN)
				continue;

			if (VarType == eCoreVariableType::VAR_INTEGER || VarType == eCoreVariableType::VAR_BOOL)
			{
				if (VarValue.find_first_not_of("0123456789") != EOF)
					*(PINT)Var->Variable = Var->iDefault;
				else
					*(PINT)Var->Variable = atoi(VarValue.c_str());
			}

			if (VarType == eCoreVariableType::VAR_FLOAT || VarType == eCoreVariableType::VAR_DOUBLE)
			{
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
			}

			if (VarType == eCoreVariableType::VAR_STRING) strcpy_s((PCoreString)Var->Variable, VarValue.size() + 1, VarValue.c_str());

			if (VarType == eCoreVariableType::CTRL_COMBOBOX)
			{
				if (VarValue.find_first_not_of("0123456789") == EOF)
					((UI_ComboBox*)Var->Variable)->SelectedItem = (CoreComboboxItem*)(*(DWORD*)Var->Variable + atoi(VarValue.c_str()) * sizeof(CoreComboboxItem));
			}

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