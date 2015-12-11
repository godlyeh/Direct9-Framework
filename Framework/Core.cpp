/*

	File: Core

*/
#include "Core.h"

CFrameworkCore* g_Core = NULL;
UI_Setup* GUI = NULL;
UI_Mouse* MouseInfo = new UI_Mouse();
K_Button* KeyPressed = NULL;
CMemoryScanner* MemoryScanner = NULL;
VectorMath* VecMath = new VectorMath;

void CFrameworkCore::RegisterCoreVariables()	
{
	Settings->Register("Render Tick", &RenderTick, eCoreVariableType::VAR_INTEGER, 5, 40);
	Settings->Register("Core Tick", &CoreTick, eCoreVariableType::VAR_INTEGER, 5, 50);
}

CFrameworkCore::CFrameworkCore(PCoreString ProcessName, PCoreString WindowName, int Width, int Height)
{
	static bool bFirst = true;

	if (bFirst)
	{
		// Init info
		CLog::Log("\n");
		CLog::Log(" * * * * * * * * * * * * * * * * * * * * * * * *");
		CLog::Log("    D3D9 Framework");
		CLog::Log("    by godly");
		CLog::Log("    version %s", CORE_FRAMEWORK_VERSION);
		CLog::Log("    log level %s", szLogType[CLog::LogLevel]);
		CLog::Log("    framework cpu %s", FrameworkCPU);
		CLog::Log(" * * * * * * * * * * * * * * * * * * * * * * * *\n");

		// Register core variables
		RegisterCoreVariables();

		//Load and save default file
		Settings->LoadAllSettings();
		Settings->Save(CORE_SETTINGS_DEFAULT);

		// Set core variables
		TmrRender = new CoreTimer::Countdown(RenderTick);

		bFirst = false;
	}

	// Get process info
	CLog::Log(eLogType::HIGH, "Getting hack path");
	if (GetModuleFileName(GetModuleHandle(NULL), Path, MAX_PATH))
	{
		*(strrchr(Path, '\\') + 1) = NULL;
		CLog::Log(eLogType::HIGH, " Path retrieved: %s", Path);
	}
	else
		CLog::Log(eLogType::HIGH, " FAILED");

	// Get process info
	CLog::Log("Getting process info for %s", ProcessName);
	if (Process->Init(ProcessName) == FALSE)
	{
		CLog::Log("Failed to retrieve info on %s", ProcessName);
		return;
	}
	CLog::Log("Information for %s retrieved", ProcessName);

	// Create window
	CLog::Log("\nCreating window");
	if (Window->Register((HINSTANCE)GetModuleHandle(NULL), Width, Height, WindowName, true) == E_FAIL)
	{
		CLog::Log("Failed to create window");
		return;
	}
	CLog::Log("Window successfully created");

	// Create D3D9 handlers
	CLog::Log("\nCreating Direct3D9 handlers");
	if (Device->CreateDevice(Window->HWnd, Width, Height) == E_FAIL)
	{
		CLog::Log("Failed creating Direct3D9 handlers!");
		return;
	}
	CLog::Log("Direct3D9 handlers set up");

	// Create D3D9X handlers
	CLog::Log("\nCreating Direct3D9X handlers");
	if (Render->Init(Device->pDevice) == FALSE)
	{
		CLog::Log("Failed creating Direct3D9X handlers!");
		return;
	}
	CLog::Log("Direct3D9X handlers set up");

	CLog::Log("");

	// Copy game process name and get screen info
	KeyPressed = new K_Button(Window->hInstance);
	MemoryScanner = new CMemoryScanner(Process->Handle);
	strcpy_s(GameProcessName, ProcessName);
	Utilities::GetWindowInformation(Process->HWnd, &ScreenInfo);
	
	// Set game focus
	PlaceSceneOnWindow();
	SetForegroundWindow(Process->HWnd);
	SetFocus(Process->HWnd);
	ShowWindow(Process->HWnd, SW_SHOWNORMAL);

	TextSize = Render->GetStringHeight();
	CaptionSize = TextSize + 4;
	TmrThread = new CoreTimer::Countdown(CoreTick);
	CoreInitialized = true;
}

CFrameworkCore::~CFrameworkCore()
{
	Settings->Save(CORE_SETTINGS_DEFAULT);
	Render->Release();
	Device->Release();
	Process->CleanUp();
	KeyPressed->~K_Button();
	MemoryScanner->~CMemoryScanner();
	CoreInitialized = false;
}

void CFrameworkCore::PlaceSceneOnWindow()
{
	static int X, Y, W, H;
	Utilities::GetWindowInformation(Process->HWnd, &ScreenInfo);

	// Move overlay to proper screen
	if (X != ScreenInfo.X || Y != ScreenInfo.Y || W != ScreenInfo.Width || H != ScreenInfo.Height)
	{
		Render->pD3DFont->OnLostDevice();
		Render->pD3DLine->OnLostDevice();

		MoveWindow(Window->HWnd, (int)ScreenInfo.X, (int)ScreenInfo.Y, (int)ScreenInfo.Width, (int)ScreenInfo.Height, FALSE);
		Device->D3DParameters.BackBufferWidth = (int)ScreenInfo.Width;
		Device->D3DParameters.BackBufferHeight = (int)ScreenInfo.Height;
		Device->pDevice->Reset(&Device->D3DParameters);

		Render->pD3DFont->OnResetDevice();
		Render->pD3DLine->OnResetDevice();
	}
	
}

bool CFrameworkCore::RenderScene(PVOID pRenderScene, HWND DesiredForegroundWindow)
{
	MSG Msg = { 0 };

	// Place overlay
	static CoreTimer::Countdown *tmrChangeScene = new CoreTimer::Countdown(500);
	if (!tmrChangeScene->Running() && Device->pDevice)
	{
		PlaceSceneOnWindow();
		tmrChangeScene->Reset();
	}

	// Save core settings
	static CoreTimer::Countdown *tmrSaveCoreSettings = new CoreTimer::Countdown(60000);
	if (!tmrSaveCoreSettings->Running() && Device->pDevice)
	{
		Settings->Save(CORE_SETTINGS_DEFAULT);
		tmrSaveCoreSettings->Reset();
	}

	// Perform core tick for timers
	CoreTimer::PerformCoreTick();

	// RenderScene
	if (!TmrRender->Running() && Device->pDevice)
	{
		// FPS
		static CoreTimer::Countdown *TmrFPS = new CoreTimer::Countdown(1000);
		static int TmpFPS = 0;
		if (!TmrFPS->Running())
		{
			// Get screen info
			Utilities::GetWindowInformation(Process->HWnd, &ScreenInfo);

			TmrFPS->Reset();
			FramesPerSecond = TmpFPS;
			TmpFPS = 0;
		}

		// Clear backbuffer
		Device->pDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_RGBA(1,2,3,4), 1.0f, 0);

		// Draw scene
		Device->pDevice->BeginScene();

		// Render the scene
		if (pRenderScene && GetForegroundWindow() == DesiredForegroundWindow) ((void(__cdecl*)())pRenderScene)();

		// End scene
		Device->pDevice->EndScene();
		Device->pDevice->Present(0, 0, 0, 0);

		TmrRender->Reset();

		// Add frame
		++TmpFPS;
	}

	if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return (Msg.message != WM_QUIT && Process->Running());
}