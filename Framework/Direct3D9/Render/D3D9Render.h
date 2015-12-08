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

	//Render lag compensation
	void CompensateRenderLag(float *x, float *y);

	// Font handling
	HRESULT SetFont(LPIDirect3DDevice9 pDevice, PCoreString FontName, float Size);
	void DrawString(bool CenterText, float x, float y, COLOR32 Color, PCoreString szText, ...);
	float GetStringWidth(char *szText, ...);
	float GetStringHeight();

	// 2D drawing funcs
	void Line(float x1, float y1, float x2, float y2, float lw, COLOR32 Color);
	void LineRect(float x, float y, float w, float h, float lw, COLOR32 Color);
	void FillRect(float x, float y, float w, float h, COLOR32 Color);
	void DepthFrame(float x, float y, float w, float h);

private:
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9  pIndexBuffer;
};

COLOR32 rgb(int r, int g, int b, int a);
COLOR32 rgb(int r, int g, int b);