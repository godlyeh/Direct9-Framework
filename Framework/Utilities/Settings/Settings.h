/*

	File: Settings

	Used for storing settings

*/

enum eCoreVariableType : int
{
	VAR_UNKNOWN = 0,
	VAR_INTEGER = 1,
	VAR_BOOL = 1,
	VAR_FLOAT = 2,
	VAR_DOUBLE = 3,
	VAR_STRING = 4
};

static char szCoreVariableType[][16]
{
	"UNKNOWN",
	"INTEGER/BOOLEAN",
	"FLOAT",
	"DOUBLE",
	"STRING"
};

typedef struct
{
	CoreString Name;
	PVOID Variable;
	eCoreVariableType Type;

	double dMinValue;
	double dMaxValue;

	int iDefault;
	float fDefault;
	double dDefault;
	char szDefault[256];
}CoreVariable;

class CSettings
{
public:
	char Path[MAX_PATH];

public:
	CSettings(PCoreString szFileName);
	~CSettings();

public:
	void Register(PCoreString Name, PVOID Variable, eCoreVariableType Type, double dMin = 0, double dMax = 0);

	void Remove(PCoreString Name);
	void Remove(PVOID Variable);

	void BoundVariable(CoreVariable* Var);

	CoreVariable* GetCoreVariable(PCoreString Name);
	CoreVariable* GetCoreVariable(PVOID Variable);

public:
	PCoreString CreateElementLine(PCoreString Name, bool SubItem);
	void Save(PCoreString SettingsName);

	void LoadRawData(std::vector<std::string>* RawData);
	std::string GetElementData(PCoreString Element, std::string RawData);
	eCoreVariableType GetElementDataType(PCoreString TypeName);
	CoreVariable* LoadSetting(PCoreString Name);
	void LoadAllSettings();

private:
	std::fstream File;
	std::vector<CoreVariable>StoredSettings;
};