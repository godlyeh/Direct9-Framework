/*

File: UI_Button

used for button handling

*/
#include "..\..\..\..\Core.h"

UI_Button::UI_Button(PCoreString ButtonText, float x, float y, LPVOID ButtonFunction, LPVOID Args, COLOR32 Color)
{
	strcpy_s(Text, ButtonText);
	X = x;
	Y = y;
	TextColor = Color;
	Function = ButtonFunction;
	FunctionArgs = Args;
}

void UI_Button::Draw(float x, float y, bool Visible)
{
	if (Visible)
	{
		float _X = x + X;
		float _Y = y + Y + g_Core->CaptionSize;
		float _W = g_Core->Render->GetStringWidth(Text) + 12;
		float _H = g_Core->TextSize + 4;
		bool MouseOver = (MouseInfo->MouseOver(_X, _Y, _W, _H));
		bool HasLowerCase = false;

		// Check for lower case and increase size
		int i = 0;
		while (Text[i])
		{
			if (islower(Text[i]))
			{
				HasLowerCase = true;
				_H += 3;
				break;
			}
			++i;
		}

		// Draw button
		g_Core->Render->FillRect(_X, _Y, _W, _H, MouseOver ? FocusedColor : UnfocusedColor);
		g_Core->Render->LineRect(_X, _Y, _W, _H, 1, LineColor);
		g_Core->Render->DepthFrame(_X, _Y, _W, _H);
		g_Core->Render->DepthFrame(_X + 1, _Y + 1, _W - 2, _H - 2);

		if (MouseOver && MouseInfo->Down && (MouseInfo->FocusedItem == NULL || MouseInfo->FocusedItem == this) && MouseInfo->DraggedElement == NULL)
		{
			g_Core->Render->DepthFrame(_X + 1, _Y += 1, _W - 1, _H - 1);
			MouseInfo->FocusedItem = this;
		}
		else
			MouseInfo->FocusedItem = NULL;


		g_Core->Render->DrawString(true, _X + _W / 2, _Y + 3 + (HasLowerCase ? 1 : 0), TextColor, Text);

		if (Function != NULL && MouseOver && MouseInfo->Clicked)
		{
			if (FunctionArgs) ((void(__cdecl*)(LPVOID))Function)(FunctionArgs);
			else ((void(__cdecl*)())Function)();
		}
	}
}