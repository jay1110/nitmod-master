#ifndef NITMOD_TYPES_H
#define NITMOD_TYPES_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#define GHIDRA_FIELD(obj, off, sz) (*(uint32_t *)((uint8_t *)&(obj) + (off)))

typedef uint8_t byte;
typedef uint8_t dwfenc;
typedef uint32_t dword;
typedef uint16_t word;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;

typedef void *pointer;

typedef struct gentity_s gentity_s;
struct gentity_s { uint8_t _opaque[1]; };

typedef struct obUserData_t obUserData_t;
struct obUserData_t { uint8_t _opaque[1]; };

typedef struct Vector Vector;
struct Vector { float x, y, z; };

typedef struct KeyVals KeyVals;
struct KeyVals { uint8_t _opaque[1]; };

typedef struct ostream ostream;
struct ostream { uint8_t _opaque[1]; };

typedef struct ios_base ios_base;
struct ios_base { uint8_t _opaque[1]; };

typedef struct locale locale;
struct locale { uint8_t _opaque[1]; };

typedef struct iostream iostream;
struct iostream { uint8_t _opaque[1]; };

typedef struct streambuf streambuf;
struct streambuf { uint8_t _opaque[1]; };

typedef struct allocator allocator;
struct allocator { uint8_t _opaque[1]; };

typedef struct stringstream stringstream;
struct stringstream { uint8_t _opaque[1]; };

typedef struct Init Init;
struct Init { uint8_t _opaque[1]; };

typedef struct string string;
struct string { uint8_t _opaque[1]; };

typedef FILE _IO_FILE;

#ifndef __linux__
typedef int sigset_t;
typedef int socklen_t;
typedef struct { int sa_family; char sa_data[14]; } sockaddr;
typedef struct { unsigned s_addr; } in_addr;
typedef unsigned in_addr_t;
typedef struct hostent hostent;
typedef long __off_t;
typedef long long __off64_t;
typedef unsigned __mode_t;
typedef int __pid_t;
typedef void (*__sighandler_t)(int);
typedef void *__gnuc_va_list;
typedef int (*__compar_fn_t)(const void *, const void *);
typedef long time_t;
typedef long clock_t;
typedef long ssize_t;
typedef struct tm tm;
typedef struct timeval timeval;
typedef struct timezone timezone;
typedef timezone *__timezone_ptr_t;
typedef struct stat stat;
typedef struct stat64 stat64;
typedef struct lconv lconv;
typedef struct sigaction sigaction;
typedef struct __jmp_buf_tag __jmp_buf_tag;
typedef int32_t __int32_t;
typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;
#endif

#endif /* NITMOD_TYPES_H */
