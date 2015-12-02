/*
	
	File: UI_Button

	used for button handling

*/

class UI_Button
{
public:
	UI_Button(PCHAR ButtonText, float x, float y, LPCoreFunction ButtonFunction, COLOR32 Color = CLR_TEXT_DEFAULT);
	~UI_Button() { }

public:
	void Draw(float x, float y, bool Visible = true);

public:
	CoreString Text;
	float X, Y;
	LPCoreFunction Function;
	COLOR32 UnfocusedColor = CLR_BUTTON_UNFOCUSED;
	COLOR32 FocusedColor = CLR_BUTTON_FOCUSED;
	COLOR32 LineColor = CLR_LINE_DEFAULT;
	COLOR32 TextColor = CLR_TEXT_DEFAULT;
};