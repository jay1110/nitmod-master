# Original class health limits

Update: the 15-health fallback bonus now tests the target's Battle Sense
unlock bit 3, not its displayed level. See client-skill-masks.md. Earlier
references below to level 3 describe the initial approximation.

Original CG_UpdateClassesMaxHP reads wire configstring 39 into five class
limits, keyed S/M/E/F/C in soldier/medic/engineer/fieldops/covertops order.
The two unnamed Ghidra strings were checked in the original cgame ELF at
0x111e10 (S) and 0x106f00 (C).

CG_CrosshairClientMaxHealth (sorted cgame_client.c) indexes that table by
the target's real class. A positive limit is the final maximum: it does not
receive additional medic or skill multipliers, including for disguised
targets. Otherwise it uses 100 plus 10 per valid medic on the viewed player's
team, capped at 125, plus 15 at Battle Sense level 3, then the medic 1.12
multiplier. The port uses existing typed clientInfo_t and snapshot fields.

CG_NitmodCrosshairMaxHealth reads the current original configstring on demand
instead of retaining a second offset-based/cached class table. Thus initial
gamestate, cs 39 notifications and map resets automatically use current data.
Native or advertised et260 layouts keep their existing HUD calculation.
Invalid class/client indices return no health bar; malformed, nonpositive or
overflowing limits fall back to the standard calculation. These are defensive
differences from unchecked strtol/indexing, not new protocol fields.

The player crosshair draw path now consumes this maximum; vehicle health is
unchanged. Tests cover all five explicit limits, 125 class/medic/skill fallback
combinations, updated limits, invalid numeric input and client/class bounds.
This is client display support only, not implementation of server-side class
health cvars or complete gameplay health parity. Browser replay remains open.
