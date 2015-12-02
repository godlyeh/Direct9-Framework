/*

	File: UI_Core

	Used for creating window GUI for settings handling

	Supports:
	 - Basic handling
	 - Checkbox

*/

//Colors
#define CLR_WINDOW_BACKGROUND rgb(60, 60, 60, 250)
#define CLR_TITLE_BACKGROUND rgb(80, 80, 80, 250)
#define CLR_LINE_DEFAULT rgb(0, 0, 0, 255)

#define CLR_TEXT_DEFAULT rgb(255, 255, 255)
#define CLR_CAPTION_TEXT CLR_TEXT_DEFAULT

#define CLR_CHECKBOX_CHECKED rgb(30, 30, 30)

#define CLR_FOCUSED_DEFAULT rgb(225, 225, 225)
#define CLR_UNFOCUSED_DEFAULT rgb(255, 255, 255)

#define CLR_SLIDER_DEFAULT rgb(150, 150, 150)

#define CLR_BUTTON_FOCUSED rgb(150, 150, 150)
#define CLR_BUTTON_UNFOCUSED rgb(125, 125, 125)

//Controls
#include "Controls\UI_Button.h"
#include "Controls\UI_CheckBox.h"
#include "Controls\UI_Label.h"
#include "Controls\UI_GroupBox.h"
#include "Controls\UI_Slider.h"

#include "UI_Mouse.h"

class UI_Window
{
public:
	UI_Window(PCHAR WindowCaption, int x, int y, int w, int h);
	~UI_Window() { }

public:
	void DrawWindow();
	void MoveWindow(int x, int y, int w, int h);

public:
	UI_Button* AddButton(UI_Button* Button);
	UI_GroupBox* AddGroupbox(UI_GroupBox* Groupbox);
	UI_Checkbox* AddCheckbox(UI_Checkbox* CheckBox);
	UI_Label* AddLabel(UI_Label* Label);
	UI_Slider* AddSlider(UI_Slider* Slider);

public:
	CoreString Caption;
	int X, Y, W, H;
	COLOR32 BackgroundColor = CLR_WINDOW_BACKGROUND;
	COLOR32 LineColor = CLR_LINE_DEFAULT;
	COLOR32 TextColor = CLR_TEXT_DEFAULT;
	COLOR32 TitleBackgroundColor = CLR_TITLE_BACKGROUND;
	COLOR32 TitleTextColor = CLR_CAPTION_TEXT;

private:
	std::vector<UI_Button> UIButton;
	std::vector<UI_GroupBox> UIGroupbox;
	std::vector<UI_Checkbox> UICheckbox;
	std::vector<UI_Label> UILabel;
	std::vector<UI_Slider> UISlider;
};

class UI_Setup
{
public:
	UI_Window* RegisterWindow(UI_Window *Window);
	void DrawWindows();

private:
	std::vector<UI_Window> UIWindow;
};