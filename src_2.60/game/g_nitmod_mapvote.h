#ifndef G_NITMOD_MAPVOTE_H
#define G_NITMOD_MAPVOTE_H

void G_NITMOD_MapVoteSendList( gentity_t *ent );
void G_NITMOD_MapVoteSendTally( gentity_t *ent );
void G_NITMOD_MapVoteCast( gentity_t *ent );
qboolean G_NITMOD_MapVoteExitLevel( void );
qboolean G_NITMOD_MapVoteActive( void );
qboolean G_NITMOD_MapVoteExitReady( void );

#endif
