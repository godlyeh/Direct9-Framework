/*

	File: UI_Slider

	Used for slider handling both vertically and horizontally

*/
#include "..\..\..\..\Core.h"

UI_Slider::UI_Slider(float x, float y, float size, double min, double max, PCoreVariable SliderValue, PCoreString Text, bool DrawVertically, COLOR32 Color)
{
	if (Text != NULL)
	{
		SliderText = new CoreString;
		strcpy_s(SliderText, strlen(Text) + 1, Text);
	}
	X = x;
	Y = y;
	Size = size;
	Min = min;
	Max = max;
	Value = SliderValue;
	Vertical = DrawVertically;
	TextColor = Color;
}

void UI_Slider::DrawSliderPin(float x, float y, float size, bool SetVertical)
{
	if (SetVertical)
	{
		float _X = x;
		float _Y = y - size / 2;
		g_Core->Render->FillRect(_X, _Y, size, size, SliderColor);
		for (float i = 0; i < size / 2 + 1; ++i)
			g_Core->Render->FillRect(_X - i, _Y + i, 1, size - i * 2, SliderColor);
	}
	else
	{
		float _X = x - size / 2;
		float _Y = y;
		g_Core->Render->FillRect(_X, _Y, size, size, SliderColor);
		for (float i = 0; i < size / 2 + 1; ++i)
			g_Core->Render->FillRect(_X + i, _Y + size + i, size - i * 2, 1, SliderColor);
	}
}

void UI_Slider::Draw(float x, float y, bool Visible)
{
	if (Visible)
	{
		if (Min > Max)
			return;

		float _X = x + X;
		float _Y = y + Y + g_Core->CaptionSize;
		float _SliderSize = 7;
		float _SliderMinDiff = 0;
		
		// Simple fix for easier math
		float _MinNegativeFix = 0;
		_MinNegativeFix = (float)-Min;
		Min += _MinNegativeFix;
		Max += _MinNegativeFix;
		if (Min < 0)
			_SliderMinDiff = (float)(Min * 100 / Max);

		// Value
		double _Value = *(double*)Value + _MinNegativeFix;

		if (Vertical)
		{
			// Draw scaling line
			g_Core->Render->FillRect(_X - 2, _Y, 5, 1, SliderColor); // Draw first line
			g_Core->Render->FillRect(_X, _Y + 1, 2, Size - 1, SliderColor); // Draw main line
			g_Core->Render->FillRect(_X - 2, _Y + Size, 5, 1, SliderColor); // Draw last line

			// Calc slider pin placement
			float _SliderX = _X + _SliderSize;
			float _SliderY = _Y + (float)(Size * (100 - (_Value * 100 / Max)) / 100);
			_SliderY -= _SliderMinDiff;

			// Draw slider pin
			DrawSliderPin(_SliderX, _SliderY, _SliderSize, true);

			// Move slider
			if (MouseInfo->Down && MouseInfo->DraggedElement == NULL && MouseInfo->MouseOver(_SliderX, _SliderY - _SliderSize / 2, _SliderSize, _SliderSize) || MouseInfo->Down && MouseInfo->DraggedElement == this)
			{
				MouseInfo->DraggedElement = this;
				*(double*)Value = (double)((100 - ((MouseInfo->Y - _Y) * 100 / Size)) * Max / 100);
				*(double*)Value -= (double)_MinNegativeFix;
			}
		}
		else
		{
			// Draw scaling line
			g_Core->Render->FillRect(_X, _Y - 2, 1, 5, SliderColor); // Draw first line
			g_Core->Render->FillRect(_X + 1, _Y, Size - 1, 2, SliderColor); // Draw main line
			g_Core->Render->FillRect(_X + Size, _Y - 2, 1, 5, SliderColor); // Draw last line

			// Calc slider pin placement
			float _SliderX = _X + (float)(Size * (_Value * 100 / Max) / 100);
			float _SliderY = _Y - _SliderSize - 6;
			_SliderX -= _SliderMinDiff;

			// Draw slider pin
			DrawSliderPin(_SliderX, _SliderY, _SliderSize);

			// Move slider
			if (MouseInfo->Down && MouseInfo->DraggedElement == NULL && MouseInfo->MouseOver(_SliderX - _SliderSize / 2, _SliderY, _SliderSize, _SliderSize) || MouseInfo->Down && MouseInfo->DraggedElement == this)
			{
				MouseInfo->DraggedElement = this;
				*(double*)Value = (double)(((MouseInfo->X - _X) * 100 / Size) * Max / 100);
				*(double*)Value -= (double)_MinNegativeFix;
			}
		}

		// Reset min / max
		Min -= _MinNegativeFix;
		Max -= _MinNegativeFix;

		// Bound
		if (*(double*)Value > Max) *(double*)Value = Max;
		if (*(double*)Value < Min) *(double*)Value = Min;

		//Text
		if (SliderText != NULL)
		{
			if (!_stricmp(SliderText, UI_SLIDER_VALUE_TEXT))
			{
				if (Vertical)
					g_Core->Render->DrawString(true, _X - g_Core->Render->GetStringWidth("%.2f", *(double*)Value) / 2 - 6, _Y + Size / 2, TextColor, "%.2f", *(double*)Value);
				else
					g_Core->Render->DrawString(true, _X + Size / 2, _Y + 5, TextColor, "%.2f", *(double*)Value);
			}
			else
			{
				if (Vertical)
					g_Core->Render->DrawString(true, _X - g_Core->Render->GetStringWidth(SliderText) / 2 - 6, _Y + Size / 2, TextColor, SliderText);
				else
					g_Core->Render->DrawString(true, _X + Size / 2, _Y + 5, TextColor, SliderText);
			}
		}
	}
}