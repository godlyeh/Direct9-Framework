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
#define CLR_LINE_DEFAULT rgb(90, 90, 90)

#define CLR_CLOSE_BUTTON rgb(200, 0, 0)
#define CLR_CLOSE_BUTTON_FOCUSED rgb(225, 0, 0)
#define CLR_CLOSE_BUTTON_UNFOCUSED rgb(200, 0, 0)
#define CLR_BUTTON_FOCUSED rgb(150, 150, 150)
#define CLR_BUTTON_UNFOCUSED rgb(125, 125, 125)

#define CLR_TEXT_DEFAULT rgb(255, 255, 255)
#define CLR_CAPTION_TEXT CLR_TEXT_DEFAULT

#define CLR_CHECKBOX_CHECKED rgb(30, 30, 30)

#define CLR_FOCUSED_DEFAULT rgb(255, 255, 255)
#define CLR_UNFOCUSED_DEFAULT rgb(210, 210, 210)

#define CLR_SLIDER_DEFAULT rgb(150, 150, 150)

//Controls
#include "Controls\UI_Scrollbar.h"
#include "Controls\UI_Button.h"
#include "Controls\UI_CheckBox.h"
#include "Controls\UI_ComboBox.h"
#include "Controls\UI_Label.h"
#include "Controls\UI_GroupBox.h"
#include "Controls\UI_Slider.h"

#include "UI_Mouse.h"

class UI_Window
{
public:
	UI_Window(PCoreString WindowCaption, float x, float y, float w, float h, bool *Visible, bool* MainWindowHandle = NULL, bool HasCaption = true);
	~UI_Window() { }

public:
	void DrawWindow();
	void MoveWindow(float x, float y, float w, float h);

public:
	UI_Button* AddButton(UI_Button* Button);
	UI_GroupBox* AddGroupbox(UI_GroupBox* Groupbox);
	UI_Checkbox* AddCheckbox(UI_Checkbox* CheckBox);
	UI_ComboBox* AddCombobox(UI_ComboBox* ComboBox);
	UI_Label* AddLabel(UI_Label* Label);
	UI_Scrollbar* AddScrollbar(UI_Scrollbar* Scrollbar);
	UI_Slider* AddSlider(UI_Slider* Slider);

public:
	UI_ComboBox* GetCombobox(PCoreString Text);
	UI_ComboBox* GetCombobox(UI_ComboBox* ComboBox);
	UI_ComboBox* GetCombobox(int Index);
	UI_ComboBox* GetCombobox();

public:
	bool WindowHasCaption;
	CoreString Caption;
	float X, Y, W, H;
	COLOR32 BackgroundColor = CLR_WINDOW_BACKGROUND;
	COLOR32 LineColor = CLR_LINE_DEFAULT;
	COLOR32 TextColor = CLR_TEXT_DEFAULT;
	COLOR32 TitleBackgroundColor = CLR_TITLE_BACKGROUND;
	COLOR32 TitleTextColor = CLR_CAPTION_TEXT;

public:
	bool *DrawWindows = NULL;
	bool *MainWindow = NULL;
	std::vector<UI_Button> UIButton;
	std::vector<UI_GroupBox> UIGroupbox;
	std::vector<UI_Checkbox> UICheckbox;
	std::vector<UI_ComboBox> UIComboBox;
	std::vector<UI_Label> UILabel;
	std::vector<UI_Scrollbar> UIScrollbar;
	std::vector<UI_Slider> UISlider;
};

class UI_Setup
{
public:
	UI_Window *RegisterWindow(UI_Window *Window);
	void DrawWindows();

private:
	std::vector<UI_Window> UIWindow;
};