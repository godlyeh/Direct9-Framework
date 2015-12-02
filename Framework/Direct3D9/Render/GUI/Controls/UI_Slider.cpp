/*

	File: UI_Slider

	Used for slider handling both vertically and horizontally

*/
#include "..\..\..\..\Core.h"

UI_Slider::UI_Slider(float x, float y, float size, double min, double max, LPCoreValue SliderValue, COLOR32 Color, bool DrawVertically)
{
	X = x;
	Y = y;
	Size = size;
	Min = min;
	Max = max;
	Value = SliderValue;
	Vertical = DrawVertically;
}

void UI_Slider::DrawSliderPin(float x, float y, float size)
{
	float _X = x - size / 2;
	float _Y = y;
	g_Core->Render->FillRect(_X, _Y, size, size, SliderColor);
	for (float i = 0; i < size / 2 + 1; ++i)
		g_Core->Render->FillRect(_X + i, _Y + size + i, size - i * 2, 1, SliderColor);
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
		float _MinNegativeFix = 0;
		if (Min < 0)
		{
			_MinNegativeFix = (float)-Min;
			Min += _MinNegativeFix;
			Max += _MinNegativeFix;
		}

		if (Vertical)
		{

		}
		else
		{
			g_Core->Render->FillRect(_X, _Y - 2, 1, 5, SliderColor); // Draw first line
			g_Core->Render->FillRect(_X + 1, _Y, Size, 2, SliderColor); // Draw main line
			g_Core->Render->FillRect(_X + Size + 1, _Y - 2, 1, 5, SliderColor); // Draw last line

			// Draw slider pin
			double _Value = *(double*)Value + _MinNegativeFix;
			float _SliderPercent = (float)_Value * 100 / (float)(Max - Min);
			float _SliderX = _X + _SliderPercent;
			float _SliderY = _Y - _SliderSize - 5;
			float _SliderMinDiff = 0;
			if (Min > 0) _SliderMinDiff = (float)(Min * 100 / Max);
			_SliderX -= _SliderMinDiff;

			DrawSliderPin(_SliderX, _SliderY, _SliderSize);

			// Move slider
			static bool _SliderHeld = false;
			if (MouseInfo->MouseOver(_SliderX - _SliderSize / 2, _SliderY, _SliderSize, _SliderSize) && MouseInfo->Down || MouseInfo->Down && _SliderHeld)
			{
				_SliderHeld = true;
				*(double*)Value = -(double)((_X - MouseInfo->X) * (Max - Min) / 100);
				if (_MinNegativeFix)
					*(double*)Value -= (double)_MinNegativeFix;
			}
			else
				_SliderHeld = false;
		}

		// Bound
		if (_MinNegativeFix)
		{
			Min -= _MinNegativeFix;
			Max -= _MinNegativeFix;
		}
		if (*(double*)Value > Max) *(double*)Value = Max;
		if (*(double*)Value < Min) *(double*)Value = Min;

		CLog::Log("Value: %f", *(double*)Value);
	}
}