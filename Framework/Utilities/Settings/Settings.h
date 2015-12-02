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
	CSettings(PCHAR szFileName);
	~CSettings();

public:
	void Register(PCHAR Name, PVOID Variable, eCoreVariableType Type, double dMin = 0, double dMax = 0);

	void Remove(PCHAR Name);
	void Remove(PVOID Variable);

	void BoundVariable(CoreVariable* Var);

	CoreVariable* GetCoreVariable(PCHAR Name);
	CoreVariable* GetCoreVariable(PVOID Variable);

public:
	PCHAR CreateElementLine(PCHAR Name, bool SubItem);
	void Save(PCHAR SettingsName);

	void LoadRawData(std::vector<std::string>* RawData);
	std::string GetElementData(PCHAR Element, std::string RawData);
	eCoreVariableType GetElementDataType(PCHAR TypeName);
	CoreVariable* LoadSetting(PCHAR Name);
	void LoadAllSettings();

private:
	std::fstream File;
	std::vector<CoreVariable>StoredSettings;
};