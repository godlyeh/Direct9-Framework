/*

	File: UI_Label

	used for creating simple labels

*/
#include "..\..\..\..\Core.h"

UI_Label::UI_Label(PCHAR Label, float x, float y, LPCoreString pString, COLOR32 Color)
{
	strcpy_s(Text, Label);
	X = x;
	Y = y;
	String = pString;
	TextColor = Color;
}

void UI_Label::Draw(float x, float y, bool Visible)
{
	if (Visible)
	{
		float _X = x + X;
		float _Y = y + Y + g_Core->CaptionSize;

		if (String)
			g_Core->Render->DrawString(false, _X, _Y, TextColor, "%s%s", Text, (PCHAR)String);
		else
			g_Core->Render->DrawString(false, _X, _Y, TextColor, Text);
	}
}