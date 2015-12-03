/*

	File: UI_Mouse

	used for mouse handling

*/

typedef struct
{
	int X, Y;
	bool Up;
	bool Down;
	bool Clicked;
	PCoreFunction DraggedElement;
	PCoreFunction FocusedItem;
}CoreMouseInfo;

class UI_Mouse : public CoreMouseInfo
{
public:
	void UpdateInfo();
	bool MouseOver(int x, int y, int w, int h);
	bool MouseOver(float x, float y, float w, float h);
};