/* ELF runtime, C++ cleanup
 * Recovered from Enemy Territory ui.mp.i386.so Ghidra decompilation
 */

#include "et_ui_types.h"
#include "et_ui_globals.h"
#include "et_ui_imports.h"
#include "et_ui_runtime.h"

void __do_global_dtors_aux(void)

{
{  if (completed_6288 == '\0') {
    __cxa_finalize(__dso_handle);
    deregister_tm_clones();
    completed_6288 = '\x01';
  }
  return;
}

void frame_dummy(void)

{
{  if (__JCR_END__ != 0) {
    _Jv_RegisterClasses(&__JCR_END__);
  }
  register_tm_clones();
  return;
}
