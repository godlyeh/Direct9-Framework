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
	return ((Index < CS16_MAX_CLIENTS) && ValidEntity(Index) && pEnt->player && pEnt->curstate.solid == CS16_ALIVE && (pLocal->index != pEnt->index) && !(pLocal->curstate.iuser1 == 4 && pLocal->curstate.iuser2 == Index));
}

void CS16ESP::DrawESP(bool Visible)
{
	if (Visible)
	{
		for (int i = 0; i < CS16Engine->MaxEntity; ++i)
		{
			Vec3 ScreenCoords;
			cs16_cl_entity_t* pEnt = CS16Engine->GetEntityByIndex(i);

			if (ValidPlayer(i))
			{
				cs16_player_info_t* PlayerInfo = CS16Engine->GetPlayerInfoByIndex(i);

				if (!CS16Engine->WorldToScreen(pEnt->origin + Vec3(0.0f, 0.0f, pEnt->curstate.maxs.z), ScreenCoords))
					continue;

				float X = ScreenCoords.x;
				float Y = ScreenCoords.y - 5;
#define _Y Y -= (g_Core->TextSize + 2)

				CS16Engine->Line3DBox(pEnt->origin, pEnt->curstate.mins, pEnt->curstate.maxs, Vec3(0.0f, pEnt->angles[1], 0.0f), 3, rgb(255, 0, 0, 255));

				if (CS16DVar->WeaponESP)
				{
					cs16_model_t* Model = CS16Engine->GetModelByIndex(pEnt->curstate.weaponmodel);
					if (Model && strstr(Model->name, ".mdl"))
					{
						char szModel[64];
						strcpy_s(szModel, Model->name);
						*(strrchr(szModel, '.')) = 0;
						strcpy_s(szModel, strrchr(szModel, '/') + 3);
						_strupr_s(szModel);
						g_Core->Render->DrawString(true, X, _Y, rgb(255, 0, 0), szModel);
					}

				}

				if (CS16DVar->NameESP)
					g_Core->Render->DrawString(true, X, _Y, rgb(255, 0, 0), PlayerInfo->name);
			}

			if (i >= CS16_MAX_CLIENTS && ValidEntity(i))
			{
				if (!CS16Engine->WorldToScreen(pEnt->origin + Vec3(0.0f, 0.0f, pEnt->curstate.maxs.z), ScreenCoords))
					continue;

				float X = ScreenCoords.x;
				float Y = ScreenCoords.y - 5 - g_Core->TextSize;

				// Weapon ESP
				if (CS16DVar->WeaponESP)
				{
					char szModel[64];
					strcpy_s(szModel, CS16Engine->GetModelName(pEnt));
					if (strstr(szModel, ".mdl"))
					{
						*(strrchr(szModel, '.')) = 0;
						strcpy_s(szModel, strrchr(szModel, '/') + 3);
						_strupr_s(szModel);
						g_Core->Render->DrawString(true, X, Y, rgb(255, 0, 0), szModel);
					}
				}
			}
		}
	}
}