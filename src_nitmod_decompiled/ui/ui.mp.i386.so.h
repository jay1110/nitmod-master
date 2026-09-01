typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned char    dwfenc;
typedef unsigned int    dword;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined3;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined6;
typedef unsigned long long    undefined8;
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

typedef ulong size_t;

typedef int __int32_t;

typedef struct evp_pkey_ctx_st evp_pkey_ctx_st, *Pevp_pkey_ctx_st;

struct evp_pkey_ctx_st {
};

typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;

typedef void *__gnuc_va_list;

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

typedef struct Elf32_Sym Elf32_Sym, *PElf32_Sym;

struct Elf32_Sym {
    dword st_name;
    dword st_value;
    dword st_size;
    byte st_info;
    byte st_other;
    word st_shndx;
};

typedef struct Elf32_Dyn_x86 Elf32_Dyn_x86, *PElf32_Dyn_x86;

struct Elf32_Dyn_x86 {
    enum Elf32_DynTag_x86 d_tag;
    dword d_val;
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

typedef struct Elf32_Rel Elf32_Rel, *PElf32_Rel;

struct Elf32_Rel {
    dword r_offset; // location to apply the relocation action
    dword r_info; // the symbol table index and the type of relocation
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
void FUN_00013cc0(void);
__int32_t ** __ctype_toupper_loc(void);
double cos(double __x);
char * strstr(char *__haystack,char *__needle);
int strcmp(char *__s1,char *__s2);
void * memmove(void *__dest,void *__src,size_t __n);
void free(void *__ptr);
char * stpcpy(char *__dest,char *__src);
float sqrtf(float __x);
void __cxa_finalize(void);
char * strcpy(char *__dest,char *__src);
void __gmon_start__(void);
float floorf(float __x);
char * strchr(char *__s,int __c);
size_t strlen(char *__s);
double sin(double __x);
void * memset(void *__s,int __c,size_t __n);
char * strncpy(char *__dest,char *__src,size_t __n);
double strtod(char *__nptr,char **__endptr);
int rand(void);
void sincos(double __x,double *__sinx,double *__cosx);
char * strtok(char *__s,char *__delim);
int vsnprintf(char *__s,size_t __maxlen,char *__format,__gnuc_va_list __arg);
void qsort(void *__base,size_t __nmemb,size_t __size,__compar_fn_t __compar);
long strtol(char *__nptr,char **__endptr,int __base);
double atan2(double __y,double __x);
__int32_t ** __ctype_tolower_loc(void);
void * calloc(size_t __nmemb,size_t __size);
void processEntry UI_StartServerRefresh(void);
void __x86.get_pc_thunk.bx(void);
void deregister_tm_clones(void);
void register_tm_clones(void);
void __do_global_dtors_aux(void);
void frame_dummy(void);
undefined4 BG_LoadCampaignSave(undefined4 param_1,int *param_2,char *param_3);
undefined4 BG_StoreCampaignSave(undefined4 param_1,undefined4 *param_2,char *param_3);
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
undefined1 * BG_AddSplinePath(undefined4 param_1,char *param_2,undefined4 *param_3);
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
void __x86.get_pc_thunk.cx(void);
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
void Com_Error(undefined4 param_1,char *param_2);
void Com_Printf(char *param_1);
void Com_DPrintf(char *param_1);
void UI_ClampCvar(void);
undefined1 * UI_Argv(undefined4 param_1);
undefined1 * UI_Cvar_VariableString(undefined4 param_1);
undefined4 UI_ConsoleCommand(int param_1);
void UI_AdjustFrom640(float *param_1,float *param_2,float *param_3,float *param_4);
void UI_DrawNamedPic(float param_1,float param_2,float param_3,float param_4,undefined4 param_5);
void UI_DrawHandlePic(float param_1,float param_2,float param_3,float param_4,undefined4 param_5);
void UI_DrawRotatedPic(float param_1,float param_2,float param_3,float param_4,undefined4 param_5,undefined4 param_6);
void UI_FillRect(float param_1,float param_2,float param_3,float param_4,undefined4 param_5);
void UI_DrawSides(float param_1,float param_2,float param_3,float param_4);
void UI_DrawTopBottom(float param_1,float param_2,float param_3,float param_4);
void UI_DrawRect(float param_1,float param_2,float param_3,float param_4,undefined4 param_5);
void UI_SetColor(undefined4 param_1);
void UI_UpdateScreen(void);
void UI_DrawTextBox(int param_1,int param_2,int param_3,int param_4);
bool UI_CursorInRect(int param_1,int param_2,int param_3,int param_4);
void UI_SortArenas(undefined4 *param_1,undefined4 *param_2);
void UI_SortCampaigns(int param_1,int param_2);
void UI_LoadArenas(void);
undefined * UI_FindMapInfoByMapname(undefined4 param_1);
undefined4 UI_DescriptionForCampaign(void);
undefined4 UI_NameForCampaign(void);
int UI_FindCampaignInCampaignList(int param_1);
void UI_LoadCampaigns(void);
void UI_LoadPanel_RenderHeaderText(int param_1);
void UI_LoadPanel_RenderDownloadingBar.part.0(void);
void AdjustFrom640FullScreen(float *param_1,float *param_2,float *param_3,float *param_4);
void FillRectFullScreen(float param_1,float param_2,float param_3,float param_4,undefined4 param_5);
void UI_DrawLoadPanel(undefined4 param_1,undefined4 param_2,int param_3);
bool Downloading(void);
void CG_FilledBar(float param_1,float param_2,float param_3,float param_4,undefined4 param_5,undefined4 param_6,undefined4 *param_7,float param_8,uint param_9);
void UI_LoadPanel_RenderDownloadingBar(void);
void UI_DownloadInfo(undefined4 param_1);
void UI_LoadPanel_RenderLoadingText(int param_1);
void Text_SetActiveFont(undefined4 param_1);
longdouble UI_GetValue(void);
uint UI_ServersQsortCompare_bis(int *param_1,int *param_2);
void UI_GetTeamColor(void);
void UI_FeederAddItem(void);
void _UI_DrawSides(float param_1,undefined4 param_2,float param_3,undefined4 param_4,float param_5);
void _UI_DrawTopBottom(undefined4 param_1,float param_2,undefined4 param_3,float param_4,float param_5);
int Text_Width_Ext(byte *param_1,float param_2,size_t param_3,int param_4);
int Multiline_Text_Width(byte *param_1,float param_2,size_t param_3);
int Text_Height_Ext(byte *param_1,float param_2,size_t param_3,int param_4);
int Multiline_Text_Height(byte *param_1,float param_2,size_t param_3);
void __regparm3 UI_BuildServerDisplayList(int param_1);
void UI_ServersQsortCompare(undefined4 *param_1,undefined4 *param_2);
undefined4 __regparm3 UI_GetServerStatusInfo(undefined4 param_1,undefined4 *param_2);
void UI_PlayCinematic(undefined4 param_1,float param_2,float param_3,float param_4,float param_5);
undefined1 * UI_FileText(undefined4 param_1);
undefined4 UI_OwnerDrawVisible(uint param_1);
void UI_SortMods(undefined4 *param_1,undefined4 *param_2);
void UI_BuildPlayerList(void);
void UI_RunCinematicFrame(undefined4 param_1);
void UI_DrawCinematic(undefined4 param_1,float param_2,float param_3,float param_4,float param_5);
void UI_StopServerRefresh.part.19(void);
void UI_Pause(int param_1);
char * __regparm2 UI_FeederItemText.part.33(int param_1,uint param_2,float param_3,undefined4 *param_4,undefined4 *param_5);
byte * __regparm2 Text_AutoWrap_Paint_Chunk.constprop.56(int param_1,undefined4 *param_2,float param_3,undefined4 param_4,float param_5,byte *param_6,float param_7,undefined4 param_8,undefined4 *param_9);
void _UI_SetActiveMenu.constprop.61(void);
void Text_Paint_Ext(float param_1,float param_2,float param_3,float param_4,undefined4 *param_5,byte *param_6,float param_7,size_t param_8,int param_9,int param_10);
void Text_Paint(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8);
char * UI_FeederItemText(float param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 *param_5);
void _UI_DrawRect(float param_1,float param_2,float param_3,float param_4,float param_5,undefined4 param_6);
int UI_FeederItemImage(float param_1,int param_2);
int Text_Height(byte *param_1,float param_2,size_t param_3);
void UI_ParseGameInfo.constprop.57(void);
int Text_Width(byte *param_1,float param_2,size_t param_3);
void __regparm2 Text_Paint_Limit.constprop.55(float *param_1,undefined4 *param_2,float param_3,float param_4,float param_5,byte *param_6,size_t param_7);
void __regparm2 UI_DrawCampaignMapDescription.constprop.54(float *param_1,undefined4 param_2,float param_3,float param_4,float param_5,undefined4 param_6,int param_7,int param_8);
void __regparm2 UI_DrawMissionBriefingObjectives(float *param_1,undefined4 param_2,float param_3,float param_4,float param_5,undefined4 param_6,int param_7);
undefined8 UI_FeederCount(float param_1);
void __regparm3 UI_BuildServerStatus(int param_1);
void __regparm1 UI_FeederSelection.part.24(int param_1,float param_2);
void UI_FeederSelection(float param_1,int param_2);
undefined4 UI_FeederSelectionClick(float *param_1);
void __regparm3 UI_BuildFindPlayerList(int param_1);
void UI_StopCinematic(int param_1);
int UI_OwnerDrawWidth(int param_1,float param_2);
undefined4 UI_OwnerDrawHandleKey(int param_1,undefined4 param_2,undefined4 param_3,int param_4);
void AssetCache(void);
void Text_PaintCharExt(undefined4 param_1,undefined4 param_2,float param_3,float param_4,float param_5,float param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10,undefined4 param_11);
void Text_PaintChar(undefined4 param_1,undefined4 param_2,float param_3,float param_4,float param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10);
void Text_PaintWithCursor(float param_1,float param_2,float param_3,undefined4 *param_4,byte *param_5,size_t param_6,byte param_7,size_t param_8,int param_9);
byte * Text_AutoWrap_Paint_Chunk(float param_1,float param_2,int param_3,float param_4,undefined4 *param_5,byte *param_6,float param_7,size_t param_8,int param_9,int param_10,undefined4 *param_11);
int Count_Text_AutoWrap_Paint(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,char *param_6,undefined4 param_7,undefined4 param_8);
void Text_AutoWrap_Paint(float param_1,float param_2,undefined4 param_3,int param_4,float param_5,undefined4 *param_6,undefined4 param_7,float param_8,int param_9);
void UI_ShowPostGame(undefined4 param_1);
void UI_DrawCenteredPic(undefined4 param_1,int param_2,int param_3);
void _UI_Refresh(int param_1);
void _UI_Shutdown(void);
undefined1 * GetMenuBuffer(undefined4 param_1);
undefined4 Asset_Parse(undefined4 param_1);
void UI_Report(void);
undefined4 UI_ParseMenu(undefined4 param_1);
undefined4 Load_Menu(undefined4 param_1);
void UI_LoadMenus(undefined4 param_1,int param_2);
void UI_Load(void);
void UI_DrawMapPreview(float *param_1,float param_2,undefined4 param_3,int param_4);
void __regparm2 UI_DrawMapCinematic(float *param_1,undefined4 param_2,undefined4 param_3,int param_4);
void UI_DrawNetMapPreview(undefined4 *param_1);
void UI_DrawCampaignDescription(float *param_1,float param_2,undefined4 param_3,float param_4,undefined4 param_5,undefined4 param_6,int param_7,int param_8);
void UI_DrawGametypeDescription(float *param_1,float param_2,undefined4 param_3,float param_4,undefined4 param_5,undefined4 param_6,int param_7);
void UI_OwnerDraw(float param_1,float param_2,float param_3,float param_4,float param_5,float param_6,int param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10,float param_11,float *param_12,undefined4 param_13,undefined4 param_14);
void UI_ServersSort(int param_1,int param_2);
void WM_setItemPic(undefined4 param_1,undefined4 param_2);
void WM_setVisibility(undefined4 param_1,int param_2);
bool UI_CheckExecKey(int param_1);
void UI_Update(undefined4 param_1);
void UI_RunMenuScript(void);
void _UI_Init(void);
void _UI_KeyEvent(undefined4 param_1,undefined4 param_2);
void _UI_MouseEvent(int param_1,int param_2);
void UI_LoadNonIngame(void);
undefined4 _UI_GetActiveMenu(void);
void _UI_SetActiveMenu(undefined4 param_1);
uint vmMain(undefined4 param_1,int param_2,int param_3);
void _UI_IsFullscreen(void);
void UI_ReadableSize(char *param_1,int param_2,uint param_3);
void UI_PrintTime(undefined4 param_1,undefined4 param_2,int param_3);
void Text_PaintCenter(float param_1,undefined4 param_2,float param_3,undefined4 param_4,byte *param_5);
void UI_DrawConnectScreen(int param_1);
void UI_RegisterCvars(void);
void UI_UpdateCvars(void);
void UI_Campaign_f(void);
void UI_ListCampaigns_f(void);
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
void String_Init(void);
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
void dllEntry(undefined4 param_1);
undefined4 PASSFLOAT(undefined4 param_1);
void trap_Print(undefined4 param_1);
void trap_Error(undefined4 param_1);
void trap_Milliseconds(void);
void trap_Cvar_Register(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void trap_Cvar_Update(undefined4 param_1);
void trap_Cvar_Set(undefined4 param_1,undefined4 param_2);
longdouble trap_Cvar_VariableValue(undefined4 param_1);
void trap_Cvar_VariableStringBuffer(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_Cvar_LatchedVariableStringBuffer(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_Cvar_SetValue(undefined4 param_1,undefined4 param_2);
void trap_Cvar_Reset(undefined4 param_1);
void trap_Cvar_Create(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_Cvar_InfoStringBuffer(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_Argc(void);
void trap_Argv(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_Cmd_ExecuteText(undefined4 param_1,undefined4 param_2);
void trap_AddCommand(undefined4 param_1);
void trap_FS_FOpenFile(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_FS_Read(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_FS_Write(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_FS_FCloseFile(undefined4 param_1);
void trap_FS_GetFileList(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void trap_FS_Delete(undefined4 param_1);
void trap_R_RegisterModel(undefined4 param_1);
void trap_R_RegisterSkin(undefined4 param_1);
void trap_R_RegisterFont(undefined4 param_1,undefined4 param_2,int param_3);
void trap_R_RegisterShaderNoMip(undefined4 param_1);
void trap_R_ClearScene(void);
void trap_R_AddRefEntityToScene(undefined4 param_1);
void trap_R_AddPolyToScene(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_R_AddLightToScene(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8);
void trap_R_AddCoronaToScene(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7);
void trap_R_RenderScene(undefined4 param_1);
void trap_R_SetColor(undefined4 param_1);
void trap_R_Add2dPolys(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_R_DrawStretchPic(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9);
void trap_R_DrawRotatedPic(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10);
void trap_R_ModelBounds(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_UpdateScreen(void);
void trap_CM_LerpTag(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_S_StartLocalSound(undefined4 param_1,undefined4 param_2);
void trap_S_RegisterSound(undefined4 param_1);
void trap_S_FadeBackgroundTrack(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_S_FadeAllSound(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_Key_KeynumToStringBuf(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_Key_GetBindingBuf(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_Key_KeysForBinding(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_Key_SetBinding(undefined4 param_1,undefined4 param_2);
void trap_Key_IsDown(undefined4 param_1);
void trap_Key_GetOverstrikeMode(void);
void trap_Key_SetOverstrikeMode(undefined4 param_1);
void trap_Key_ClearStates(void);
void trap_Key_GetCatcher(void);
void trap_Key_SetCatcher(undefined4 param_1);
void trap_GetClipboardData(undefined4 param_1,undefined4 param_2);
void trap_GetClientState(undefined4 param_1);
void trap_GetGlconfig(undefined4 param_1);
void trap_GetConfigString(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_LAN_GetLocalServerCount(void);
void trap_LAN_GetLocalServerAddressString(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_LAN_GetGlobalServerCount(void);
void trap_LAN_GetGlobalServerAddressString(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_LAN_GetPingQueueCount(void);
void trap_LAN_ClearPing(undefined4 param_1);
void trap_LAN_GetPing(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void trap_LAN_GetPingInfo(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_LAN_UpdateVisiblePings(undefined4 param_1);
void trap_LAN_GetServerCount(undefined4 param_1);
void trap_LAN_CompareServers(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void trap_LAN_GetServerAddressString(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void trap_LAN_GetServerInfo(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void trap_LAN_AddServer(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_LAN_RemoveServer(undefined4 param_1,undefined4 param_2);
void trap_LAN_GetServerPing(undefined4 param_1,undefined4 param_2);
void trap_LAN_ServerIsVisible(undefined4 param_1,undefined4 param_2);
void trap_LAN_ServerStatus(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_LAN_ServerIsInFavoriteList(undefined4 param_1,undefined4 param_2);
void trap_LAN_SaveCachedServers(void);
void trap_LAN_LoadCachedServers(void);
void trap_LAN_MarkServerVisible(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_SetPbClStatus(undefined4 param_1);
void trap_SetPbSvStatus(undefined4 param_1);
void trap_LAN_ResetPings(undefined4 param_1);
void trap_MemoryRemaining(void);
void trap_GetCDKey(undefined4 param_1,undefined4 param_2);
void trap_SetCDKey(undefined4 param_1);
void trap_PC_AddGlobalDefine(undefined4 param_1);
void trap_PC_RemoveAllGlobalDefines(void);
void trap_PC_LoadSource(undefined4 param_1);
void trap_PC_FreeSource(undefined4 param_1);
void trap_PC_ReadToken(undefined4 param_1,undefined4 param_2);
void trap_PC_SourceFileAndLine(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_PC_UnReadToken(undefined4 param_1);
void trap_S_StopBackgroundTrack(void);
void trap_S_StartBackgroundTrack(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_RealTime(undefined4 param_1);
void trap_CIN_PlayCinematic(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6);
void trap_CIN_StopCinematic(undefined4 param_1);
void trap_CIN_RunCinematic(undefined4 param_1);
void trap_CIN_DrawCinematic(undefined4 param_1);
void trap_CIN_SetExtents(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5);
void trap_R_RemapShader(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void trap_VerifyCDKey(undefined4 param_1,undefined4 param_2);
void trap_GetLimboString(undefined4 param_1,undefined4 param_2);
void trap_CheckAutoUpdate(void);
void trap_GetAutoUpdate(void);
void trap_openURL(undefined4 param_1);
void trap_GetHunkData(undefined4 param_1,undefined4 param_2);
void _fini(void);
__int32_t * * __ctype_toupper_loc(void);
double cos(double __x);
char * strstr(char * __haystack, char * __needle);
int strcmp(char * __s1, char * __s2);
undefined _ITM_deregisterTMCloneTable();
void * memmove(void * __dest, void * __src, size_t __n);
void free(void * __ptr);
char * stpcpy(char * __dest, char * __src);
float sqrtf(float __x);
undefined __cxa_finalize();
char * strcpy(char * __dest, char * __src);
undefined __gmon_start__();
float floorf(float __x);
char * strchr(char * __s, int __c);
size_t strlen(char * __s);
double sin(double __x);
void * memset(void * __s, int __c, size_t __n);
char * strncpy(char * __dest, char * __src, size_t __n);
double strtod(char * __nptr, char * * __endptr);
int rand(void);
void sincos(double __x, double * __sinx, double * __cosx);
char * strtok(char * __s, char * __delim);
undefined _Jv_RegisterClasses();
int vsnprintf(char * __s, size_t __maxlen, char * __format, __gnuc_va_list __arg);
void qsort(void * __base, size_t __nmemb, size_t __size, __compar_fn_t __compar);
undefined _ITM_registerTMCloneTable();
long strtol(char * __nptr, char * * __endptr, int __base);
double atan2(double __y, double __x);
__int32_t * * __ctype_tolower_loc(void);
void * calloc(size_t __nmemb, size_t __size);

