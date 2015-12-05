/*

	CS16_Main

	Used for initializing cs16

*/
#include "CS16_Main.h"

int HackThread()
{
	CoreTimer::Countdown TmrThread = CoreTimer::Countdown(g_Core->CoreTick);

	while (g_Core->Process->Running())
	{
		if (!g_Core->TmrThread->Running())
		{
			// Read game


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
	
	g_Core->Render->DrawString(false, 25, 50, rgb(255, 0, 0, 255), "%i %i", MouseInfo->X, MouseInfo->Y);
	//BoxFilled(20, 200, 100, 100, D3DCOLOR_RGBA(255, 0, 0, 255));

	// Draw GUI
	GUI->DrawWindows();
}

void Button_Test()
{
	
}

CS16Main::CS16Main()
{
	// Create core
	g_Core = new CFrameworkCore("hl.exe", "D3D9 Overlay", 800, 600);
	GUI = new UI_Setup();
	//CS16Dvar = new CS16DVars;

	// Create main GUI window
	GUIWindow = GUI->RegisterWindow(new UI_Window("GUI_Window", 2, 2, g_Core->ScreenInfo.Width - 4, g_Core->CaptionSize + 5, false));

	// Register DVars and GUI windows etc
	GUISettings->Register(GUIWindow);

	//Save
	GUISettings->LoadAllSettings();
	GUISettings->Save(GUIWindow->Caption);
	

	// Check if core was successfully initialized
	if (g_Core->CoreInitialized == false)
		return;
	
	// Get game offsets
	MemoryScanner = new CMemoryScanner(g_Core->Process->Handle);
	CS16Offset::InitOffsets(MemoryScanner);
	CS16Offset::RetrieveOffsets();

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