# Active team weapon count

Original qagame SHA-256:
`84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49`.
G_TeamCount ELF 0x558f0..0x55ae2 establishes three paths:

- Query -1 starts at one (the requester), skips the requester in the connected
  list and adds all other same-team clients. No weapon comparison is made.
- Ordinary weapon queries start at zero and match selected or latched weapon
  against either the query or weapTeamConversion[query]. A client counts once.
- Original IDs 36/37 (GPG40/M7) require the extra client flag at 0xbe4 and a
  base-rifle match using weapAlts. That private flag is not yet integrated.

## Recovered rifle-grenade subset

G_NITMOD_CountRifleGrenades now reconstructs the third path separately,
using native session team/selected/latched fields and an explicit per-slot
equipment flag array. GPG40 matches KAR98; M7 matches Carbine. Any nonzero
flag qualifies, each client counts once for the queried family, and the
requester is excluded. Current ammo and actual grenade weapon ownership
are not substitutes for this state. Invalid slot bounds/queries return -1;
callers must treat that as failure, not a zero count.

The original +0xbe4 field is a session equipment marker: the spawn weapon
assignment sets it when an allowed alternate weapon is a rifle grenade,
otherwise clears it (nitmod_weapons.c 337..353). ClientThink_checkWeapons
clears it when restricting that weapon. Session write/read/init code accesses
it in nitmod_game.c around 16460, 16661 and 16868, and userinfo publication
includes it around nitmod_client.c 2741. It must be integrated across these
paths before replacing active native rifle-grenade counting.

450 combinations test both families, selected/latched fields, zero/nonzero
flags and teams. Additional tests cover shared-cap inputs, requester exclusion,
empty lists, invalid indices/queries and null inputs. This isolated helper does
not change native session layout, persistence or protocol, and has no active
restriction call site yet.

The optional cgame rn receive field is now integrated separately and its
original token resolved. Session position 26 is documented, not migrated;
see reference/rifle-grenade-protocol.md. The server still does not publish a
new equipment state or replace active native rifle-grenade counts.

The conversion table is at ELF 0x2a5220 (PIC base 0x2a4614 plus 0xc0c).
The mapped non-identity ordinary pairs are Luger/Colt, MP40/Thompson,
Axis/Allied grenade, silenced Luger/Colt, KAR98/Carbine, Garand/K43,
akimbo Colt/Luger, scoped Garand/K43 and silenced akimbo Colt/Luger.
Weapon identities come from the separately extracted original item table;
original numeric IDs are not reused as native enum values.

G_TeamCount now lives in g_nitmod_teamcount.c and is used by existing native
restriction/airstrike callers. It reads actual level.clients, sortedClients,
sess.sessionTeam, playerWeapon and latchPlayerWeapon. Engine-owned connected
list validity is assumed as in ET; no new alive, bot or connection-state filter
is invented. All currently queried heavy weapons map to themselves, preserving
their existing counts. Native sentinel/team counts remain unchanged.

Known difference: GPG40/M7 queries retain native ET exact-match counting;
the original flag/base-rifle path is explicitly NOT claimed ported. Unmapped
native internal weapons also retain identity behavior. No protocol or UI
layout change is needed for the active ordinary-count integration.

Executable tests cover both directions of all nine pairs, latched-only match,
two matching fields counting once, requester exclusion, reversed list order,
other-team exclusion, heavy weapon identity, empty lists and retained native
rifle-grenade behavior. Host tests are not original-engine replay evidence.

G_NITMOD_CountSessionRifleGrenades now supplies the isolated rifle counter
from actual sess.rifleGrenadeStatus for connected slots. This is the existing
spawn/session/rn field, not a new inventory-derived flag. Nonzero values,
including negative values, retain original truth semantics. The 450 typed
count cases also exercise this adapter, with invalid-list/null cases. The
adapter is compiled but not yet called by native weapon restrictions; the
active G_TeamCount rifle behavior described above remains unchanged.

