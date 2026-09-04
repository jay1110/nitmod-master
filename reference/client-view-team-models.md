# First/third-person team weapon models

Original CG_RW_ParseViewType (sorted/cgame_client.c) registers model,
axisModel, alliedModel and three skins in a six-handle record per view.
CG_AddPlayerWeapon (sorted/cgame_ents.c, labels da23c/dc091) selects team
models and skins independently, falling back to the generic handle on zero.
The first-person record is at original weapon offsets 0x5d8..0x5ec and
third-person at 0x5c0..0x5d4. These offsets are evidence, not runtime storage.

Typed cgame adds viewTeamModel[W_NUM_TYPES][3]. The existing transactional
weapon loader reads axisModel/alliedModel inside firstPerson/thirdPerson.
Both active CG_AddPlayerWeapon branches use CG_NitmodViewMedia. Existing
disguise team swapping and the satchel exemption remain before selection.
The native third-person Axis skin typo (reading the first-person skin) is
removed. This is presentation only; no weapon IDs, network layouts or pak
assets change. weaponInfo_t is private cgame storage, not an engine ABI type.

Full cgame tests register both view blocks, including a zero-returning model,
exercise 48 view/team/fallback combinations with bytewise checks that all
other refEntity fields stay untouched, and verify malformed reload rollback
and successful reload clearing stale overrides. Tests cover the helper used
by the renderer, not a full rendered/disguised-player browser scene.
Original binary sources remain unchanged. Live visual parity is pending.
