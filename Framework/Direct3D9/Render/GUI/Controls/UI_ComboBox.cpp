/*

	File: UI_ComboBox

	Combobox

*/
#include "..\..\..\..\Core.h"

UI_ComboBox::UI_ComboBox(PCHAR Name, float x, float y, float w, int* SelectedItemVariable, COLOR32 Color, int DisplayMaxItems)
{
	X = x;
	Y = y;
	W = w;
	SelectedIndex = SelectedItemVariable;
	if (!SelectedIndex)
		SelectedIndex = new int(0);
	MaxItems = DisplayMaxItems;
	ScrollbarValue = 0;
	strcpy_s(Text, Name);
}

void UI_ComboBox::Draw(float x, float y, bool Visible)
{
	if (Visible)
	{
		Index = *SelectedIndex;
		float _X = x + X;
		float _Y = y + Y;
		float _W = W;
		float _H = g_Core->TextSize + 4;

		// Draw box
		g_Core->Render->FillRect(_X, _Y, _W, _H, BackgroundColor);
		g_Core->Render->LineRect(_X, _Y, _W, _H, 1, LineColor);
		g_Core->Render->DepthFrame(_X, _Y, _W, _H);

		// Draw selected text
		if (Items.size() > 0)
		{
			SelectedItem = &Items[Index];
			g_Core->Render->DrawString(false, _X + 5, _Y + 1, TextColor, SelectedItem->Text);
		}
		else
			SelectedItem = NULL;

		// Draw dropdown button
		float _BtnX = _X + _W;
		float _BtnY = _Y;
		float _BtnSize = _H;

		g_Core->Render->FillRect(_BtnX, _BtnY, _BtnSize, _BtnSize, BackgroundButtonColor);
		g_Core->Render->LineRect(_BtnX, _BtnY, _BtnSize, _BtnSize, 1, LineColor);
		g_Core->Render->DepthFrame(_BtnX, _BtnY, _BtnSize, _BtnSize);

		// Draw dropdown triangle
		for (float i = 0; i < _BtnSize / 2 - 4; ++i)
			g_Core->Render->FillRect(_BtnX + 4 + i, _BtnY + _BtnSize / 2 - 2 + i, _BtnSize - i * 2 - 8, 1, LineColor);

		// Draw textbox
		float _TxtX = _X;
		float _TxtY = _Y + _BtnSize + 2;
		float _TxtW = _W;

		// Setup scrollbar
		float _ScrollbarX = _X + _W;
		float _ScrollbarY = _Y + _BtnSize + 2;
		float _ScrollbarW = _BtnSize;
		float _ScrollbarH = _BtnSize * MaxItems;
		int _ScrollbarMax = (int)Items.size() - MaxItems;

		// Doesnt apply for scrollbar but were using the var to check if were within box
		if (_ScrollbarMax < 0)
			_ScrollbarH = _BtnSize * (MaxItems - (MaxItems - Items.size()));

		// Mouse over box
		bool MouseOver = MouseInfo->MouseOver(_TxtX + (Scrollbar == NULL ? _BtnSize : 0), _TxtY, _TxtW, _ScrollbarH);
		if (!MouseOver && !MouseInfo->MouseOver(_BtnX, _BtnY, _BtnSize, _BtnSize) && MouseInfo->Clicked)
			MouseInfo->FocusedItem = NULL;

		// Handle combobox
		MouseOver = MouseInfo->MouseOver(_BtnX, _BtnY, _BtnSize, _BtnSize);

		// Focus handle
		bool Scrolling = (Scrollbar != NULL && MouseInfo->FocusedItem == Scrollbar);

		if (!Scrolling)
		{
			if (MouseInfo->Clicked && MouseOver && MouseInfo->DraggedElement == NULL && MouseInfo->FocusedItem == NULL)
				MouseInfo->FocusedItem = this;
			else if (MouseOver && MouseInfo->FocusedItem != NULL && MouseInfo->Clicked)
				MouseInfo->FocusedItem = NULL;
		}

		//Scrollbar
		if (!Scrollbar && _ScrollbarMax > 0)
			Scrollbar = new UI_Scrollbar(_ScrollbarX, _ScrollbarY, _ScrollbarW, _ScrollbarH, 0, (float)_ScrollbarMax, &ScrollbarValue);
		else if (Scrollbar != NULL && _ScrollbarMax <= 0)
			Scrollbar = NULL;

		// Display list
		if (MouseInfo->FocusedItem == this || Scrolling)
		{
			if (Scrollbar != NULL)
			{
				Scrollbar->X = _ScrollbarX;
				Scrollbar->Y = _ScrollbarY;
				Scrollbar->W = _ScrollbarW;
				Scrollbar->H = _ScrollbarH;
				Scrollbar->Max = (double)_ScrollbarMax;
				Scrollbar->Draw(0, 0);

				if (MouseInfo->Down && MouseInfo->MouseOver(_ScrollbarX, _ScrollbarY, _ScrollbarW, _ScrollbarH + _BtnSize) || MouseInfo->Down && Scrolling)
					MouseInfo->FocusedItem = Scrollbar;
				else
					MouseInfo->FocusedItem = this;
			}

			g_Core->Render->DepthFrame(_BtnX + 1, _BtnY + 1, _BtnSize - 1, _BtnSize - 1);

			// Draw items
			if (!Scrollbar)
				ScrollbarValue = 0;

			for (int i = 0; i < MaxItems; ++i)
			{
				if (i == Items.size())
					break;

				MouseOver = MouseInfo->MouseOver(_TxtX, _TxtY + i * _BtnSize, _TxtW + (Scrollbar == NULL ? _BtnSize : 0), _BtnSize);
				g_Core->Render->FillRect(_TxtX, _TxtY + i * _BtnSize, _TxtW + (Scrollbar == NULL ? _BtnSize : 0), _BtnSize, MouseOver ? ItemFocusedBackground : ItemUnfocusedBackground);
				g_Core->Render->DrawString(false, _TxtX + 5, _TxtY + 1 + i * _BtnSize, TextColor, Items[i + (int)ScrollbarValue].Text);

				if (MouseOver && MouseInfo->Clicked)
				{
					*SelectedIndex = i + (int)ScrollbarValue;
					SelectedItem = &Items[*SelectedIndex];
					MouseInfo->FocusedItem = NULL;
				}
			}

			// Perform scroll
			MouseOver = MouseInfo->MouseOver(_X, _Y, _W + _BtnSize, _ScrollbarH);
			if (MouseOver)
			{
				if (MouseInfo->ScrolledUp)
					--ScrollbarValue;
				if (MouseInfo->ScrolledDown)
					++ScrollbarValue;

				if (ScrollbarValue <= 0) ScrollbarValue = 0;
				if (ScrollbarValue > _ScrollbarMax) ScrollbarValue = (double)_ScrollbarMax;
			}
		}
	}
}

CoreComboboxItem* UI_ComboBox::AddItem(PCoreString Text)
{
	Items.push_back(CoreComboboxItem(Text, (int)Items.size() - 1));
	return &Items[Items.size() - 1];
}