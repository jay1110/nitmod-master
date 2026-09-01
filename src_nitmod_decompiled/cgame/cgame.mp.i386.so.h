typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned char    dwfenc;
typedef unsigned int    dword;
typedef long long    longlong;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined3;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined6;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef unsigned short    word;
#define unkbyte9   unsigned long long
#define unkbyte10   unsigned long long
#define unkbyte11   unsigned long long
#define unkbyte12   unsigned long long
#define unkbyte13   unsigned long long
#define unkbyte14   unsigned long long
#define unkbyte15   unsigned long long
#define unkbyte16   unsigned long long

#define unkuint9   unsigned long long
#define unkuint10   unsigned long long
#define unkuint11   unsigned long long
#define unkuint12   unsigned long long
#define unkuint13   unsigned long long
#define unkuint14   unsigned long long
#define unkuint15   unsigned long long
#define unkuint16   unsigned long long

#define unkint9   long long
#define unkint10   long long
#define unkint11   long long
#define unkint12   long long
#define unkint13   long long
#define unkint14   long long
#define unkint15   long long
#define unkint16   long long

#define unkfloat1   float
#define unkfloat2   float
#define unkfloat3   float
#define unkfloat5   double
#define unkfloat6   double
#define unkfloat7   double
#define unkfloat9   long double
#define unkfloat11   long double
#define unkfloat12   long double
#define unkfloat13   long double
#define unkfloat14   long double
#define unkfloat15   long double
#define unkfloat16   long double

#define BADSPACEBASE   void
#define code   void

typedef struct eh_frame_hdr eh_frame_hdr, *Peh_frame_hdr;

struct eh_frame_hdr {
    byte eh_frame_hdr_version; // Exception Handler Frame Header Version
    dwfenc eh_frame_pointer_encoding; // Exception Handler Frame Pointer Encoding
    dwfenc eh_frame_desc_entry_count_encoding; // Encoding of # of Exception Handler FDEs
    dwfenc eh_frame_table_encoding; // Exception Handler Table Encoding
};

typedef struct fde_table_entry fde_table_entry, *Pfde_table_entry;

struct fde_table_entry {
    dword initial_loc; // Initial Location
    dword data_loc; // Data location
};

typedef ushort sa_family_t;

typedef void _IO_lock_t;

typedef struct _IO_marker _IO_marker, *P_IO_marker;

typedef struct _IO_FILE _IO_FILE, *P_IO_FILE;

typedef long __off_t;

typedef longlong __quad_t;

typedef __quad_t __off64_t;

typedef ulong size_t;

struct _IO_FILE {
    int _flags;
    char *_IO_read_ptr;
    char *_IO_read_end;
    char *_IO_read_base;
    char *_IO_write_base;
    char *_IO_write_ptr;
    char *_IO_write_end;
    char *_IO_buf_base;
    char *_IO_buf_end;
    char *_IO_save_base;
    char *_IO_backup_base;
    char *_IO_save_end;
    struct _IO_marker *_markers;
    struct _IO_FILE *_chain;
    int _fileno;
    int _flags2;
    __off_t _old_offset;
    ushort _cur_column;
    char _vtable_offset;
    char _shortbuf[1];
    _IO_lock_t *_lock;
    __off64_t _offset;
    void *__pad1;
    void *__pad2;
    void *__pad3;
    void *__pad4;
    size_t __pad5;
    int _mode;
    char _unused2[40];
};

struct _IO_marker {
    struct _IO_marker *_next;
    struct _IO_FILE *_sbuf;
    int _pos;
};

typedef struct stat stat, *Pstat;

typedef ulonglong __u_quad_t;

typedef __u_quad_t __dev_t;

typedef ulong __ino_t;

typedef uint __mode_t;

typedef uint __nlink_t;

typedef uint __uid_t;

typedef uint __gid_t;

typedef long __blksize_t;

typedef long __blkcnt_t;

typedef struct timespec timespec, *Ptimespec;

typedef long __time_t;

struct timespec {
    __time_t tv_sec;
    long tv_nsec;
};

struct stat {
    __dev_t st_dev;
    ushort __pad1;
    __ino_t st_ino;
    __mode_t st_mode;
    __nlink_t st_nlink;
    __uid_t st_uid;
    __gid_t st_gid;
    __dev_t st_rdev;
    ushort __pad2;
    __off_t st_size;
    __blksize_t st_blksize;
    __blkcnt_t st_blocks;
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
    ulong __unused4;
    ulong __unused5;
};

typedef void *__gnuc_va_list;

typedef struct timeval timeval, *Ptimeval;

typedef long __suseconds_t;

struct timeval {
    __time_t tv_sec;
    __suseconds_t tv_usec;
};

typedef struct tm tm, *Ptm;

struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
    long tm_gmtoff;
    char *tm_zone;
};

typedef __time_t time_t;

typedef struct sigaction sigaction, *Psigaction;

typedef union _union_1051 _union_1051, *P_union_1051;

typedef struct siginfo siginfo, *Psiginfo;

typedef struct siginfo siginfo_t;

typedef struct __sigset_t __sigset_t, *P__sigset_t;

typedef void (*__sighandler_t)(int);

typedef union _union_1031 _union_1031, *P_union_1031;

typedef struct _struct_1032 _struct_1032, *P_struct_1032;

typedef struct _struct_1033 _struct_1033, *P_struct_1033;

typedef struct _struct_1034 _struct_1034, *P_struct_1034;

typedef struct _struct_1035 _struct_1035, *P_struct_1035;

typedef struct _struct_1036 _struct_1036, *P_struct_1036;

typedef struct _struct_1037 _struct_1037, *P_struct_1037;

typedef int __pid_t;

typedef union sigval sigval, *Psigval;

typedef union sigval sigval_t;

typedef long __clock_t;

struct _struct_1032 {
    __pid_t si_pid;
    __uid_t si_uid;
};

union sigval {
    int sival_int;
    void *sival_ptr;
};

struct _struct_1034 {
    __pid_t si_pid;
    __uid_t si_uid;
    sigval_t si_sigval;
};

struct _struct_1035 {
    __pid_t si_pid;
    __uid_t si_uid;
    int si_status;
    __clock_t si_utime;
    __clock_t si_stime;
};

struct _struct_1037 {
    long si_band;
    int si_fd;
};

struct _struct_1033 {
    int si_tid;
    int si_overrun;
    sigval_t si_sigval;
};

struct _struct_1036 {
    void *si_addr;
};

union _union_1031 {
    int _pad[29];
    struct _struct_1032 _kill;
    struct _struct_1033 _timer;
    struct _struct_1034 _rt;
    struct _struct_1035 _sigchld;
    struct _struct_1036 _sigfault;
    struct _struct_1037 _sigpoll;
};

struct __sigset_t {
    ulong __val[32];
};

union _union_1051 {
    __sighandler_t sa_handler;
    void (*sa_sigaction)(int, siginfo_t *, void *);
};

struct siginfo {
    int si_signo;
    int si_errno;
    int si_code;
    union _union_1031 _sifields;
};

struct sigaction {
    union _union_1051 __sigaction_handler;
    struct __sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer)(void);
};

typedef uint uint32_t;

typedef uint32_t in_addr_t;

typedef struct _IO_FILE FILE;

typedef struct sockaddr sockaddr, *Psockaddr;

struct sockaddr {
    sa_family_t sa_family;
    char sa_data[14];
};

typedef uint __socklen_t;

typedef __socklen_t socklen_t;

typedef long __fd_mask;

typedef struct __sigset_t sigset_t;

typedef struct fd_set fd_set, *Pfd_set;

struct fd_set {
    __fd_mask fds_bits[32];
};

typedef int __ssize_t;

typedef __ssize_t ssize_t;

typedef int __int32_t;

typedef struct hostent hostent, *Phostent;

struct hostent {
    char *h_name;
    char **h_aliases;
    int h_addrtype;
    int h_length;
    char **h_addr_list;
};

typedef struct evp_pkey_ctx_st evp_pkey_ctx_st, *Pevp_pkey_ctx_st;

struct evp_pkey_ctx_st {
};

typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;

typedef int (*__compar_fn_t)(void *, void *);

typedef enum Elf32_DynTag_x86 {
    DT_NULL=0,
    DT_NEEDED=1,
    DT_PLTRELSZ=2,
    DT_PLTGOT=3,
    DT_HASH=4,
    DT_STRTAB=5,
    DT_SYMTAB=6,
    DT_RELA=7,
    DT_RELASZ=8,
    DT_RELAENT=9,
    DT_STRSZ=10,
    DT_SYMENT=11,
    DT_INIT=12,
    DT_FINI=13,
    DT_SONAME=14,
    DT_RPATH=15,
    DT_SYMBOLIC=16,
    DT_REL=17,
    DT_RELSZ=18,
    DT_RELENT=19,
    DT_PLTREL=20,
    DT_DEBUG=21,
    DT_TEXTREL=22,
    DT_JMPREL=23,
    DT_BIND_NOW=24,
    DT_INIT_ARRAY=25,
    DT_FINI_ARRAY=26,
    DT_INIT_ARRAYSZ=27,
    DT_FINI_ARRAYSZ=28,
    DT_RUNPATH=29,
    DT_FLAGS=30,
    DT_PREINIT_ARRAY=32,
    DT_PREINIT_ARRAYSZ=33,
    DT_RELRSZ=35,
    DT_RELR=36,
    DT_RELRENT=37,
    DT_ANDROID_REL=1610612751,
    DT_ANDROID_RELSZ=1610612752,
    DT_ANDROID_RELA=1610612753,
    DT_ANDROID_RELASZ=1610612754,
    DT_ANDROID_RELR=1879040000,
    DT_ANDROID_RELRSZ=1879040001,
    DT_ANDROID_RELRENT=1879040003,
    DT_GNU_PRELINKED=1879047669,
    DT_GNU_CONFLICTSZ=1879047670,
    DT_GNU_LIBLISTSZ=1879047671,
    DT_CHECKSUM=1879047672,
    DT_PLTPADSZ=1879047673,
    DT_MOVEENT=1879047674,
    DT_MOVESZ=1879047675,
    DT_FEATURE_1=1879047676,
    DT_POSFLAG_1=1879047677,
    DT_SYMINSZ=1879047678,
    DT_SYMINENT=1879047679,
    DT_GNU_XHASH=1879047924,
    DT_GNU_HASH=1879047925,
    DT_TLSDESC_PLT=1879047926,
    DT_TLSDESC_GOT=1879047927,
    DT_GNU_CONFLICT=1879047928,
    DT_GNU_LIBLIST=1879047929,
    DT_CONFIG=1879047930,
    DT_DEPAUDIT=1879047931,
    DT_AUDIT=1879047932,
    DT_PLTPAD=1879047933,
    DT_MOVETAB=1879047934,
    DT_SYMINFO=1879047935,
    DT_VERSYM=1879048176,
    DT_RELACOUNT=1879048185,
    DT_RELCOUNT=1879048186,
    DT_FLAGS_1=1879048187,
    DT_VERDEF=1879048188,
    DT_VERDEFNUM=1879048189,
    DT_VERNEED=1879048190,
    DT_VERNEEDNUM=1879048191,
    DT_AUXILIARY=2147483645,
    DT_FILTER=2147483647
} Elf32_DynTag_x86;

typedef struct Elf32_Sym Elf32_Sym, *PElf32_Sym;

struct Elf32_Sym {
    dword st_name;
    dword st_value;
    dword st_size;
    byte st_info;
    byte st_other;
    word st_shndx;
};

typedef struct Elf32_Phdr Elf32_Phdr, *PElf32_Phdr;

typedef enum Elf_ProgramHeaderType_x86 {
    PT_NULL=0,
    PT_LOAD=1,
    PT_DYNAMIC=2,
    PT_INTERP=3,
    PT_NOTE=4,
    PT_SHLIB=5,
    PT_PHDR=6,
    PT_TLS=7,
    PT_GNU_EH_FRAME=1685382480,
    PT_GNU_STACK=1685382481,
    PT_GNU_RELRO=1685382482
} Elf_ProgramHeaderType_x86;

struct Elf32_Phdr {
    enum Elf_ProgramHeaderType_x86 p_type;
    dword p_offset;
    dword p_vaddr;
    dword p_paddr;
    dword p_filesz;
    dword p_memsz;
    dword p_flags;
    dword p_align;
};

typedef struct GnuBuildId GnuBuildId, *PGnuBuildId;

struct GnuBuildId {
    dword namesz; // Length of name field
    dword descsz; // Length of description field
    dword type; // Vendor specific type
    char name[4]; // Vendor name
    byte hash[20];
};

typedef struct Elf32_Dyn_x86 Elf32_Dyn_x86, *PElf32_Dyn_x86;

struct Elf32_Dyn_x86 {
    enum Elf32_DynTag_x86 d_tag;
    dword d_val;
};

typedef struct Elf32_Rel Elf32_Rel, *PElf32_Rel;

struct Elf32_Rel {
    dword r_offset; // location to apply the relocation action
    dword r_info; // the symbol table index and the type of relocation
};

typedef enum Elf_SectionHeaderType_x86 {
    SHT_NULL=0,
    SHT_PROGBITS=1,
    SHT_SYMTAB=2,
    SHT_STRTAB=3,
    SHT_RELA=4,
    SHT_HASH=5,
    SHT_DYNAMIC=6,
    SHT_NOTE=7,
    SHT_NOBITS=8,
    SHT_REL=9,
    SHT_SHLIB=10,
    SHT_DYNSYM=11,
    SHT_INIT_ARRAY=14,
    SHT_FINI_ARRAY=15,
    SHT_PREINIT_ARRAY=16,
    SHT_GROUP=17,
    SHT_SYMTAB_SHNDX=18,
    SHT_ANDROID_REL=1610612737,
    SHT_ANDROID_RELA=1610612738,
    SHT_GNU_ATTRIBUTES=1879048181,
    SHT_GNU_HASH=1879048182,
    SHT_GNU_LIBLIST=1879048183,
    SHT_CHECKSUM=1879048184,
    SHT_SUNW_move=1879048186,
    SHT_SUNW_COMDAT=1879048187,
    SHT_SUNW_syminfo=1879048188,
    SHT_GNU_verdef=1879048189,
    SHT_GNU_verneed=1879048190,
    SHT_GNU_versym=1879048191
} Elf_SectionHeaderType_x86;

typedef struct Elf32_Shdr Elf32_Shdr, *PElf32_Shdr;

struct Elf32_Shdr {
    dword sh_name;
    enum Elf_SectionHeaderType_x86 sh_type;
    dword sh_flags;
    dword sh_addr;
    dword sh_offset;
    dword sh_size;
    dword sh_link;
    dword sh_info;
    dword sh_addralign;
    dword sh_entsize;
};

typedef struct Elf32_Ehdr Elf32_Ehdr, *PElf32_Ehdr;

struct Elf32_Ehdr {
    byte e_ident_magic_num;
    char e_ident_magic_str[3];
    byte e_ident_class;
    byte e_ident_data;
    byte e_ident_version;
    byte e_ident_osabi;
    byte e_ident_abiversion;
    byte e_ident_pad[7];
    word e_type;
    word e_machine;
    dword e_version;
    dword e_entry;
    dword e_phoff;
    dword e_shoff;
    dword e_flags;
    word e_ehsize;
    word e_phentsize;
    word e_phnum;
    word e_shentsize;
    word e_shnum;
    word e_shstrndx;
};




