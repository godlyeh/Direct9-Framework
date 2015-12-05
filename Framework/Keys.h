enum eKBCallback : int
{
	K_CALLBACK_MOUSE,
	K_CALLBACK_MOUSEWHEEL,
	K_CALLBACK_KEYBOARD
};

enum eKButton : int
{
	// Mouse
	K_MOUSE1 = VK_LBUTTON, //1
	K_MOUSE2 = VK_RBUTTON, //2
	K_MOUSE3 = VK_MBUTTON, //4
	K_MOUSE4 = VK_XBUTTON1, //5
	K_MOUSE5 = VK_XBUTTON2, //6

	K_MWHEELUP = 0xA, //10
	K_MWHEELDOWN = 0xB, //11

	// Keyboard controls
	K_BACKSPACE = VK_BACK, //8
	K_TAB = VK_TAB, //9
	K_ENTER = VK_RETURN,//13
	K_SPACE = VK_SPACE, //32
	K_ALT = VK_MENU, //18
	K_PAUSE = VK_PAUSE, //19
	K_CAPSLOCK = VK_CAPITAL, //20
	K_ESC = VK_ESCAPE, //27
	K_PAGEUP = VK_PRIOR, //33
	K_PAGEDOWN = VK_NEXT, //34
	K_END = VK_END, //35
	K_HOME = VK_HOME, //36
	K_LEFTARROW = VK_LEFT, //37
	K_UPARROW = VK_UP, //38
	K_RIGHTARROW = VK_RIGHT, //39
	K_DOWNARROW = VK_DOWN, //40
	K_PRINTSCREEN = VK_SNAPSHOT, //44
	K_INSERT = VK_INSERT, //45
	K_DELETE = VK_DELETE, //46
	K_NUMLOCK = VK_NUMLOCK, //144
	K_SCROLLOCK = VK_SCROLL, //145
	K_LSHIFT = VK_LSHIFT, //160
	K_RSHIFT = VK_RSHIFT, //161
	K_LCTRL = VK_LCONTROL, //162
	K_RCTRL = VK_LCONTROL, //163
	//K_COLON = VK_OEM_1, K_PLUS, K_COMMA, K_MINUS, K_PERIOD, K_QUESTIONMARK, //186 - 191

	// Keyboard numerical
	K_0 = 0x30, K_1, K_2, K_3, K_4, K_5, K_6, K_7, K_8, K_9, //48 - 57

	// Keyboard keys
	K_A = 0x41, K_B, K_C, K_D, K_E, K_F, K_G, K_H, K_I, K_J, K_K, K_L, K_M, K_N, K_O, K_P, K_Q, K_R, K_S, K_T, K_U, K_V, K_W, K_X, K_Y, K_Z, //65 - 90

	K_NUMPAD0 = VK_NUMPAD0, K_NUMPAD1, K_NUMPAD2, K_NUMPAD3, K_NUMPAD4, K_NUMPAD5, K_NUMPAD6, K_NUMPAD7, K_NUMPAD8, K_NUMPAD9, //96 - 105

	K_NUMPADMULTIPLY = VK_MULTIPLY, K_NUMPADADDITION, K_NUMPADSEPERATOR, K_NUMPADSUBTRACT, K_NUMPADDECIMAL, K_NUMPADDIVIDE, //106 - 111

	K_F1 = VK_F1, K_F2, K_F3, K_F4, K_F5, K_F6, K_F7, K_F8, K_F9, K_10, K_11, K_12, K_13, K_14, K_15, K_16, K_17, K_18, K_19, K_20, K_21, K_22, K_23, K_24 //112 - 135
};

