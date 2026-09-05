#include "g_local.h"
#include "g_nitmod_banners.h"
#include "g_nitmod_legacy_cvars.h"
#include <limits.h>

#define NITMOD_MAX_BANNERS 9

static int bannerIndex;
static int bannerNextTime;

static int G_NITMOD_BannerNextTime(int interval) {
	double next = (double)level.time + (double)interval * 1000.0;
	return next > INT_MAX ? INT_MAX : (int)next;
}

static void G_NITMOD_BannerCommandText(const char *input, char *output, int size) {
	int used = 0;
	if (!output || size <= 0) return;
	if (!input) input = "";
	while (*input && used < size - 1) {
		unsigned char c = (unsigned char)*input++;
		if (c == '"') c = '\'';
		if (c == '\r') continue;
		if (c == '\n') {
			if (used + 2 >= size) break;
			output[used++] = '\\';
			output[used++] = 'n';
			continue;
		}
		if (c < 32) continue;
		output[used++] = (char)c;
	}
	output[used] = '\0';
}

void G_NITMOD_BannersReset(void) {
	bannerIndex = 1;
	bannerNextTime = 0;
}

void G_NITMOD_BannersRunFrame(void) {
	char raw[256], message[512];
	int interval = G_NITMOD_LegacyCvarInteger("g_msgs", 0);
	int position = G_NITMOD_LegacyCvarInteger("g_msgpos", 0);
	int attempts;

	if (interval <= 0 || level.intermissiontime) {
		bannerNextTime = 0;
		return;
	}
	if (bannerNextTime <= 0) bannerNextTime = G_NITMOD_BannerNextTime(interval);
	if (level.time < bannerNextTime) return;
	bannerNextTime = G_NITMOD_BannerNextTime(interval);
	if (position < 0) position = 0;
	if (position > 2) position = 2;

	for (attempts = 0; attempts < NITMOD_MAX_BANNERS; ++attempts) {
		trap_Cvar_VariableStringBuffer(va("g_msg%i", bannerIndex), raw, sizeof(raw));
		bannerIndex = bannerIndex % NITMOD_MAX_BANNERS + 1;
		if (!raw[0]) {
			/* Original Nitmod treats the first empty slot as the end and wraps. */
			bannerIndex = 1;
			trap_Cvar_VariableStringBuffer("g_msg1", raw, sizeof(raw));
			if (!raw[0]) return;
			bannerIndex = 2;
		}
		G_NITMOD_BannerCommandText(raw, message, sizeof(message));
		if (message[0]) {
			trap_SendServerCommand(-1, va("bp %i \"%s\"", position, message));
			return;
		}
	}
}
