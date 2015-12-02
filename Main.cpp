#include "Main.h"

CS16Main *g_CS16Core = NULL;

void RenderScene2()
{
	// Draw frames per second
	if (g_Core->FramesPerSecond > 0)
		g_Core->Render->DrawString(false, 25, 25, rgb(255, 0, 0, 255), "FPS: %i", g_Core->FramesPerSecond);
}

int main()
{
	// Counter-Strike 1.6
	g_CS16Core = new CS16Main();

	// ARK

	g_Core->~CFrameworkCore();
	system("pause");

	return 0;
}