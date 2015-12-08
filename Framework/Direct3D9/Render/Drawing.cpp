/*

	File: Drawing

	Used for 2D drawing

*/
#include "..\..\Core.h"

void CRender::CompensateRenderLag(float *x, float *y)
{
	*x -= (MouseInfo->X - (int)(g_Core->ScreenInfo.Width / 2));
	*y -= (MouseInfo->Y - (int)(g_Core->ScreenInfo.Height / 2));

	if (g_Core->RenderLagCompensation > 0.0)
	{
		*x *= (float)g_Core->RenderLagCompensation;
		*y *= (float)g_Core->RenderLagCompensation;
	}
}

void CRender::Line(float x1, float y1, float x2, float y2, float lw, COLOR32 Color)
{
	D3DXVECTOR2 Vertex[] = { D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2) };

	pD3DLine->SetWidth(lw);
	pD3DLine->Draw(Vertex, 2, D3DCOLOR_RGBA(Color.r, Color.g, Color.b, Color.a));
}

void CRender::LineRect(float x, float y, float w, float h, float lw, COLOR32 Color)
{
	Line(x - lw + 1,			y - lw / 2,			x + w + lw - 1,				y - lw / 2,						lw, Color); // Top
	Line(x - lw + 1,			y + h + lw / 2,		x + w + lw - 1,				y + h + lw / 2,					lw, Color); // Bottom
	Line(x - lw / 2,			y,					x - lw / 2,					y + h + (lw > 1 ? 1 : 0),		lw, Color); // Left
	Line(x + w + lw / 2 - 1,	y,					x + w + lw / 2 - 1,			y + h + (lw > 1 ? 1 : 0),		lw, Color); // Right
}

void CRender::FillRect(float x, float y, float w, float h, COLOR32 Color)
{
	D3DXVECTOR2 Vertex[] = { D3DXVECTOR2((float)x, (float)(y + h / 2)), D3DXVECTOR2((float)(x + w), (float)(y + h / 2)) };

	pD3DLine->SetWidth((float)h);
	pD3DLine->Draw(Vertex, 2, D3DCOLOR_RGBA(Color.r, Color.g, Color.b, Color.a));
}

void CRender::DepthFrame(float x, float y, float w, float h)
{
	FillRect(x + 1, y + 1, w - 2, 1, rgb(0, 0, 0, 128)); //Upper line
	FillRect(x + 1, y + 2, 1, h - 3, rgb(0, 0, 0, 128)); //Left line
	FillRect(x + 1, y + h - 1, w - 2, 1, rgb(255, 255, 255, 48)); //Bottom line
	FillRect(x + w - 2, y + 2, 1, h - 3, rgb(255, 255, 255, 48)); //Right line
}