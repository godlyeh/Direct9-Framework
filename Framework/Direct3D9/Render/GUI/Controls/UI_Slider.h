/*

File: UI_Slider

Used for slider handling both vertically and horizontally

*/

#define UI_SLIDER_VALUE_TEXT "#DisplaySliderValue"

class UI_Slider
{
public:
	UI_Slider(float x, float y, float size, double min, double max, PCoreVariable SliderValue, PCoreString Text = NULL, bool DrawVertically = false, COLOR32 Color = CLR_TEXT_DEFAULT);
	~UI_Slider() { }

public:
	void DrawSliderPin(float x, float y, float size);
	void Draw(float x, float y, bool Visible = true);

public:
	PCoreString SliderText = NULL;
	bool Vertical;
	float X, Y;
	float Size;
	double Min, Max;
	PCoreVariable Value;
	COLOR32 SliderColor = CLR_SLIDER_DEFAULT;
	COLOR32 TextColor = CLR_TEXT_DEFAULT;
};