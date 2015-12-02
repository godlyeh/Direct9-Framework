/*

File: UI_Slider

Used for slider handling both vertically and horizontally

*/

class UI_Slider
{
public:
	UI_Slider(int x, int y, int size, double min, double max, LPCoreValue SliderValue, COLOR32 Color = CLR_SLIDER_DEFAULT, bool DrawVertically = false);
	~UI_Slider() { }

public:
	void DrawSliderPin(int x, int y, int size);
	void Draw(int x, int y, bool Visible = true);

public:
	bool Vertical;
	int X, Y;
	int Size;
	double Min;
	double Max;
	LPCoreValue Value;
	COLOR32 SliderColor = CLR_SLIDER_DEFAULT;
};