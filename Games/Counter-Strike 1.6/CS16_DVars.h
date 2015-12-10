/*

	File: CS16_DVars

	Used for saving variables for cs16

*/
class CS16DVars
{
public:
	CS16DVars()
	{
		CheatSettings = new CSettings("CS16_Cheat_Settings");
		GUISettings = new CSettings("CS16_GUI_Settings");

		// ESP
		CheatSettings->Register("ESP Lag Compensation", &ESPLagCompensation, eCoreVariableType::VAR_DOUBLE, 0, 2);
		CheatSettings->Register("Player Name ESP", &NameESP, eCoreVariableType::VAR_BOOL);
		CheatSettings->Register("Player Weapon ESP", &WeaponESP, eCoreVariableType::VAR_BOOL);

		// Load and save
		//CheatSettings->LoadAllSettings();
		CheatSettings->Save("Cheat Settings");
		//GUISettings->LoadAllSettings();
		GUISettings->Save("GUI Window Settings");
	}
	~CS16DVars() { }

public:
	// ESP
	double ESPLagCompensation = 1.0;

	bool NameESP = true;
	bool WeaponESP = true;

public:
	// GUI Window
	bool GUI_Active = false;
	bool GUI_Settings_Active = false;

public:
	CSettings* CheatSettings = NULL;
	CSettings* GUISettings = NULL;
};