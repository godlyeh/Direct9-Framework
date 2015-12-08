/*

	CS16_Structs

	Structs copied from sdk

*/

typedef Vec3 vec3_t;
typedef struct { byte r, g, b; }color24;
typedef struct { unsigned r, g, b, a; }colorVec;

#define HISTORY_MAX				64  // Must be power of 2
#define	MAX_INFO_STRING			256
#define	MAX_SCOREBOARDNAME		32
#define MAX_QPATH				64

typedef enum
{
	t_sound = 0,
	t_skin,
	t_model,
	t_decal,
	t_generic,
	t_eventscript
} resourcetype_t;

typedef struct
{
	short TeamNumber;
	char TeamName[9];
	char _UNUSED[0x5D];
} cs16_teaminfo_t;

typedef struct
{
	// Time stamp for this movement
	float					animtime;

	vec3_t					origin;
	vec3_t					angles;
} cs16_position_history_t;

typedef struct
{
	byte					mouthopen;		// 0 = mouth closed, 255 = mouth agape
	byte					sndcount;		// counter for running average
	int						sndavg;			// running average
} cs16_mouth_t;

typedef struct
{
	float					prevanimtime;
	float					sequencetime;
	byte					prevseqblending[2];
	vec3_t					prevorigin;
	vec3_t					prevangles;

	int						prevsequence;
	float					prevframe;

	byte					prevcontroller[4];
	byte					prevblending[2];
} cs16_latchedvars_t;

typedef struct
{
	// Fields which are filled in by routines outside of delta compression
	int			entityType;
	// Index into cl_entities array for this entity.
	int			number;
	float		msg_time;

	// Message number last time the player/entity state was updated.
	int			messagenum;

	// Fields which can be transitted and reconstructed over the network stream
	vec3_t		origin;
	vec3_t		angles;

	int			modelindex;
	int			sequence;
	float		frame;
	int			colormap;
	short		skin;
	short		solid;
	int			effects;
	float		scale;

	byte		eflags;

	// Render information
	int			rendermode;
	int			renderamt;
	color24		rendercolor;
	int			renderfx;

	int			movetype;
	float		animtime;
	float		framerate;
	int			body;
	byte		controller[4];
	byte		blending[4];
	vec3_t		velocity;

	// Send bbox down to client for use during prediction.
	vec3_t		mins;
	vec3_t		maxs;

	int			aiment;
	// If owned by a player, the index of that player ( for projectiles ).
	int			owner;

	// Friction, for prediction.
	float		friction;
	// Gravity multiplier
	float		gravity;

	// PLAYER SPECIFIC
	int			team;
	int			playerclass;
	int			health;
	int			spectator;
	int         weaponmodel;
	int			gaitsequence;
	// If standing on conveyor, e.g.
	vec3_t		basevelocity;
	// Use the crouched hull, or the regular player hull.
	int			usehull;
	// Latched buttons last time state updated.
	int			oldbuttons;
	// -1 = in air, else pmove entity number
	int			onground;
	int			iStepLeft;
	// How fast we are falling
	float		flFallVelocity;

	float		fov;
	int			weaponanim;

	// Parametric movement overrides
	vec3_t				startpos;
	vec3_t				endpos;
	float				impacttime;
	float				starttime;

	// For mods
	int			iuser1;
	int			iuser2;
	int			iuser3;
	int			iuser4;
	float		fuser1;
	float		fuser2;
	float		fuser3;
	float		fuser4;
	vec3_t		vuser1;
	vec3_t		vuser2;
	vec3_t		vuser3;
	vec3_t		vuser4;
}cs16_entity_state_t;

typedef struct
{
	int						index;      // Index into cl_entities ( should match actual slot, but not necessarily )

	int						player;     // True if this entity is a "player"

	cs16_entity_state_t			baseline;   // The original state from which to delta during an uncompressed message
	cs16_entity_state_t			prevstate;  // The state information from the penultimate message received from the server
	cs16_entity_state_t			curstate;   // The state information from the last message received from server

	int						current_position;  // Last received history update index
	cs16_position_history_t		ph[HISTORY_MAX];   // History of position and angle updates for this player

	cs16_mouth_t					mouth;			// For synchronizing mouth movements.

	cs16_latchedvars_t			latched;		// Variables used by studio model rendering routines

	// Information based on interplocation, extrapolation, prediction, or just copied from last msg received.
	//
	float					lastmove;

	// Actual render position and angles
	vec3_t					origin;
	vec3_t					angles;

	// Attachment points
	vec3_t					attachment[4];

	// Other entity local information
	int						trivial_accept;

	DWORD					model;			// cl.model_precache[ curstate.modelindes ];  all visible entities have a model
	DWORD					efrag;			// linked list of efrags
	DWORD					topnode;		// for bmodels, first world node that splits bmodel, or NULL if not split

	float					syncbase;		// for client-side animations -- used by obsolete alias animation system, remove?
	int						visframe;		// last frame this entity was found in an active leaf
	colorVec				cvFloorColor;
}cs16_cl_entity_t;

typedef struct
{
	int userid; //0x0000 
	char userinfo[256]; //0x0004 
	char name[32]; //0x0104 
	int specator; //0x0124 
	int ping; //0x0128 
	int packet_loss; //0x012C 
	char model[64]; //0x0130 
	int topcolor; //0x0170 
	int bottomcolor; //0x0174 
	char _0x0178[216];
}cs16_player_info_t;