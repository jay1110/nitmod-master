#ifndef G_NITMOD_GEOIP_H
#define G_NITMOD_GEOIP_H
void G_NITMOD_GeoIPLoad(void);
void G_NITMOD_GeoIPClose(void);
int G_NITMOD_GeoIPCountry(const char *address,int bot);
#endif
