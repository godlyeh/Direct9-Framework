/*

File: UI_Slider

Used for slider handling both vertically and horizontally

*/

class UI_Slider
{
public:
	UI_Slider(float x, float y, float size, double min, double max, LPCoreValue SliderValue, COLOR32 Color = CLR_SLIDER_DEFAULT, bool DrawVertically = false);
	~UI_Slider() { }

public:
	void DrawSliderPin(float x, float y, float size);
	void Draw(float x, float y, bool Visible = true);

public:
	bool Vertical;
	float X, Y;
	float Size;
	double Min;
	double Max;
	LPCoreValue Value;
	COLOR32 SliderColor = CLR_SLIDER_DEFAULT;
};