/*

	CS16_Main

	Used for initializing cs16

*/
#include "CS16_Main.h"

CS16EngineInfo *CS16Engine = new CS16EngineInfo();
CS16OffsetInfo *CS16Offset = new CS16OffsetInfo();
UI_Window* GUI_Main = NULL;
UI_Window* GUI_ESP = NULL;
CS16DVars* CS16DVar = NULL;

int HackThread()
{
	bool bFirst = true;
	CoreTimer::Countdown TmrSlowRead = CoreTimer::Countdown(100);

	// Get offsets
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

	// Run cheat thread
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
	
	//BoxFilled(20, 200, 100, 100, D3DCOLOR_RGBA(255, 0, 0, 255));

	// Draw ESP
	CS16ESP::DrawESP();

	// Draw GUI
	GUI->DrawWindows();
}

void KeyEvents(eKBCallback Callback)
{
	if (KeyPressed->KeyPress(eKButton::K_INSERT))
		CS16DVar->GUI_Active = !CS16DVar->GUI_Active;
}

void OpenSettingsWindow()
{
	CS16DVar->GUI_Settings_Active = !CS16DVar->GUI_Settings_Active;
}

CS16Main::CS16Main()
{
	// Create core
	g_Core = new CFrameworkCore("hl.exe", "D3D9 Overlay", 800, 600);
	GUI = new UI_Setup();
	CS16DVar = new CS16DVars();

	// Init Key bindins
	KeyPressed->HookKeyEvents(KeyEvents);

	// Create Main GUI Window
	float _X = 2;
	float _Y = 2;
	float _W = g_Core->ScreenInfo.Width - 3;
	float _H = g_Core->CaptionSize + 11;

	GUI_Main = GUI->RegisterWindow(new UI_Window("Settings", _X, _Y, _W, _H, &CS16DVar->GUI_Active, 0, false));
	GUI_Main->AddLabel(new UI_Label("Godly Framework v1.1", 10, 14));
	GUI_Main->AddButton(new UI_Button("ESP Settings", 200, 10, OpenSettingsWindow));

	// Esp Settings Window
	_X = 5;
	_Y = _H + 5;
	_W = 300;
	_H = 200;
	GUI_ESP = GUI->RegisterWindow(new UI_Window("ESP Settings", _X, _Y, _W, _H, &CS16DVar->GUI_Settings_Active, &CS16DVar->GUI_Active));
	
	// Esp Settings Controls
	_X = 0;
	_Y = 0;
	GUI_ESP->AddGroupbox(new UI_GroupBox("Misc", _X + 10, _Y + 10, _W - 20, 50));
	GUI_ESP->AddSlider(new UI_Slider(_X + 20, _Y + 20, _W - 40, 0.0f, 2.0f, &CS16DVar->ESPLagCompensation, UI_SLIDER_VALUE_TEXT));
	_Y += 50 + g_Core->TextSize * 1.5f;

	// Esp Settinsgs :: Player Groupbox
	GUI_ESP->AddGroupbox(new UI_GroupBox("Player", _X + 10, _Y, _W - 20, 100));
	GUI_ESP->AddCheckbox(new UI_Checkbox(&CS16DVar->NameESP, "Name", _X + 20, _Y + 15));
	GUI_ESP->AddCheckbox(new UI_Checkbox(&CS16DVar->WeaponESP, "Weapon", _X + g_Core->Render->GetStringWidth("Name") + 125, _Y + 15));
	_Y += 110 + g_Core->TextSize * 1.5f;

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