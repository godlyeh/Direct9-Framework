/*

	File: UI_GroupBox

	Used for groupbox, todo: bind objects to it

*/

class UI_GroupBox
{
public:
	UI_GroupBox(PCHAR Caption, int x, int y, int w, int h, COLOR32 Color = CLR_TEXT_DEFAULT);
	~UI_GroupBox() { }

public:
	void Draw(int x, int y, bool Visible = true);

public:
	CoreString Text;
	int X, Y, W, H;
	COLOR32 TextColor = CLR_TEXT_DEFAULT;
	COLOR32 LineColor = CLR_LINE_DEFAULT;
};