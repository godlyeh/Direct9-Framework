/*

	File: CS16_Engine

	Used for cs16 engine handling

*/

#define CS16_MAX_CLIENTS 32
#define CS16_MAX_MODELS 512

class CS16EngineInfo
{
public:
	CS16EngineInfo()
	{
		Entity = new cs16_cl_entity_t[4096];
		TeamInfo = new cs16_teaminfo_t[CS16_MAX_CLIENTS];
		PlayerInfo = new cs16_player_info_t[CS16_MAX_CLIENTS];
		ModelArray = new DWORD[CS16_MAX_MODELS];
	}

public:
	int MaxEntity;
	int LocalIndex;
	float CameraMatrix[4][4];

	char MapName[MAX_PATH];

	
	cs16_cl_entity_t* Entity = NULL;
	cs16_teaminfo_t* TeamInfo = NULL;
	cs16_player_info_t* PlayerInfo = NULL;
	DWORD* ModelArray = NULL;

public:
	void ReadGameInfoSlow();
	void ReadGameInfo();

public:
	cs16_cl_entity_t* GetLocalPlayer();
	cs16_cl_entity_t* GetEntityByIndex(int Index);
	cs16_player_info_t* GetLocalPlayerInfo();
	cs16_player_info_t* GetPlayerInfoByIndex(int Index);
	cs16_model_t* GetModelByIndex(int Index);
	cs16_model_t* GetModelByIndex(cs16_cl_entity_t *pEntity);
	char* GetModelName(int Index);
	char* GetModelName(cs16_cl_entity_t *pEntity);

	bool WorldToScreen(float* WorldPos, float* Out);

	void VectorLine(float* From, float* To, float lw, COLOR32 Color);
	void Line3DBox(Vec3 WorldPos, Vec3 Mins, Vec3 Maxs, float* Angles, float lw, COLOR32 Color);
};