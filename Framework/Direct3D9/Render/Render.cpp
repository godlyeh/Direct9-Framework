/*

	File: Render

	Used for mostly init rendering

*/
#include "..\..\Core.h"

BOOL CRender::Init(LPIDirect3DDevice9 pDevice)
{
	// Init line
	CLog::Log(eLogType::HIGH, "> Creating D3D9X line handler");
	if (D3DXCreateLine(pDevice, &pD3DLine) != S_OK)
	{
		CLog::Log(eLogType::HIGH, " > FAILED");
		return E_FAIL;
	}
	pD3DLine->SetPattern(0xFFFFFFFF);
	pD3DLine->SetAntialias(TRUE);
	CLog::Log(eLogType::HIGH, " > SUCCESS [0x%p]", pD3DLine);

	// Init font
	if (SetFont(pDevice, "Arial", 16) != S_OK)
		return FALSE;

	return TRUE;
}

void CRender::Release()
{
	CLog::Log(eLogType::HIGH, "> Releasing D3D9X handlers");

	// Release d3dx line
	if (pD3DLine)
	{
		CLog::Log(eLogType::HIGH, " > D3D9X Line released");
		pD3DLine->Release();
	}

	// Release d3dx font
	if (pD3DFont)
	{
		CLog::Log(eLogType::HIGH, " > D3D9X Font released");
		pD3DFont->Release();
	}

	CLog::Log(eLogType::HIGH, "> All D3D9X handlers released");
}

COLOR32 rgb(int r, int g, int b, int a)
{
	COLOR32 Color = { r, g, b, a };
	return Color;
}

COLOR32 rgb(int r, int g, int b)
{
	COLOR32 Color = { r, g, b, 255 };
	return Color;
}