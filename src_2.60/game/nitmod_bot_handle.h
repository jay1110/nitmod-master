#ifndef NITMOD_BOT_HANDLE_H
#define NITMOD_BOT_HANDLE_H
#include <stdint.h>
#define NITMOD_BOT_ENTITY_COUNT 1024
#define NITMOD_BOT_WORLD_INDEX 1022
#define NITMOD_BOT_INVALID_HANDLE UINT32_C(0x0000ffff)
/* Wire bits only: not a native pointer or a C++ GameEntity ABI replacement. */
typedef uint32_t nitmodBotHandle_t;
/* Explicit original four-byte record. Flag meanings are not yet recovered. */
typedef struct {
    uint16_t serial;
    uint8_t flags;
    uint8_t reserved;
} nitmodBotHandleEntry_t;
/* Initialize allocated records; preserves upper flags and reserved bytes. */
void NITMOD_BotInitHandles(nitmodBotHandleEntry_t entries[NITMOD_BOT_ENTITY_COUNT]);
/* Mutation only. A future adapter must deliver deletion before this call. */
int NITMOD_BotAdvanceHandle(nitmodBotHandleEntry_t entries[NITMOD_BOT_ENTITY_COUNT], int index);
nitmodBotHandle_t NITMOD_BotPackHandle(int index, uint16_t serial);
int NITMOD_BotHandleIndex(nitmodBotHandle_t handle);
uint16_t NITMOD_BotHandleSerial(nitmodBotHandle_t handle);
/* Borrowed table entries; caller supplies current state, no lifecycle mutation. */
int NITMOD_BotResolveHandle(nitmodBotHandle_t handle,
    const uint16_t serials[NITMOD_BOT_ENTITY_COUNT],
    const unsigned char inuse[NITMOD_BOT_ENTITY_COUNT]);
#endif
