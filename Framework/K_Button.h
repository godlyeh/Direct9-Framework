/*

File: K_Button

Used for key handling

*/

typedef void(__cdecl* pfnEventHook)(eKBCallback Callback);

class K_Button
{
public:
	K_Button(HINSTANCE hInst);
	~K_Button();

public:
	void HookKeyEvents(pfnEventHook KeyEventsFunction);
	bool KeyPress(eKButton Button);

public:
	pfnEventHook Function = NULL;
	BYTE Keys[255];

public:
	HHOOK MouseHook;
	HHOOK KeyboardHook;
};