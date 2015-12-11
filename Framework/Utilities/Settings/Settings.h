/*

	File: Settings

	Used for storing settings

*/

enum eCoreVariableType : int
{
	VAR_UNKNOWN,
	VAR_INTEGER,
	VAR_BOOL,
	VAR_FLOAT,
	VAR_DOUBLE,
	VAR_STRING,
	VAR_COLOR
};

static char szCoreVariableType[][16]
{
	"Unknown",
	"Int",
	"Bool",
	"Float",
	"Double",
	"String",
	"Color"
};

typedef struct
{
	CoreString Name;
	PVOID Variable;
	eCoreVariableType Type;

	double dMinValue;
	double dMaxValue;

	COLOR32 clrDefault;
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
	// Reg var
	void Register(PCoreString Name, PVOID Variable, eCoreVariableType Type, double dMin = 0, double dMax = 0);

	// Control vars
	void Register(UI_Window *Window);
	void Register(UI_Checkbox *Checkbox);
	void Register(UI_ComboBox *Combobox);

	void Remove(PCoreString Name);
	void Remove(PVOID Variable);

	void BoundVariable(CoreVariable* Var);
	void OutputSetting(CoreVariable *Var, PCHAR szValue, ...);
	void OutputSetting(CoreVariable *Var, PCHAR Name, PCHAR szValue, ...);

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