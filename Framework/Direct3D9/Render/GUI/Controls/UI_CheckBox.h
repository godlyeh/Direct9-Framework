/*

	File: UI_CheckBox

	Checkbox handler

*/

class UI_Checkbox
{
public:
	UI_Checkbox(LPVOID Var, PCoreString ControlText, float x, float y, COLOR32 Color = CLR_TEXT_DEFAULT);
	~UI_Checkbox();

public:
	void Draw(float x, float y, bool Visible = true);

public:
	// Info
	CoreString Text;
	LPVOID Value;
	
	// Position
	float Size = 0;
	float X, Y;

	// Color
	COLOR32 UnfocusedColor = CLR_UNFOCUSED_DEFAULT;
	COLOR32 FocusedColor = CLR_FOCUSED_DEFAULT;
	COLOR32 CheckedColor = CLR_CHECKBOX_CHECKED;
	COLOR32 TextColor = CLR_TEXT_DEFAULT;
	COLOR32 LineColor = CLR_LINE_DEFAULT;
};