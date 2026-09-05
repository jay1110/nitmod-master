#include "q_shared.h"
//#include "bg_public.h"

#ifdef GAMEDLL
#include "g_local.h"
#else
#ifdef CGAMEDLL
#include "../cgame/cg_local.h"
#else
#include "../ui/ui_local.h"
#endif
#endif

// Campaign File Handling

// Saves
// Explicit little-endian encoding for the original i386 file format.

/* The original i386 campaign.dat is little endian: four-byte ident, one-byte
 * version, then 32-bit counts/hashes and variable-length completed-map lists.
 * Bound every read by the actual file length, before indexing typed arrays. */
static qboolean BG_CampaignReadInt(fileHandle_t file, int *remaining, int *value) {
	unsigned char bytes[4];
	unsigned int bits;
	if(*remaining < 4) return qfalse;
	trap_FS_Read(bytes, sizeof(bytes), file);
	*remaining -= 4;
	bits = (unsigned int)bytes[0] | ((unsigned int)bytes[1] << 8) |
	       ((unsigned int)bytes[2] << 16) | ((unsigned int)bytes[3] << 24);
	memcpy(value, &bits, sizeof(bits));
	return qtrue;
}

qboolean BG_LoadCampaignSave(const char *filename, cpsFile_t *file, const char *profile) {
	fileHandle_t handle = 0;
	int remaining, i, j;
	unsigned int hash = 0, index;
	unsigned char version;
	if(!file) return qfalse;
	memset(file, 0, sizeof(*file));
	if(!filename || !profile) return qfalse;
	remaining = trap_FS_FOpenFile(filename, &handle, FS_READ);
	if(remaining < 0 || !handle) return qfalse;
	if(!BG_CampaignReadInt(handle, &remaining, &file->header.ident) ||
	   file->header.ident != CPS_IDENT || remaining < 1) goto invalid;
	trap_FS_Read(&version, 1, handle); --remaining;
	file->header.version = version;
	if(version != CPS_VERSION ||
	   !BG_CampaignReadInt(handle, &remaining, &file->header.numCampaigns) ||
	   !BG_CampaignReadInt(handle, &remaining, &file->header.profileHash) ||
	   file->header.numCampaigns < 0 || file->header.numCampaigns > MAX_CAMPAIGNS) goto invalid;
	for(index = 0; profile[index]; ++index)
		hash += (unsigned int)tolower((unsigned char)profile[index]) * (index + 119u);
	if((unsigned int)file->header.profileHash != hash) goto invalid;
	for(i = 0; i < file->header.numCampaigns; ++i) {
		cpsCampaign_t *campaign = &file->campaigns[i];
		if(!BG_CampaignReadInt(handle, &remaining, &campaign->shortnameHash) ||
		   !BG_CampaignReadInt(handle, &remaining, &campaign->progress) ||
		   campaign->progress < 0 || campaign->progress > MAX_MAPS_PER_CAMPAIGN) goto invalid;
		for(j = 0; j < campaign->progress; ++j)
			if(!BG_CampaignReadInt(handle, &remaining, &campaign->maps[j].mapnameHash)) goto invalid;
	}
	trap_FS_FCloseFile(handle);
	return qtrue;
invalid:
	trap_FS_FCloseFile(handle);
	memset(file, 0, sizeof(*file));
	Com_Printf("^1WARNING: BG_LoadCampaignSave: invalid, truncated or incompatible campaignsave\n");
	return qfalse;
}

static void BG_CampaignWriteInt(fileHandle_t file, int value) {
    unsigned int bits = (unsigned int)value;
    unsigned char bytes[4];
    int i;
    for(i = 0; i < 4; ++i) bytes[i] = (unsigned char)(bits >> (8 * i));
    trap_FS_Write(bytes, sizeof(bytes), file);
}

qboolean BG_StoreCampaignSave(const char *filename, cpsFile_t *file, const char *profile) {
    fileHandle_t handle = 0;
    unsigned int hash = 0, index;
    unsigned char version = CPS_VERSION;
    int i, j;
    /* Validate the entire payload before opening FS_WRITE (which truncates). */
    if(!filename || !profile || !file || file->header.numCampaigns < 0 ||
       file->header.numCampaigns > MAX_CAMPAIGNS) return qfalse;
    for(i = 0; i < file->header.numCampaigns; ++i)
        if(file->campaigns[i].progress < 0 ||
           file->campaigns[i].progress > MAX_MAPS_PER_CAMPAIGN) return qfalse;
    if(trap_FS_FOpenFile(filename, &handle, FS_WRITE) < 0 || !handle) return qfalse;
    for(index = 0; profile[index]; ++index)
        hash += (unsigned int)tolower((unsigned char)profile[index]) * (index + 119u);
    file->header.ident = CPS_IDENT;
    file->header.version = version;
    memcpy(&file->header.profileHash, &hash, sizeof(hash));
    BG_CampaignWriteInt(handle, file->header.ident);
    trap_FS_Write(&version, 1, handle);
    BG_CampaignWriteInt(handle, file->header.numCampaigns);
    BG_CampaignWriteInt(handle, file->header.profileHash);
    for(i = 0; i < file->header.numCampaigns; ++i) {
        BG_CampaignWriteInt(handle, file->campaigns[i].shortnameHash);
        BG_CampaignWriteInt(handle, file->campaigns[i].progress);
        for(j = 0; j < file->campaigns[i].progress; ++j)
            BG_CampaignWriteInt(handle, file->campaigns[i].maps[j].mapnameHash);
    }
    trap_FS_FCloseFile(handle);
    return qtrue;
}
