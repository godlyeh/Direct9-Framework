/*

	File: UI_Core

	Used for handling settings with GUI

*/
#include "..\..\..\Core.h"

void CloseGUIWindow(bool *WindowToDraw)
{
	*WindowToDraw = !*WindowToDraw;
}

UI_Window::UI_Window(PCoreString WindowCaption, float x, float y, float w, float h, bool *Visible, bool *MainWindowHandle, bool HasCaption)
{
	strcpy_s(Caption, WindowCaption);
	X = x;
	Y = y;
	W = w;
	H = h;
	WindowHasCaption = HasCaption;
	DrawWindows = Visible;
	if (DrawWindows == NULL)
		DrawWindows = new bool(true);
	MainWindow = MainWindowHandle;
}

void UI_Window::DrawWindow()
{
	static UI_Button* CloseButton = new UI_Button("X", 0, 0, CloseGUIWindow);

	if (MainWindow != NULL && *MainWindow == false)
		return;

	if (*DrawWindows == true)
	{
		float _Y = Y;
		float _Size = g_Core->CaptionSize + 6;

		// Draw titlebar
		if (WindowHasCaption)
		{
			// Draw caption
			g_Core->Render->FillRect(X, _Y, W, _Size, TitleBackgroundColor);
			g_Core->Render->DrawString(false, X + 15, _Y + 5, TitleTextColor, Caption);

			// Draw dots
			for (int i = 0; i < 3; ++i)
			{
				g_Core->Render->FillRect(X + 3 + i * 3, _Y + 2, 2, 3, BackgroundColor);
				if (i < 2)
					g_Core->Render->FillRect(X + 3 + i * 3, _Y + 5, 2, 3, BackgroundColor);
				if (i < 1)
					g_Core->Render->FillRect(X + 3 + i * 3, _Y + 8, 2, 3, BackgroundColor);
			}

			_Y += _Size;
		}

		// Draw window
		g_Core->Render->FillRect(X, _Y, W, H, BackgroundColor);
		g_Core->Render->LineRect(X, _Y - (WindowHasCaption ? _Size : 0), W, H + (WindowHasCaption ? _Size : 0), 1, LineColor);
		g_Core->Render->Line(X + 1, _Y, X + W, _Y, 1, LineColor);
		g_Core->Render->DepthFrame(X, _Y, W, H);

		// Fix pos
		if (!WindowHasCaption)
			_Y -= _Size;

		// Draw groupboxes
		for (int i = 0; i < (int)UIGroupbox.size(); ++i)
			UIGroupbox[i].Draw(X, _Y);

		// Draw buttons
		for (int i = 0; i < (int)UIButton.size(); ++i)
			UIButton[i].Draw(X, _Y);

		// Draw checkboxes
		for (int i = 0; i < (int)UICheckbox.size(); ++i)
			UICheckbox[i].Draw(X, _Y - g_Core->CaptionSize);

		// Draw labels
		for (int i = 0; i < (int)UILabel.size(); ++i)
			UILabel[i].Draw(X, _Y);

		// Draw Sliders
		for (int i = 0; i < (int)UISlider.size(); ++i)
			UISlider[i].Draw(X, _Y);

		// Draw Comboboxes
		for (int i = 0; i < (int)UIComboBox.size(); ++i)
			UIComboBox[i].Draw(X, _Y);

		// Draw Scrollbars
		for (int i = 0; i < (int)UIScrollbar.size(); ++i)
			UIScrollbar[i].Draw(X, _Y);

		// Draw close button
		if (WindowHasCaption)
		{
			// Draw close button
			CloseButton->X = W - 9 - g_Core->TextSize;
			CloseButton->Y = 3;
			CloseButton->FocusedColor = CLR_CLOSE_BUTTON_FOCUSED;
			CloseButton->UnfocusedColor = CLR_CLOSE_BUTTON_UNFOCUSED;
			CloseButton->Draw(X, Y - g_Core->CaptionSize);

			// Setup clicks for our close button
			static bool bFocus = false;
			static bool bPressed = false;
			static bool bDown = false;

			if (!MouseInfo->Down && !bDown)
				bPressed = false;

			if (MouseInfo->Down && !bDown)
				bDown = true;

			if (!MouseInfo->Down && bDown)
			{
				bDown = false;
				bPressed = true;
			}

			// Close window and force focus
			if (MouseInfo->MouseOver(X + W - 9 - g_Core->TextSize, Y + 3, g_Core->TextSize + 4, g_Core->TextSize + 3))
			{
				MouseInfo->FocusedItem = this;

				if (MouseInfo->Down) bFocus = true;

				if (bPressed)
					CloseGUIWindow(DrawWindows);
			}
			else if (MouseInfo->Down && bFocus)
				MouseInfo->FocusedItem = this;
			else
			{
				bFocus = false;
				MouseInfo->FocusedItem = NULL;
			}
		}
	}
}

