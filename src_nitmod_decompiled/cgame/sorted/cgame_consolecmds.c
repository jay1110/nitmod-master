/* Client console commands — recovered from qagame.mp.i386.so Ghidra decompile */
#include "nitmod_types.h"
#include "nitmod_globals.h"
#include "nitmod_imports.h"
#include "cgame_consolecmds.h"

uint32_t CG_ConsoleCommand(void)
{
  uint32_t tmp_u1;
  int tmp_i2;
  uint32_t tmp_u3;
  int tmp_i4;
  
  if (g_unk_01047b00 != 0) {
    tmp_u1 = CG_Argv(0);
    tmp_i2 = Q_stricmp(tmp_u1,&g_unk_0011288a);
    if ((((tmp_i2 == 0) || (tmp_i2 = Q_stricmp(tmp_u1,"say_team"), tmp_i2 == 0)) ||
        (tmp_i2 = Q_stricmp(tmp_u1,"say_teamnl"), tmp_i2 == 0)) ||
       (((tmp_i2 = Q_stricmp(tmp_u1,"say_buddy"), tmp_i2 == 0 ||
         (tmp_i2 = Q_stricmp(tmp_u1,&g_unk_00112768), tmp_i2 == 0)) ||
        ((tmp_i2 = Q_stricmp(tmp_u1,&g_unk_00113436), tmp_i2 == 0 ||
         (tmp_i2 = Q_stricmp(tmp_u1,&g_unk_00113439), tmp_i2 == 0)))))) {
      tmp_u3 = ConcatArgs(1);
      tmp_i2 = need_escape(tmp_u3);
      if (tmp_i2 != 0) {
        tmp_u3 = ConcatArgs(1);
        tmp_u3 = escape_string(tmp_u3);
        tmp_u1 = va("%s \"%s\"\n",tmp_u1,tmp_u3);
        trap_SendClientCommand(tmp_u1);
        return 0xffffffff;
      }
    }
    tmp_i2 = 0;
    do {
      tmp_i4 = Q_stricmp(tmp_u1,(&commands)[tmp_i2 * 2]);
      if (tmp_i4 == 0) {
        (*(void *)(&g_ptr_CG_TestGun_f_0013d904)[tmp_i2 * 2])();
        return 1;
      }
      tmp_i2 = tmp_i2 + 1;
    } while (tmp_i2 != 0x44);
  }
  return 0;
}

void CG_InitConsoleCommands(void)
{
  Elf32_DynTag_x86 *pEVar1;
  uint8_t **tmp_ppu2;
  
  tmp_ppu2 = &commands;
  do {
    pEVar1 = &((Elf32_Dyn_x86 *)tmp_ppu2)->d_tag;
    tmp_ppu2 = (uint8_t **)((int)tmp_ppu2 + 8);
    trap_AddCommand((uint8_t *)*pEVar1);
  } while ((Elf32_Dyn_x86 *)tmp_ppu2 != _DYNAMIC);
  trap_AddCommand("kill");
  trap_AddCommand(&g_unk_0011288a);
  trap_AddCommand(&g_unk_00111bdf);
  trap_AddCommand(&g_unk_0011276b);
  trap_AddCommand("notarget");
  trap_AddCommand("noclip");
  trap_AddCommand("setviewpos");
  trap_AddCommand("nofatigue");
  trap_AddCommand("listcampaigns");
  trap_AddCommand("team");
  trap_AddCommand("follow");
  trap_AddCommand("callvote");
  trap_AddCommand("vote");
  trap_AddCommand("follownext");
  trap_AddCommand("followprev");
  trap_AddCommand("start_match");
  trap_AddCommand("reset_match");
  trap_AddCommand("swap_teams");
  trap_AddCommand(&g_unk_0011e3bb);
  trap_AddCommand("bottomshots");
  trap_AddCommand("commands");
  trap_AddCommand("lock");
  trap_AddCommand("notready");
  trap_AddCommand("pause");
  trap_AddCommand("players");
  trap_AddCommand("readyteam");
  trap_AddCommand("ready");
  trap_AddCommand(&g_unk_00112813);
  trap_AddCommand("say_teamnl");
  trap_AddCommand("say_team");
  trap_AddCommand("scores");
  trap_AddCommand("specinvite");
  trap_AddCommand("speclock");
  trap_AddCommand("specunlock");
  trap_AddCommand("statsall");
  trap_AddCommand("statsdump");
  trap_AddCommand("topshots");
  trap_AddCommand("unlock");
  trap_AddCommand("unpause");
  trap_AddCommand("unready");
  trap_AddCommand("weaponstats");
  trap_AddCommand("fireteam");
  trap_AddCommand("showstats");
  trap_AddCommand("ignore");
  trap_AddCommand("unignore");
  trap_AddCommand("campaign");
  trap_AddCommand("setclass");
  trap_AddCommand("imready");
  trap_AddCommand("say_buddy");
  trap_AddCommand("setspawnpt");
  trap_AddCommand(&g_unk_00112889);
  trap_AddCommand("vsay_buddy");
  trap_AddCommand("vsay_team");
  trap_AddCommand("where");
  trap_AddCommand(&g_unk_00113439);
  trap_RemoveCommand("+lookup");
  trap_RemoveCommand("+lookdown");
  trap_RemoveCommand("-lookup");
  trap_RemoveCommand("-lookdown");
  trap_AddCommand("playdead");
  trap_AddCommand("dropobj");
  trap_AddCommand("damage");
  trap_AddCommand("sslogin");
  trap_AddCommand("sslogout");
  trap_AddCommand("sclogin");
  trap_AddCommand("sclogout");
  return;
}

uint8_t * CG_Argv(uint32_t param_1)
{
  trap_Argv(param_1,buffer_12934,0x400);
  return buffer_12934;
}

