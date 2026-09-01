#ifndef NITMOD_IMPORTS_H
#define NITMOD_IMPORTS_H

#include "nitmod_types.h"

/* libc / libstdc++ imports from the original .so PLT — do not compile stubs */

int setsockopt(int __fd,int __level,int __optname,void *__optval,socklen_t __optlen);
double cos(double __x);
char * strstr(char *__haystack,char *__needle);
int strcmp(char *__s1,char *__s2);
int printf(char *__format,...);
int fflush(FILE *__stream);
void * memmove(void *__dest,void *__src,size_t __n);
void free(void *__ptr);
int fclose(FILE *__stream);
time_t time(time_t *__timer);
__sighandler_t signal(int __sig,__sighandler_t __handler);
int select(int __nfds,fd_set *__readfds,fd_set *__writefds,fd_set *__exceptfds,timeval *__timeout);
double pow(double __x,double __y);
void rewind(FILE *__stream);
float ceilf(float __x);
int unlink(char *__name);
char * strsignal(int __sig);
float sqrtf(float __x);
int fseek(FILE *__stream,long __off,int __whence);
int ioctl(int __fd,ulong __request,...);
void __cxa_finalize(void);
int __xstat(int __ver,char *__filename,stat *__stat_buf);
char * strcat(char *__dest,char *__src);
size_t fread(void *__ptr,size_t __size,size_t __n,FILE *__stream);
char * strcpy(char *__dest,char *__src);
double floor(double __x);
void * malloc(size_t __size);
void __gmon_start__(void);
void exit(int __status);
float floorf(float __x);
size_t strftime(char *__s,size_t __maxsize,char *__format,tm *__tp);
tm * localtime(time_t *__timer);
int rename(char *__old,char *__new);
char * strchr(char *__s,int __c);
size_t strlen(char *__s);
double sin(double __x);
int bind(int __fd,sockaddr *__addr,socklen_t __len);
long ftell(FILE *__stream);
void __isoc99_sscanf(void);
void backtrace_symbols(void);
FILE * fopen(char *__filename,char *__modes);
void * memset(void *__s,int __c,size_t __n);
int mkdir(char *__path,__mode_t __mode);
double tan(double __x);
double sqrt(double __x);
char * strncpy(char *__dest,char *__src,size_t __n);
double strtod(char *__nptr,char **__endptr);
int rand(void);
ssize_t sendto(int __fd,void *__buf,size_t __n,int __flags,sockaddr *__addr,socklen_t __addr_len);
void sincos(double __x,double *__sinx,double *__cosx);
char * strtok(char *__s,char *__delim);
int sigemptyset(sigset_t *__set);
char * strrchr(char *__s,int __c);
int getsockname(int __fd,sockaddr *__addr,socklen_t *__len);
int sprintf(char *__s,char *__format,...);
int remove(char *__filename);
int vsnprintf(char *__s,size_t __maxlen,char *__format,__gnuc_va_list __arg);
void qsort(void *__base,size_t __nmemb,size_t __size,__compar_fn_t __compar);
int socket(int __domain,int __type,int __protocol);
int sigaction(int __sig,sigaction *__act,sigaction *__oact);
in_addr_t inet_addr(char *__cp);
void backtrace(void);
hostent * gethostbyname(char *__name);
long strtol(char *__nptr,char **__endptr,int __base);
int connect(int __fd,sockaddr *__addr,socklen_t __len);
int close(int __fd);
double atan2(double __y,double __x);
__int32_t ** __ctype_tolower_loc(void);
void * calloc(size_t __nmemb,size_t __size);
char * strncat(char *__dest,char *__src,size_t __n);

#endif
