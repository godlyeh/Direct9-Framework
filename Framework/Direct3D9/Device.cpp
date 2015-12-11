/*

	File: Device

	Used for Direct3D9 handling

*/
#include "..\Core.h"

HRESULT CDeviceHandler::CreateDevice(HWND hWnd, int Width, int Height)
{
	// Result
	HRESULT Result = S_OK;

	// Set SDK version
	CLog::Log(eLogType::HIGH, "> Creating Direct3D9 handler");
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pD3D)
	{
		CLog::Log(eLogType::HIGH, " > FAILED");
		return E_FAIL;
	}
	CLog::Log(eLogType::HIGH, " > SUCCESS [0x%p]", pD3D);

	// Setup parameters
	//D3DParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	D3DParameters.BackBufferCount = 0;
	D3DParameters.BackBufferFormat = D3DFMT_X8R8G8B8;
	D3DParameters.BackBufferWidth = Width;
	D3DParameters.BackBufferHeight = Height;
	D3DParameters.Windowed = true;
	D3DParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	D3DParameters.EnableAutoDepthStencil = TRUE;
	D3DParameters.Flags = 0;
	D3DParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	D3DParameters.hDeviceWindow = hWnd;
	D3DParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	D3DParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3DParameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	D3DParameters.MultiSampleQuality = 0;

	// Create device
	CLog::Log(eLogType::HIGH, "> Creating device");
	Result = pD3D->CreateDevice(D3DADAPTER_DEFAULT,
								D3DDEVTYPE_HAL, //Hardware Abstraction Layer
								hWnd,
								D3DCREATE_HARDWARE_VERTEXPROCESSING,
								&D3DParameters, &pDevice);

	if (FAILED(Result))
	{
		CLog::Log(eLogType::HIGH, " > FAILED");
		return Result;
	}
	CLog::Log(eLogType::HIGH, " > SUCCESS [0x%p]", pDevice);

	return Result;
}

void CDeviceHandler::Release()
{
	CLog::Log(eLogType::HIGH, "> Releasing D3D9 handlers");

	// Release d3d
	if (pD3D)
	{
		CLog::Log(eLogType::HIGH, " > D3D9 released");
		pD3D->Release();
	}

	if (pDevice)
	{
		CLog::Log(eLogType::HIGH, " > Device released");
		pDevice->Release();
	}

	CLog::Log(eLogType::HIGH, "> All D3D9 handlers released");
}