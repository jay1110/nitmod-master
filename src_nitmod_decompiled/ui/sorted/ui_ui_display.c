/**
 * @file ui_ui_display.c
 * @brief ui_display
 *
 * Recovered from Enemy Territory ui.mp.i386.so
 */

#include "ui_types.h"
#include "ui_globals.h"
#include "ui_imports.h"
#include "ui_ui_display.h"

uint32_t Display_KeyBindPending(void) {
  return g_waitingForKey;
}

int Display_VisibleMenuCount(void) {
  int tmp_i1;
  uint *tmp_pu2;

  if (menuCount < 1) {
    tmp_i1 = 0;
  }
  else {
    tmp_pu2 = &g_dat_003f16c8;
    tmp_i1 = 0;
    do {
      if ((*tmp_pu2 & 0x100004) != 0) {
        tmp_i1 = tmp_i1 + 1;
      }
      tmp_pu2 = tmp_pu2 + 0x346;
    } while (tmp_pu2 != &g_dat_003f16c8 + menuCount * 0x346);
  }
  return tmp_i1;
}
