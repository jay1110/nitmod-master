#include "g_local.h"
#include "g_nitmod_banners.h"
#include "g_nitmod_legacy_cvars.h"
#include <limits.h>

static int bannerIndex;

void G_NITMOD_BannersReset(void) {
	bannerIndex = 0;
}

int G_NITMOD_BannerIndex(void) {
	return bannerIndex;
}

void G_NITMOD_SetBannerIndex(int index) {
	bannerIndex = index;
}

void G_NITMOD_BannersRunFrame(void) {
	char message[256];
	int interval = G_NITMOD_LegacyCvarInteger("g_msgs", 0);
	int position;

	/* Original G_RunFrame uses absolute whole-second multiples, including
	 * time zero and intermission; changing g_msgs takes effect immediately. */
	if (!interval || level.time % 1000 || (level.time / 1000) % interval) return;

	trap_Cvar_VariableStringBuffer(va("g_msg%i", bannerIndex), message, sizeof(message));
	if (!message[0]) {
		/* The first empty slot ends the list. There is no fixed slot limit. */
		bannerIndex = 1;
		trap_Cvar_VariableStringBuffer("g_msg1", message, sizeof(message));
	} else {
		/* Match the original 32-bit increment without signed-overflow UB. */
		bannerIndex = bannerIndex == INT_MAX ? INT_MIN : bannerIndex + 1;
	}
	if (!message[0]) return;
	if (bannerIndex == 1) bannerIndex = 2;
	position = G_NITMOD_LegacyCvarInteger("g_msgpos", 0);
	trap_SendServerCommand(-1, va("bp %i \"%s\"", position, message));
}
