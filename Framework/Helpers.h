/*

	File: Helpers

	Used for definitions, enumerators etc...

*/

// x64 or x86 setup
#ifdef _WIN64
typedef DWORD64 FDWORD;
#define FrameworkCPU "x64"
#else
#define FrameworkCPU "x86"
typedef DWORD FDWORD;
#endif

// Custom FVF for d3d
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

struct CustomVertex
{
	FLOAT x, y, z, rhw;
	DWORD color;
};

// Close app with error
#define CLOSE_ERROR() { system("pause"); \
						return 0; }

// Setup va list and get arguments
#define GET_VA_ARGS(Text, Buffer) { ZeroMemory(&Buffer, sizeof(Buffer)); \
								  va_list valist; \
								  va_start(valist, Text); \
								  _vsnprintf_s(Buffer, sizeof(Buffer), Text, valist); \
								  va_end(valist); }

// Screen info
typedef struct
{
	bool Minimized;
	bool Fullscreen;
	bool WindowedFullscreen;
	int X, Y;
	int Width, Height;
}SCREENINFO;
typedef SCREENINFO* LPSCREENINFO;

// Typedef helpers
typedef FDWORD CoreOffset;
typedef char CoreString[256];
typedef PCHAR PCoreString;
typedef double CoreValue;
typedef CoreValue CoreBool;
typedef CoreValue CoreInt;
typedef CoreValue CoreFloat;
typedef CoreValue* PCoreVariable;
typedef LPVOID PCoreFunction;
typedef double* PDOUBLE;
typedef struct { int r, g, b, a; }COLOR32;

// D3D typedefs
typedef IDirect3D9* LPIDirect3D9;
typedef IDirect3DDevice9* LPIDirect3DDevice9;
typedef ID3DXLine* LPID3DXLine;
typedef ID3DXFont* LPID3DXFont;