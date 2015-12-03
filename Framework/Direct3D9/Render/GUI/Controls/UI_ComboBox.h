/*

File: UI_ComboBox

Combobox

*/

class CoreComboboxItem
{
public:
	CoreComboboxItem(PCoreString ItemText, int ItemIndex, bool Fix = false)
	{
		strcpy_s(Text, ItemText);
		CrappyFix = Fix;
		Index = ItemIndex;
	}

public:
	CoreString Text;
	int Index;
	bool CrappyFix = false;
};

class UI_ComboBox
{
public:
	UI_ComboBox(float x, float y, float w, std::vector<CoreComboboxItem>* ItemArray = NULL, COLOR32 Color = CLR_TEXT_DEFAULT, int DisplayMaxItems = 10);
	~UI_ComboBox() { }

public:
	void Draw(float x, float y, bool Visible = true);
	void AddVectorArray(std::vector<CoreComboboxItem>* ItemArray);
	void AddItem(PCoreString Text);

public:
	CoreComboboxItem *SelectedItem = new CoreComboboxItem("", 0, true);
	std::vector<CoreComboboxItem> Items;
	int MaxItems;
	float X, Y, W;
	COLOR32 TextColor = CLR_TEXT_DEFAULT;
	COLOR32 BackgroundColor = CLR_UNFOCUSED_DEFAULT;
	COLOR32 BackgroundButtonColor = CLR_UNFOCUSED_DEFAULT;
	COLOR32 LineColor = CLR_LINE_DEFAULT;
	COLOR32 ItemUnfocusedBackground = CLR_UNFOCUSED_DEFAULT;
	COLOR32 ItemFocusedBackground = CLR_FOCUSED_DEFAULT;
};