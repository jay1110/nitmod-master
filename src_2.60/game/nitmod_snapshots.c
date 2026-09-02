#include "nitmod_protocol.h"
#include "nitmod_snapshots.h"

int NITMOD_ParseSimpleConfigSnapshot( int argc, nitmodSnapshotArgument_t argv, nitmodSimpleConfig_t *output ) {
	nitmodSimpleConfig_t next;
	if( argc != 12 || !argv || !output ) {
		return 0;
	}
	if( !NITMOD_ParseProtocolSigned( argv(1), &next.doubleJump ) ||
		!NITMOD_ParseProtocolSigned( argv(2), &next.missileCams ) ||
		!NITMOD_ParseProtocolSigned( argv(3), &next.war ) ||
		!NITMOD_ParseProtocolSigned( argv(4), &next.noReload ) ||
		!NITMOD_ParseProtocolSigned( argv(5), &next.filterCams ) ||
		!NITMOD_ParseProtocolSigned( argv(6), &next.spectatorNames ) ||
		!NITMOD_ParseProtocolSigned( argv(7), &next.misc ) ||
		!NITMOD_ParseProtocolSigned( argv(8), &next.proneDelay ) ||
		!NITMOD_ParseProtocolSigned( argv(9), &next.dynamiteTimer ) ||
		!NITMOD_ParseProtocolSigned( argv(10), &next.crouchStandDelay ) ||
		!NITMOD_ParseProtocolSigned( argv(11), &next.standCrouchDelay ) ) {
		return 0;
	}
	*output = next;
	return 1;
}

int NITMOD_ParseGameStateSnapshot( int argc, nitmodSnapshotArgument_t argv, nitmodGameState_t *output ) {
	nitmodGameState_t next;
	if( argc != 21 || !argv || !output ) {
		return 0;
	}
	/* # must not replace scores delivered independently by tsc. */
	next = *output;
	if( !NITMOD_ParseProtocolSigned( argv(1), &next.panzerRestriction ) ||
		!NITMOD_ParseProtocolSigned( argv(2), &next.maxPanzers ) ||
		!NITMOD_ParseProtocolSigned( argv(3), &next.maxMG42s ) ||
		!NITMOD_ParseProtocolSigned( argv(4), &next.maxFlamers ) ||
		!NITMOD_ParseProtocolSigned( argv(5), &next.maxMortars ) ||
		!NITMOD_ParseProtocolSigned( argv(6), &next.maxRifleGrenades ) ||
		!NITMOD_ParseProtocolSigned( argv(7), &next.adrenaline ) ||
		!NITMOD_ParseProtocolSigned( argv(8), &next.keepAwards ) ||
		!NITMOD_ParseProtocolSigned( argv(9), &next.maxSoldiers ) ||
		!NITMOD_ParseProtocolSigned( argv(10), &next.maxMedics ) ||
		!NITMOD_ParseProtocolSigned( argv(11), &next.maxEngineers ) ||
		!NITMOD_ParseProtocolSigned( argv(12), &next.maxFieldops ) ||
		!NITMOD_ParseProtocolSigned( argv(13), &next.maxCovertops ) ||
		!NITMOD_ParseProtocolSigned( argv(14), &next.weapons ) ||
		!NITMOD_ParseProtocolFloat( argv(15), &next.doubleJumpHeight ) ||
		!NITMOD_ParseProtocolSigned( argv(16), &next.tdmOptions ) ||
		!NITMOD_ParseProtocolSigned( argv(17), &next.dmOptions ) ||
		!NITMOD_ParseProtocolSigned( argv(18), &next.gravity ) ||
		!NITMOD_ParseProtocolSigned( argv(19), &next.mapCount ) ||
		!NITMOD_ParseProtocolSigned( argv(20), &next.resetXPMapCount ) ) {
		return 0;
	}
	*output = next;
	return 1;
}

int NITMOD_ParseObjectiveSnapshot( int argc, nitmodSnapshotArgument_t argv, int maxClients, nitmodObjectiveEvent_t *output ) {
	nitmodObjectiveEvent_t next;
	if( argc != 6 || !argv || !output || maxClients <= 0 ) {
		return 0;
	}
	if( !NITMOD_ParseProtocolSigned( argv(1), &next.type ) ||
		!NITMOD_ParseProtocolSigned( argv(2), &next.detail ) ||
		!NITMOD_ParseProtocolSigned( argv(3), &next.objective ) ||
		!NITMOD_ParseProtocolSigned( argv(4), &next.actor ) ||
		!NITMOD_ParseProtocolSigned( argv(5), &next.meansOfDeath ) ) {
		return 0;
	}
	if( next.actor < 0 || next.actor >= maxClients ) {
		return 0;
	}
	*output = next;
	return 1;
}


int NITMOD_ParseChargeSnapshot( int argc, nitmodSnapshotArgument_t argv, nitmodChargeTimes_t *output ) {
	nitmodChargeTimes_t next;
	if( argc != 11 || !argv || !output ) {
		return 0;
	}
	if( !NITMOD_ParseProtocolSigned( argv(1), &next.soldier[0] ) ||
		!NITMOD_ParseProtocolSigned( argv(2), &next.soldier[1] ) ||
		!NITMOD_ParseProtocolSigned( argv(3), &next.medic[0] ) ||
		!NITMOD_ParseProtocolSigned( argv(4), &next.medic[1] ) ||
		!NITMOD_ParseProtocolSigned( argv(5), &next.engineer[0] ) ||
		!NITMOD_ParseProtocolSigned( argv(6), &next.engineer[1] ) ||
		!NITMOD_ParseProtocolSigned( argv(7), &next.fieldops[0] ) ||
		!NITMOD_ParseProtocolSigned( argv(8), &next.fieldops[1] ) ||
		!NITMOD_ParseProtocolSigned( argv(9), &next.covertops[0] ) ||
		!NITMOD_ParseProtocolSigned( argv(10), &next.covertops[1] ) ) {
		return 0;
	}
	*output = next;
	return 1;
}

int NITMOD_ParseTeamScoreSnapshot( int argc, nitmodSnapshotArgument_t argv, nitmodTeamScores_t *output ) {
	nitmodTeamScores_t next;
	if( argc != 3 || !argv || !output ) {
		return 0;
	}
	if( !NITMOD_ParseProtocolSigned( argv(1), &next.axis ) ||
		!NITMOD_ParseProtocolSigned( argv(2), &next.allies ) ) {
		return 0;
	}
	*output = next;
	return 1;
}

int NITMOD_ParseMapStatsSnapshot( int argc, nitmodSnapshotArgument_t argv, nitmodMapEndStats_t *output ) {
	nitmodMapEndStats_t next;
	if( argc != 6 || !argv || !output ) {
		return 0;
	}
	/* These signedness choices match qagame's mes %u %u %i %i %u. */
	if( !NITMOD_ParseProtocolUnsigned( argv(1), &next.bodyshots ) ||
		!NITMOD_ParseProtocolUnsigned( argv(2), &next.headshots ) ||
		!NITMOD_ParseProtocolSigned( argv(3), &next.kills ) ||
		!NITMOD_ParseProtocolSigned( argv(4), &next.deaths ) ||
		!NITMOD_ParseProtocolUnsigned( argv(5), &next.revives ) ) {
		return 0;
	}
	*output = next;
	return 1;
}
