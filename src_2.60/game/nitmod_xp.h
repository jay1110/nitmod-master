#ifndef NITMOD_XP_H
#define NITMOD_XP_H
int NITMOD_XPEncode(const float skills[7],char encoded[1024]);
int NITMOD_XPDecode(const char *encoded,float skills[7]);
/* On success, add saved integer skills to the supplied running total. */
int NITMOD_XPDecodeTotal(const char *encoded,float skills[7],float *total);
#endif
