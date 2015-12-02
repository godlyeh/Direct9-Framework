/*

	File: UI_CheckBox

	Checkbox handler

*/

class UI_Checkbox
{
public:
	UI_Checkbox(LPCoreValue Var, PCHAR ControlText, int x, int y, COLOR32 Color = CLR_TEXT_DEFAULT);
	~UI_Checkbox();

public:
	void Draw(int x, int y, bool Visible = true);

public:
	// Info
	CoreString Text;
	LPCoreValue Value;
	
	// Position
	int Size = 0;
	int X, Y;

	// Color
	COLOR32 UnfocusedColor = CLR_UNFOCUSED_DEFAULT;
	COLOR32 FocusedColor = CLR_FOCUSED_DEFAULT;
	COLOR32 CheckedColor = CLR_CHECKBOX_CHECKED;
	COLOR32 TextColor = CLR_TEXT_DEFAULT;
	COLOR32 LineColor = CLR_LINE_DEFAULT;
};