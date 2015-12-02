/*

File: UI_GroupBox

Used for groupbox, todo: bind objects to it

*/
#include "..\..\..\..\Core.h"

UI_GroupBox::UI_GroupBox(PCHAR Caption, int x, int y, int w, int h, COLOR32 Color)
{
	strcpy_s(Text, Caption);
	X = x;
	Y = y;
	W = w;
	H = h;
	TextColor = Color;
}

void UI_GroupBox::Draw(int x, int y, bool Visible)
{
	if (Visible)
	{
		int _X = x + X;
		int _Y = y + Y + g_Core->CaptionSize;
		int _StrW = g_Core->Render->GetStringWidth(Text);
		int _W = W;
		int _H = H;
		if (_W + 30 < _StrW + 30)
			_W = _StrW + 30;

		g_Core->Render->FillRect(_X, _Y, 10, 1, LineColor); // Left upper
		g_Core->Render->DrawString(false, _X + 10 + 3, _Y - g_Core->TextSize / 2, TextColor, Text); // String
		g_Core->Render->FillRect(_X + 10 + _StrW + 8, _Y, _W - 10 - _StrW - 7, 1, LineColor); // Right upper
		g_Core->Render->FillRect(_X, _Y + 1, 1, _H, LineColor); // Left
		g_Core->Render->FillRect(_X + _W, _Y + 1, 1, _H, LineColor); // Right
		g_Core->Render->FillRect(_X + 1, _Y + _H + 1, _W - 1, 1, LineColor); // Bottom
	}
}