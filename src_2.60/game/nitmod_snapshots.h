#ifndef NITMOD_SNAPSHOTS_H
#define NITMOD_SNAPSHOTS_H

typedef const char *(*nitmodSnapshotArgument_t)( int index );

typedef struct {
	int doubleJump;
	int missileCams;
	int war;
	int noReload;
	int filterCams;
	int spectatorNames;
	int misc;
	int proneDelay;
	int dynamiteTimer;
	int crouchStandDelay;
	int standCrouchDelay;
} nitmodSimpleConfig_t;

typedef struct {
	int panzerRestriction;
	int maxPanzers;
	int maxMG42s;
	int maxFlamers;
	int maxMortars;
	int maxRifleGrenades;
	int adrenaline;
	int keepAwards;
	int maxSoldiers;
	int maxMedics;
	int maxEngineers;
	int maxFieldops;
	int maxCovertops;
	int weapons;
	float doubleJumpHeight;
	int tdmOptions;
	int dmOptions;
	int gravity;
	int mapCount;
	int resetXPMapCount;
	/* Local score cache, not part of the # wire message. */
	int teamScoreAxis;
	int teamScoreAllies;
	/* Original z1 server command, likewise independent from #. */
	int tdmScoreLimit;
	/* Original DM command: winning client for gametype 8 intermission. */
	int dmWinnerClient;
} nitmodGameState_t;

typedef struct {
	int type;
	int detail;
	int objective;
	int actor;
	int meansOfDeath;
} nitmodObjectiveEvent_t;

typedef struct {
	int soldier[2];
	int medic[2];
	int engineer[2];
	int fieldops[2];
	int covertops[2];
} nitmodChargeTimes_t;

typedef struct {
	int axis;
	int allies;
} nitmodTeamScores_t;

typedef struct {
	unsigned int bodyshots;
	unsigned int headshots;
	int kills;
	int deaths;
	unsigned int revives;
} nitmodMapEndStats_t;

/* argv uses engine argument positions (command=0). All fields are parsed
 * before committing output; on failure the previous snapshot is retained. */
int NITMOD_ParseChargeSnapshot( int argc, nitmodSnapshotArgument_t argv, nitmodChargeTimes_t *output );
int NITMOD_ParseTeamScoreSnapshot( int argc, nitmodSnapshotArgument_t argv, nitmodTeamScores_t *output );
int NITMOD_ParseMapStatsSnapshot( int argc, nitmodSnapshotArgument_t argv, nitmodMapEndStats_t *output );

int NITMOD_ParseSimpleConfigSnapshot( int argc, nitmodSnapshotArgument_t argv, nitmodSimpleConfig_t *output );
int NITMOD_ParseGameStateSnapshot( int argc, nitmodSnapshotArgument_t argv, nitmodGameState_t *output );
int NITMOD_ParseObjectiveSnapshot( int argc, nitmodSnapshotArgument_t argv, int maxClients, nitmodObjectiveEvent_t *output );

#endif
