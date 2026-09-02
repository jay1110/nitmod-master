# Landmine initial-trigger team filter

Update: the owner bit-0x100 rule below is now ported as well; historical pending
notes in the initial section are superseded by the owner-rule section.

Original G_LandmineThink tests g_friendlyFire bit 0x20 at ELF 0x8ad17.
When a parent exists and the candidate's session team equals G_LandmineTeam,
it compares candidate and parent entityState.clientNum (offset 0xac), rejecting
different client numbers. Original comparisons at 0x8af54/0x8af5a are pinned
by byte assertions against the hash-checked reference module. This is not a
pointer identity test; the owner need not itself have a client object for this
specific rule. Parent absence bypasses the filter.

G_NITMOD_MineTeamContact implements only this rule and safely rejects missing
candidate/client pointers. G_LandmineThink invokes it before the existing
contact geometry. LandminePostThink intentionally does not: the original
post-trigger hold test has no corresponding team exclusion. No Cvar definition
or protocol message changes are necessary; the existing g_friendlyFire value
is used without broadening the meaning of its other bits elsewhere.

Tests cover 4096 flag/team/parent/owner-identity combinations (all flags 0..511),
plus missing candidate/client guards. Separate candidate/owner objects with
equal client numbers verify the owner exception; their entity numbers do not
determine the result. A compiled offsetof assertion pins native clientNum to
0xac, and source checks pin the initial-trigger hook and absence from post-think.
These are policy and source-integration checks, not actual query/contact replay.

Original bit 0x100's owner/weapon exception, Omni-bot filtering and pretrigger
event, private weapon variant and live gameplay parity remain unported. The
existing geometry and trigger transition tests remain separate. Native/WASM
builds and all 81 CTests pass; no cgame/ui message or structure changes.

## Owner exclusion with pliers exception

Original ELF 0x8ac60 tests bit 0x100; equal entityState.clientNum values reach
the entityState.weapon comparison with 0x14 at 0x8ade0. The hash-pinned original
BG_RegisterWeapon filename extractor resolves original identity 20 to
pliers.weap, normal definition. This is translated to native WP_PLIERS, never
copied as a numeric native weapon ID. The weapon-path reference test asserts
that mapping and the production semantic enum; instruction tests pin both
the bit mask and original weapon comparison.

When a parent exists and bit 0x100 is set, a matching owner client number is
excluded unless the candidate's s.weapon is WP_PLIERS. Team affiliation does
not gate this rule. The earlier bit-0x20 teammate exclusion still applies
independently and before this rule. Parent absence bypasses both. Post-trigger
holding logic still uses neither filter.

The expanded executable matrix has 12288 cases: all flags 0..511, candidate
teams Axis/Allies, parent present/absent, same/different client numbers and
MP40/pliers/smoke-marker weapon identities. playerState.weapon is intentionally
opposite to the tested entityState choice, detecting a wrong-field port. This
tests the isolated policy and pinned hook, not real engine candidate queries.
Omni-bot filtering/pretrigger callbacks, the private mine variant and runtime
original/browser parity remain outstanding. Native/WASM builds and 81 tests pass.
