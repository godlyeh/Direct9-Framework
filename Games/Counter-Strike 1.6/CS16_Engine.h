/*

	File: CS16_Engine

	Used for cs16 engine handling

*/

#define CS16_MAX_CLIENTS 32

class CS16EngineInfo
{
public:
	CS16EngineInfo()
	{
		Entity = new cs16_cl_entity_t[4096];
		TeamInfo = new cs16_teaminfo_t[CS16_MAX_CLIENTS];
		PlayerInfo = new cs16_player_info_t[CS16_MAX_CLIENTS];
	}

public:
	int MaxEntity;
	int LocalIndex;
	float CameraMatrix[4][4];

	char MapName[MAX_PATH];

	cs16_cl_entity_t* Entity = NULL;
	cs16_teaminfo_t* TeamInfo = NULL;
	cs16_player_info_t* PlayerInfo = NULL;

public:
	void ReadGameInfoSlow();
	void ReadGameInfo();

public:
	bool WorldToScreen(float *WorldPos, float *Out);
};