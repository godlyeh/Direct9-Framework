/*

File: UI_Scrollbar

Universal scrolbar handling

*/
#include "..\..\..\..\Core.h"

UI_Scrollbar::UI_Scrollbar(float x, float y, float w, float h, float min, float max, LPVOID ScrollbarValue, bool IsVertical, COLOR32 Color)
{
	X = x;
	Y = y;
	W = w;
	H = h;
	Min = (double)min;
	Max = (double)max;
	Vertical = IsVertical;
	SliderColor = Color;
	Value = ScrollbarValue;
	if (Value == NULL)
		Value = new double(0);
}

void UI_Scrollbar::DrawSlider(float x, float y, float w, float h)
{
	if (Vertical)
		g_Core->Render->FillRect(x + 1, y + 4, w - 5, h - 6, SliderColor);
	else
		g_Core->Render->FillRect(x, y + 1, w, h - 4, SliderColor);
}

void UI_Scrollbar::Draw(float x, float y, bool Visible)
{
	if (Visible)
	{
		if (W < 6)
			W = 6;

		// Simple fix for easier math
		float _MinNegativeFix = 0;
		_MinNegativeFix = (float)-Min;
		Min += _MinNegativeFix;
		Max += _MinNegativeFix;

		// Values
		double _Value = *(double*)Value + _MinNegativeFix;
		float _X = x + X;
		float _Y = y + Y;
		float _W = W;
		float _H = H;

		if (Vertical)
		{
			 // Draw scrollbar
			float _SliderW = _W;
			float _SliderH = _H * 0.25f;

			g_Core->Render->FillRect(_X, _Y, _W, _H, ScrollbarBackground);
			g_Core->Render->LineRect(_X, _Y, _W, _H, 1, LineColor);
			g_Core->Render->DepthFrame(_X, _Y, _W, _H);
		
			// Calc slider placement
			float _SliderX = _X + 2;
			float _ValuePercent = (float)(_Value * 100 / Max);
			float _SliderPlacement = (_ValuePercent * _H / 100);
			float _SliderPercent = (_SliderPlacement * 100 / _H);
			float _SliderPlacementFix = (_SliderH * _SliderPercent / 100);
			float _SliderY = _Y + _SliderPlacement - _SliderPlacementFix;

			// Draw slider
			DrawSlider(_SliderX, _SliderY, _SliderW, _SliderH);

			// Move slider
			if (MouseInfo->Down && MouseInfo->DraggedElement == NULL && MouseInfo->FocusedItem == NULL && MouseInfo->MouseOver(_SliderX, _SliderY, _SliderW, _SliderH) || MouseInfo->Down && MouseInfo->DraggedElement == this || MouseInfo->Down && MouseInfo->FocusedItem == this)
			{
				MouseInfo->DraggedElement = this;
				float _MouseY = MouseInfo->Y - _Y;
				float _MousePercent = _MouseY * 100 / _H;
				*(double*)Value = (double)(Max * _MousePercent / 100);
				*(double*)Value -= (double)_MinNegativeFix;
			}

		}
		else
		{

		}

		// Reset min / max
		Min -= _MinNegativeFix;
		Max -= _MinNegativeFix;

		// Bound variable
		if (*(double*)Value > Max) *(double*)Value = Max;
		if (*(double*)Value < Min) *(double*)Value = Min;
	}
}