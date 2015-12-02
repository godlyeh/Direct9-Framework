/*

	UI_Label

	used for creating simple labels

*/

class UI_Label
{
public:
	UI_Label(PCHAR Label, int x, int y, LPCoreString pString = NULL, COLOR32 = CLR_TEXT_DEFAULT);
	~UI_Label() { }

public:
	void Draw(int x, int y, bool Visible = true);

public:
	int X, Y;
	CoreString Text;
	LPCoreString String;
	COLOR32 TextColor = CLR_TEXT_DEFAULT;
};