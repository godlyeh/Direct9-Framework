/*

	CS16_Main

	Used for initializing cs16

*/
#include "CS16_Main.h"

CS16EntityInfo *CS16Entity = new CS16EntityInfo[4096];
CS16EngineInfo *CS16Engine = new CS16EngineInfo();
CS16OffsetInfo *CS16Offset = new CS16OffsetInfo();
UI_Window* GUI_Main = NULL;
UI_Window* GUI_ESP = NULL;

int HackThread()
{
	bool bFirst = true;
	CoreTimer::Countdown TmrSlowRead = CoreTimer::Countdown(100);

	CS16Offset->RetrieveOffsets();
	while (true)
	{
		DWORD dwEntityAllocation = 0;
		MemoryScanner->Read(CS16Offset->Entity, &dwEntityAllocation, sizeof(DWORD));
		if (dwEntityAllocation != 0)
		{
			CS16Offset->Entity = dwEntityAllocation;
			
			break;
		}

		Sleep(5000);
	}

	CLog::Log(eLogType::HIGH, " > Entity allocation found: 0x%p", CS16Offset->Entity);

	while (g_Core->Process->Running())
	{
		if (!TmrSlowRead.Running() || bFirst)
		{
			CS16Engine->ReadGameInfoSlow();

			TmrSlowRead.Reset();
			bFirst = false;
		}

		if (!g_Core->TmrThread->Running())
		{
			CS16Engine->ReadGameInfo();

			g_Core->TmrThread->Reset();
		}
	}

	return 0;
}

void RenderScene()
{
	// Draw frames per second
	if (g_Core->FramesPerSecond > 0)
		g_Core->Render->DrawString(false, 25, 25, rgb(255, 0, 0, 255), "FPS: %i", g_Core->FramesPerSecond);
	
	g_Core->Render->DrawString(false, 25, 50, rgb(255, 0, 0, 255), "%i", CS16DVar.GUI_Active);
	//BoxFilled(20, 200, 100, 100, D3DCOLOR_RGBA(255, 0, 0, 255));

	// Draw GUI
	GUI->DrawWindows();
}

void KeyEvents(eKBCallback Callback)
{
	if (KeyPressed->KeyPress(eKButton::K_INSERT))
		CS16DVar.GUI_Active = !CS16DVar.GUI_Active;
}

void OpenSettingsWindow()
{
	CS16DVar.GUI_Settings_Active = !CS16DVar.GUI_Settings_Active;
}

CS16Main::CS16Main()
{
	// Create core
	g_Core = new CFrameworkCore("hl.exe", "D3D9 Overlay", 800, 600);
	GUI = new UI_Setup();

	// Init Key bindins
	KeyPressed->HookKeyEvents(KeyEvents);

	// Create Main GUI Window
	float _X = 2;
	float _Y = 2;
	float _W = g_Core->ScreenInfo.Width - 3;
	float _H = g_Core->CaptionSize + 11;
	GUI_Main = GUI->RegisterWindow(new UI_Window("Settings", _X, _Y, _W, _H, &CS16DVar.GUI_Active, 0, false));
	GUI_Main->AddLabel(new UI_Label("Godly Framework v1.0", 10, 10));
	GUI_Main->AddButton(new UI_Button("ESP Settings", 200, 7, OpenSettingsWindow));

	_X = 5;
	_Y = _H + 5;
	_W = 300;
	_H = 200;
	GUI_ESP = GUI->RegisterWindow(new UI_Window("ESP Settings", _X, _Y, _W, _H, &CS16DVar.GUI_Settings_Active, &CS16DVar.GUI_Active));
	GUI_ESP->AddGroupbox(new UI_GroupBox("Player", 10, 10, _W - 20, 100));
	GUI_ESP->AddCheckbox(new UI_Checkbox(&CS16DVar.NameESP, "Name", 20, 25));

	// Register dvars
	CheatSettings->Register("Player Name ESP", &CS16DVar.NameESP, eCoreVariableType::VAR_BOOL);

	//Save settings
	CheatSettings->LoadAllSettings();
	GUISettings->LoadAllSettings();
	CheatSettings->Save("Cheat Settings");
	GUISettings->Save("GUI Settings");

	// Check if core was successfully initialized
	if (g_Core->CoreInitialized == false)
		return;
	
	// Init offsets
	CS16Offset->InitOffsets();

	// Read game
	CLog::Log(eLogType::HIGH, "Creating hack thread");
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HackThread, NULL, 0, 0);
	CLog::Log(eLogType::HIGH, " Done");

	// Run 1.6 framework
	while (g_Core->RenderScene(RenderScene, g_Core->Process->HWnd));
}

CS16Main::~CS16Main()
{
	g_Core->~CFrameworkCore();
	//CS16DVar = NULL;
}