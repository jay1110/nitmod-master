# Team models for linked weapon parts

CG_RW_ParseViewType in sorted/cgame_client.c accepts axisModel/alliedModel
within weaponLink/part. Original part records have tag plus six handles
(model/team models/skins), stride 0x58. CG_AddPlayerWeapon in cgame_ents.c
selects these in its linked-part loop (local_40c, labels da775/db490).

The typed partModel_t now stores teamModel[3]. Both view parsers register
these handles; ordinary first-person linked parts use CG_NitmodPartMedia
before the model-presence test. Model and skin fall back independently to
their generic handles. Disguise changes the selected team, except satchel.
Existing animation, tag positioning and powerup rendering remain in place.
The earlier native Axis-first skin predicate did not properly swap a
disguised Axis player's available Axis skin; selection now uses one team.

Part records are cleared by their existing definition initialization and
participate in transactional whole-weapon parsing. Full-cgame tests cover
both views and all native slots, all team/fallback combinations, malformed
reload rollback and duplicate-part replacement clearing old team handles.
Only model/skin fields may change in the output refEntity.

The follow-up extends W_MAX_PARTS to the original 16 indices; parser tests
now register every slot for both views. Indices outside 0..15 remain rejected.
Third-person part
definitions are parsed but the generic attachment loop is first-person.
Dedicated mortar bipod rendering still uses its native special path.
Original decompile's inconsistent fallback/index branches are not copied as
raw memory operations. Full original animation and browser visual parity
remain open. No pak assets, protocol IDs or original binaries are changed.
