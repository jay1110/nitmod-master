/**
 * @file ui_runtime.c
 * @brief C++ Runtime
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 */

#include "ui_types.h"
#include "ui_globals.h"
#include "ui_imports.h"
#include "ui_runtime.h"

void __do_global_dtors_aux(void) {
  if (completed_6288 == '\0') {
    __cxa_finalize(__dso_handle);
    deregister_tm_clones();
    completed_6288 = '\x01';
  }
  return;
}

int _init(EVP_PKEY_CTX *ctx) {
  int tmp_i1;

  tmp_i1 = __gmon_start__();
  return tmp_i1;
}
