#include "g_local.h"
#include "g_nitmod_entities.h"

/* nitrox_FadeLandmines: remove the entity's marker from each team's map
 * before releasing the engine-owned mine. Called only with g_entities slots. */
void NITMOD_FreeFadedLandmine( gentity_t *mine ) {
	int team;
	int entityNum;
	if( !mine ) {
		return;
	}
	entityNum = (int)( mine - g_entities );
	for( team = 0; team < 2; team++ ) {
		mapEntityData_t *marker = G_FindMapEntityData( &mapEntityData[team], entityNum );
		if( marker ) {
			G_FreeMapEntityData( &mapEntityData[team], marker );
		}
	}
	G_FreeEntity( mine );
}