int _init(EVP_PKEY_CTX *ctx);
void FUN_0001a090(void);
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
void processEntry PM_ReloadClip(void);
void __regparm3 CG_ItemPickup(int param_1);
undefined4 __regparm2 CG_RW_ParseViewType(undefined4 param_1,char *param_2,int param_3);
void __regparm3 CG_ContinueWeaponAnim(uint param_1);
void __x86.get_pc_thunk.bx(void);
void deregister_tm_clones(void);
void register_tm_clones(void);
void __do_global_dtors_aux(void);
void frame_dummy(void);
int BG_StringHashValue(char *param_1);
int BG_StringHashValue_Lwr(char *param_1);
void BG_AnimParseError(char *param_1);
void __regparm2 BG_ParseCommands.isra.0(int *param_1,int param_2,int param_3);
int __regparm3 BG_IndexForString.constprop.4(char *param_1,undefined4 *param_2);
int BG_AnimationForString(char *param_1,int param_2);
int BG_IndexForString(char *param_1,undefined4 *param_2,int param_3);
char * BG_CopyStringIntoBuffer(char *param_1,int param_2,uint param_3,int *param_4);
void BG_InitWeaponStrings(void);
void BG_ParseConditionBits(undefined4 param_1,undefined4 param_2,int param_3,uint *param_4);
undefined4 BG_ParseConditions(undefined4 param_1,int *param_2);
void BG_AnimParseAnimScript(int param_1,undefined4 param_2,undefined4 param_3,int param_4);
undefined4 BG_EvaluateConditions(int param_1,int *param_2);
int * BG_FirstValidItem(int param_1,int *param_2);
int BG_PlayAnim(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6,int param_7,int param_8);
void BG_PlayAnimName(undefined4 param_1,int param_2,char *param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7);
uint BG_ExecuteCommand(int param_1,int param_2,short *param_3,int param_4,int param_5,int param_6);
uint BG_AnimScriptAnimation(int param_1,int param_2,uint param_3,undefined4 param_4);
undefined4 BG_AnimScriptCannedAnimation(int param_1,int param_2);
undefined4 BG_AnimScriptEvent(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5);
int BG_GetAnimString(int param_1,int param_2);
void BG_UpdateConditionValue(int param_1,int param_2,undefined4 param_3,int param_4);
int BG_GetConditionValue(int param_1,int param_2,int param_3);
undefined4 BG_GetConditionBitFlag(int param_1,int param_2,undefined4 param_3);
void BG_SetConditionBitFlag(int param_1,int param_2,undefined4 param_3);
void BG_ClearConditionBitFlag(int param_1,int param_2,undefined4 param_3);
int BG_GetAnimScriptAnimation(int param_1,int param_2,int param_3,int param_4);
undefined4 BG_GetAnimationForIndex(int param_1,int param_2);
void BG_AnimUpdatePlayerStateConditions(int *param_1);
undefined4 BG_RAG_ParseError(undefined4 param_1,char *param_2);
void BG_ClearAnimationPool(void);
undefined4 BG_R_RegisterAnimationGroup(undefined4 param_1,int param_2);
undefined4 BG_LoadCampaignSave(undefined4 param_1,int *param_2,char *param_3);
undefined4 BG_StoreCampaignSave(undefined4 param_1,undefined4 *param_2,char *param_3);
undefined4 BG_PCF_ParseError(undefined4 param_1,char *param_2);
undefined4 BG_ParseCharacterFile(undefined4 param_1,int param_2);
undefined1 * BG_GetCharacter(int param_1,int param_2);
undefined1 * BG_GetCharacterForPlayerstate(int param_1);
void BG_ClearCharacterPool(void);
undefined1 * BG_FindFreeCharacter(undefined4 param_1);
undefined1 * BG_FindCharacter(undefined4 param_1);
void __x86.get_pc_thunk.cx(void);
void BG_GetFromTable(int param_1);
int * BG_FindItemForWeapon(int param_1);
int BG_FindClipForWeapon(int param_1);
int BG_FindAmmoForWeapon(int param_1);
uint BG_AkimboFireSequence(int param_1,int param_2,int param_3);
bool BG_IsAkimboWeapon(int param_1);
bool BG_IsAkimboSideArm(int param_1,int param_2);
undefined4 BG_AkimboSidearm(int param_1);
int * BG_FindItem(undefined4 param_1);
int * BG_FindItemForClassName(undefined4 param_1);
undefined4 BG_WeaponInWolfMP(undefined4 param_1);
undefined4 SkillForClass(int param_1);
int BG_GrenadesForClass(int param_1,int param_2);
char BG_GrenadeTypeForTeam(int param_1);
void BG_CalculateSpline_r(int param_1,float *param_2,undefined4 *param_3,float param_4);
bool BG_PlayerTouchesItem(int param_1,int param_2,int param_3);
undefined4 BG_TraverseSpline(float *param_1,int *param_2);
undefined4 BG_RaySphereIntersection(float param_1,float *param_2,float *param_3,float *param_4,float *param_5);
void BG_LinearPathOrigin2(float param_1,int *param_2,float *param_3,float *param_4);
void BG_ComputeSegments(int param_1);
void BG_EvaluateTrajectory(undefined4 *param_1,int param_2,float *param_3,int param_4,int param_5);
void BG_EvaluateTrajectoryDelta(undefined4 *param_1,int param_2,float *param_3);
void BG_GetMarkDir(float *param_1,int param_2,float *param_3);
void BG_AddPredictableEventToPlayerstate(undefined4 param_1,undefined4 param_2,int param_3);
byte BG_GetPrimaryWeaponForPlayerState(int param_1);
void BG_PlayerStateToEntityState(int param_1,undefined4 *param_2,undefined4 param_3,int param_4);
uint BG_DuplicateWeapon(uint param_1);
int * BG_ValidStatWeapon(uint param_1);
int BG_WeaponForMOD(int param_1);
undefined1 * BG_Find_PathCorner(undefined4 param_1);
void BG_AddPathCorner(undefined4 param_1,undefined4 *param_2);
undefined1 * BG_Find_Spline(undefined4 param_1);
undefined1 * BG_AddSplinePath(undefined4 param_1,undefined1 *param_2,undefined4 *param_3);
void BG_AddSplineControl(int param_1,undefined4 param_2);
longdouble BG_SplineLength(undefined4 param_1);
void BG_BuildSplinePaths(void);
undefined1 * BG_GetSplineData(int param_1,uint *param_2);
int BG_MaxAmmoForWeapon(int param_1,int param_2);
bool BG_AddMagicAmmo(int param_1,int param_2,int param_3,int param_4);
uint BG_CanItemBeGrabbed(int param_1,int param_2,undefined4 param_3);
void BG_CreateRotationMatrix(undefined4 param_1,int param_2);
void BG_TransposeMatrix(undefined4 *param_1,undefined4 *param_2);
void BG_RotatePoint(float *param_1,float *param_2);
void PC_SourceWarning(undefined4 param_1,char *param_2);
void PC_SourceError(undefined4 param_1,char *param_2);
undefined4 PC_Float_Parse(undefined4 param_1,float *param_2);
undefined4 PC_Color_Parse(undefined4 param_1,int param_2);
undefined4 PC_Vec_Parse(undefined4 param_1,int param_2);
undefined4 PC_Int_Parse(undefined4 param_1,int *param_2);
bool PC_String_Parse(undefined4 param_1,undefined4 *param_2);
void PC_String_tolower(char *param_1);
bool PC_String_ParseNoAlloc(undefined4 param_1,undefined4 param_2,undefined4 param_3);
byte BG_simpleWeaponState(int param_1);
int BG_cleanName(char *param_1,char *param_2,int param_3,int param_4);
void BG_setCrosshair(char *param_1,float *param_2,float param_3,undefined4 param_4);
bool BG_isLightWeaponSupportingFastReload(uint param_1);
bool BG_IsScopedWeapon(int param_1);
void BG_InitLocations(float *param_1,float *param_2);
undefined1 * BG_GetLocationString(float *param_1);
void BG_ClipVelocity(float *param_1,float *param_2,float *param_3,float param_4);
bool BG_BBoxCollision(float *param_1,float *param_2,float *param_3,float *param_4);
undefined4 BG_FootstepForSurface(uint param_1);
bool BG_CheckCharge(int *param_1);
void ConcatArgs(int param_1);
undefined4 Nit_RemoveWordInString(char *param_1,char *param_2);
void nitrox_AddPredictableDamage(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4);
void __regparm3 PM_StartWeaponAnim(uint param_1);
void PM_DropTimers(void);
void PM_Friction(void);
void PM_SetWaterLevel(void);
void PM_SetMovementDir(void);
longdouble __regparm2 PM_CmdScale.isra.0(char param_1,char param_2,char param_3);
void __regparm2 PM_TraceAllLegs.constprop.8(int param_1,float *param_2,float *param_3);
void PM_CheckDuck(void);
void PM_WaterMove(void);
void PM_AirMove(void);
void __regparm3 PM_BeginWeaponReload(int param_1);
longdouble Com_GetFlamethrowerRange(void);
void PM_AddEvent(undefined4 param_1);
void PM_AddEventExt(undefined4 param_1,undefined4 param_2);
bool PM_IdleAnimForWeapon(int param_1);
undefined4 PM_AltSwitchFromForWeapon(void);
int PM_AltSwitchToForWeapon(int param_1);
int PM_AttackAnimForWeapon(int param_1);
undefined4 PM_LastAttackAnimForWeapon(int param_1);
int PM_ReloadAnimForWeapon(int param_1);
undefined4 PM_RaiseAnimForWeapon(int param_1);
undefined4 PM_DropAnimForWeapon(int param_1);
void PM_AddTouchEnt(int param_1);
void PM_ContinueWeaponAnim(uint param_1);
void PM_ClipVelocity(float *param_1,float *param_2,float *param_3,float param_4);
void PM_TraceLegs(int *param_1,float *param_2,float *param_3,float *param_4,int param_5,int param_6,code *param_7,undefined4 param_8,uint param_9);
void PM_TraceHead(undefined4 param_1,undefined4 param_2,float *param_3,undefined4 param_4,int param_5,code *param_6,undefined4 param_7,uint param_8);
void PM_TraceAllLegs(int param_1,undefined4 param_2,float *param_3,float *param_4);
void PM_GroundTrace(void);
void PM_TraceAll(int param_1,float *param_2,float *param_3);
void PM_BeginWeaponChange(int param_1,int param_2,int param_3);
void PM_CheckForReload(int param_1);
void PM_WeaponUseAmmo(int param_1,int param_2);
undefined4 PM_WeaponAmmoAvailable(int param_1);
bool PM_WeaponClipEmpty(undefined4 param_1);
void PM_CoolWeapons(void);
void PM_AdjustAimSpreadScale(void);
uint PM_AltFire(void);
void PM_Weapon(void);
bool PM_AltFiring(int param_1);
void PM_UpdateLean(int param_1,int param_2,int param_3);
void PM_UpdateFlyLean(int param_1,float param_2);
void PM_UpdateViewAngles(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5);
void PM_CheckLadderMove(void);
void PM_LadderMove(void);
void PM_Sprint(void);
void PM_CheckAttack(void);
void PmoveSingle(int *param_1);
uint Pmove(int *param_1);
void PmovePredict(int *param_1,undefined4 param_2);
undefined1 * BG_GetPlayerClassInfo(int param_1,uint param_2);
undefined1 * BG_PlayerClassForPlayerState(int param_1);
bool BG_ClassHasWeapon(int param_1,int param_2);
bool BG_WeaponIsPrimaryForClassAndTeam(int param_1,int param_2,int param_3);
char * BG_TeamName(int param_1);
char * BG_ShortClassnameForNumber(undefined4 param_1);
char * BG_ClassnameForNumber(undefined4 param_1);
char * BG_ClassnameForNumber_Filename(undefined4 param_1);
undefined4 BG_ClassSkillForClass(uint param_1);
bool PM_SlideMove(int param_1);
void PM_StepSlideMove(undefined4 param_1);
undefined4 BG_SS_ParseError(undefined4 param_1,char *param_2);
void BG_ClearScriptSpeakerPool(void);
undefined4 BG_NumScriptSpeakers(void);
int BG_GetIndexForSpeaker(int param_1);
undefined1 * BG_GetScriptSpeaker(int param_1);
undefined4 BG_SS_DeleteSpeaker(int param_1);
undefined4 BG_SS_StoreSpeaker(int param_1);
undefined4 BG_LoadSpeakerScript(undefined4 param_1);
undefined4 BG_WeapStatForWeapon(int param_1);
undefined4 BG_GetStatGoombas(int param_1);
undefined4 BG_SetStatGoombas(int param_1,undefined4 param_2);
undefined4 BG_GetStatBestSpree(int param_1);
undefined4 BG_SetStatBestSpree(int param_1,undefined4 param_2);
undefined4 BG_GetKillSpree(int param_1);
undefined4 BG_SetKillSpree(int param_1,undefined4 param_2);
undefined4 BG_AdjustKillSpree(int param_1,int param_2);
undefined4 BG_AdjustGoombas(int param_1,int param_2);
void CG_GenerateTracemap(void);
undefined4 BG_LoadTraceMap(undefined4 param_1,float *param_2,float *param_3);
longdouble BG_GetSkyHeightAtPoint(float *param_1);
longdouble BG_GetSkyGroundHeightAtPoint(float *param_1);
longdouble BG_GetGroundHeightAtPoint(float *param_1);
undefined4 BG_GetTracemapGroundFloor(void);
void etpro_FinalizeTracemapClamp(int *param_1,int *param_2);
undefined4 BG_RW_ParseError(undefined4 param_1,char *param_2);
undefined4 __regparm3 BG_ParseWeaponConfig(undefined4 param_1,int param_2);
undefined4 __regparm2 BG_RW_ParseDefinition(undefined4 param_1,int param_2,int param_3);
undefined4 __regparm1 BG_RegisterWeaponFromWeaponFile(int param_1,undefined4 param_2,int param_3);
void BG_RegisterWeapon(uint param_1,int param_2);
undefined1 * in_word_set(byte *param_1,uint param_2);
undefined4 nitrox_GetTokenForString(char *param_1);
bool nitrox_CreateDirectory(undefined4 param_1);
undefined1 *BG_BuildFilePath(char *param_1,undefined4 param_2,undefined4 param_3,undefined1 *param_4,undefined4 param_5);
uint BG_IsFile(char *param_1);
uint BG_IsDirectory(char *param_1);
bool BG_DeleteFile(char *param_1);
bool BG_RenameFile(char *param_1,char *param_2);
int CG_EffectGust(void);
undefined4 CG_SnowParticleGenerate(float *param_1,float *param_2);
undefined4 CG_RainParticleGenerate(float *param_1,float *param_2,float param_3);
undefined4 CG_SnowParticleCheckVisible(float *param_1);
undefined4 CG_RainParticleCheckVisible(float *param_1);
void CG_SnowParticleRender(float *param_1);
void CG_RainParticleRender(float *param_1);
undefined4 CG_AtmosphericKludge(void);
void CG_EffectParse(undefined4 param_1);
void CG_AddAtmosphericEffects(void);
undefined4 CG_RegisterCharacter(undefined4 param_1,int param_2);
int CG_CharacterForClientinfo(int param_1,int param_2);
void CG_CharacterForPlayerstate(int param_1);
void CG_RegisterPlayerClasses(void);
void __regparm1 CG_DrawGrid.constprop.8(int param_1,float param_2,float param_3,float param_4,float param_5);
undefined4 CG_CommandCentreSpawnPointClick.part.3(void);
int __regparm2 CG_DrawSpawnPointInfo.constprop.5(int param_1,int param_2,int param_3,int param_4,int *param_5);
void CG_TransformToCommandMapCoord(float *param_1,float *param_2);
int CG_CurLayerForZ(int param_1);
void CG_TransformAutomapEntity(void);
void CG_AdjustAutomapZoom(int param_1);
void CG_ParseMapEntity(int *param_1,int *param_2,undefined4 param_3);
void CG_ParseMapEntityInfo(int param_1,int param_2);
bool CG_DisguiseMapCheck(int param_1);
void CG_DrawMapEntity(int param_1,float param_2,float param_3,float param_4,float param_5,byte param_6,int *param_7,int param_8,int param_9,int param_10);
void CG_DrawExpandedAutoMap(void);
int CG_DrawSpawnPointInfo(int param_1,int param_2,int param_3,int param_4,int param_5,int *param_6,int param_7);
void CG_DrawMortarMarker(int param_1,int param_2,int param_3,int param_4,undefined4 param_5,int *param_6);
void CG_DrawMap(float param_1,float param_2,float param_3,float param_4,undefined4 param_5,int *param_6,int param_7,undefined4 param_8,int param_9);
void CG_DrawAutoMap(void);
undefined4 * CG_ScanForCommandCentreEntity(void);
undefined4 CG_PlayerSelected(void);
undefined4 CG_CommandCentreLayersClick(void);
undefined4 CG_CommandCentreSpawnPointClick(void);
void CG_CommandCentreClick(int param_1);
void CG_CommandMap_SetHighlightText(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void CG_CommandMap_DrawHighlightText(void);
void CG_ToggleAutomap_f(void);
void CG_ResetMaxSpeed_f(void);
void CG_QuickMessage_f(void);
void CG_dumpStats_f(void);
void CG_ForceTapOut_f(void);
void CG_currentTime_f(void);
void nitrox_MinimizeET_f(void);
void CG_Viewpos_f(void);
void CG_autoRecord_f(void);
void CG_SayPlayerClass_f(void);
void CG_keyOn_f(void);
void CG_ResetTimer_f(void);
void CG_TimerSet_f(void);
void CG_SetWeaponCrosshair_f(void);
void nitmod_PrintCGS(void);
void CG_CPM_f(void);
void CG_UndoSpeaker_f(void);
void CG_ModifySpeaker_f(void);
void CG_AutomapZoomOut_f(void);
void CG_AutomapZoomIn_f(void);
void CG_SelectBuddy_f(void);
void CG_FTSayPlayerClass_f(void);
void CG_MessageSend_f(void);
void CG_StatsUp_f(void);
void CG_topshotsUp_f(void);
void CG_ScoresUp_f(void);
void nitrox_GlobalStatsCmd_f(void);
void CG_AutomapExpandDown_f(void);
void CG_AutomapExpandUp_f(void);
void CG_LimboMenu_f(void);
void CG_keyOff_f(void);
void CG_ClassMenu_f(void);
void CG_QuickFireteamAdmin_f(void);
void CG_topshotsDown_f(void);
void CG_ScoresDown_f(void);
void CG_StatsDown_f(void);
void CG_autoScreenShot_f(void);
void CG_vstrDown_f(void);
void CG_vstrUp_f(void);
void CG_TeamVoiceChat_f(void);
void CG_VoiceChat_f(void);
void CG_MessageMode_f(void);
void CG_DumpSpeaker_f(void);
void CG_EditSpeakers_f(void);
void CG_QuickFireteams_f(void);
void CG_BuddyVoiceChat_f(void);
void CG_Class_f(void);
undefined4 nitrox_ClassNumForLetter(char *param_1);
void CG_QuickFireteamMessage_f(void);
void CG_wStatsDown_f(void);
void CG_wStatsUp_f(void);
void CG_toggleSpecHelp_f(void);
undefined4 CG_ConsoleCommand(void);
void CG_InitConsoleCommands(void);
void CG_parseMapVoteListInfo(void);
void CG_parseMapVoteTally(void);
int CG_SortPlayersByXP(int *param_1,int *param_2);
void CG_TeamDebriefingMapWinner_Draw(void);
void CG_Debriefing_ChatEdit_Draw(int param_1);
void CG_Debriefing_PlayerTime_Draw(int param_1);
void CG_Debriefing2TeamSkillHeaders_Draw(int param_1);
void CG_DebriefingPlayerWeaponStats_Draw(int param_1);
void CG_Debriefing_ChatBox_Draw(int param_1);
void CG_Debriefing_PlayerHitReg_Draw(int param_1);
void CG_TeamDebriefingMapList_Draw(int param_1);
void CG_DebriefingPlayerList_Draw(int param_1);
void CG_MapVoteList_Draw(int param_1);
void CG_DebriefingXPHeader_Draw(undefined4 param_1);
undefined4 CG_Debriefing_QCButton_KeyDown(undefined4 param_1,int param_2);
void CG_Debriefing_ChatEditFinish(int param_1);
void CG_TeamDebriefingOutcome_Draw(int param_1);
undefined4 CG_Debriefing_NextButton_KeyDown(undefined4 param_1,int param_2);
undefined4 CG_TeamDebriefingMapList_KeyDown(int param_1,int param_2);
undefined4 CG_Debriefing2_Maps_KeyDown(int param_1,int param_2);
undefined4 CG_MapVote_VoteButton_KeyDown(undefined4 param_1,int param_2);
undefined4 CG_Debriefing_ReadyButton_KeyDown(undefined4 param_1,int param_2);
undefined4 CG_MapVote_MultiVoteButton_KeyDown(int param_1,int param_2);
undefined4 CG_Debriefing_Scrollbar_KeyUp(int param_1,int param_2);
void CG_TeamDebriefingMapShot_Draw(int param_1);
undefined4 CG_Debriefing_ChatButton_KeyDown(undefined4 param_1,int param_2);
undefined4 CG_MapVoteList_KeyDown(undefined4 param_1,int param_2);
undefined4 CG_DebriefingPlayerList_KeyDown(undefined4 param_1,int param_2);
int __regparm3 CG_TeamDebriefing_CalcXP.constprop.18(int param_1,int param_2);
void CG_Debriefing_PlayerName_Draw(int param_1);
void CG_Debriefing_PlayerRank_Draw(int param_1);
void CG_Debriefing_PlayerACC_Draw(int param_1);
void CG_Debriefing_PlayerXP_Draw(int param_1);
void CG_DebriefingTitle_Draw(int param_1);
void CG_Debriefing_PlayerMedals_Draw(int param_1);
void CG_PanelButtonsRender_Window(int param_1);
void CG_Debriefing_NextButton_Draw(int param_1);
void CG_PanelButtonsRender_Button(int param_1);
void CG_Debriefing_ChatButton_Draw(int param_1);
void CG_Debriefing_ReadyButton_Draw(int param_1);
void CG_Debriefing_PlayerSkills_Draw(int param_1);
void CG_MapVote_VoteButton_Draw(int param_1);
void CG_ChatPanel_Setup(void);
void CG_Debriefing_Startup(void);
void CG_Debriefing_Shutdown(void);
void CG_Debriefing_InfoRequests(void);
undefined4 CG_Debriefing_Draw(void);
void CG_MapVote_SetSelectedMap(int param_1);
int CG_Debriefing_GetNextWeaponStat(int param_1);
void CG_Debriefing_TimeToString(float param_1);
char * CG_Debriefing_FullRankNameForClientInfo(int param_1);
undefined * CG_Debriefing_RankNameForClientInfo(int param_1);
void CG_Debriefing_ParseWeaponAccuracies(void);
void CG_Debriefing_ParsePlayerKillsDeaths(void);
void CG_Debriefing_ParseWeaponStats(void);
void CG_Debriefing_ParseHitRegions(void);
undefined4 CG_Debriefing_ServerCommand(undefined4 param_1);
undefined4 CG_Debriefing_ScrollGetMax(int param_1);
int CG_Debriefing_ScrollGetCount(int param_1);
undefined4 CG_Debriefing_ScrollGetOffset(int param_1);
void CG_Debriefing_ScrollSetOffset(int param_1,undefined4 param_2);
int CG_Debriefing_ScrollGetBarRect(int param_1,undefined4 *param_2);
void CG_Debriefing_ScrollCheckOffset(int param_1);
void CG_Debriefing_Scrollbar_Draw(int param_1);
undefined4 CG_Debriefing_Scrollbar_KeyDown(int param_1,int param_2);
void CG_Debriefing_MouseEvent(int param_1,int param_2);
void CG_Debriefing_KeyEvent(int param_1,int param_2);
int CG_Debriefing_GetSelectedClientInfo(void);
void CG_Debrieing_SetSelectedClient(int param_1);
longdouble CG_Debriefing_CalcCampaignProgress(void);
int CG_TeamDebriefing_CalcXP(int param_1,int param_2,int param_3);
void CG_TeamDebriefingTeamSkillXP_Draw(int param_1);
void CG_TeamDebriefingTeamXP_Draw(int param_1);
void CG_PanelButtonsRender_Button_Ext(float *param_1,int param_2);
void CG_MapVote_MultiVoteButton_Draw(int param_1);
void CG_PanelButtonsRender_Window_Ext(float *param_1,int param_2,int param_3,int param_4,undefined4 param_5,int param_6);
char * CG_Debreifing2_WinStringForTeam(int param_1);
int CG_Debriefing_FindWinningTeamForMap(void);
undefined4 CG_Debriefing_FindWinningTeamForPos(int param_1);
void CG_Debreifing2_Maps_Draw(int param_1);
void CG_Debreifing2_MissionTitle_Draw(int param_1);
void CG_Debriefing2TeamSkillXP_Draw(int param_1);
void CG_Debreifing2_Mission_Draw(int param_1);
undefined4 CG_Debriefing_FindOveralWinningTeam(void);
int CG_Debriefing_FindWinningTeam(void);
void CG_DrawFlashFade(void);
void CG_DrawBinocReticle(void);
void CG_DrawAnnouncement(void);
void CG_DrawObjectiveInfo(void);
void CG_Coronas.part.4(void);
int __regparm2 CG_Text_Width_Ext.constprop.17(byte *param_1,int param_2,float param_3);
void __regparm2 CG_Text_Paint_Ext.constprop.18(undefined4 *param_1,byte *param_2,float param_3,float param_4,float param_5,float param_6,int param_7,int param_8);
void CG_DrawCrosshair(void);
void CG_DrawBannerPrint(void);
void CG_DrawCenterString(void);
void CG_DrawDemoRecording.part.3(void);
void __regparm2 CG_Text_Paint_Centred_Ext.constprop.15(undefined4 *param_1,byte *param_2,float param_3,float param_4,float param_5,float param_6,int param_7);
void CG_DrawPlayerStatus(void);
void CG_Text_SetActiveFont(undefined4 param_1);
int CG_Text_Width_Ext(byte *param_1,float param_2,size_t param_3,int param_4);
int CG_Text_Width(byte *param_1,float param_2,size_t param_3);
int CG_Text_Height_Ext(byte *param_1,float param_2,size_t param_3,int param_4);
int CG_Text_Height(byte *param_1,float param_2,size_t param_3);
void CG_Text_PaintChar_Ext(undefined4 param_1,undefined4 param_2,float param_3,float param_4,float param_5,float param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10,undefined4 param_11);
void CG_Text_Paint_Ext(float param_1,float param_2,float param_3,float param_4,undefined4 *param_5,byte *param_6,float param_7,size_t param_8,int param_9,int param_10);
void CG_Text_Paint_Centred_Ext(void);
void CG_Text_Paint(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8);
int CG_DrawField(int param_1,int param_2,char *param_3,int param_4,int param_5,int param_6,int param_7,int param_8);
longdouble CG_DrawTime(float param_1,int param_2);
void CG_AddLagometerFrameInfo(void);
void CG_AddLagometerSnapshotInfo(undefined4 *param_1);
void CG_DrawDisconnect(undefined4 param_1);
longdouble CG_DrawLagometer(float param_1);
void CG_DrawUpperRight(void);
char * CG_PickupItemText(int param_1);
char * CG_PickupItemTextShort(int param_1);
void CG_DrawLivesLeft(void);
void CG_CenterPrint(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void CG_PrintAnnouncement(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4);
void CG_ScanForCrosshairMine(int param_1);
void CG_ScanForCrosshairDynamite(undefined4 *param_1);
void CG_CheckForCursorHints(void);
int CG_CrosshairClientMaxHealth(void);
void CG_DrawCrosshairNames(void);
int CG_CalculateReinfTime_Float(int param_1);
int CG_CalculateReinfTime(int param_1);
void CG_ObjectivePrint(undefined4 param_1,undefined4 param_2);
void CG_DrawTimedMenus(void);
void CG_DrawCompassIcon(float param_1,float param_2,float param_3,float param_4,float *param_5,float *param_6,undefined4 param_7,float param_8,int param_9);
bool CG_CheckDisguise(void);
int CG_ClassSkillForPosition(int param_1,int param_2);
void CG_DrawSkillLevels(void);
void CG_DrawActivePowerups(void);
void CG_InitStatsDebug(void);
void CG_StatsDebugAddText(byte *param_1);
void CG_DrawDemoRecording(void);
void CG_DrawOnScreenNames(void);
void CG_BannerPrint(undefined4 param_1);
void nitrox_DrawPopup(void);
void CG_StartShakeCamera(float param_1);
void CG_ShakeCamera(void);
void CG_Coronas(void);
void CG_DrawMiscGamemodels(void);
undefined4 nitrox_DrawGlobalStats(void);
void CG_DrawMissileCamera(float *param_1);
void CG_DrawAnnouncer(void);
void CG_DrawActive(int param_1);
void CG_AddAnnouncer(int param_1,int param_2,undefined4 param_3,int param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9);
void __x86.get_pc_thunk.dx(void);
void __regparm2 CG_DrawStringExt3.constprop.0(int param_1,int param_2,byte *param_3,undefined4 *param_4);
void CG_HudPlacement(undefined4 param_1);
void CG_AdjustFrom640(float *param_1,float *param_2,float *param_3,float *param_4);
void CG_FillRect(float param_1,float param_2,float param_3,float param_4,undefined4 param_5);
void CG_FillRectGradient(float param_1,float param_2,float param_3,float param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7);
void CG_FilledBar(float param_1,float param_2,float param_3,float param_4,float *param_5,float *param_6,undefined4 *param_7,float param_8,uint param_9);
void CG_HorizontalPercentBar(float param_1,float param_2,float param_3,float param_4,float param_5);
void CG_DrawSides(float param_1,float param_2,float param_3,float param_4,float param_5);
void CG_DrawTopBottom(float param_1,float param_2,float param_3,float param_4,float param_5);
void CG_DrawSides_NoScale(float param_1,float param_2,float param_3,float param_4,float param_5);
void CG_DrawTopBottom_NoScale(float param_1,float param_2,float param_3,float param_4,float param_5);
void CG_DrawRect(float param_1,float param_2,float param_3,float param_4,float param_5,undefined4 param_6);
void CG_DrawRect_FixedBorder(float param_1,float param_2,float param_3,float param_4,int param_5,undefined4 param_6);
void CG_DrawPicST(float param_1,float param_2,float param_3,float param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9);
void CG_AdjustFrom640FullScreen(float *param_1,float *param_2,float *param_3,float *param_4);
void CG_DrawPicFullScreen(float param_1,float param_2,float param_3,float param_4,undefined4 param_5);
void CG_FillRectFullScreen(float param_1,float param_2,float param_3,float param_4,undefined4 param_5);
void CG_DrawPic(float param_1,float param_2,float param_3,float param_4,undefined4 param_5);
void CG_DrawRotatedPic(float param_1,float param_2,float param_3,float param_4,undefined4 param_5,undefined4 param_6);
void CG_DrawChar(int param_1,int param_2,int param_3,int param_4,uint param_5);
void CG_DrawChar2(int param_1,int param_2,int param_3,int param_4,uint param_5);
void CG_DrawStringExt(int param_1,int param_2,byte *param_3,undefined4 *param_4,int param_5,int param_6,int param_7,int param_8,int param_9);
void CG_DrawStringExt_Shadow(int param_1,int param_2,byte *param_3,undefined4 *param_4,int param_5,int param_6,int param_7,int param_8,int param_9);
void CG_DrawStringExt2(void);
void CG_DrawStringExt3(int param_1,int param_2,byte *param_3,undefined4 *param_4,int param_5,int param_6,int param_7,int param_8,int param_9);
void CG_DrawBigString(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void CG_DrawBigStringColor(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void CG_DrawBigString2(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void CG_DrawBigStringColor2(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void CG_DrawSmallString(int param_1,int param_2,byte *param_3,undefined4 param_4);
void CG_DrawSmallStringColor(int param_1,int param_2,byte *param_3,undefined4 param_4);
void CG_DrawTinyStringColor(int param_1,int param_2,byte *param_3,undefined4 param_4);
int CG_DrawStrlen(char *param_1);
void CG_TileClear(void);
undefined4 * CG_FadeColor(int param_1,int param_2);
void CG_ColorForHealth(undefined4 *param_1);
uint CG_BubbleTrail(float *param_1,float *param_2,undefined4 param_3,float param_4);
void CG_SmokePuff(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,float param_4,float param_5,float param_6,undefined4 param_7,float param_8,int param_9,int param_10,undefined4 param_11,undefined4 param_12);
void CG_SpawnEffect(void);
int CG_MakeExplosion(float *param_1,float *param_2,undefined4 param_3,undefined4 param_4,int param_5,int param_6);
void CG_AddBloodTrails(float *param_1,float *param_2,int param_3,int param_4,int param_5,float param_6);
void CG_Bleed(float *param_1,int param_2);
void CG_LaunchGib(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,int param_5,float param_6,undefined4 param_7);
void CG_LoseACC(int param_1,float *param_2,int param_3,undefined4 param_4,int param_5);
int CG_GetOriginForTag(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,float *param_5,int param_6);
void CG_GibPlayer(undefined4 *param_1,float *param_2,float *param_3);
void CG_SparklerSparks(undefined4 *param_1,int param_2);
longdouble lt_random(int param_1,int param_2);
longdouble lt_crandom(int param_1,int param_2);
void CG_ProjectedSpotLight(float *param_1,float *param_2);
void CG_RumbleEfx(float param_1,float param_2);
void InitSmokeSprites(void);
undefined4 CG_SpawnSmokeSprite(int param_1,float param_2);
void CG_RenderSmokeGrenadeSmoke(int param_1,int param_2);
void CG_AddSmokeSprites(void);
void __regparm3 CG_Bomb(int param_1);
int __regparm2 CG_DrawMineMarkerFlag.isra.0(int param_1,int param_2,undefined4 param_3,undefined4 *param_4);
void __regparm3 CG_Missile(int param_1);
void __regparm3 CG_InterpolateEntityPosition.part.3(int param_1);
void __regparm3 CG_EntityEffects(undefined4 *param_1);
void __regparm3 CG_Cabinet.part.6(int param_1,int param_2);
void CG_PositionEntityOnTag(int param_1,int param_2,undefined4 param_3,undefined4 param_4,float *param_5);
void CG_PositionRotatedEntityOnTag(int param_1,int param_2,undefined4 param_3);
void CG_SetEntitySoundPosition(undefined4 *param_1);
void CG_AddLightstyle(undefined4 *param_1);
bool CG_PlayerSeesItem(int param_1,int param_2,undefined4 param_3);
void __regparm3 CG_Item(int param_1);
void CG_Beam_2(int param_1);
void __regparm3 CG_ProcessEntity(int *param_1);
void CG_Beam(int param_1);
undefined4 CG_Cabinet(undefined4 param_1,uint param_2);
void CG_SetupCabinets(void);
undefined4 CG_AddLinkedEntity(int param_1,int param_2,int param_3);
void CG_AdjustPositionForMover(float *param_1,int param_2,undefined4 param_3,undefined4 param_4,float *param_5,float *param_6);
void CG_CalcEntityLerpPositions(int *param_1);
void CG_AddCEntity(int *param_1);
undefined4 CG_AddCEntity_Filter(int param_1);
undefined4 __regparm3 CG_AddEntityToTag.part.10(int *param_1);
undefined4 CG_AddEntityToTag(int param_1);
void __regparm3 CG_Mover_PostProcess.part.11(int param_1);
void CG_Mover_PostProcess(int param_1);
void CG_AddPacketEntities(void);
void CGRefEntityToTag(int param_1,undefined4 *param_2);
void CGTagToRefEntity(int param_1,undefined4 *param_2);
void CG_AttachBitsToTank(int param_1,undefined2 *param_2,undefined2 *param_3,undefined2 *param_4,undefined2 *param_5,undefined2 *param_6,float *param_7,undefined4 param_8,int param_9);
void __regparm2 CG_BotDebugLine(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3);
void __regparm3 CG_StartFootStepSound.isra.0.part.1(undefined4 *param_1,undefined4 param_2);
void __regparm3 CG_MortarImpact.part.2(int param_1,float *param_2);
void CG_PrecacheFXSounds(void);
void CG_RubbleFx(undefined4 *param_1,float *param_2,int param_3,int param_4,int param_5,int param_6,int param_7,float param_8,float param_9);
void CG_Rubble(int param_1,undefined4 param_2,undefined4 param_3,int param_4);
void CG_Explodef(undefined4 *param_1,float *param_2,int param_3,int param_4,int param_5,int param_6,int param_7);
void CG_Explode(int param_1,undefined4 param_2,undefined4 param_3,int param_4);
void CG_Effect(int param_1,float *param_2,float *param_3);
void CG_Shard(int param_1,undefined4 *param_2,float *param_3);
void CG_ShardJunk(undefined4 param_1,undefined4 *param_2,float *param_3);
void CG_Debris(int param_1,undefined4 *param_2,undefined4 *param_3);
void CG_MortarImpact(int param_1,float *param_2,int param_3,int param_4);
void CG_MortarMiss(int param_1,undefined4 *param_2);
undefined4 CG_GetGameSound(int param_1);
undefined4 CG_CustomSound(int param_1);
void CG_EntityEvent(int *param_1,undefined4 *param_2);
void CG_CheckEvents(int param_1);
uint CG_SortFireTeam(int *param_1,int *param_2);
void CG_SortClientFireteam(void);
void CG_ParseFireteams(void);
undefined4 CG_IsOnSameFireteam(int param_1,int param_2);
undefined4 CG_IsOnFireteam(int param_1);
int CG_IsFireTeamLeader(int param_1);
int CG_SortedFireTeamPlayerForPosition(int param_1);
undefined4 SkillNumForClass(uint param_1);
int weaponIconScale(int param_1);
void CG_DrawFireTeamOverlay(float *param_1);
undefined4 CG_FireteamHasClass(int param_1,int param_2);
undefined * CG_BuildSelectedFirteamString(void);
void CG_Fireteams_MenuTitleText_Draw(int param_1);
undefined8 __regparm3 CG_CountFireteamsByTeam.part.0(int param_1);
uint CG_CountFireteamsByTeam(int param_1);
void CG_DrawFireteamsByTeam(int param_1,int param_2);
int CG_CountPlayersSF(void);
int CG_CountPlayersNF(void);
int CG_PlayerSFFromPos(int param_1,int *param_2);
int CG_PlayerNFFromPos(int param_1,int *param_2);
void CG_DrawPlayerSF(int param_1,int *param_2);
void CG_DrawPlayerNF(int param_1,int *param_2);
void CG_Fireteams_MenuText_Draw(int param_1);
void CG_Fireteams_Setup(void);
void CG_Fireteams_KeyHandling(uint param_1,int param_2);
void CG_Fireteams_Draw(void);
undefined4 CG_FireteamCheckExecKey(uint param_1,int param_2);
void CG_FlameLerpVec(float *param_1,float *param_2,float param_3,float *param_4);
void CG_FlameAdjustSpeed(int param_1,float param_2);
void CG_ClearFlameChunks(void);
void CG_SpawnFlameChunk(int *param_1);
void CG_FireFlameChunks(int *param_1,float *param_2,undefined4 *param_3,float param_4,int param_5,int param_6);
void CG_FreeFlameChunk(int *param_1);
void CG_MergeFlameChunks(int param_1,int *param_2);
int CG_FlameCalcOrg(int param_1,int param_2,float *param_3);
void CG_MoveFlameChunk(int param_1);
void CG_FlameDamage(void);
void CG_AddFlameSpriteToScene(int param_1,float param_2,float param_3);
void CG_AddFlameToScene(int param_1);
void CG_GenerateShaders(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,int param_8,int param_9);
void CG_InitFlameChunks(void);
void CG_AddFlameChunks(void);
void CG_UpdateFlamethrowerSounds(void);
void CG_DemoHelpDraw.part.1(void);
void CG_LoadingString(char *param_1);
void CG_DrawInformation(undefined4 param_1);
void CG_ShowHelp_On(int *param_1);
void CG_ShowHelp_Off(int *param_1);
void CG_DemoClick(int param_1,int param_2);
void CG_GameStatsDraw(void);
void CG_TopShotsDraw(void);
void CG_DemoHelpDraw(void);
char * CG_getBindKeyName(undefined4 param_1,char *param_2,undefined4 param_3);
void CG_SpecHelpDraw(void);
void CG_DrawOverlays(void);
void CG_LimboPanelRenderText_NoLMS(undefined4 param_1);
void CG_LimboPanelRenderText_SkillsText(undefined4 param_1);
void CG_LimboPanel_RenderObjectiveBack(int param_1);
void CG_LimboPanel_Filter_Draw(int param_1);
void CG_LimboPanel_RenderMedal(int param_1);
void CG_LimboPanel_RenderSkillIcon(int param_1);
void CG_LimboPanel_NameEditFinish(int param_1);
void CG_LimboPanel_RenderTeamButton(int param_1);
void CG_LimboPanel_ClassBar_Draw(int param_1);
void CG_LimboPanel_RenderCommandMap(int param_1);
undefined4 CG_LimboPanel_PlusButton_KeyDown(undefined4 param_1,int param_2);
undefined4 CG_LimboPanel_MinusButton_KeyDown(undefined4 param_1,int param_2);
undefined4 CG_LimboPanel_Filter_KeyDown(int param_1,int param_2);
undefined4 CG_LimboPanel_BriefingButton_KeyDown(undefined4 param_1,int param_2);
void CG_LimboPanel_BriefingButton_Draw(int param_1);
undefined4 CG_LimboPanel_CancelButton_KeyDown(undefined4 param_1,int param_2);
void __regparm2 CG_DrawLimboPlayerHead.part.6(float *param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,int param_6,int param_7);
void CG_LimboPanel_RenderHead(int param_1);
void CG_LimboPanel_WeaponLights(int param_1);
undefined4 CG_LimboPanel_WeaponPanel_KeyDown(int param_1,int param_2);
void CG_LimboPanel_RenderLight(int param_1);
undefined4 CG_LimboPanel_ObjectiveText_KeyDown(int param_1,int param_2);
void CG_LimboPanel_Border_Draw(int param_1);
void CG_LimboPanel_RenderObjectiveText(int param_1);
long CG_LimboPanel_GetMaxObjectives(void);
bool CG_LimboPanel_RenderLight_GetValue(int param_1);
undefined4 CG_DrawLimboPlayerHead(undefined4 param_1,int param_2);
void CG_DrawBorder(float param_1,float param_2,float param_3,float param_4,int param_5,int param_6);
void CG_LimboPanel_RenderCounterNumber(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,float param_5,undefined4 param_6,undefined4 param_7,int param_8);
int CG_LimboPanel_RenderCounter_ValueForButton(int param_1);
uint CG_LimboPanel_RenderCounter(int param_1);
int CG_LimboPanel_RenderCounter_RollTimeForButton(int param_1);
undefined4 CG_LimboPanel_RenderCounter_MaxChangeForButton(int param_1);
char CG_LimboPanel_RenderCounter_NumRollers(int param_1);
undefined4 CG_LimboPanel_RenderCounter_CountsDown(int param_1);
bool CG_LimboPanel_RenderCounter_CountsUp(int param_1);
undefined4 CG_LimboPanel_RenderCounter_StartSet(int param_1);
bool CG_LimboPanel_RenderCounter_IsReversed(int param_1);
void CG_LimboPanel_RenderCounter_GetShaders(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4);
void CG_LimboPanel_Init(void);
undefined4 CG_LimboPanel_Draw(void);
void CG_LimboPanel_KeyHandling(int param_1,int param_2);
void CG_LimboPanel_GetWeaponCardIconData(uint param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,undefined4 *param_5,undefined4 *param_6,undefined4 *param_7,undefined4 *param_8);
undefined4 CG_LimboPanel_GetTeam(void);
int CG_LimboPanel_GetRealTeam(void);
undefined4 CG_LimboPanel_GetClass(void);
void CG_LimboPanel_GetCharacter(void);
void CG_LimboPanel_GetPlayerClass(void);
void CG_LimboPanel_SetSelectedWeaponNumForSlot(int param_1,undefined4 param_2);
void CG_LimboPanel_RequestObjective(void);
undefined8 CG_LimboPanel_ClassCount(int param_1);
uint CG_LimboPanel_TeamCount(int param_1);
bool CG_IsHeavyWeapon(int param_1);
bool CG_LimboPanel_ClassIsDisabled(int param_1);
void CG_LimboPanel_RenderClassButton(int param_1);
bool CG_LimboPanel_RealWeaponIsDisabled(int param_1);
void CG_LimboPanel_WeaponPanel_DrawWeapon(float *param_1,int param_2,int param_3,undefined4 param_4,int param_5);
int CG_LimboPanel_WeaponCount_ForSlot(int param_1);
void CG_LimboPanel_WeaponIsDisabled(void);
undefined4 CG_LimboPanel_GetSelectedWeaponNum(void);
int CG_LimboPanel_GetWeaponForNumber(int param_1,int param_2,int param_3);
int CG_LimboPanel_WeaponCount(void);
void CG_LimboPanel_SendSetupMsg(int param_1);
undefined4 CG_LimboPanel_OkButton_KeyDown(undefined4 param_1,int param_2);
int CG_LimboPanel_GetSelectedWeaponForSlot(int param_1);
int CG_LimboPanel_GetSelectedWeapon(void);
undefined4 CG_LimboPanel_WeaponLights_KeyDown(int param_1,int param_2);
undefined4 CG_LimboPanel_TeamButton_KeyDown(int param_1,int param_2);
void CG_LimboPanel_GetSelectedWeaponStat(void);
void CG_LimboPanel_RequestWeaponStats(void);
undefined4 CG_LimboPanel_ClassButton_KeyDown(int param_1,int param_2);
void CG_LimboPanel_Setup(void);
void CG_LimboPanel_SetSelectedWeaponNum(int param_1);
void CG_LimboPanel_WeaponPanel(int param_1);
undefined4 CG_LimboPanel_WeaponPanel_KeyUp(int param_1,int param_2);
int CG_LimboPanel_GetWeaponNumberForPos(int param_1);
void CG_LoadPanel_RenderMissionDescriptionText(int param_1);
void CG_LoadPanel_RenderCampaignNameText(int param_1);
void CG_LoadPanel_RenderCampaignTypeText(int param_1);
void nitrox_LoadPanel_LoadingBar(void);
char * CG_LoadPanel_GameTypeName(undefined4 param_1);
void CG_DrawConnectScreen(int param_1);
void CG_LoadPanel_KeyHandling(undefined4 param_1,undefined4 param_2);
undefined4 CG_LoadPanel_ContinueButtonKeyDown(undefined4 param_1,int param_2);
float * CG_GetLocation(float *param_1);
char * CG_GetLocationMsg(float *param_1);
void CG_LoadLocations(void);
void CG_InitLocalEntities(void);
void CG_FreeLocalEntity(int *param_1);
undefined1 * CG_FindLocalEntity(int param_1,int param_2);
int * CG_AllocLocalEntity(void);
void CG_BloodTrail(int param_1);
void CG_FragmentBounceMark(int param_1,int param_2);
void CG_FragmentBounceSound(int param_1,int param_2);
void CG_ReflectVelocity(int param_1,int *param_2);
void CG_AddEmitter(int param_1);
void CG_AddFragment(int *param_1);
void CG_AddMovingTracer(int param_1);
void CG_AddSparkElements(int *param_1);
void CG_AddFuseSparkElements(int param_1);
void CG_AddBloodElements(int param_1);
void CG_AddDebrisElements(int *param_1);
void CG_AddFadeRGB(int param_1);
void CG_AddConstRGB(int param_1);
void CG_AddLocalEntities(void);
int CG_FeederCount(float param_1);
undefined4 CG_FeederItemImage(void);
void CG_FeederSelection(float param_1,int param_2);
char * CG_FeederItemText(float param_1,int param_2,int param_3,undefined4 *param_4);
longdouble CG_Cvar_Get(undefined4 param_1);
void CG_Text_PaintWithCursor(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9);
void CG_RunCinematicFrame(undefined4 param_1);
void CG_DrawCinematic(undefined4 param_1,float param_2,float param_3,float param_4,float param_5);
void CG_StopCinematic(undefined4 param_1);
void CG_PlayCinematic(undefined4 param_1,float param_2,float param_3,float param_4,float param_5);
void CG_RegisterSounds(void);
void CG_setClientFlags.part.0(void);
void CG_Error.constprop.3(void);
void CG_ConfigStringCopy(uint param_1,char *param_2,undefined4 param_3);
void GetMacAddress(void);
void CG_RegisterCvars(void);
void CG_UpdateCvars(void);
void CG_setClientFlags(void);
undefined4 CG_CrosshairPlayer(void);
void CG_Printf(char *param_1);
void Com_Printf(char *param_1);
void CG_Error(char *param_1);
void Com_Error(undefined4 param_1,char *param_2);
undefined1 * CG_Argv(undefined4 param_1);
void CG_nameCleanFilename(byte *param_1,byte *param_2,uint param_3);
void CG_generateFilename(void);
int CG_findClientNum(char *param_1);
void CG_printConsoleString(undefined4 param_1);
void CG_LoadObjectiveData(void);
void CG_SetupDlightstyles(void);
int CG_ConfigString(uint param_1);
void CG_StartMusic(void);
void CG_QueueMusic(void);
void CG_LoadHudMenu(void);
void CG_AssetCache(void);
bool CG_execFile(undefined4 param_1);
undefined4 CG_BackupProfile(void);
void CG_RestoreProfile(void);
void CG_Init(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5);
uint vmMain(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6);
void CG_Shutdown(void);
void CG_CheckExecKey(undefined4 param_1);
void jP_SetHUDColors(void);
undefined4 CG_GetGameModel(int param_1);
void CG_AddToTeamChat(char *param_1,int param_2);
void CG_GetRealTime(void);
void CG_WriteToLog(char *param_1);
void CG_InitMarkPolys(void);
void CG_FreeMarkPoly(int *param_1);
int * CG_AllocMark(void);
void CG_ImpactMark(undefined4 param_1,float *param_2,float *param_3,float param_4,float param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,int param_10);
void CG_AddMarks(void);
undefined4 CG_DescriptionForCampaign(void);
undefined4 CG_NameForCampaign(void);
undefined4 CG_FindCampaignInFile(undefined4 param_1,undefined4 param_2,int param_3);
undefined4 CG_FindArenaInfo(undefined4 param_1,undefined4 param_2,int param_3);
void CG_LocateCampaign(void);
void CG_LocateArena(void);
void CG_FitTextToWidth_Ext(char *param_1,undefined4 param_2,float param_3,uint param_4,undefined4 param_5);
void CG_DrawPlayerWeaponIcon(float *param_1,undefined4 param_2,int param_3,undefined4 *param_4);
void CG_DrawCursorhint(float *param_1);
longdouble CG_GetValue(void);
void CG_DrawWeapStability(undefined4 *param_1);
void CG_DrawWeapHeat(undefined4 *param_1);
void CG_MouseEvent(int param_1,int param_2);
void CG_EventHandling(int param_1,int param_2);
void CG_KeyEvent(undefined4 param_1,int param_2);
int CG_ClientNumFromName(undefined4 param_1);
void CG_GetTeamColor(undefined4 *param_1);
void __regparm2 CG_ParticleBubble.part.0(int param_1,float *param_2,int param_3,int param_4,float param_5,undefined4 param_6);
void CG_ClearParticles(void);
void CG_AddParticleToScene(int param_1,float *param_2);
void CG_AddParticles(void);
void CG_ParticleSnowFlurry(int param_1,int param_2);
void CG_ParticleSnow(int param_1,float *param_2,int param_3,int param_4,float param_5,undefined4 param_6);
undefined4 CG_ParticleBubble(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void CG_ParticleSmoke(int param_1,int param_2);
void CG_ParticleBulletDebris(undefined4 *param_1,undefined4 *param_2,int param_3);
void CG_ParticleDirtBulletDebris(undefined4 *param_1,undefined4 *param_2,int param_3);
void CG_ParticleDirtBulletDebris_Core(undefined4 *param_1,undefined4 *param_2,int param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7);
void CG_ParticleExplosion(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,int param_4,int param_5,int param_6,int param_7);
void CG_ParticleExplosionTrail(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,int param_4,int param_5,int param_6,int param_7);
void CG_AddParticleShrapnel(void);
undefined4 CG_NewParticleArea(undefined4 param_1);
void CG_SnowLink(int param_1,int param_2);
void CG_ParticleImpactSmokePuffExtended(int param_1,undefined4 *param_2,int param_3,int param_4,int param_5,int param_6,undefined4 param_7,float param_8);
void CG_ParticleImpactSmokePuff(int param_1,undefined4 *param_2);
void CG_Particle_Bleed(int param_1,undefined4 *param_2,undefined4 param_3,int param_4,int param_5);
void CG_Particle_OilParticle(int param_1,undefined4 *param_2,float *param_3,int param_4,undefined4 param_5);
void CG_Particle_OilSlick(int param_1,int param_2);
void CG_OilSlickRemove(int param_1);
undefined4 ValidBloodPool(float *param_1);
void CG_ParticleBloodCloud(int param_1,undefined4 *param_2,undefined4 param_3);
void CG_ParticleBloodCloudZombie(int param_1,undefined4 *param_2,undefined4 param_3);
void CG_ParticleSparks(undefined4 *param_1,undefined4 *param_2,int param_3,float param_4,float param_5,float param_6);
void CG_ParticleDust(int param_1,float *param_2,float *param_3);
void CG_ParticleMisc(int param_1,undefined4 *param_2,int param_3,int param_4);
void __regparm2 CG_PlayerFloatSprite(int *param_1,undefined4 param_2,int param_3,int param_4);
void __regparm2 CG_SwingAngles(float *param_1,int *param_2,float param_3,float param_4,float param_5,float param_6);
bool CG_EntOnFire(int *param_1);
bool CG_IsCrouchingAnim(undefined4 param_1,uint param_2);
void CG_ParseTeamXPs(int param_1);
void CG_PlayerClassForClientinfo(int param_1,int param_2);
void CG_RunLerpFrame(undefined4 param_1,int param_2,undefined4 *param_3,uint param_4,float param_5);
void CG_SetLerpFrameAnimationRate(int param_1,undefined4 param_2,int param_3,uint param_4);
void __regparm2 CG_RunLerpFrameRate.part.2(undefined4 param_1,int *param_2,int param_3,int *param_4,int param_5);
void CG_RunLerpFrameRate(undefined4 param_1,int *param_2,int param_3,int *param_4,int param_5);
void CG_ClearLerpFrameRate(int param_1,undefined4 param_2,undefined4 *param_3,uint param_4);
void CG_SetLerpFrameAnimationRateCorpse(int param_1,int param_2,uint param_3);
void CG_RunLerpFrameRateCorpse(undefined4 param_1,int *param_2,uint param_3,int param_4);
void CG_PredictLean(int param_1,int param_2,int param_3,int param_4);
void __regparm2 CG_PlayerAngles(undefined1 *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 param_4);
bool CG_WorldCoordToScreenCoordFloat(float *param_1,float *param_2,float *param_3);
void CG_AddOnScreenText(undefined4 param_1,float *param_2);
void CG_PlayerFloatText(int param_1,undefined4 param_2,int param_3);
void CG_AddWoundedPlayer(undefined4 param_1,float *param_2);
void CG_WoundedPlayerFloatName(int *param_1,undefined4 param_2,int param_3);
void CG_AddRefEntityWithPowerups(int param_1,undefined4 param_2,int param_3,int *param_4,undefined4 *param_5);
undefined1 * vtosf(float *param_1);
void CG_AnimPlayerConditions(int param_1,int *param_2);
void CG_ResetPlayerEntity(undefined4 *param_1);
void CG_NewClientInfo(int param_1,char *param_2);
void CG_GetBleedOrigin(undefined4 *param_1,undefined4 *param_2,int param_3);
undefined4 CG_GetTag(int param_1,undefined4 param_2,float *param_3);
undefined4 CG_GetWeaponTag(int param_1,undefined4 param_2,float *param_3);
void CG_SetHudHeadLerpFrameAnimation(int param_1,int param_2,uint param_3);
void CG_ClearHudHeadLerpFrame(int param_1,undefined4 *param_2,uint param_3);
void CG_RunHudHeadLerpFrame(int param_1,undefined4 *param_2,uint param_3,float param_4);
void CG_Player(uint *param_1);
void CG_HudHeadAnimation(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,undefined4 *param_5,uint param_6);
void CG_CheckAmmo(void);
void CG_DamageFeedback(int param_1,int param_2,int param_3);
char * CG_TeamnameForNumber(int param_1);
void CG_Respawn(int param_1);
void CG_CheckPlayerstateEvents(int param_1,int param_2);
void CG_CheckChangedPredictableEvents(int param_1);
void CG_CheckLocalSounds(int param_1,int param_2);
void CG_TransitionPlayerState(undefined4 *param_1,undefined4 *param_2);
undefined1 * CG_PB_FindFreePolyBuffer(int param_1,int param_2,int param_3);
void CG_PB_ClearPolyBuffers(void);
void CG_PB_RenderPolyBuffers(void);
void CG_InitPMGraphics(void);
void CG_InitPM(void);
void CG_AddToListFront(int *param_1,int param_2);
void CG_UpdatePMLists(void);
undefined4 * CG_FindFreePMItem2(void);
undefined4 * CG_FindFreePMItem(void);
void CG_AddPMItem(uint param_1,char *param_2,uint param_3,uint *param_4);
void CG_PMItemBigSound(int *param_1);
void CG_AddPMItemBig(int param_1,undefined4 param_2,int param_3,undefined4 *param_4);
void CG_DrawPMItems(void);
void CG_DrawPMItemsBig(void);
undefined4 CG_GetPMItemText(int param_1);
void CG_PlayPMItemSound(int param_1);
undefined4 CG_GetPMItemIcon(int param_1);
void nitrox_AddGraphicObituary(char *param_1,undefined4 param_2,char *param_3,undefined4 *param_4,undefined4 param_5);
void CG_TraceCapsule_World(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7);
uint CG_PointContents(undefined4 param_1,int param_2);
void __regparm3 CG_InterpolatePlayerState(int param_1);
void CG_Trace(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,int param_6,undefined4 param_7);
void CG_TraceCapsule(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,int param_6,undefined4 param_7);
void CG_BuildSolidList(void);
void CG_Trace_World(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7);
undefined4 CG_PredictionOk(int param_1,int param_2);
void CG_PredictPlayerState(void);
uint CG_SortPlayersByKD(int *param_1,int *param_2);
void __regparm2 WM_DrawClientScore_Small.isra.1(int param_1,int param_2,int *param_3,float param_4,int param_5);
void WM_TimeToString(float param_1);
void CG_DrawBottom_NoScale(undefined4 param_1,float param_2,undefined4 param_3,float param_4,float param_5);
undefined4 cf_draw(float param_1,float param_2,undefined4 param_3,int param_4);
int WM_DrawObjectives(int param_1,int param_2,int param_3);
void WM_DrawClientScore(int param_1,int param_2,int *param_3,undefined4 param_4,float param_5,int param_6);
int WM_TeamScoreboard(int param_1,int param_2,int param_3,float param_4,int param_5,int param_6);
undefined4 CG_DrawScoreboard(void);
void __regparm3 CG_printFile.part.0(undefined4 param_1);
void CG_printFile(undefined4 param_1);
undefined4 __regparm3 CG_ParseVoiceChats.constprop.4(undefined4 param_1,int param_2);
void CG_parseWeaponStats_cmd.constprop.5(void);
void CG_ParseServerinfo(char *param_1);
void InitSkillLevelStructure(int param_1);
void CG_UpdateSkills(undefined4 param_1);
int CG_OIDInfoForEntityNum(int param_1);
void CG_ParseOIDInfo(int param_1);
void CG_ParseOIDInfos(void);
void CG_ParseSpawns(void);
void CG_ParseReinforcementTimes(char *param_1);
void CG_SetConfigValues(void);
void CG_ShaderStateChanged(void);
void nitrox_ConfigStringModified(void);
void nitrox_ProcessNewCS(uint param_1);
void CG_AddToNotify(char *param_1);
undefined4 CG_ParseVoiceChats(undefined4 param_1,int param_2,int param_3);
void CG_LoadVoiceChats(void);
undefined4 CG_GetVoiceChat(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4,int *param_5,float param_6);
undefined1 * CG_VoiceChatListForClient(int param_1);
void CG_PlayVoiceChat(int *param_1);
void CG_PlayBufferedVoiceChats(void);
void CG_AddBufferedVoiceChat(int param_1);
void CG_VoiceChatLocal(int param_1,undefined4 param_2,uint param_3,undefined4 param_4,undefined4 param_5,undefined4 *param_6,float param_7);
void CG_VoiceChat(int param_1);
undefined4 * CG_LocalizeServerCommand(char *param_1);
void CG_ParseWarmup(void);
void CG_ParseWolfinfo(void);
void CG_topshotsParse_cmd(void);
void CG_ParseWeaponStats(void);
void CG_ParsePortalPos(void);
void CG_parseWeaponStatsGS_cmd(void);
void CG_parseWeaponStats_cmd(code *param_1);
void CG_wstatsParse_cmd(void);
void CG_parseBestShotsStats_cmd(int param_1,code *param_2);
void CG_parseTopShotsStats_cmd(int param_1,code *param_2);
void CG_scores_cmd(void);
void CG_dumpStats(void);
bool Info_NextKey(undefined4 *param_1,char *param_2);
bool nitrox_NextKey(undefined4 *param_1,char *param_2);
void CG_ServerCommand(void);
void CG_ExecuteNewServerCommands(int param_1);
void CG_TransitionEntity(int param_1);
void CG_SetInitialSnapshot(int param_1);
void CG_ProcessSnapshots(void);
void CG_SpeakerEditor_NoiseEditFinish(int param_1);
void CG_SpeakerEditor_TargetnameEditFinish(int param_1);
void CG_SpeakerEditor_Back(int param_1);
void CG_SpeakerInfo_Text(int param_1);
void CG_SpeakerEditor_LocInfo(int param_1);
void CG_SpeakerEditor_RenderEdit(int param_1);
void CG_SpeakerEditor_RenderButton(int param_1);
void CG_SpeakerEditor_RenderDropdown(int param_1);
undefined4 CG_SpeakerEditor_Dropdown_KeyDown(undefined4 param_1,int param_2);
undefined4 CG_SpeakerEditor_Ok_KeyDown(undefined4 param_1,int param_2);
undefined4 CG_SpeakerEditor_Cancel_KeyDown(undefined4 param_1,int param_2);
undefined4 CG_SpeakerEditor_Delete_KeyDown(undefined4 param_1,int param_2);
void CG_SpeakerEditor_WaitEditFinish(int param_1);
void CG_SpeakerEditor_RandomEditFinish(int param_1);
void CG_SpeakerEditor_VolumeEditFinish(int param_1);
void CG_SpeakerEditor_RangeEditFinish(int param_1);
undefined4 CG_SpeakerEditor_NoiseEdit_KeyDown(int param_1,uint param_2);
undefined4 CG_SpeakerEditor_Looped_KeyUp(int param_1,int param_2);
undefined4 CG_SpeakerEditor_Broadcast_KeyUp(int param_1,int param_2);
undefined4 CG_SpeakerEditor_Cancel_KeyUp(int param_1,int param_2);
void CG_RenderScriptSpeakers(void);
void CG_SoundLoadSoundFiles(void);
int CG_SoundScriptPrecache(char *param_1);
undefined4 CG_SoundPickOldestRandomSound(int param_1,undefined4 param_2,undefined4 param_3);
void CG_AddBufferedSoundScript(undefined4 param_1);
void CG_UpdateBufferedSoundScripts(void);
undefined4 CG_SoundPlaySoundScript(char *param_1,undefined4 param_2,undefined4 param_3,int param_4);
void CG_SoundPlayIndexedScript(int param_1);
void CG_SoundInit(void);
undefined4 CG_SaveSpeakersToScript(void);
undefined4 CG_SpeakerEditor_Ok_KeyUp(int param_1,int param_2);
undefined4 CG_SpeakerEditor_Delete_KeyUp(int param_1,int param_2);
void CG_AddLineToScene(undefined4 *param_1,undefined4 *param_2,float *param_3);
void CG_SetViewanglesForSpeakerEditor(void);
void CG_GetStrFromStrArray(char *param_1,int param_2);
void CG_SpeakerEditorDraw(void);
void CG_SpeakerEditor_KeyHandling(int param_1,int param_2);
void CG_SpeakerEditorMouseMove_Handling(int param_1,int param_2);
void CG_ActivateEditSoundMode(void);
void CG_DeActivateEditSoundMode(void);
void CG_ModifyEditSpeaker(void);
void CG_UndoEditSpeaker(void);
void CG_ToggleActiveOnScriptSpeaker(undefined4 param_1);
void CG_UnsetActiveOnScriptSpeaker(undefined4 param_1);
void CG_SetActiveOnScriptSpeaker(undefined4 param_1);
void CG_AddScriptSpeakers(void);
void SP_trigger_objective_info(void);
void SP_path_corner_2(void);
void SP_info_train_spline_main(void);
void SP_corona(void);
void SP_misc_gamemodel(void);
undefined4 CG_SpawnString(char *param_1,undefined4 param_2,undefined4 *param_3);
int CG_SpawnFloat(char *param_1,char *param_2,float *param_3);
int CG_SpawnInt(char *param_1,char *param_2,long *param_3);
int CG_SpawnVector(char *param_1,undefined4 param_2,int param_3);
int CG_SpawnVector2D(char *param_1,undefined4 param_2,int param_3);
undefined1 * vtos(float *param_1);
void CG_ParseEntityFromSpawnVars(void);
void CG_AddSpawnVarToken(char *param_1);
undefined4 CG_ParseSpawnVars(void);
void SP_worldspawn(void);
void CG_ParseEntitiesFromString(void);
void CG_LoadRankIcons(void);
void dllEntry(undefined4 param_1);
void trap_PumpEventLoop(void);
void trap_Print(undefined4 param_1);
void trap_Error(undefined4 param_1);
void trap_Milliseconds(void);
void trap_Cvar_Register(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void trap_Cvar_Update(undefined4 param_1);
void trap_Cvar_Set(undefined4 param_1,undefined4 param_2);
void trap_Cvar_VariableStringBuffer(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_Cvar_LatchedVariableStringBuffer(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_Argc(void);
void trap_Argv(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_Args(undefined4 param_1,undefined4 param_2);
void trap_FS_FOpenFile(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_FS_Read(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_FS_Write(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_FS_FCloseFile(undefined4 param_1);
void trap_FS_GetFileList(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void trap_FS_Delete(undefined4 param_1);
void trap_SendConsoleCommand(undefined4 param_1);
void trap_AddCommand(undefined4 param_1);
void trap_RemoveCommand(undefined4 param_1);
void trap_SendClientCommand(undefined4 param_1);
void trap_UpdateScreen(void);
void trap_CM_NumInlineModels(void);
void trap_CM_InlineModel(undefined4 param_1);
void trap_CM_TempBoxModel(undefined4 param_1,undefined4 param_2);
void trap_CM_TempCapsuleModel(undefined4 param_1,undefined4 param_2);
void trap_CM_PointContents(undefined4 param_1,undefined4 param_2);
void trap_CM_TransformedPointContents(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void trap_CM_BoxTrace(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7);
void trap_CM_TransformedBoxTrace(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9);
void trap_CM_CapsuleTrace(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7);
void trap_CM_TransformedCapsuleTrace(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9);
void trap_CM_MarkFragments(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7);
void trap_R_ProjectDecal(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7);
void trap_R_ClearDecals(void);
void trap_S_StartSound(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void trap_S_StartSoundVControl(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void trap_S_StartSoundEx(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void trap_S_StartSoundExVControl(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6);
void trap_S_StartLocalSound(undefined4 param_1,undefined4 param_2);
void trap_S_ClearLoopingSounds(void);
void trap_S_ClearSounds(undefined4 param_1);
void trap_S_AddLoopingSound(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void trap_S_AddRealLoopingSound(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6);
void trap_S_StopStreamingSound(undefined4 param_1);
void trap_S_UpdateEntityPosition(undefined4 param_1,undefined4 param_2);
void trap_S_GetVoiceAmplitude(undefined4 param_1);
void trap_S_Respatialize(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void trap_S_GetSoundLength(undefined4 param_1);
void trap_S_GetCurrentSoundTime(void);
void trap_S_StartBackgroundTrack(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_S_FadeBackgroundTrack(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_S_FadeAllSound(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_S_StartStreamingSound(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void trap_R_GetSkinModel(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_R_GetShaderFromModel(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_R_ClearScene(void);
void trap_R_AddRefEntityToScene(int param_1);
void trap_R_AddPolyToScene(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_R_AddPolyBufferToScene(undefined4 param_1);
void trap_R_AddPolysToScene(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void trap_R_AddLightToScene(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8);
void trap_R_AddCoronaToScene(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7);
void trap_R_SetFog(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7);
void trap_R_SetGlobalFog(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6);
void trap_R_RenderScene(undefined4 param_1);
void trap_R_SaveViewParms(void);
void trap_R_RestoreViewParms(void);
void trap_R_SetColor(undefined4 param_1);
void trap_R_DrawStretchPic(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9);
void trap_R_DrawRotatedPic(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10);
void trap_R_DrawStretchPicGradient(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10,undefined4 param_11);
void trap_R_Add2dPolys(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_R_ModelBounds(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_R_LerpTag(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void trap_R_RemapShader(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_GetGlconfig(undefined4 param_1);
void trap_GetGameState(undefined4 param_1);
void trap_GetCurrentSnapshotNumber(undefined4 param_1,undefined4 param_2);
void trap_GetSnapshot(undefined4 param_1,undefined4 param_2);
void trap_GetServerCommand(undefined4 param_1);
void trap_GetCurrentCmdNumber(void);
void trap_GetUserCmd(undefined4 param_1,undefined4 param_2);
void trap_SetUserCmdValue(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void trap_SetClientLerpOrigin(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void testPrintInt(undefined4 param_1,undefined4 param_2);
void testPrintFloat(undefined4 param_1,undefined4 param_2);
void trap_MemoryRemaining(void);
void trap_loadCamera(undefined4 param_1,undefined4 param_2);
void trap_startCamera(undefined4 param_1,undefined4 param_2);
void trap_stopCamera(undefined4 param_1);
void trap_getCameraInfo(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void trap_Key_IsDown(undefined4 param_1);
void trap_Key_GetCatcher(void);
void trap_Key_GetOverstrikeMode(void);
void trap_Key_SetOverstrikeMode(undefined4 param_1);
void trap_Key_KeysForBinding(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_Key_SetCatcher(undefined4 param_1);
void trap_Key_GetKey(undefined4 param_1);
void trap_PC_AddGlobalDefine(undefined4 param_1);
void trap_PC_LoadSource(undefined4 param_1);
void trap_PC_FreeSource(undefined4 param_1);
void trap_PC_ReadToken(undefined4 param_1,undefined4 param_2);
void trap_PC_SourceFileAndLine(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_PC_UnReadToken(undefined4 param_1);
void trap_S_StopBackgroundTrack(void);
void trap_RealTime(undefined4 param_1);
void trap_SnapVector(undefined4 param_1);
void trap_CIN_PlayCinematic(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6);
void trap_CIN_StopCinematic(undefined4 param_1);
void trap_CIN_RunCinematic(undefined4 param_1);
void trap_CIN_DrawCinematic(undefined4 param_1);
void trap_CIN_SetExtents(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void trap_GetEntityToken(undefined4 param_1,undefined4 param_2);
void trap_UI_Popup(undefined4 param_1);
void trap_Key_GetBindingBuf(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_Key_SetBinding(undefined4 param_1,undefined4 param_2);
void trap_Key_KeynumToStringBuf(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_S_RegisterSound(undefined4 param_1);
void trap_R_RegisterModel(undefined4 param_1);
void trap_R_RegisterSkin(undefined4 param_1);
void trap_R_RegisterShader(undefined4 param_1);
void trap_R_RegisterShaderNoMip(undefined4 param_1);
void trap_R_RegisterFont(undefined4 param_1,undefined4 param_2,int param_3);
void trap_CM_LoadMap(undefined4 param_1);
void trap_R_LoadWorldMap(undefined4 param_1);
void trap_R_inPVS(undefined4 param_1,undefined4 param_2);
void trap_GetHunkData(undefined4 param_1,undefined4 param_2);
bool isET260(void);
void trap_SendMessage(undefined4 param_1,undefined4 param_2);
undefined4 trap_MessageStatus(void);
undefined4 trap_R_LoadDynamicShader(undefined4 param_1,undefined4 param_2);
void trap_R_RenderToTexture(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
undefined4 trap_R_GetTextureId(undefined4 param_1);
void trap_R_Finish(void);
void CG_ClearTrails(void);
int * CG_SpawnTrailJunc(int *param_1);
int CG_AddTrailJunc(uint param_1,int param_2,undefined4 param_3,int param_4,int param_5,undefined4 *param_6,int param_7,float param_8,float param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 *param_13,undefined4 *param_14,float param_15,float param_16);
int CG_AddSparkJunc(uint param_1,int param_2,undefined4 param_3,undefined4 *param_4,int param_5,float param_6,float param_7,undefined4 param_8,undefined4 param_9);
int CG_AddSmokeJunc(uint param_1,int param_2,undefined4 param_3,undefined4 *param_4,int param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8);
void CG_FreeTrailJunc(int *param_1);
void CG_KillTrail(undefined4 *param_1);
void CG_AddTrailToScene(int param_1,int param_2,int param_3);
void CG_AddTrails(void);
void __regparm3 CG_DrawSkyBoxPortal.part.0(int param_1);
void CG_TestModel_f(void);
void CG_TestGun_f(void);
void CG_TestModelNextFrame_f(void);
void CG_TestModelPrevFrame_f(void);
void CG_TestModelNextSkin_f(void);
void CG_TestModelPrevSkin_f(void);
void CG_Letterbox(float param_1,float param_2,int param_3);
void CG_OffsetThirdPersonView(void);
void CG_KickAngles(void);
void CG_AdjustZoomVal(float param_1,int param_2);
void CG_ZoomIn_f(void);
void CG_ZoomOut_f(void);
void CG_Zoom(void);
bool CG_CalcFov(void);
void CG_CalcViewValues(void);
char * CG_MustParse(undefined4 param_1,undefined4 param_2);
void CG_ParseSkyBox(void);
void CG_ParseTagConnects(void);
void CG_ParseTagConnect(undefined4 param_1);
undefined4 CG_DrawSkyBoxPortal(undefined4 param_1);
void CG_SetupFrustum(void);
bool CG_CullPoint(float *param_1);
bool CG_CullPointAndRadius(float *param_1,float param_2);
void CG_DrawActiveFrame(int param_1,int param_2,int param_3);
void CG_PanzerFaustEjectBrass(int param_1);
void __regparm3 CG_CalculateWeaponPosition(float *param_1,float *param_2);
void CG_RocketTrail(int param_1);
void CG_DynamiteTrail(int param_1);
void CG_GrenadeTrail(int param_1);
undefined4 __regparm3 CG_ParseWeaponConfig(undefined4 param_1,int param_2);
undefined4 CG_RW_ParseError(undefined4 param_1,char *param_2);
void __regparm3 CG_AddWeaponWithPowerups.isra.1(int param_1);
void __regparm2 CG_AddSparks.part.12(float *param_1,float *param_2,int param_3,int param_4,int param_5,float param_6);
void __regparm2 CG_AddBulletParticles.part.13(float *param_1,float *param_2,int param_3,int param_4,float param_5);
void __regparm2 CG_AddDirtBulletParticles.part.14(undefined4 *param_1,float *param_2,int param_3,int param_4,int param_5,float param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10);
undefined4 __regparm3 CG_RegisterWeaponFromWeaponFile(int param_1,int param_2);
void CG_PyroSmokeTrail(undefined4 *param_1);
void AddLean(undefined4 param_1,float *param_2,float param_3);
void CG_MachineGunEjectBrassNew(int param_1);
void CG_MachineGunEjectBrass(int param_1);
void CG_GetWindVector(float *param_1);
void CG_RailTrail2(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,int param_4,undefined4 param_5);
void __regparm2 CG_RailTrail.part.5(undefined4 param_1,float *param_2,float *param_3,undefined4 param_4);
void __regparm3 CG_DrawHitBoxOnHit.part.11(undefined4 *param_1);
void CG_RailTrail(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3,int param_4,int param_5);
void CG_RegisterWeapon(uint param_1,int param_2);
void CG_RegisterItemVisuals(int param_1);
undefined8 CG_GetPartFramesFromWeap(int param_1,int param_2,int param_3,int param_4,int param_5);
void CG_ClearWeapLerpFrame(int param_1,undefined4 *param_2,uint param_3);
undefined4 CG_WeaponSelectable(int param_1);
undefined4 CG_WeaponIndex(int param_1,int *param_2,undefined4 *param_3);
void CG_SetSniperZoom(int param_1,int param_2);
void CG_PlaySwitchSound(int param_1,int param_2);
void CG_FinishWeaponChange(int param_1,int param_2);
void CG_AltWeapon_f(void);
void CG_NextWeap(int param_1);
void CG_PrevWeap(int param_1);
void CG_LastWeaponUsed_f(void);
void CG_NextWeaponInBank_f(void);
void CG_PrevWeaponInBank_f(void);
void CG_NextWeapon_f(void);
void CG_PrevWeapon_f(void);
bool is_sidearm_smg(void);
void CG_WeaponBank_f(void);
void CG_Weapon_f(void);
void CG_OutOfAmmoChange(int param_1);
void CG_MG42EFX(int *param_1);
void CG_AddPlayerWeapon(float *param_1,int param_2,int *param_3);
void CG_AddViewWeapon(int param_1);
void CG_MortarEFX(int param_1);
void CG_WeaponFireRecoil(undefined4 param_1);
void CG_DrawHitBoxOnHit(int *param_1);
void CG_FireWeapon(int *param_1,int param_2);
undefined4 CG_AddSparks(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
undefined4 CG_AddBulletParticles(undefined4 param_1);
void CG_AddDirtBulletParticles(void);
void CG_AddDebris(undefined4 *param_1,float *param_2,int param_3,int param_4,int param_5);
void CG_WaterRipple(undefined4 param_1,undefined4 *param_2,undefined4 param_3,int param_4,int param_5);
void CG_MissileHitWall(int param_1,int param_2,float *param_3,float *param_4,uint param_5);
void CG_MissileHitWallSmall(undefined4 param_1,undefined4 param_2,float *param_3,float *param_4);
void CG_MissileHitPlayer(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void CG_SpawnTracer(int param_1,float *param_2,float *param_3);
void CG_DrawTracer(float *param_1,float *param_2);
void CG_Tracer(float *param_1,float *param_2,int param_3);
undefined4 CG_CalcMuzzlePoint(int param_1,float *param_2);
void SnapVectorTowards(float *param_1,float *param_2);
void CG_Bullet(float *param_1,int param_2,undefined4 param_3,int param_4,int param_5,int param_6,float param_7);
void CG_createStatsWindow(void);
void CG_windowInit(void);
void CG_windowReset(undefined4 *param_1,int param_2,int param_3);
undefined * CG_windowAlloc(int param_1,int param_2);
void CG_windowFree(undefined *param_1);
void CG_windowCleanup(void);
void CG_demoAviFPSDraw(void);
void CG_demoTimescaleDraw(void);
void CG_windowNormalizeOnText(int param_1);
void CG_windowDraw(void);
void CG_printWindow(undefined4 param_1);
void CG_initStrings(void);
undefined4 CG_addString(int param_1,undefined4 param_2);
void CG_removeStrings(int param_1);
void Q_rand(int *param_1);
uint Q_random(uint *param_1);
longdouble Q_crandom(uint *param_1);
undefined1 ClampChar(int param_1);
int ClampShort(int param_1);
int DirToByte(float *param_1);
void ByteToDir(uint param_1,undefined4 *param_2);
undefined3 ColorBytes3(float param_1,float param_2,float param_3);
undefined4 ColorBytes4(float param_1,float param_2,float param_3,float param_4);
void NormalizeColor(float *param_1,float *param_2);
undefined4 PlaneFromPoints(float *param_1,float *param_2,float *param_3,float *param_4);
void RotatePointAroundVertex(float *param_1,float param_2,float param_3,float param_4,float *param_5);
void vectoangles(float *param_1,float *param_2);
void AnglesToAxis(float *param_1,float *param_2);
void AxisClear(undefined4 *param_1);
void AxisCopy(undefined4 *param_1,undefined4 *param_2);
void ProjectPointOnPlane(float *param_1,float *param_2,float *param_3);
void MakeNormalVectors(float *param_1,float *param_2,float *param_3);
void VectorRotate(float *param_1,float *param_2,float *param_3);
int Q_rsqrt(int param_1);
uint Q_fabs(uint param_1);
longdouble LerpAngle(float param_1,float param_2,float param_3);
void LerpPosition(float *param_1,float *param_2,float param_3,float *param_4);
void AngleSubtract(float param_1,float param_2);
void AnglesSubtract(float *param_1,float *param_2,float *param_3);
longdouble AngleMod(float param_1);
longdouble AngleNormalize2Pi(float param_1);
longdouble AngleNormalize360(float param_1);
uint AngleNormalizeInt(uint param_1);
longdouble AngleNormalize180(float param_1);
longdouble AngleDelta(float param_1,float param_2);
void SetPlaneSignbits(float *param_1);
longdouble RadiusFromBounds(float *param_1,float *param_2);
void ClearBounds(undefined4 *param_1,undefined4 *param_2);
void AddPointToBounds(float *param_1,float *param_2,float *param_3);
bool PointInBounds(float *param_1,float *param_2,float *param_3);
bool VectorCompare(float *param_1,float *param_2);
void VectorNormalize(float *param_1);
void VectorNormalizeFast(float *param_1);
longdouble VectorNormalize2(float *param_1,float *param_2);
void _VectorMA(float *param_1,float param_2,float *param_3,float *param_4);
longdouble _DotProduct(float *param_1,float *param_2);
void _VectorSubtract(float *param_1,float *param_2,float *param_3);
void _VectorAdd(float *param_1,float *param_2,float *param_3);
void _VectorCopy(undefined4 *param_1,undefined4 *param_2);
void _VectorScale(float *param_1,float param_2,float *param_3);
void CrossProduct(float *param_1,float *param_2,float *param_3);
longdouble VectorLength(float *param_1);
longdouble VectorLengthSquared(float *param_1);
longdouble Distance(float *param_1,float *param_2);
longdouble DistanceSquared(float *param_1,float *param_2);
void VectorInverse(float *param_1);
void Vector4Scale(float *param_1,float param_2,float *param_3);
int Q_log2(int param_1);
void MatrixMultiply(float *param_1,float *param_2,float *param_3);
void AngleVectors(float *param_1,float *param_2,float *param_3,float *param_4);
void PerpendicularVector(float *param_1,float *param_2);
void RotatePointAroundVector(float *param_1,float *param_2,float *param_3,float param_4);
void RotateAroundDirection(float *param_1,float param_2);
void GetPerpendicularViewVector(float *param_1,float *param_2,float *param_3,float *param_4);
void ProjectPointOntoVector(float *param_1,float *param_2,float *param_3,float *param_4);
void ProjectPointOntoVectorBounded(float *param_1,float *param_2,float *param_3,float *param_4);
longdouble DistanceFromLineSquared(float *param_1,float *param_2,float *param_3);
longdouble DistanceFromVectorSquared(float *param_1,float *param_2,float *param_3);
longdouble vectoyaw(float *param_1);
void AxisToAngles(int param_1,float *param_2);
longdouble VectorDistance(float *param_1,float *param_2);
longdouble VectorDistanceSquared(float *param_1,float *param_2);
undefined8 __regparm3 COM_ParseExt.constprop.2(int *param_1);
void __regparm3 Info_RemoveKey_Big.part.1(char *param_1,char *param_2);
void __regparm3 Info_RemoveKey.part.0(char *param_1,char *param_2);
void Com_Clamp(void);
void COM_FixPath(char *param_1);
char * COM_SkipPath(char *param_1);
void COM_StripExtension(char *param_1,char *param_2);
void COM_StripFilename(char *param_1,char *param_2);
uint COM_BitCheck(int param_1,uint param_2);
void COM_BitSet(int param_1,uint param_2);
void COM_BitClear(int param_1,uint param_2);
void COM_BackupParseSession(undefined4 *param_1);
void COM_RestoreParseSession(undefined4 *param_1);
undefined4 COM_GetCurrentParseLine(void);
void COM_Parse(void);
void COM_ParseError(char *param_1);
int COM_Compress(char *param_1);
undefined1 * COM_ParseExt(int *param_1,int param_2);
void COM_MatchToken(undefined4 param_1,char *param_2);
void SkipBracedSection_Depth(int *param_1,int param_2);
void SkipBracedSection(int *param_1);
void SkipRestOfLine(undefined4 *param_1);
void Parse1DMatrix(undefined4 param_1,uint param_2,int param_3);
void Parse2DMatrix(undefined4 param_1,int param_2,int param_3,int param_4);
void Parse3DMatrix(undefined4 param_1,int param_2,int param_3,int param_4,int param_5);
bool Q_isprint(int param_1);
bool Q_islower(int param_1);
bool Q_isupper(int param_1);
bool Q_isalpha(uint param_1);
bool Q_isnumeric(int param_1);
bool Q_isalphanumeric(uint param_1);
bool Q_isforfilename(uint param_1);
char * Q_strrchr(char *param_1,char param_2);
void Q_strncpyz(char *param_1,char *param_2,int param_3);
int Q_stricmpn(char *param_1,char *param_2,int param_3);
int Q_strncmp(char *param_1,char *param_2,int param_3);
int Q_stricmp(char *param_1,char *param_2);
char * Q_strlwr(char *param_1);
char * Q_strupr(char *param_1);
void Q_strcat(char *param_1,uint param_2,char *param_3);
int Q_PrintStrlen(char *param_1);
void Q_CleanStr(char *param_1);
undefined4 Q_isBadDirChar(char param_1);
char * Q_CleanDirName(char *param_1);
void Com_sprintf(char *param_1,size_t param_2,char *param_3);
void COM_BeginParseSession(undefined4 param_1);
void va(char *param_1);
void tv(undefined4 param_1,undefined4 param_2,undefined4 param_3);
char * Info_ValueForKey(char *param_1,char *param_2);
undefined4 Info_NextPair(undefined4 *param_1,char *param_2,char *param_3);
void Info_RemoveKey(char *param_1,char *param_2);
void Info_RemoveKey_Big(char *param_1,char *param_2);
bool Info_Validate(char *param_1);
void Info_SetValueForKey(char *param_1,char *param_2,char *param_3);
void Info_SetValueForKey_Big(char *param_1,char *param_2,char *param_3);
undefined1 * Q_StrReplace(uint *param_1,char *param_2,char *param_3);
undefined8 COM_ParseExt_nico(undefined4 *param_1,int param_2);
undefined4 encode64(byte *param_1,char *param_2,int param_3);
void decode64(int param_1);
undefined4 FileExists(undefined4 param_1);
void nitrox_ClampFloat(float *param_1,float param_2,float param_3);
void nitrox_ClampInt(int *param_1,float param_2,float param_3);
undefined4 need_escape(byte *param_1);
byte * escape_string(byte *param_1);
void unescape_string(char *param_1);
void nitrox_stripLeadingSpaces(char *param_1);
void Script_SetTeamColor(int param_1);
void Script_CheckAutoUpdate(void);
void Script_GetAutoUpdate(void);
void Script_Abort(undefined4 param_1,undefined4 *param_2);
undefined4 ItemParse_decoration(int param_1);
undefined4 ItemParse_textasint(int param_1);
undefined4 ItemParse_textasfloat(int param_1);
undefined4 ItemParse_wrapped(int param_1);
undefined4 ItemParse_autowrapped(int param_1);
undefined4 ItemParse_horizontalscroll(int param_1);
undefined4 ItemParse_noToggle(int param_1);
undefined4 MenuParse_popup(int param_1);
undefined4 MenuParse_outOfBounds(int param_1);
undefined4 MenuParse_drawAlwaysOnTop(int param_1);
undefined4 MenuParse_modal(int param_1);
void Scroll_Slider_ThumbFunc(int param_1);
bool ItemParse_name(int param_1,undefined4 param_2);
bool ItemParse_focusSound(int param_1,undefined4 param_2);
bool ItemParse_text(int param_1,undefined4 param_2);
bool ItemParse_group(int param_1,undefined4 param_2);
bool ItemParse_asset_shader(int param_1,undefined4 param_2);
bool ItemParse_background(int param_1,undefined4 param_2);
bool ItemParse_cinematic(int param_1,undefined4 param_2);
bool ItemParse_cvarTest(int param_1,undefined4 param_2);
bool MenuParse_background(int param_1,undefined4 param_2);
bool MenuParse_cinematic(int param_1,undefined4 param_2);
bool MenuParse_soundLoop(int param_1,undefined4 param_2);
bool ItemParse_feeder(int param_1,undefined4 param_2);
bool ItemParse_bordersize(int param_1,undefined4 param_2);
bool ItemParse_textalignx(int param_1,undefined4 param_2);
bool ItemParse_textaligny(int param_1,undefined4 param_2);
bool ItemParse_textscale(int param_1,undefined4 param_2);
undefined4 ItemParse_backcolor(int param_1,undefined4 param_2);
undefined4 ItemParse_forecolor(int param_1,undefined4 param_2);
undefined4 ItemParse_bordercolor(int param_1,undefined4 param_2);
bool ItemParse_special(int param_1,undefined4 param_2);
bool MenuParse_borderSize(int param_1,undefined4 param_2);
undefined4 MenuParse_backcolor(int param_1,undefined4 param_2);
undefined4 MenuParse_forecolor(int param_1,undefined4 param_2);
undefined4 MenuParse_bordercolor(int param_1,undefined4 param_2);
undefined4 MenuParse_focuscolor(int param_1,undefined4 param_2);
undefined4 MenuParse_disablecolor(int param_1,undefined4 param_2);
bool MenuParse_fadeClamp(int param_1,undefined4 param_2);
bool MenuParse_fadeAmount(int param_1,undefined4 param_2);
undefined4 ItemParse_origin(int param_1,undefined4 param_2);
bool ItemParse_style(int param_1,undefined4 param_2);
bool ItemParse_bitflag(int param_1,undefined4 param_2);
bool ItemParse_border(int param_1,undefined4 param_2);
undefined4 ItemParse_visible(int param_1,undefined4 param_2);
bool ItemParse_ownerdraw(int param_1,undefined4 param_2);
bool ItemParse_align(int param_1,undefined4 param_2);
bool ItemParse_textalign(int param_1,undefined4 param_2);
bool ItemParse_textstyle(int param_1,undefined4 param_2);
bool ItemParse_textfont(int param_1,undefined4 param_2);
bool ItemParse_ownerdrawFlag(int param_1,undefined4 param_2);
void ItemParse_settingDisabled(int param_1,undefined4 param_2);
void ItemParse_settingEnabled(int param_1,undefined4 param_2);
void ItemParse_voteFlag(int param_1,undefined4 param_2);
bool MenuParse_fullscreen(int param_1,undefined4 param_2);
bool MenuParse_style(int param_1,undefined4 param_2);
undefined4 MenuParse_visible(int param_1,undefined4 param_2);
bool MenuParse_border(int param_1,undefined4 param_2);
bool MenuParse_ownerdrawFlag(int param_1,undefined4 param_2);
bool MenuParse_ownerdraw(int param_1,undefined4 param_2);
bool MenuParse_fadeCycle(int param_1,undefined4 param_2);
bool MenuParse_itemHotkeyMode(int param_1,undefined4 param_2);
bool ItemParse_outlinecolor(int param_1,undefined4 param_2);
bool MenuParse_outlinecolor(int param_1,undefined4 param_2);
undefined4 * __regparm3 Item_CorrectedTextRect(int param_1);
bool MenuParse_name(int param_1,undefined4 param_2);
uint __regparm3 Item_SettingShow.constprop.35(int param_1);
bool __regparm3 Item_SettingShow.constprop.36(int param_1);
bool MenuParse_rect(int param_1,undefined4 param_2);
bool ItemParse_rect(int param_1,undefined4 param_2);
undefined4 __regparm3 Item_ValidateTooltipData.part.24(int param_1);
bool ItemParse_tooltip(int param_1,undefined4 param_2);
bool ItemParse_tooltipalignx(int param_1,undefined4 param_2);
bool ItemParse_tooltipaligny(int param_1,undefined4 param_2);
undefined4 ItemParse_addColorRangeRel(int param_1,undefined4 param_2);
undefined4 ItemParse_addColorRange(int param_1,undefined4 param_2);
void Script_ExecWolfConfig(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Tooltip_Initialize(int param_1);
void Tooltip_ComputePosition(int param_1);
void Cui_WideRect(float *param_1);
longdouble Cui_WideX(float param_1);
longdouble Cui_WideXoffset(void);
undefined1 * UI_Alloc(int param_1);
void __regparm3 Item_ValidateTypeData.part.21(int param_1);
undefined4 ItemParse_asset_model(int param_1,undefined4 param_2);
bool ItemParse_model_origin(int param_1,undefined4 param_2);
bool ItemParse_model_fovx(int param_1,undefined4 param_2);
bool ItemParse_model_fovy(int param_1,undefined4 param_2);
bool ItemParse_model_rotation(int param_1,undefined4 param_2);
bool ItemParse_model_angle(int param_1,undefined4 param_2);
undefined4 ItemParse_model_animplay(int param_1,undefined4 param_2);
undefined4 ItemParse_notselectable(int param_1);
undefined4 ItemParse_type(int param_1,undefined4 param_2);
bool ItemParse_elementwidth(int param_1,undefined4 param_2);
bool ItemParse_elementheight(int param_1,undefined4 param_2);
bool ItemParse_elementtype(int param_1,undefined4 param_2);
undefined4 ItemParse_columns(int param_1,undefined4 param_2);
bool ItemParse_contextMenu(int param_1,undefined4 param_2);
undefined4 ItemParse_cvar(int param_1,undefined4 param_2);
undefined4 ItemParse_maxChars(int param_1,undefined4 param_2);
undefined4 ItemParse_maxPaintChars(int param_1,undefined4 param_2);
bool ItemParse_cvarFloat(int param_1,undefined4 param_2);
void UI_InitMemory(void);
undefined4 UI_OutOfMemory(void);
char * String_Alloc(char *param_1);
bool ItemParse_textfile(int param_1,undefined4 param_2);
undefined4 ItemParse_cvarStrList(int param_1,undefined4 param_2);
undefined4 ItemParse_cvarFloatList(int param_1,undefined4 param_2);
undefined4 ItemParse_cvarListUndefined(int param_1,undefined4 param_2);
void Script_SetAsset(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Script_ClearCvar(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Script_SetPlayerModel(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Script_SetPlayerHead(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Script_SetBackground(int param_1,undefined4 param_2,undefined4 param_3);
void Script_Exec(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Script_ExecNOW(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Script_Play(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Script_playLooped(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Script_SetColor(int param_1,undefined4 param_2,undefined4 param_3);
void Script_SetCvar(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Script_CopyCvar(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Script_ToggleCvarBit(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void __regparm3 Item_RunScript.constprop.37(int param_1,char *param_2);
void __regparm3 Menu_RunCloseScript.part.10(int param_1);
void Script_CloseAllOtherMenus(int param_1);
void Script_CloseAll(void);
void Script_FadeOutMenu(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Script_FadeInMenu(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void String_Report(void);
void LerpColor(float *param_1,float *param_2,float *param_3,float param_4);
undefined4 Float_Parse(undefined4 param_1,float *param_2);
undefined4 Color_Parse(undefined4 param_1,int param_2);
undefined4 Int_Parse(undefined4 param_1,long *param_2);
bool Rect_Parse(undefined4 param_1,float *param_2);
undefined4 String_Parse(undefined4 param_1,undefined4 *param_2);
bool PC_Char_Parse(undefined4 param_1,undefined1 *param_2);
undefined4 PC_Script_Parse(undefined4 param_1,undefined4 *param_2);
bool ItemParse_onEsc(int param_1,undefined4 param_2);
bool ItemParse_onEnter(int param_1,undefined4 param_2);
bool ItemParse_onFocus(int param_1,undefined4 param_2);
bool ItemParse_leaveFocus(int param_1,undefined4 param_2);
bool ItemParse_mouseEnter(int param_1,undefined4 param_2);
bool ItemParse_mouseExit(int param_1,undefined4 param_2);
bool ItemParse_mouseEnterText(int param_1,undefined4 param_2);
bool ItemParse_mouseExitText(int param_1,undefined4 param_2);
bool ItemParse_action(int param_1,undefined4 param_2);
bool ItemParse_accept(int param_1,undefined4 param_2);
bool ItemParse_enableCvar(int param_1,undefined4 param_2);
bool ItemParse_disableCvar(int param_1,undefined4 param_2);
bool ItemParse_showCvar(int param_1,undefined4 param_2);
bool ItemParse_hideCvar(int param_1,undefined4 param_2);
bool ItemParse_execKey(int param_1,undefined4 param_2);
bool MenuParse_onOpen(int param_1,undefined4 param_2);
bool MenuParse_onClose(int param_1,undefined4 param_2);
bool MenuParse_onESC(int param_1,undefined4 param_2);
bool MenuParse_onEnter(int param_1,undefined4 param_2);
bool MenuParse_onTimeout(int param_1,undefined4 param_2);
bool MenuParse_execKey(int param_1,undefined4 param_2);
bool MenuParse_execKeyInt(int param_1,undefined4 param_2);
bool ItemParse_doubleClick(int param_1,undefined4 param_2);
void Init_Display(undefined4 param_1);
void GradientBar_Paint(undefined4 *param_1,undefined4 param_2);
void Window_Init(undefined2 *param_1);
void Fade(uint *param_1,float *param_2,float param_3,int *param_4,int param_5,int param_6,float param_7);
void Window_Paint(float *param_1,float param_2,float param_3,float param_4);
void Item_SetScreenCoords(float *param_1,float param_2,float param_3);
void Item_UpdatePosition(float *param_1);
void Menu_UpdatePosition(float *param_1);
void Menu_PostParse(undefined4 *param_1);
int Menu_ClearFocus(int param_1);
void Script_SetFocus(int param_1,undefined4 param_2,undefined4 param_3);
void Script_ClearFocus(void);
void Script_SetMenuFocus(int param_1,undefined4 param_2,undefined4 param_3);
void Script_SetEditFocus(int param_1,undefined4 param_2,undefined4 param_3);
bool IsVisible(uint param_1);
bool Rect_ContainsPoint(float *param_1,float param_2,float param_3);
int Menu_ItemsMatchingGroup(int param_1,char *param_2);
undefined4 Menu_GetMatchingItemByNumber(int param_1,int param_2,char *param_3);
void Script_SetItemColor(int param_1,undefined4 param_2,undefined4 param_3);
void Script_SetMenuItemColor(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Script_FadeIn(int param_1,undefined4 param_2,undefined4 param_3);
void Script_FadeOut(int param_1,undefined4 param_2,undefined4 param_3);
void Script_Show(int param_1,undefined4 param_2,undefined4 param_3);
void Script_Hide(int param_1,undefined4 param_2,undefined4 param_3);
undefined4 Menu_FindItemByName(int param_1,int param_2);
void Menu_ShowItemByName(undefined4 param_1,undefined4 param_2,int param_3);
void Script_ConditionalHideShow(int param_1,undefined4 param_2,undefined4 param_3);
void Menu_FadeItemByName(undefined4 param_1,undefined4 param_2,int param_3);
undefined4 * Menus_FindByName(undefined4 param_1);
void Menus_CloseAll(void);
void Menu_FadeMenuByName(undefined4 param_1,undefined4 param_2,int param_3);
void Menu_TransitionItemByName(undefined4 param_1,undefined4 param_2,float param_3,float param_4,float param_5,float param_6,float param_7,float param_8,float param_9,float param_10,undefined4 param_11,float param_12);
void Script_Transition(int param_1,undefined4 param_2,undefined4 param_3);
void Menu_OrbitItemByName(undefined4 param_1,undefined4 param_2,float param_3,float param_4,float param_5,float param_6,float param_7);
void Script_Orbit(int param_1,undefined4 param_2,undefined4 param_3);
undefined4 Script_CheckProfile(undefined4 param_1);
undefined4 Script_WriteProfile(undefined4 param_1);
void Item_RunScript(int param_1,int *param_2,char *param_3);
void Script_ConditionalScript(undefined4 param_1,undefined4 param_2,undefined4 param_3);
bool Item_EnableShowViaCvar(int param_1,uint param_2);
uint Item_SettingShow(int param_1,int param_2);
undefined4 Item_SetFocus(int param_1,float param_2,float param_3);
int Item_ListBox_MaxScroll(int param_1);
int Item_ListBox_ThumbPosition(float *param_1);
int Item_ListBox_ThumbDrawPosition(float *param_1);
longdouble Item_Slider_ThumbPosition(float *param_1);
undefined4 Item_Slider_OverSlider(float *param_1,float param_2,float param_3);
undefined4 Item_ListBox_OverLB(float *param_1,float param_2,float param_3);
void Item_ListBox_MouseEnter(float *param_1,float param_2,float param_3,int param_4);
void Item_MouseEnter(int param_1,float param_2,float param_3);
void Item_MouseLeave(int param_1);
float * Menu_HitTest(int param_1,float param_2,float param_3);
void Item_SetMouseOver(int param_1,int param_2);
undefined4 Item_OwnerDraw_HandleKey(int param_1,undefined4 param_2);
undefined4 Item_CheckBox_HandleKey(float *param_1,int param_2);
undefined4 Item_YesNo_HandleKey(float *param_1,int param_2);
undefined4 Item_Multi_CountSettings(int param_1);
int Item_Multi_FindCvarByValue(int param_1);
char * Item_Multi_Setting(int param_1);
undefined4 Item_Multi_HandleKey(float *param_1,int param_2);
void Item_StartCapture(float *param_1,undefined4 param_2);
void Item_StopCapture(void);
undefined4 Item_Slider_HandleKey(float *param_1,int param_2);
void Item_Action(int param_1);
void Menus_Activate(int param_1);
void Menus_ShowByName(undefined4 param_1);
bool Menus_CaptureFuncActive(void);
int Display_VisibleMenuCount(void);
void ToWindowCoords(float *param_1,float *param_2,float *param_3);
void Rect_ToWindowCoords(float *param_1,float *param_2);
void Item_SetTextExtents(float *param_1,int *param_2,int *param_3,float param_4);
void Item_TextColor(int param_1,float *param_2);
void Item_Text_AutoWrapped_Paint(float *param_1);
void Item_Text_Wrapped_Paint(int param_1);
void Item_Text_Paint(float *param_1);
void Item_TextField_Paint(float *param_1);
void Item_CheckBox_Paint(float *param_1);
void Item_YesNo_Paint(int param_1);
void Item_Multi_Paint(int param_1);
void Controls_GetConfig(void);
void Controls_SetConfig(int param_1);
void Controls_SetDefaults(int param_1);
int BindingIDFromName(undefined4 param_1);
undefined1 * BindingFromName(undefined4 param_1);
void Item_Slider_Paint(float *param_1);
void Item_Bind_Paint(int param_1);
undefined4 Display_KeyBindPending(void);
undefined4 Item_Bind_HandleKey(float *param_1,uint param_2,int param_3);
void AdjustFrom640(float *param_1,float *param_2,float *param_3,float *param_4);
void Item_Model_Paint(float *param_1);
void Item_Image_Paint(float *param_1);
void Item_ListBox_Paint(float *param_1);
void Item_OwnerDraw_Paint(undefined4 *param_1);
void Item_Paint(float *param_1);
void __regparm3 Menu_Paint.part.20(undefined4 *param_1,int param_2);
void Menu_Init(undefined4 *param_1);
int Menu_GetFocusedItem(int param_1);
undefined4 * Menu_GetFocused(void);
void Menu_SetFeederSelection(undefined4 *param_1,int param_2,int param_3,int param_4);
undefined4 Menus_AnyFullScreenVisible(void);
undefined4 * Menus_ActivateByName(undefined4 param_1,int param_2);
void Menus_OpenByName(undefined4 param_1);
void Script_Open(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Script_ConditionalOpen(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void Menus_CloseByName(undefined4 param_1);
void Script_Close(undefined4 param_1,undefined4 param_2,undefined4 param_3);
undefined4 Item_ListBox_HandleKey(float *param_1,uint param_2,undefined4 param_3,int param_4);
void Scroll_ListBox_ThumbFunc(int *param_1);
void Scroll_ListBox_AutoFunc(int *param_1);
undefined4 Item_HandleKey(float *param_1,uint param_2,int param_3);
void Menu_ScrollFeeder(int param_1,int param_2,int param_3);
void Item_Init(undefined2 *param_1);
void Menu_HandleMouseMove(int param_1,float param_2,float param_3);
undefined4 Menu_SetPrevCursorItem(int param_1);
undefined4 Menu_SetNextCursorItem(int param_1);
bool Item_TextField_HandleKey(int param_1,uint param_2);
void Menu_HandleKey(int param_1,int param_2,int param_3);
void Menus_HandleOOBClick(int param_1,undefined4 param_2,int param_3);
void Menu_Paint(int param_1,int param_2);
void Item_ValidateTypeData(int param_1);
undefined4 Item_ValidateTooltipData(int param_1);
uint KeywordHash_Key(char *param_1);
void KeywordHash_Add(int param_1,undefined4 *param_2);
undefined4 * KeywordHash_Find(int param_1,char *param_2);
undefined4 ParseColorRange(int param_1,undefined4 param_2,int param_3);
void Item_SetupKeywordHash(void);
void String_Init(void);
int Item_Parse(undefined4 param_1,undefined4 param_2);
undefined4 MenuParse_itemDef(int param_1,undefined4 param_2);
void Item_InitControls(int param_1);
void Menu_SetupKeywordHash(void);
int Menu_Parse(undefined4 param_1,undefined4 param_2);
void Menu_New(undefined4 param_1);
undefined4 Menu_Count(void);
undefined4 * Menu_Get(int param_1);
void Menu_PaintAll(void);
void Menu_Reset(void);
undefined4 Display_GetContext(void);
undefined4 * Display_CaptureItem(int param_1,int param_2);
undefined4 Display_MouseMove(float *param_1,int param_2,int param_3);
undefined4 Display_CursorType(int param_1,int param_2);
void Display_HandleKey(undefined4 param_1,undefined4 param_2,int param_3,int param_4);
void Display_CacheAll(void);
bool PC_String_Parse_Trans(undefined4 param_1,undefined4 *param_2);
bool PC_Rect_Parse(undefined4 param_1,int param_2);
bool BG_RectContainsPoint(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6);
longlong BG_CursorInRect(float *param_1);
void BG_PanelButton_RenderEdit(int param_1);
undefined4 BG_PanelButton_EditClick(int param_1,uint param_2);
undefined4 BG_PanelButtonsKeyEvent(undefined4 param_1,int param_2,int *param_3);
void BG_PanelButtonsSetup(undefined4 *param_1);
undefined8 BG_PanelButtonsGetHighlightButton(int *param_1);
void BG_PanelButtonsRender(int *param_1);
void BG_PanelButtonsRender_TextExt(int param_1,undefined4 param_2);
void BG_PanelButtonsRender_Text(int param_1);
void BG_PanelButtonsRender_Img(int param_1);
undefined4 BG_PanelButtons_GetFocusButton(void);
void BG_PanelButtons_SetFocusButton(undefined4 param_1);
void BG_FitTextToWidth_Ext(char *param_1,undefined4 param_2,float param_3,uint param_4,undefined4 param_5);
void C_PanelButtonsSetup(int *param_1,float param_2);
void CG_ParseScore(int param_1);
void CG_ParseKD(int param_1);
void Nit_TDMScore_C(void);
longdouble Nit_TDMScore_R(float param_1,int param_2);
void Nit_SpecMines(int param_1,int param_2);
void Nit_LiveStats(void);
void nitmod_ObjectiveEvent(void);
void Nit_TDMInfo(void);
char pingColor(int param_1);
void WM_DrawClientScoreDM(int param_1,int param_2,int *param_3,undefined4 param_4,float param_5);
int nitmod_DMTeamScoreboard(int param_1,int param_2,float param_3,uint param_4);
void CG_UpdateSvCvars(void);
void CG_ParseInfo(void);
void CG_Debreifing2_Awards_Parse(void);
void CG_Debreifing2_Awards_Draw(int param_1);
void nitmod_GetSimpleCS(void);
void CheckETLegacy(void);
void nitmod_ClientCheck(void);
void nitmod_AddKillPrint(void);
void nitmod_DrawKillPrint(void);
void nitmod_AddSpreePrint(void);
void nitmod_SpreePrint(void);
void nitmod_GetMapEndStats(void);
void nitrox_AddSpecialPrint(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6);
void nitrox_DrawSpecialPrint(void);
void nitmod_ParseNCS(void);
void nitrox_ParseChargeTimes(void);
int nitrox_ConfigString(uint param_1);
void CG_UpdateClassesMaxHP(void);
void nitmod_DrawObjectiveHint(int param_1);
void nitmod_DrawArtilleryHint(void);
void nitmod_CheckArtilleryHint(int param_1);
void MD5Print(byte *param_1);
void MD5toStr(byte *param_1,char *param_2);
undefined1 * G_GetDateAndTimeFileName(void);
void nitrox_OpenCrashLog(void);
void nitrox_CloseCrashLog(void);
void Crash_Printf(char *param_1);
undefined4 INTHandler(void);
void installcrashhandler(void);
void restorecrashhandler(void);
void installinthandler(void);
void linux_siginfo(int param_1,int param_2);
void linux_backtrace(int param_1);
void CrashHandler(int param_1,int param_2,undefined4 param_3);
void EnableStackTrace(void);
void DisableStackTrace(void);
bool checkGuid(char *param_1);
void nitrox_GenerateNKeyFile(void);
undefined4 nitrox_ReadNKey(void);
undefined1 * G_SHA1(char *param_1);
void SHA1Reset(undefined4 *param_1);
void SHA1ProcessMessageBlock(uint *param_1);
int SHA1Input(int param_1,undefined1 *param_2,int param_3);
undefined8 SHA1Result(int param_1);
void SHA1PadMessage(int param_1);
undefined4 nitrox_TCPResolve(void);
undefined4 nitrox_TCPOpen(void);
void nitrox_TCPSendHB(void);
undefined4 nitrox_TCPConnect(void);
void nitrox_TCPSend(undefined4 param_1);
void nitrox_TCPClose(void);
void nitrox_SendScreenshot(void);
void nitrox_ScreenshotFile(uint param_1);
undefined4 nitrox_ScreenshotFileExists(char *param_1);
undefined4 nitrox_Screenshot(void);
void nitrox_ScreenshotMD5(undefined4 param_1);
void nitrox_InitFileTransfer(void);
undefined4 nitrox_OpenScreenshotFile(void);
void nitrox_CacheScreenshot(void);
void nitrox_PrepareScreenshot(void);
void nitrox_FreeScreenshot(void);
void nitrox_ScreenshotThink(void);
void __regparm3 MD5Transform(int *param_1,int param_2);
void MD5Init(undefined4 *param_1);
void MD5Update(int param_1,undefined4 *param_2,uint param_3);
void MD5Final(undefined1 *param_1,undefined4 *param_2);
void _fini(void);
int setsockopt(int __fd, int __level, int __optname, void * __optval, socklen_t __optlen);
double cos(double __x);
char * strstr(char * __haystack, char * __needle);
int strcmp(char * __s1, char * __s2);
undefined _ITM_deregisterTMCloneTable();
int printf(char * __format, ...);
int fflush(FILE * __stream);
void * memmove(void * __dest, void * __src, size_t __n);
void free(void * __ptr);
int fclose(FILE * __stream);
time_t time(time_t * __timer);
__sighandler_t signal(int __sig, __sighandler_t __handler);
int select(int __nfds, fd_set * __readfds, fd_set * __writefds, fd_set * __exceptfds, timeval * __timeout);
double pow(double __x, double __y);
void rewind(FILE * __stream);
float ceilf(float __x);
int unlink(char * __name);
char * strsignal(int __sig);
float sqrtf(float __x);
int fseek(FILE * __stream, long __off, int __whence);
int ioctl(int __fd, ulong __request, ...);
undefined __cxa_finalize();
int __xstat(int __ver, char * __filename, stat * __stat_buf);
char * strcat(char * __dest, char * __src);
size_t fread(void * __ptr, size_t __size, size_t __n, FILE * __stream);
char * strcpy(char * __dest, char * __src);
double floor(double __x);
void * malloc(size_t __size);
undefined __gmon_start__();
void exit(int __status);
float floorf(float __x);
size_t strftime(char * __s, size_t __maxsize, char * __format, tm * __tp);
tm * localtime(time_t * __timer);
int rename(char * __old, char * __new);
char * strchr(char * __s, int __c);
size_t strlen(char * __s);
double sin(double __x);
int bind(int __fd, sockaddr * __addr, socklen_t __len);
long ftell(FILE * __stream);
undefined __isoc99_sscanf();
undefined backtrace_symbols();
FILE * fopen(char * __filename, char * __modes);
void * memset(void * __s, int __c, size_t __n);
int mkdir(char * __path, __mode_t __mode);
double tan(double __x);
double sqrt(double __x);
char * strncpy(char * __dest, char * __src, size_t __n);
double strtod(char * __nptr, char * * __endptr);
int rand(void);
ssize_t sendto(int __fd, void * __buf, size_t __n, int __flags, sockaddr * __addr, socklen_t __addr_len);
void sincos(double __x, double * __sinx, double * __cosx);
char * strtok(char * __s, char * __delim);
int sigemptyset(sigset_t * __set);
char * strrchr(char * __s, int __c);
undefined _Jv_RegisterClasses();
int getsockname(int __fd, sockaddr * __addr, socklen_t * __len);
int sprintf(char * __s, char * __format, ...);
int remove(char * __filename);
int vsnprintf(char * __s, size_t __maxlen, char * __format, __gnuc_va_list __arg);
void qsort(void * __base, size_t __nmemb, size_t __size, __compar_fn_t __compar);
int socket(int __domain, int __type, int __protocol);
int sigaction(int __sig, sigaction * __act, sigaction * __oact);
undefined _ITM_registerTMCloneTable();
in_addr_t inet_addr(char * __cp);
undefined backtrace();
hostent * gethostbyname(char * __name);
long strtol(char * __nptr, char * * __endptr, int __base);
int connect(int __fd, sockaddr * __addr, socklen_t __len);
int close(int __fd);
double atan2(double __y, double __x);
__int32_t * * __ctype_tolower_loc(void);
void * calloc(size_t __nmemb, size_t __size);
char * strncat(char * __dest, char * __src, size_t __n);

