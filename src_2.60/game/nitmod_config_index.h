#ifndef NITMOD_CONFIG_INDEX_H
#define NITMOD_CONFIG_INDEX_H

typedef const char *(*nitmodReadConfigIndex_t)( void *context, int index );

/* Slot zero is reserved. Search stops at the first empty slot, as in
 * nitrox_CSIndex. Return -1 on creation overflow, -2 on invalid arguments,
 * 0 for empty name/not found, or the relative index. needsWrite distinguishes
 * an existing entry from a free slot; storage and transmission are adapters. */
int NITMOD_FindConfigIndex( const char *name, int count, int create,
	nitmodReadConfigIndex_t read, void *context, int *needsWrite );

#endif
