/*

	File: D3D9Core

	Used for handling D3D9

*/

// Window handler
class CWindowHandler
{
public:
	// Variables
	WNDCLASSEX				wndClass;
	HINSTANCE               hInstance = NULL;
	HWND                    HWnd = NULL;
	RECT					Rect;
	MSG						Msg;

	int X, Y, W, H;

	// Register window and create it
	LRESULT Register(HINSTANCE hInst, int nWidth, int nHeight, LPCTSTR szWindowName, BOOL Overlay);
};

// Device handler
class CDeviceHandler
{
public:
	// Parameters
	D3DPRESENT_PARAMETERS D3DParameters;

	// Handlers
	LPIDirect3D9 pD3D;
	LPIDirect3DDevice9 pDevice;

	// Create direct 9 device
	HRESULT CreateDevice(HWND hWnd, int Width, int Height);
	void Release();
};