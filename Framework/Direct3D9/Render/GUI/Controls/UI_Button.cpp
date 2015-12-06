/*

File: UI_Button

used for button handling

*/
#include "..\..\..\..\Core.h"

UI_Button::UI_Button(PCoreString ButtonText, float x, float y, LPVOID ButtonFunction, COLOR32 Color)
{
	strcpy_s(Text, ButtonText);
	X = x;
	Y = y;
	TextColor = Color;
	Function = ButtonFunction;
}

void UI_Button::Draw(float x, float y, bool Visible)
{
	if (Visible)
	{
		float _X = x + X;
		float _Y = y + Y + g_Core->CaptionSize;
		float _W = g_Core->Render->GetStringWidth(Text) + 10;
		float _H = g_Core->TextSize + 2;
		bool MouseOver = (MouseInfo->MouseOver(_X, _Y, _W, _H));

		// Draw checkbox
		g_Core->Render->FillRect(_X, _Y, _W, _H, MouseOver ? FocusedColor : UnfocusedColor);
		g_Core->Render->LineRect(_X, _Y, _W, _H, 1, LineColor);
		g_Core->Render->DepthFrame(_X, _Y, _W, _H);
		g_Core->Render->DepthFrame(_X + 1, _Y + 1, _W - 2, _H - 2);

		g_Core->Render->DrawString(true, _X + _W / 2, _Y + 1, TextColor, Text);

		if (MouseOver && MouseInfo->Down && MouseInfo->DraggedElement == NULL)
			g_Core->Render->DepthFrame(_X + 1, _Y + 1, _W - 1, _H - 1);

		if (Function != NULL && MouseOver && MouseInfo->Clicked)
			((void(__cdecl*)())Function)();
	}
}