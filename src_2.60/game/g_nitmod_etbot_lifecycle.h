#ifndef G_NITMOD_ETBOT_LIFECYCLE_H
#define G_NITMOD_ETBOT_LIFECYCLE_H

#ifdef __cplusplus
extern "C" {
#endif
int Bot_Interface_Init(void);
void Bot_Interface_InitHandles(void);
int Bot_Interface_Shutdown(void);
void Bot_Interface_Update(void);
void Bot_Interface_ConsoleCommand(void);
qboolean Bot_Interface_IsLoaded(void);
const char *Bot_Interface_LibraryPath(void);
struct gentity_s;
void Bot_Queue_EntityCreated(struct gentity_s *entity);
void Bot_Event_EntityDeleted(struct gentity_s *entity);
void Bot_Event_ClientConnected(int clientNum, qboolean isBot);
void Bot_Event_ClientDisConnected(int clientNum);
void Bot_Event_TakeDamage(int clientNum, struct gentity_s *attacker);
void Bot_Event_Death(int clientNum, struct gentity_s *killer, const char *meansOfDeath);
void Bot_Event_KilledSomeone(int clientNum, struct gentity_s *victim, const char *meansOfDeath);
void Bot_Event_FireWeapon(int clientNum, int weaponId, struct gentity_s *projectile);
void Bot_Event_AddWeapon(int clientNum, int weaponId);
void Bot_Event_RemoveWeapon(int clientNum, int weaponId);
void Bot_Event_ResetWeapons(int clientNum);
void Bot_Event_Healed(int clientNum, struct gentity_s *healer);
void Bot_Event_RecievedAmmo(int clientNum, struct gentity_s *supplier);
void Bot_Event_Revived(int clientNum, struct gentity_s *medic);
int Bot_WeaponGameToBot(int weapon);
#ifdef __cplusplus
}
#endif

#endif
