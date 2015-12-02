/*

	File: UI_Checkbox

	checkbox handling

*/
#include "..\..\..\..\Core.h"

UI_Checkbox::UI_Checkbox(LPCoreValue Var, PCHAR ControlText, int x, int y, COLOR32 Color)
{
	strcpy_s(Text, ControlText);
	X = x;
	Y = y;
	TextColor = Color;
	Size = g_Core->TextSize - 4;
	Value = Var;
}

UI_Checkbox::~UI_Checkbox()
{
	
}

void UI_Checkbox::Draw(int x, int y, bool Visible)
{
	if (Visible)
	{
		int _X = x + X;
		int _Y = y + Y + g_Core->CaptionSize;
		bool MouseOver = MouseInfo->MouseOver(_X, _Y, Size, Size);

		// Draw checkbox
		g_Core->Render->FillRect(_X, _Y, Size, Size, MouseOver ? UnfocusedColor : FocusedColor);
		g_Core->Render->LineRect(_X, _Y, Size, Size, 1, LineColor);
		g_Core->Render->DepthFrame(_X, _Y, Size, Size);

		// Draw checked
		if (*(int*)Value != NULL)
		{
			g_Core->Render->Line(_X + 3, _Y + 3, _X + Size - 3, _Y + Size - 2, 2, CheckedColor);
			g_Core->Render->Line(_X + Size - 3, _Y + 2, _X + 3, _Y + Size - 3, 2, CheckedColor);
		}

		// Handle click
		if (MouseInfo->Clicked && MouseInfo->MouseOver(_X, _Y, Size, Size))
			*(int*)Value = !*(int*)Value;

		// Draw text
		g_Core->Render->DrawString(false, _X + Size + 7, _Y - 2, TextColor, Text);
	}
}