/*

	File: UI_Scrollbar

	Universal scrolbar handling

*/

class UI_Scrollbar
{
public:
	UI_Scrollbar(float x, float y, float w, float h, float min, float max, PCoreVariable ScrollbarValue = NULL, bool IsVertical = true, COLOR32 Color = CLR_SLIDER_DEFAULT);
	~UI_Scrollbar() { }

public:
	void DrawSlider(float x, float y, float w, float h);
	void Draw(float x, float y, bool Visible = true);

public:
	bool Vertical;
	float X, Y, W, H;
	double Min, Max;
	PCoreVariable Value;
	COLOR32 ScrollbarBackground = CLR_FOCUSED_DEFAULT;
	COLOR32 SliderColor = CLR_SLIDER_DEFAULT;
	COLOR32 LineColor = CLR_LINE_DEFAULT;
};