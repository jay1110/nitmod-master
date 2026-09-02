#ifndef G_NITMOD_EQUIPMENT_H
#define G_NITMOD_EQUIPMENT_H
struct gclient_s;
void G_NITMOD_ReadEquipment( struct gclient_s *client, int clientNum );
void G_NITMOD_WriteEquipment( const struct gclient_s *client, int clientNum );
#endif
