#ifndef NITMOD_MD5_H
#define NITMOD_MD5_H
#include <stddef.h>
/* Wire checksum only; MD5 is not an authentication or tamper-proof primitive. */
void NITMOD_MD5Hex(const void *bytes, size_t length, char hex[33]);
#endif