G_NITMOD_ReadWeaponCounts now atomically fills the composed policy's teamSize
and two weapon-count fields. Ordinary queries use equivalent-weapon matching;
GPG40/M7 use both session-qualified base-rifle families. It validates
requester entity/client array identity and every connected-list slot without
subtracting unrelated pointers. Errors preserve the entire input;
success preserves configuration. Tests cover all 450 rifle
cases, nine ordinary pairs in both directions, heavy count and invalid inputs.
The adapter remains outside the active native restriction path.

Team-size list mapping is now resolved, but cache refresh timing is not.
G_TeamCountPlayers
(ELF 0x55740) iterates original level+0x98 entries, while G_TeamCount
(ELF 0x558f0) iterates level+0x9c entries. Both use sorted slots at +0xa4.
The team-cache producer counts team 1/2 without requester exclusion; the
restriction fallback for other teams starts at one and excludes requester.
CalculateRanks (ELF 0x7c8c0; sorted nitmod_unknown.c) establishes +0x98 as
numConnectedClients: every nonzero pers.connected appends a sorted slot and
increments it. +0x9c increments only for non-spectators and maps to native
numNonSpectatorClients. The weapon loop uses that LENGTH of the sorted list,
not a new per-entry spectator filter. The earlier isolated rifle counter's
connected-length assumption was incorrect and has been corrected. Active
native G_TeamCount retains its historical connected-length behavior.

The snapshot now scans all connected slots for Axis/Allies population,
including the requester and connecting clients. Other teams use one plus
matching non-requester entries in the non-spectator-length prefix. Both
weapon families and ordinary matches use that prefix. Tests deliberately
separate the two lengths, exercise spectator fallback, connecting state and
reject a prefix longer than the connected list without partial output.

This reproduces the value at cache refresh, not stale-cache behavior: original
ClientBegin calls CalculateRanks then G_TeamCountPlayers, and team command
paths also refresh the cache explicitly. The helper recomputes on request;
these lifecycle hooks remain unported. Do not activate it as a parity-complete
replacement until refresh ordering and callers have been integrated.

## Explicit cache lifecycle (partial integration)

G_NITMOD_RefreshTeamPopulation now reconstructs the original two-team cache
from the connected list; G_NITMOD_ResetTeamPopulation invalidates it at map
initialization. ClientConnect, ClientBegin and ClientDisconnect call refresh
immediately after their existing CalculateRanks call, matching the reviewed
original tails. The ordinary live snapshot remains available for comparison;
G_NITMOD_ReadCachedWeaponCounts substitutes the cached Axis/Allies population
while preserving live weapon counts and the live other-team fallback.

Tests cover initial invalid cache, refresh, a team change before/after refresh,
both teams, disconnect/empty population, map reset, and invalid-list refresh.
Invalid input invalidates the cache rather than exposing partially counted
values, an intentional safety difference. Failed snapshot reads leave outputs
unchanged. A separate source test pins the three post-CalculateRanks hooks
and map reset. These are host tests, not original-engine replay evidence.

Bot/team-command refresh paths remain pending, and no gameplay restriction
caller uses the cached reader yet. Do not replace all CalculateRanks callers
with implicit refresh: that would lose the original explicit timing distinction.

Cmd_Team_f now also refreshes in the !SetTeam branch immediately before
G_SetClientWeapons, matching the original inline recount in nitmod_cmds.c.
The source hook test pins this placement. This does not claim completion of
the separate Nitmod class command or Omni-bot callbacks; those remain pending.

SetTeam's setweapons branch now refreshes after assigning sess.sessionTeam
and before the existing native G_SetClientWeapons call. Original SetTeam
(nitmod_unknown.c, inline recount before LAB_0006e1c2) uses precisely this
ordering, before ClientUserinfoChanged/ClientBegin. No extra CalculateRanks
is inserted: the existing list is intentionally retained until ClientBegin.
The hook test verifies the condition and relative positions. An integration
scenario changes Axis to Allies with a populated target team and demonstrates
that stale versus refreshed population changes the heavy-limit decision.
The native setter itself remains unchanged; only the cache hook is active.
