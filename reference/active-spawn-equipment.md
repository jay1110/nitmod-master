# Spawn attachments and dual SMG

Follow-up: medic primary suppression and its dualSMG interaction are active;
see active-medic-loadout.md.

The native Engineer spawn now checks the mapped restriction for GPG40/M7
before granting the attachment. The base Kar98/Carbine remains available.
The already-reset rifleGrenadeStatus becomes one only after an allowed grant;
existing post-spawn clientinfo publication and session storage carry rn.

g_dualSMG is registered with original default 0 and flags 0 (original cvar
table 0x2a9d30). The active spawn gives the opposite SMG when the primary is
MP40/Thompson, otherwise the team SMG. Covert ops are excluded. Medics receive
zero base reserve, other classes the native default; all get the default clip.
The extra weapon does not replace the selected weapon. Native knife-only mode
retains precedence. War modes 1..4 do not receive this normal-class addition;
their complete spawn loadouts remain separate work. Settings take effect at
the next equipment assignment.

Evidence: original G_AddClassWeapons, ELF 0x4ba20, nitmod_weapons.c. Its
dual-SMG branch follows primary assignment and uses a zero reserve multiplier
for medics; the alternate-weapon restriction precedes the grenade grant and
status update. Original arbitrary class tables, skill ability words and ammo
definitions are not activated by this patch; native AddExtraSpawnAmmo remains.

Full qagame tests execute SetWolfSpawnWeapons on both teams against combined
rifle caps and teammate counts, verifying ownership, ammo and rn. Dual-SMG
tests compare complete clients with the native baseline across four classes,
two teams and two loadouts. Existing client-token tests verify rn publication.
No new protocol field or pak change. Dedicated/browser gameplay not verified.
