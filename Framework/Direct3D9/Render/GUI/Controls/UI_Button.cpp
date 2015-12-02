/*

File: UI_Button

used for button handling

*/
#include "..\..\..\..\Core.h"

UI_Button::UI_Button(PCHAR ButtonText, int x, int y, LPCoreFunction ButtonFunction, COLOR32 Color)
{
	strcpy_s(Text, ButtonText);
	X = x;
	Y = y;
	TextColor = Color;
	Function = ButtonFunction;
}

void UI_Button::Draw(int x, int y, bool Visible)
{
	if (Visible)
	{
		int _X = x + X;
		int _Y = y + Y + g_Core->CaptionSize;
		int _W = g_Core->Render->GetStringWidth(Text) + 10;
		int _H = g_Core->TextSize + 2;
		bool MouseOver = MouseInfo->MouseOver(_X, _Y, _W, _H);

		// Draw checkbox
		g_Core->Render->FillRect(_X, _Y, _W, _H, MouseOver ? UnfocusedColor : FocusedColor);
		g_Core->Render->LineRect(_X, _Y, _W, _H, 1, LineColor);
		g_Core->Render->DepthFrame(_X, _Y, _W, _H);

		g_Core->Render->DrawString(true, _X + _W / 2, _Y + 1, TextColor, Text);

		if (MouseOver && MouseInfo->Down)
			g_Core->Render->DepthFrame(_X + 1, _Y + 1, _W - 1, _H - 1);

		if (Function != NULL && MouseOver && MouseInfo->Clicked)
			((void(__cdecl*)())Function)();
	}
}