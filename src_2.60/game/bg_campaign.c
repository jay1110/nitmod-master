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
// FIXME: need byteswapping for macs

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

qboolean BG_StoreCampaignSave( const char *filename, cpsFile_t *file, const char *profile ) {
	fileHandle_t f;
	long hash;
	char *ch;
	int i, j;

	// open the file
	if( trap_FS_FOpenFile( filename, &f, FS_WRITE ) < 0 ) {
		return( qfalse );
	}

	// write the header
	file->header.ident = CPS_IDENT;
	file->header.version = CPS_VERSION;

	trap_FS_Write( &file->header.ident, sizeof(int), f );
	trap_FS_Write( &file->header.version, 1, f );
	trap_FS_Write( &file->header.numCampaigns, sizeof(int), f );

	// generate hash for profile
	for( hash = 0, ch = (char *)profile; *ch != '\0'; ch++ ) {
		hash += (long)(tolower(*ch))*((ch-profile)+119);
	}

	file->header.profileHash = (int)hash;

	trap_FS_Write( &file->header.profileHash, sizeof(int), f );

	// write the campaigns and maps
	for( i = 0; i < file->header.numCampaigns; i++ ) {
		trap_FS_Write( &file->campaigns[i].shortnameHash, sizeof(int), f );
		trap_FS_Write( &file->campaigns[i].progress, sizeof(int), f );

		// all completed maps
		for( j = 0; j < file->campaigns[i].progress; j++ ) {
			trap_FS_Write( &file->campaigns[i].maps[j].mapnameHash, sizeof(int), f );
		}
	}

	// done
	trap_FS_FCloseFile( f );

	return( qtrue );
}
