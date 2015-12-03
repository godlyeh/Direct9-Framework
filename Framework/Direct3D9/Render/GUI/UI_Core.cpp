/*

	File: UI_Core

	Used for handling settings with GUI

*/
#include "..\..\..\Core.h"

UI_Window::UI_Window(PCoreString WindowCaption, float x, float y, float w, float h)
{
	strcpy_s(Caption, WindowCaption);
	X = x;
	Y = y;
	W = w;
	H = h;
}

void UI_Window::DrawWindow()
{
	// Draw titlebar
	g_Core->Render->FillRect(X, Y, W, g_Core->CaptionSize + 2, TitleBackgroundColor);
	g_Core->Render->DrawString(false, X + 10, Y + 2, TitleTextColor, Caption);

	// Draw window
	g_Core->Render->FillRect(X, Y + g_Core->CaptionSize + 2, W, H, BackgroundColor);
	g_Core->Render->LineRect(X, Y, W, H + g_Core->CaptionSize + 2, 1, LineColor);
	g_Core->Render->Line(X + 1, Y + g_Core->CaptionSize + 2, X + W, Y + g_Core->CaptionSize + 2, 1, LineColor);
	g_Core->Render->DepthFrame(X, Y + g_Core->CaptionSize + 2, W, H);

	// Draw groupboxes
	for (int i = 0; i < (int)UIGroupbox.size(); ++i)
		UIGroupbox[i].Draw(X, Y);

	// Draw buttons
	for (int i = 0; i < (int)UIGroupbox.size(); ++i)
		UIButton[i].Draw(X, Y);

	// Draw checkboxes
	for (int i = 0; i < (int)UICheckbox.size(); ++i)
		UICheckbox[i].Draw(X, Y);

	// Draw labels
	for (int i = 0; i < (int)UILabel.size(); ++i)
		UILabel[i].Draw(X, Y);

	// Draw Sliders
	for (int i = 0; i < (int)UISlider.size(); ++i)
		UISlider[i].Draw(X, Y);
}

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

UI_Label* UI_Window::AddLabel(UI_Label* Label)
{
	UILabel.push_back(*Label);
	return &UILabel[UILabel.size() - 1];
}

UI_Slider* UI_Window::AddSlider(UI_Slider* Slider)
{
	UISlider.push_back(*Slider);
	return &UISlider[UISlider.size() - 1];
}

/*
	
	UI Setup

*/
UI_Window* UI_Setup::RegisterWindow(UI_Window* Window)
{
	UIWindow.push_back(*Window);
	return &UIWindow[UIWindow.size() - 1];
}

void UI_Setup::DrawWindows()
{
	// Get mouse info
	MouseInfo->UpdateInfo();

	// Handle window dragging
	static UI_Window *DraggedElement = NULL;
	for (int i = (int)UIWindow.size() - 1; i >= 0; --i)
	{
		// Handle window dragging
		static UI_Window *DraggedElement = NULL;
		if (MouseInfo->Down)
		{
			if (DraggedElement != NULL || MouseInfo->MouseOver(UIWindow[i].X, UIWindow[i].Y, UIWindow[i].W, g_Core->CaptionSize))
			{
				static float DiffX = 0;
				static float DiffY = 0;

				// Rearrange windows
				if (DraggedElement == NULL)
				{
					std::iter_swap(UIWindow.begin() + (int)UIWindow.size() - 1, UIWindow.begin() + i);
					DraggedElement = &UIWindow[(int)UIWindow.size() - 1];
					DiffX = MouseInfo->X - DraggedElement->X;
					DiffY = MouseInfo->Y - DraggedElement->Y;
				}

				if (DraggedElement != NULL)
				{
					DraggedElement->X = MouseInfo->X - DiffX;
					DraggedElement->Y = MouseInfo->Y - DiffY;
				}
			}
		}
		else
			DraggedElement = NULL;
	}

	// Handle windows
	for (int i = 0; i < (int)UIWindow.size(); ++i)
	{
		

		// Draw windows
		UIWindow[i].DrawWindow();
	}
}