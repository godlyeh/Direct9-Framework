/*

	File: Window

	Used for window handling

*/
#include "..\Core.h"

MARGINS margin = { 0, 0, 0, 0 };

// Window proc
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT Paint;
	HDC hDC;

	switch (uMessage)
	{
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &Paint);
		CLog::Log(eLogType::DEBUG, " > Message: WM_Paint");
		EndPaint(hWnd, &Paint);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		CLog::Log(eLogType::DEBUG, " > Message: WM_DESTROY");
		break;

	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}

	return 0;
}

// Register window
LRESULT CWindowHandler::Register(HINSTANCE hInst, int nWidth, int nHeight, LPCTSTR WindowName, BOOL Overlay)
{
	// Setup window class
	ZeroMemory(&wndClass, sizeof(WNDCLASSEX));

	CLog::Log(eLogType::DEBUG, "> Setting up window class");

	if (Overlay == FALSE)
	{
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	}

	wndClass.hInstance = hInst;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hCursor = LoadCursor(hInst, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;
	wndClass.lpszClassName = "D3D9Framework";
	wndClass.lpszMenuName = NULL;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	CLog::Log(eLogType::DEBUG, " > Done");

	// Register window class
	CLog::Log(eLogType::HIGH, "> Registering window class");
	if (!RegisterClassEx(&wndClass))
	{
		CLog::Log(eLogType::HIGH, " > FAILED");
		return E_FAIL;
	}
	CLog::Log(eLogType::HIGH, " > SUCCESS");

	// Create window
	X = 0;
	Y = 0;
	W = (float)nWidth;
	H = (float)nHeight;
	Rect = { (int)X, (int)Y, (int)W, (int)H };
	margin = { -1 };
	hInstance = hInst;
	
	if (Overlay)
	{
		CLog::Log(eLogType::HIGH, "> Creating direct3d9 overlay window");

		HWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_COMPOSITED | WS_EX_TRANSPARENT | WS_EX_LAYERED, wndClass.lpszClassName, WindowName,
							  WS_POPUP,
							  CW_USEDEFAULT, CW_USEDEFAULT, (Rect.right - Rect.left), (Rect.bottom - Rect.top),
							  NULL, NULL,
							  hInst,
							  NULL);

		CLog::Log(eLogType::DEBUG, " > Trying to extend Dwm into client frame");
		if (DwmExtendFrameIntoClientArea(HWnd, &margin) != S_OK)
		{
			CLog::Log(eLogType::DEBUG, "  > Could not extend dwm into client area");
			return E_FAIL;
		}
		CLog::Log(eLogType::DEBUG, "  > Extended Dwm into area");
	}
	else
	{
		CLog::Log(eLogType::HIGH, "> Creating window");

		HWnd = CreateWindowEx(0, wndClass.lpszClassName, WindowName,
							  WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
							  CW_USEDEFAULT, CW_USEDEFAULT, (Rect.right - Rect.left), (Rect.bottom - Rect.top),
							  NULL, NULL,
							  hInst,
							  NULL);
	}

	if (HWnd == NULL)
	{
		CLog::Log(eLogType::HIGH, " > FAILED");
		return E_FAIL;
	}

	// Show window
	CLog::Log(eLogType::HIGH, " > SUCCESS [0x%p]", HWnd);
	ShowWindow(HWnd, SW_SHOWNORMAL);
	UpdateWindow(HWnd);
	MoveWindow(HWnd, (int)X, (int)Y, (int)W, (int)H, FALSE);

	return S_OK;
}