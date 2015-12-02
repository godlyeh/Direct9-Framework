/*
	
	File: UI_Button

	used for button handling

*/

class UI_Button
{
public:
	UI_Button(PCHAR ButtonText, int x, int y, LPCoreFunction ButtonFunction, COLOR32 Color = CLR_TEXT_DEFAULT);
	~UI_Button() { }

public:
	void Draw(int x, int y, bool Visible = true);

public:
	CoreString Text;
	int X, Y;
	LPCoreFunction Function;
	COLOR32 UnfocusedColor = CLR_BUTTON_UNFOCUSED;
	COLOR32 FocusedColor = CLR_BUTTON_FOCUSED;
	COLOR32 LineColor = CLR_LINE_DEFAULT;
	COLOR32 TextColor = CLR_TEXT_DEFAULT;
};