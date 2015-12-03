/*

	File: Font

	Used for font handling

*/
#include "..\..\Core.h"

HRESULT CRender::SetFont(LPIDirect3DDevice9 pDevice, PCoreString FontName, float Size)
{
	CLog::Log(eLogType::HIGH, "> Creating D3D9X font handler");

	// Set font
	CLog::Log(eLogType::DEBUG, " > Setting font to %s", FontName);
	
	// Release old font
	if (pD3DFont)
	{
		pD3DFont->Release();
		CLog::Log(eLogType::DEBUG, "  > Released old font handler");
	}

	// Init font
	if (D3DXCreateFont(pDevice, (int)Size, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, FontName, &pD3DFont) != S_OK)
	{
		CLog::Log(eLogType::HIGH, " > FAILED");
		return E_FAIL;
	}

	CLog::Log(eLogType::HIGH, " > SUCCESS [0x%p]", pD3DFont);
	return S_OK;
}

void CRender::DrawString(bool CenterText, float x, float y, COLOR32 Color, PCoreString szText, ...)
{
	char szBuffer[1024];
	GET_VA_ARGS(szText, szBuffer);

	if (CenterText)
		x -= GetStringWidth(szBuffer) / 2;

	RECT Rect = { (int)x, (int)y, 0, 0 };
	RECT ShadowRect = { (int)x + 1, (int)y + 1, 0, 0 };
	RECT ShadowRect2 = { (int)x + 2, (int)y + 1, 0, 0 };
	RECT ShadowRect3 = { (int)x + 2, (int)y + 2, 0, 0 };
	pD3DFont->DrawText(NULL, szBuffer, -1, &ShadowRect, DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, Color.a - 25));
	pD3DFont->DrawText(NULL, szBuffer, -1, &ShadowRect2, DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, Color.a - 25));
	pD3DFont->DrawText(NULL, szBuffer, -1, &ShadowRect3, DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(0, 0, 0, Color.a - 25));
	pD3DFont->DrawText(NULL, szBuffer, -1, &Rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_RGBA(Color.r, Color.g, Color.g, Color.a));
}

float CRender::GetStringWidth(char *szText, ...)
{
	char szBuffer[1024];
	GET_VA_ARGS(szText, szBuffer);

	RECT Rect; ZeroMemory(&Rect, sizeof(Rect));
	pD3DFont->DrawText(0, szBuffer, -1, &Rect, DT_CALCRECT, 0);
	return (float)Rect.right;
}

float CRender::GetStringHeight()
{
	return (float)pD3DFont->DrawText(0, "Aj", -1, 0, DT_CALCRECT, 0);
}