/*

	Create controls

*/

UI_Button* UI_Window::AddButton(UI_Button* Button)
{
	UIButton.push_back(*Button);
	return &UIButton[UIButton.size() - 1];
}

UI_GroupBox* UI_Window::AddGroupbox(UI_GroupBox* GroupBox)
{
	UIGroupbox.push_back(*GroupBox);
	return &UIGroupbox[UIGroupbox.size() - 1];
}

UI_Checkbox* UI_Window::AddCheckbox(UI_Checkbox* CheckBox)
{
	UICheckbox.push_back(*CheckBox);
	return &UICheckbox[UICheckbox.size() - 1];
}

UI_ComboBox* UI_Window::AddCombobox(UI_ComboBox* ComboBox)
{
	UIComboBox.push_back(*ComboBox);
	return &UIComboBox[UIComboBox.size() - 1];
}

UI_Label* UI_Window::AddLabel(UI_Label* Label)
{
	UILabel.push_back(*Label);
	return &UILabel[UILabel.size() - 1];
}

UI_Scrollbar* UI_Window::AddScrollbar(UI_Scrollbar* Scrollbar)
{
	UIScrollbar.push_back(*Scrollbar);
	return &UIScrollbar[UIScrollbar.size() - 1];
}

UI_Slider* UI_Window::AddSlider(UI_Slider* Slider)
{
	UISlider.push_back(*Slider);
	return &UISlider[UISlider.size() - 1];
}

/*

	Get controls etc

*/

UI_ComboBox* UI_Window::GetCombobox(PCoreString Text)
{
	for (int i = 0; i < (int)UIComboBox.size() - 1; ++i)
	{
		for (int x = 0; x < (int)UIComboBox.size() - 1; ++x)
			if (!_stricmp(UIComboBox[i].Items[x].Text, Text))
				return &UIComboBox[i];
	}

	return NULL;
}

UI_ComboBox* UI_Window::GetCombobox(UI_ComboBox* ComboBox)
{
	for (int i = 0; i < (int)UIComboBox.size() - 1; ++i)
		if (ComboBox == &UIComboBox[i])
			return &UIComboBox[i];

	return NULL;
}

UI_ComboBox* UI_Window::GetCombobox(int Index)
{
	if (Index > (int)UIComboBox.size() - 1)
		return NULL;

	return &UIComboBox[Index];
}

UI_ComboBox* UI_Window::GetCombobox()
{
	if (UIComboBox.size() == 0)
		return NULL;

	return &UIComboBox[UICheckbox.size() - 1];
}

/*
	
	UI Setup

*/
UI_Window *UI_Setup::RegisterWindow(UI_Window* Window)
{
	UIWindow.push_back(*Window);
	return &UIWindow[UIWindow.size() - 1];
}

void UI_Setup::DrawWindows()
{
	// Get mouse info
	MouseInfo->UpdateInfo();

	// Handle windows
	for (int i = 0; i < (int)UIWindow.size(); ++i)
	{
		// Draw windows
		UIWindow[i].DrawWindow();
	}

	// Handle window dragging
	for (int i = (int)UIWindow.size() - 1; i >= 0; --i)
	{
		if (!UIWindow[i].WindowHasCaption)
			continue;

		// Handle window dragging
		if (MouseInfo->Down && MouseInfo->DraggedElement == NULL && MouseInfo->MouseOver(UIWindow[i].X, UIWindow[i].Y, UIWindow[i].W, g_Core->CaptionSize) || MouseInfo->Down && MouseInfo->DraggedElement == &UIWindow[i])
		{
			static int DiffX = 0;
			static int DiffY = 0;

			// Rearrange windows
			if (MouseInfo->DraggedElement == NULL)
			{
				std::iter_swap(UIWindow.begin() + (int)UIWindow.size() - 1, UIWindow.begin() + i);
				MouseInfo->DraggedElement = &UIWindow[(int)UIWindow.size() - 1];
				DiffX = MouseInfo->X - (int)((UI_Window*)(MouseInfo->DraggedElement))->X;
				DiffY = MouseInfo->Y - (int)((UI_Window*)(MouseInfo->DraggedElement))->Y;
			}

			if (MouseInfo->DraggedElement != NULL)
			{
				((UI_Window*)(MouseInfo->DraggedElement))->X = (float)(MouseInfo->X - DiffX);
				((UI_Window*)(MouseInfo->DraggedElement))->Y = (float)(MouseInfo->Y - DiffY);
			}
		}
	}

	MouseInfo->ScrolledDown = false;
	MouseInfo->ScrolledUp = false;
}