/*

	UI_Settings

	Used for saving controls

*/
#include "..\..\Core.h"

void CSettings::Register(UI_Window *Window)
{
#define WindowName(name) Utilities::GetStringWithArgs("%s %s", Window->Caption, name)
#define RegisterWindowColor(name, variable) Register(WindowName(name), &variable, eCoreVariableType::VAR_INTEGER, 0, 255)
#define RegisterWindowPos(name, variable) Register(WindowName(name), &variable, eCoreVariableType::VAR_FLOAT)

	
	Register(Window->Caption, &Window->Caption, eCoreVariableType::VAR_STRING);
	RegisterWindowPos("X", Window->X);
	RegisterWindowPos("Y", Window->Y);
	RegisterWindowPos("Width", Window->W);
	RegisterWindowPos("Height", Window->H);
	RegisterWindowColor("Text Red", Window->TextColor.r);
	RegisterWindowColor("Text Green", Window->TextColor.g);
	RegisterWindowColor("Text Blue", Window->TextColor.b);
	RegisterWindowColor("Text Alpha", Window->TextColor.a);
	RegisterWindowColor("Titlebar Text Red", Window->TitleTextColor.r);
	RegisterWindowColor("Titlebar Text Green", Window->TitleTextColor.g);
	RegisterWindowColor("Titlebar Text Blue", Window->TitleTextColor.b);
	RegisterWindowColor("Titlebar Text Alpha", Window->TitleTextColor.a);
	RegisterWindowColor("Titlebar Background Red", Window->TitleBackgroundColor.r);
	RegisterWindowColor("Titlebar Background Green", Window->TitleBackgroundColor.g);
	RegisterWindowColor("Titlebar Background Blue", Window->TitleBackgroundColor.b);
	RegisterWindowColor("Titlebar Background Alpha", Window->TitleBackgroundColor.a);
	RegisterWindowColor("Background Background Red", Window->BackgroundColor.r);
	RegisterWindowColor("Background Background Green", Window->BackgroundColor.g);
	RegisterWindowColor("Background Background Blue", Window->BackgroundColor.b);
	RegisterWindowColor("Background Background Alpha", Window->BackgroundColor.a);
	RegisterWindowColor("Line Background Red", Window->LineColor.r);
	RegisterWindowColor("Line Background Green", Window->LineColor.g);
	RegisterWindowColor("Line Background Blue", Window->LineColor.b);
	RegisterWindowColor("Line Background Alpha", Window->LineColor.a);
}