/*

File: UI_ComboBox

Combobox

*/

class CoreComboboxItem
{
public:
	CoreComboboxItem(PCoreString ItemText, int ItemIndex)
	{
		strcpy_s(Text, ItemText);
		Index = ItemIndex;
	}

public:
	CoreString Text;
	int Index;
};

class UI_ComboBox
{
public:
	UI_ComboBox(PCHAR Name, float x, float y, float w, std::vector<CoreComboboxItem>* ItemArray = NULL, COLOR32 Color = CLR_TEXT_DEFAULT, int DisplayMaxItems = 10);
	~UI_ComboBox() { }

public:
	int GetIndex();
	void Draw(float x, float y, bool Visible = true);
	void SetSelectedItem(CoreComboboxItem *Item);
	void AddVectorArray(std::vector<CoreComboboxItem>* ItemArray);
	CoreComboboxItem* AddItem(PCoreString Text);

public:
	CoreComboboxItem *SelectedItem = NULL;
	std::vector<CoreComboboxItem> Items;
	CoreString Text;
	int MaxItems;
	int Index;
	float X, Y, W;
	COLOR32 TextColor = CLR_TEXT_DEFAULT;
	COLOR32 BackgroundColor = CLR_UNFOCUSED_DEFAULT;
	COLOR32 BackgroundButtonColor = CLR_UNFOCUSED_DEFAULT;
	COLOR32 LineColor = CLR_LINE_DEFAULT;
	COLOR32 ItemUnfocusedBackground = CLR_UNFOCUSED_DEFAULT;
	COLOR32 ItemFocusedBackground = CLR_FOCUSED_DEFAULT;

private:
	double ScrollbarValue;
	UI_Scrollbar *Scrollbar = NULL;
};