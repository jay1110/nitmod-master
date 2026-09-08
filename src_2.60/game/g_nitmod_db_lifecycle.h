#ifndef G_NITMOD_DB_LIFECYCLE_H
#define G_NITMOD_DB_LIFECYCLE_H
/* Private export, called only after trap_NitmodDatabaseStorage1 negotiation. */
#define GAME_NITMOD_DB_PRE_SHUTDOWN 0x4e444201
int G_NITMOD_DatabasePrepareShutdown(void);
int G_NITMOD_DatabaseIsShuttingDown(void);
#endif
