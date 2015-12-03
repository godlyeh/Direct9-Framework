/*

	File: UI_ComboBox

	Combobox

*/
#include "..\..\..\..\Core.h"

UI_ComboBox::UI_ComboBox(float x, float y, float w, std::vector<CoreComboboxItem>* ItemArray, COLOR32 Color, int DisplayMaxItems)
{
	X = x;
	Y = y;
	W = w;
	AddVectorArray(ItemArray);
	MaxItems = DisplayMaxItems;
}

void UI_ComboBox::Draw(float x, float y, bool Visible)
{
	if (Visible)
	{
		float _X = x + X;
		float _Y = y + Y;
		float _W = W;
		float _H = g_Core->TextSize + 4;

		// Draw box
		g_Core->Render->FillRect(_X, _Y, _W, _H, BackgroundColor);
		g_Core->Render->LineRect(_X, _Y, _W, _H, 1, LineColor);
		g_Core->Render->DepthFrame(_X, _Y, _W, _H);

		// Draw selected text
		if (SelectedItem)
			g_Core->Render->DrawString(false, _X + 5, _Y + 1, TextColor, SelectedItem->Text);

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
		float _TxtY = _Y + _H + 2;
		float _TxtW = W + _BtnSize;

		bool MouseOver = MouseInfo->MouseOver(_TxtX, _TxtY, _TxtW, _H * Items.size());
		if (!MouseOver && !MouseInfo->MouseOver(_BtnX, _BtnY, _BtnSize, _BtnSize) && MouseInfo->Down)
			MouseInfo->FocusedItem = NULL;

		// Handle combobox
		MouseOver = MouseInfo->MouseOver(_BtnX, _BtnY, _BtnSize, _BtnSize);

		// Focus handle
		if (MouseInfo->Clicked && MouseOver && MouseInfo->DraggedElement == NULL && MouseInfo->FocusedItem == NULL)
			MouseInfo->FocusedItem = this;
		else if (MouseOver && MouseInfo->FocusedItem != NULL && MouseInfo->Clicked)
			MouseInfo->FocusedItem = NULL;

		// Display list
		if (MouseInfo->FocusedItem == this)
		{
			g_Core->Render->DepthFrame(_BtnX + 1, _BtnY + 1, _BtnSize - 1, _BtnSize - 1);

			for (int i = 0; i < MaxItems; ++i)
			{
				if (i == Items.size())
					break;

				MouseOver = MouseInfo->MouseOver(_TxtX, _TxtY + i * _H, _TxtW, _H);
				g_Core->Render->FillRect(_TxtX, _TxtY + i * _H, _TxtW, _H, MouseOver ? ItemFocusedBackground : ItemUnfocusedBackground);
				g_Core->Render->DrawString(false, _TxtX + 5, _TxtY + 1 + i * _H, TextColor, Items[i].Text);

				if (MouseOver && MouseInfo->Clicked)
				{
					SelectedItem = &Items[i];
					MouseInfo->FocusedItem = NULL;
				}
			}
		}
	}
}

void UI_ComboBox::AddItem(PCoreString Text)
{
	Items.push_back(CoreComboboxItem(Text, Items.size() - 1));
	if (SelectedItem->CrappyFix) SelectedItem = &Items[0];
}

void UI_ComboBox::AddVectorArray(std::vector<CoreComboboxItem>* ItemArray)
{
	if (ItemArray)
	{
		Items.insert(Items.end(), ItemArray->begin(), ItemArray->end());
		SelectedItem = &Items[0];
		if (SelectedItem->CrappyFix) SelectedItem = &Items[0];
	}
}