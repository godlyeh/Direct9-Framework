/*

	File: UI_Slider

	Used for slider handling both vertically and horizontally

*/
#include "..\..\..\..\Core.h"

UI_Slider::UI_Slider(int x, int y, int size, double min, double max, LPCoreValue SliderValue, COLOR32 Color, bool DrawVertically)
{
	X = x;
	Y = y;
	Size = size;
	Min = min;
	Max = max;
	Value = SliderValue;
	Vertical = DrawVertically;
}

void UI_Slider::DrawSliderPin(int x, int y, int size)
{
	int _X = x - size / 2;
	int _Y = y;
	g_Core->Render->FillRect(_X, _Y, size, size, SliderColor);
	for (int i = 0; i < size / 2 + 1; ++i)
		g_Core->Render->FillRect(_X + i, _Y + size + i, size - i * 2, 1, SliderColor);
}

void UI_Slider::Draw(int x, int y, bool Visible)
{
	if (Visible)
	{
		int _X = x + X;
		int _Y = y + Y + g_Core->CaptionSize;
		int _SliderSize = 7;

		if (Vertical)
		{

		}
		else
		{
			g_Core->Render->FillRect(_X, _Y - 2, 1, 5, SliderColor); // Draw first line
			g_Core->Render->FillRect(_X + 1, _Y, Size, 2, SliderColor); // Draw main line
			g_Core->Render->FillRect(_X + Size + 1, _Y - 2, 1, 5, SliderColor); // Draw last line

			// Draw slider pin
			double _Value = *(double*)Value;
			int _SliderPercent = (int)(_Value * 100 / (Max - Min));
			int _SliderX = _X + _SliderPercent;
			int _SliderY = _Y - _SliderSize - 5;
			DrawSliderPin(_SliderX, _SliderY, _SliderSize);

			// Move slider
			static bool _SliderHeld = false;
			static int _SliderMouseX = 0;
			if (MouseInfo->MouseOver(_SliderX, _SliderY, _SliderSize, _SliderSize) && MouseInfo->Down || MouseInfo->Down && _SliderHeld)
			{
				_SliderHeld = true;
				*(double*)Value = -(double)((_X - MouseInfo->X) * (Max - Min) / 100);
			}
			else
				_SliderHeld = false;
		}

		// Bound
		if (*(double*)Value > Max) *(double*)Value = Max;
		if (*(double*)Value < Min) *(double*)Value = Min;

		CLog::Log("%f", *(double*)Value);
	}
}