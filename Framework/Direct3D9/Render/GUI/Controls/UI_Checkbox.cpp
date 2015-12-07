/*

	File: UI_Checkbox

	checkbox handling

*/
#include "..\..\..\..\Core.h"

UI_Checkbox::UI_Checkbox(LPVOID Var, PCoreString ControlText, float x, float y, COLOR32 Color)
{
	strcpy_s(Text, ControlText);
	X = x;
	Y = y;
	TextColor = Color;
	Size = g_Core->TextSize - 3;
	Value = Var;
}

UI_Checkbox::~UI_Checkbox()
{
	
}

void UI_Checkbox::Draw(float x, float y, bool Visible)
{
	if (Visible)
	{
		float _X = x + X;
		float _Y = y + Y + g_Core->CaptionSize;
		bool MouseOver = MouseInfo->MouseOver(_X, _Y, Size, Size);

		// Draw checkbox
		g_Core->Render->FillRect(_X, _Y, Size, Size, MouseOver ? UnfocusedColor : FocusedColor);
		g_Core->Render->LineRect(_X, _Y, Size, Size, 1, LineColor);
		g_Core->Render->DepthFrame(_X, _Y, Size, Size);

		// Draw checked
		if (*(int*)Value != NULL)
			g_Core->Render->DrawString(true, _X + Size / 2 + 1, _Y - 1.5f, TextColor, "x");

		// Mouse down
		if (MouseOver && MouseInfo->Down && MouseInfo->DraggedElement == NULL)
			g_Core->Render->DepthFrame(_X + 1, _Y + 1, Size - 1, Size - 1);

		// Handle click
		if (MouseInfo->Clicked && MouseInfo->MouseOver(_X, _Y, Size, Size))
			*(bool*)Value = !*(bool*)Value;

		// Draw text
		g_Core->Render->DrawString(false, _X + Size + 7, _Y - 1, TextColor, Text);
	}
}