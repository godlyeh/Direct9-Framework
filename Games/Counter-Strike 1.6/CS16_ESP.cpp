/*

File: CS16_ESP

Extra sensory perception

*/
#include "CS16_Main.h"

bool CS16ESP::ValidEntity(int Index)
{
	cs16_cl_entity_t* pLocal = CS16Engine->GetLocalPlayer();
	cs16_cl_entity_t* pEnt = CS16Engine->GetEntityByIndex(Index);
	return (pEnt && pLocal && pEnt->curstate.messagenum >= pLocal->curstate.messagenum);
}

bool CS16ESP::ValidPlayer(int Index)
{
	cs16_cl_entity_t* pLocal = CS16Engine->GetLocalPlayer();
	cs16_cl_entity_t* pEnt = CS16Engine->GetEntityByIndex(Index);
	return ((Index < CS16_MAX_CLIENTS) && ValidEntity(Index) && pEnt->player && (pLocal->index != pEnt->index) && !(pLocal->curstate.iuser1 == 4 && pLocal->curstate.iuser2 == Index));
}

void CS16ESP::DrawESP(bool Visible)
{
	if (Visible)
	{
		for (int i = 0; i < CS16Engine->MaxEntity; ++i)
		{
			cs16_cl_entity_t* pEnt = CS16Engine->GetEntityByIndex(i);

			if (ValidPlayer(i))
			{
				Vec3 ScreenCoords;
				cs16_player_info_t* PlayerInfo = CS16Engine->GetPlayerInfoByIndex(i);
				CS16Engine->Line3DBox(pEnt->origin, pEnt->curstate.mins, pEnt->curstate.maxs, Vec3(0.0f, pEnt->angles[1], 0.0f), 3, rgb(255, 0, 0, 255));
				continue;
				if (!CS16Engine->WorldToScreen(pEnt->origin, ScreenCoords))
					continue;

				float X = ScreenCoords.x;
				float Y = ScreenCoords.y;
				CLog::Log("%.2f %.2f", X, Y);
				g_Core->Render->DrawString(true, X, Y, rgb(255, 0, 0), PlayerInfo->name);
			}
		}
	}
}