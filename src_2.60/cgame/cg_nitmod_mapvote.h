#ifndef CG_NITMOD_MAPVOTE_H
#define CG_NITMOD_MAPVOTE_H
#include "../game/nitmod_snapshots.h"
qboolean CG_NitmodMapVoteEnabled(void);
int CG_NitmodNextDebriefPage(int page);
qboolean CG_NitmodMapCycleText(const nitmodGameState_t *state, qboolean uppercase, char *text, int size);
qboolean CG_NitmodMapCycleReset(const nitmodGameState_t *state);
qboolean CG_NitmodScoreboardCycleText(const nitmodGameState_t *state, int gametype, char *text, int size);
typedef struct {
    rectDef_t rect;
    int slot;
    char label[32];
    char mapName[128];
} nitmodMapVoteButton_t;
qboolean CG_NitmodMapVoteButton(int row, nitmodMapVoteButton_t *button);
void CG_NitmodMapVoteScrollRect(rectDef_t *rect);

void CG_NitmodParseMapVoteList( void );
void CG_NitmodParseMapVoteTally( void );
void CG_NitmodMapVoteList_f( void );
void CG_NitmodMapVote_f( void );
void CG_NitmodMapVoteReset( void );
void CG_NitmodMapVoteRequest( void );
void CG_NitmodMapVoteDraw( void );
qboolean CG_NitmodMapVoteKeyEvent( int key, qboolean down );

#endif
