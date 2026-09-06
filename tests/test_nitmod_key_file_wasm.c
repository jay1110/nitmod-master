#include "cg_local.h"
#include "cg_nitmod_config.h"
#include <assert.h>
#include <stdio.h>
static char fileData[100], supplied[33];
static int fileSize, reads, closes;
int trap_FS_FOpenFile(const char *path,fileHandle_t *file,fsMode_t mode) {
    assert(!strcmp(path,"nkey.dat") && mode == FS_READ);
    *file = 1; return fileSize;
}
void trap_FS_Read(void *out,int size,fileHandle_t file) {
    assert(file == 1 && size == 44 && size <= fileSize);
    memcpy(out,fileData,size); ++reads;
}
void trap_FS_FCloseFile(fileHandle_t file) { assert(file == 1); ++closes; }
void trap_Cvar_Set(const char *name,const char *value) {
    assert(!strcmp(name,"n_guid") && strlen(value) <= 32);
    strcpy(supplied,value);
}
void CG_Printf(const char *format,...) { (void)format; }
qboolean NITMOD_GenerateMissingNKey(char guid[33]) { assert(0); return qfalse; }
int main(void) {
    static const char key[] = "QUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBS0s=";
    int size;
    for(size = 0; size <= 100; ++size) {
        memset(fileData,0xa5,sizeof(fileData));
        memcpy(fileData,key,44);
        fileSize=size; reads=closes=0;
        NITMOD_ReadNKey();
        assert(closes == 1 && reads == (size >= 44));
        assert(size >= 44 ? !strcmp(supplied,"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAKK") : !supplied[0]);
        assert((unsigned char)fileData[99] == 0xa5);
    }
    fileData[0]='!';
    NITMOD_ReadNKey();
    assert(!supplied[0]);
    puts("NKey file loader: sizes 0..100, trailing bytes and invalid prefix passed");
    return 0;
}
