/*

	File: D3D9Render

	Used for 2D drawing

*/
class CRender
{
public:
	// Direct X handlers
	LPID3DXLine pD3DLine = NULL;
	LPID3DXFont pD3DFont = NULL;

	// Render func
	BOOL Init(LPIDirect3DDevice9 pDevice);
	void Release();

	// Font handling
	HRESULT SetFont(LPIDirect3DDevice9 pDevice, PCHAR FontName, int Size);
	void DrawString(bool CenterText, int x, int y, COLOR32 Color, PCHAR szText, ...);
	int GetStringWidth(char *szText, ...);
	int GetStringHeight();

	// 2D drawing funcs
	void Line(int x1, int y1, int x2, int y2, int lw, COLOR32 Color);
	void LineRect(int x, int y, int w, int h, int lw, COLOR32 Color);
	void FillRect(int x, int y, int w, int h, COLOR32 Color);
	void DepthFrame(int x, int y, int w, int h);
};

COLOR32 rgb(int r, int g, int b, int a);
COLOR32 rgb(int r, int g, int b);