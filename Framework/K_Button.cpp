/*

	File: K_Button

	Used for key handling

*/
#include "Core.h"

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case WM_MOUSEWHEEL:
		MSLLHOOKSTRUCT* MouseData = (MSLLHOOKSTRUCT*)lParam;

		if (GET_WHEEL_DELTA_WPARAM(MouseData->mouseData) == WHEEL_DELTA)
		{
			KeyPressed->Keys[eKButton::K_MWHEELUP] = 1;
			MouseInfo->ScrolledUp = true;
		}
		else
		{
			KeyPressed->Keys[eKButton::K_MWHEELDOWN] = 1;
			MouseInfo->ScrolledDown = true;
		}

		if (KeyPressed->Function)
			((pfnEventHook)KeyPressed->Function)(eKBCallback::K_CALLBACK_MOUSEWHEEL);

		KeyPressed->Keys[eKButton::K_MWHEELUP] = KeyPressed->Keys[eKButton::K_MWHEELUP] = 0;

		break;
	}

	return 0;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT* KeyboardInfo = (KBDLLHOOKSTRUCT*)lParam;
		int vKey = KeyboardInfo->vkCode;

		if (!(KeyboardInfo->flags &LLKHF_UP))
			KeyPressed->Keys[vKey] = 1;
		else
			KeyPressed->Keys[vKey] = 0;

		if (KeyPressed->Function)
			((pfnEventHook)KeyPressed->Function)(eKBCallback::K_CALLBACK_KEYBOARD);
	}

	return 0;
}

void K_Button::HookKeyEvents(pfnEventHook KeyEventsFunction)
{
	Function = KeyEventsFunction;
}

bool K_Button::KeyPress(eKButton Button)
{
	if (Button == eKButton::K_MWHEELUP || Button == eKButton::K_MWHEELDOWN)
	{
		if (Button == eKButton::K_MWHEELUP && Keys[eKButton::K_MWHEELUP]) return true;
		if (Button == eKButton::K_MWHEELDOWN && Keys[eKButton::K_MWHEELDOWN]) return true;

		return false;
	}

	return Keys[Button] == 1;
}

K_Button::K_Button(HINSTANCE hInst)
{
	//MouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInst, 0);
	KeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInst, 0);
}

K_Button::~K_Button()
{
	UnhookWindowsHookEx(MouseHook);
	UnhookWindowsHookEx(KeyboardHook);
}