/*

	UI_Label

	used for creating simple labels

*/

class UI_Label
{
public:
	UI_Label(PCHAR Label, float x, float y, LPCoreString pString = NULL, COLOR32 = CLR_TEXT_DEFAULT);
	~UI_Label() { }

public:
	void Draw(float x, float y, bool Visible = true);

public:
	float X, Y;
	CoreString Text;
	LPCoreString String;
	COLOR32 TextColor = CLR_TEXT_DEFAULT;
};