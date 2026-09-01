/* ELF/C++ runtime remnants — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_runtime.h"

int _init(EVP_PKEY_CTX *ctx)
{
  int tmp_i1;
  
  tmp_i1 = __gmon_start__();
  return tmp_i1;
}

void deregister_tm_clones(void)
{
  return;
}

void register_tm_clones(void)
{
  return;
}

void __do_global_dtors_aux(void)
{
  if (completed_6288 == '\0') {
    __cxa_finalize(__dso_handle);
    deregister_tm_clones();
    completed_6288 = '\x01';
  }
  return;
}

void frame_dummy(void)
{
  if (__JCR_END__ != 0) {
    _Jv_RegisterClasses(&__JCR_END__);
  }
  register_tm_clones();
  return;
}

void _fini(void)
{
  return;
}

