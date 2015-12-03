/*

	File: UI_GroupBox

	Used for groupbox, todo: bind objects to it

*/

class UI_GroupBox
{
public:
	UI_GroupBox(PCoreString Caption, float x, float y, float w, float h, COLOR32 Color = CLR_TEXT_DEFAULT);
	~UI_GroupBox() { }

public:
	void Draw(float x, float y, bool Visible = true);

public:
	CoreString Text;
	float X, Y, W, H;
	COLOR32 TextColor = CLR_TEXT_DEFAULT;
	COLOR32 LineColor = CLR_LINE_DEFAULT;
};