static char KButtonName[][255] =
{
	"UNKN", /*0*/
	"MOUSE1", /*1*/
	"MOUSE2", /*2*/
	"UNKN", /*3*/
	"MOUSE3", /*4*/
	"MOUSE4", /*5*/
	"MOUSE5", /*6*/
	"UNKN", /*7*/
	"BACKSPACE", //8
	"TAB", /*9*/
	"MWHEELUP", /*10*/
	"MWHEELDOWN", /*11*/
	"UNKN", /*12*/
	"ENTER", /*13*/
	"UNKN", /*14*/
	"UNKN", /*15*/
	"SHIFT", /*16*/
	"CTRL", /*17*/
	"ALT", /*18*/
	"PAUSE", /*19*/
	"CAPSLOCK", /*20*/
	"UNKN", /*21*/
	"UNKN", /*22*/
	"UNKN", /*23*/
	"UNKN", /*24*/
	"UNKN", /*25*/
	"UNKN", /*26*/
	"ESCAPE", /*27*/
	"UNKN", /*28*/
	"UNKN", /*29*/
	"UNKN", /*30*/
	"UNKN", /*31*/
	"SPACE", /*32*/
	"PAGEUP", /*33*/
	"PAGEDOWN", /*34*/
	"END", /*35*/
	"HOME", /*36*/
	"LEFTARROW", /*37*/
	"UPARROW", /*38*/
	"RIGHTARROW", /*39*/
	"DOWNARROW", /*40*/
	"UNKN", /*41*/
	"UNKN", /*42*/
	"UNKN", /*43*/
	"PRINTSCREEN", /*44*/
	"INSERT", /*45*/
	"DELETE", /*46*/
	"UNKN", /*47*/
	"0", /*48*/
	"1", /*49*/
	"2", /*50*/
	"3", /*51*/
	"4", /*52*/
	"5", /*53*/
	"6", /*54*/
	"7", /*55*/
	"8", /*56*/
	"9", /*57*/
	"UNKN", /*58*/
	"UNKN", /*59*/
	"UNKN", /*60*/
	"UNKN", /*61*/
	"UNKN", /*62*/
	"UNKN", /*63*/
	"UNKN", /*64*/
	"A", /*65*/
	"B", /*66*/
	"C", /*67*/
	"D", /*68*/
	"E", /*69*/
	"F", /*70*/
	"G", /*71*/
	"H", /*72*/
	"I", /*73*/
	"J", /*74*/
	"K", /*75*/
	"L", /*76*/
	"M", /*77*/
	"N", /*78*/
	"O", /*79*/
	"P", /*80*/
	"Q", /*81*/
	"R", /*82*/
	"S", /*83*/
	"T", /*84*/
	"U", /*85*/
	"V", /*86*/
	"W", /*87*/
	"X", /*88*/
	"Y", /*89*/
	"Z", /*90*/
	"UNKN", /*91*/
	"UNKN", /*92*/
	"UNKN", /*93*/
	"UNKN", /*94*/
	"UNKN", /*95*/
	"NUMPAD0", /*96*/
	"NUMPAD1", /*97*/
	"NUMPAD2", /*98*/
	"NUMPAD3", /*99*/
	"NUMPAD4", /*100*/
	"NUMPAD5", /*101*/
	"NUMPAD6", /*102*/
	"NUMPAD7", /*103*/
	"NUMPAD8", /*104*/
	"NUMPAD9", /*105*/
	"NUMPAD*", /*106*/
	"NUMPADADD", /*107*/
	"NUMPADSEPERATOR", /*108*/
	"NUMPADSUBTRACT", /*109*/
	",", /*110*/
	"/", /*111*/
	"F1", /*112*/
	"F2", /*113*/
	"F3", /*114*/
	"F4", /*115*/
	"F5", /*116*/
	"F6", /*117*/
	"F7", /*118*/
	"F8", /*119*/
	"F9", /*120*/
	"F10", /*121*/
	"F11", /*122*/
	"F12", /*123*/
	"F13", /*124*/
	"F14", /*125*/
	"F15", /*126*/
	"F16", /*127*/
	"F17", /*128*/
	"F18", /*129*/
	"F19", /*130*/
	"F20", /*131*/
	"F21", /*132*/
	"F22", /*133*/
	"F23", /*134*/
	"F24", /*135*/
	"UNKN", /*136*/
	"UNKN", /*137*/
	"UNKN", /*138*/
	"UNKN", /*139*/
	"UNKN", /*140*/
	"UNKN", /*141*/
	"UNKN", /*142*/
	"UNKN", /*143*/
	"NUMLOCK", /*144*/
	"SCROLLOCK", /*145*/
	"UNKN", /*146*/
	"UNKN", /*147*/
	"UNKN", /*148*/
	"UNKN", /*149*/
	"UNKN", /*150*/
	"UNKN", /*151*/
	"UNKN", /*152*/
	"UNKN", /*153*/
	"UNKN", /*154*/
	"UNKN", /*155*/
	"UNKN", /*156*/
	"UNKN", /*157*/
	"UNKN", /*158*/
	"UNKN", /*159*/
	"LEFTSHIFT", /*160*/
	"RIGHTSHIFT", /*161*/
	"LEFTCTRL", /*162*/
	"RIGHTCTRL", /*163*/
	"UNKN", /*164*/
	"UNKN", /*165*/
	"UNKN", /*166*/
	"UNKN", /*167*/
	"UNKN", /*168*/
	"UNKN", /*169*/
	"UNKN", /*170*/
	"UNKN", /*171*/
	"UNKN", /*172*/
	"UNKN", /*173*/
	"UNKN", /*174*/
	"UNKN", /*175*/
	"UNKN", /*176*/
	"UNKN", /*177*/
	"UNKN", /*178*/
	"UNKN", /*179*/
	"UNKN", /*180*/
	"UNKN", /*181*/
	"UNKN", /*182*/
	"UNKN", /*183*/
	"UNKN", /*184*/
	"UNKN", /*185*/
	":", /*186*/
	"+", /*187*/
	",", /*188*/
	"-", /*189*/
	".", /*190*/
	"?", /*191*/
	"UNKN", /*192*/
	"UNKN", /*193*/
	"UNKN", /*194*/
	"UNKN", /*195*/
	"UNKN", /*196*/
	"UNKN", /*197*/
	"UNKN", /*198*/
	"UNKN", /*199*/
	"UNKN", /*200*/
	"UNKN", /*201*/
	"UNKN", /*202*/
	"UNKN", /*203*/
	"UNKN", /*204*/
	"UNKN", /*205*/
	"UNKN", /*206*/
	"UNKN", /*207*/
	"UNKN", /*208*/
	"UNKN", /*209*/
	"UNKN", /*210*/
	"UNKN", /*211*/
	"UNKN", /*212*/
	"UNKN", /*213*/
	"UNKN", /*214*/
	"UNKN", /*215*/
	"UNKN", /*216*/
	"UNKN", /*217*/
	"UNKN", /*218*/
	"UNKN", /*219*/
	"UNKN", /*220*/
	"UNKN", /*221*/
	"UNKN", /*222*/
	"UNKN", /*223*/
	"UNKN", /*224*/
	"UNKN", /*225*/
	"UNKN", /*226*/
	"UNKN", /*227*/
	"UNKN", /*228*/
	"UNKN", /*229*/
	"UNKN", /*230*/
	"UNKN", /*231*/
	"UNKN", /*232*/
	"UNKN", /*233*/
	"UNKN", /*234*/
	"UNKN", /*235*/
	"UNKN", /*236*/
	"UNKN", /*237*/
	"UNKN", /*238*/
	"UNKN", /*239*/
	"UNKN", /*240*/
	"UNKN", /*241*/
	"UNKN", /*242*/
	"UNKN", /*243*/
	"UNKN", /*244*/
	"UNKN", /*245*/
	"UNKN", /*246*/
	"UNKN", /*247*/
	"UNKN", /*248*/
	"UNKN", /*249*/
	"UNKN", /*250*/
	"UNKN", /*251*/
	"UNKN", /*252*/
	"UNKN", /*253*/
	"UNKN", /*254*/
};