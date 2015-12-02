/*

	Direct3D9 Framework
	by:			godly

	Framework is setup to work for all x64 games played in windowmode using Dwm and D3D9.
	Framework contains:
		- 2D Drawing


	Easy to use. Declare CFrameworkCore and Initialize it
*/
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// System file include
#include <Windows.h>
#include <String>
#include <Vector>
#include <FStream>
#include <TlHelp32.h>
#include <Dwmapi.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9core.h>

// Framework file include
#include "Helpers.h"

#include "Utilities\Settings\Settings.h"
#include "Utilities\Vector\Vector3.h"
#include "Utilities\UtilCore.h"
#include "Utilities\ByteScan\ByteScan.h"
#include "Utilities\Timer.h"

#include "Direct3D9\D3D9Core.h"
#include "Direct3D9\Render\D3D9Render.h"
#include "Direct3D9\Render\GUI\UI_Core.h"

// Framework variables
#define CORE_FRAMEWORK_VERSION "1.0.0.0"
#define CORE_SETTINGS_DEFAULT "Core Settings"

// Core class
class CFrameworkCore
{
public:
	// Core successfully initialized
	bool CoreInitialized = false;
	// Caption size
	float TextSize = 0;
	float CaptionSize = 0;
	// Core Tick
	int CoreTick = 15;
	CoreTimer::Countdown *TmrThread = NULL;
	// Core render timer
	int RenderTick = 30;
	int FramesPerSecond = 30;
	CoreTimer::Countdown *TmrRender = NULL;
	// Process screen info
	SCREENINFO ScreenInfo;
	// Hack path
	char Path[MAX_PATH];
	// Game name
	CoreString GameProcessName;

public:
	CSettings* Settings = new CSettings("CoreSettings");
	CWindowHandler* Window = new CWindowHandler();
	CDeviceHandler* Device = new CDeviceHandler();
	CRender* Render = new CRender();
	CProcess* Process = new CProcess();

public:
	CFrameworkCore(PCHAR ProcessName, PCHAR WindowName, int Width, int Height);
	~CFrameworkCore();

public:
	void PlaceSceneOnWindow();
	bool RenderScene(PVOID pRenderScene, HWND DesiredForegroundWindow);

private:
	void RegisterCoreVariables();
};

extern CFrameworkCore* g_Core;
extern UI_Setup* GUI;
extern UI_Mouse* MouseInfo;
