/*

	File: UI_Mouse

	Used for mouse handling

*/
#include "..\..\..\Core.h"

void UI_Mouse::UpdateInfo()
{
	// Get mouse pos
	tagPOINT Pos;
	GetCursorPos(&Pos);

	// Get window info
	WINDOWINFO Info;
	Info.cbSize = sizeof(WINDOWINFO);
	if (GetWindowInfo(g_Core->Process->HWnd, &Info) == FALSE)
		return;

	X = Pos.x - Info.rcClient.left;
	Y = Pos.y - Info.rcClient.top;
	Up = false;
	Down = GetAsyncKeyState(MK_LBUTTON) != 0;

	// Register clicks
	static bool bHeld = false;
	static bool bReleased = false;
	if (Down && !bHeld)
	{
		bHeld = true;
		bReleased = false;
	}
	if (!Down && bHeld)
	{
		bHeld = false;
		bReleased = true;
	}
	if (bReleased)
	{
		Up = true;
		bReleased = false;
	}

	// Set mouse click, same as up
	Clicked = Up;

	if (X < 0) X = 0;
	if (Y < 0) Y = 0;
	if (Pos.x > Info.rcClient.right) X = Info.rcClient.right - Info.rcClient.left;
	if (Pos.y > Info.rcClient.bottom) Y = Info.rcClient.bottom - Info.rcClient.top;
}

bool UI_Mouse::MouseOver(int x, int y, int w, int h)
{
	if (X < x || Y < y) return false;
	if (X > x + w || Y > y + h) return false;

	return true;
}