# Intermission configstring collision and private weapon media

Original CG_ServerCommand's `cs` switch (sorted cgame_servercmds.c) handles
0x1e as global fog and 0x21 as intermissionStartTime. Native ET uses 33 as
global fog, 36 as intermissionStartTime. A `cs 33` carrying a timestamp was
therefore interpreted as a fog restore, entering the engine renderer with
unrelated data. The renderer assumes a valid global fog on the loaded map.

CG_ConfigString now maps known logical core slots for original servers;
CG_ConfigStringModified maps the wire notification back to the logical slot.
Music queue, mover/construction names, reinforcement seeds, server toggles,
map XP and intermission time use the observed original numbering. Native
versioninfo has no mapped original counterpart and reads empty. Original
34..39 notifications are not routed to unrelated native callbacks; their
remaining original-specific handlers are not implemented by this change.
Later continuation: original slot 39 class health limits are now consumed
on demand by the crosshair HUD (see client-class-health.md).
Original slot 34 now supplies the 16 Nitmod round awards and invalidates the
debrief cache on updates (see client-round-awards.md).
Native/advertised et260 layouts retain native indices.

Fog parsing rejects incomplete, non-finite, negative, extra-token and invalid
restore messages. Colors must be 0..1, duration an integer, and depth must
remain positive when converted to float. Restore accepts two fields or the
six-field server representation. A genuinely valid fog command on a map
without global fog still depends on the engine's renderer contract.

`mes` now accepts original-server messages without a reconstruction-only
capability. Original nitmod_GetMapEndStats consumes five arguments in the
same bodyshots/headshots/kills/deaths/revives order as the existing typed
parser. Argument/numeric validation is retained.

Private weapon media: the original poison.weap, bomb.weap, poisongas.weap
and landmine_pgas.weap now load into four separate weaponInfo_t records at
map initialization. Wire IDs 47,48,50,51 have explicit lookup and failure
rollback. Existing assets are read only. This is media preparation only:
weapon ownership translation, banks, prediction and firing for these four
identities remain incomplete and are not enabled by the media cache.

Tests: actual cs/mes dispatch, no fog call for intermission timestamp,
malformed fog messages, valid set/restore and native-layout behavior;
unchanged original private .weap files parsed with model-registration stubs.
Live browser intermission and private-weapon gameplay remain unverified.
