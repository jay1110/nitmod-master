# Original dynamite-count reconstruction

Status: target lookup, primary association and count/compare consumer ported.
Production-function WASM test passes for multiple charges, wrong association,
flag absence, client-slot exclusion and both count/abort outcomes. Real
plant/defuse/explode and entity-reuse gameplay verification remains pending.

Follow-up disassembly confirmed the jump at 0xb1ec2 to 0xb1ed6, where the
original targetname token is parsed numerically and compared with the count.
That original quirk is now preserved. The notes below record the investigation
that led to the port; their implementation checklist is historical.

`G_ScriptAction_Accum` original ELF `0xb1e20` resolves the target with
`BG_StringHashValue` and `G_FindByTargetnameFast`. The loop at `0xb1e90`
starts at entity 64 and counts a flag at entity offset `0x4fc` together with
an objective entity number at `0x500`. The 0x184fc/0x18500 displacements
include the initial 64 * 0x600 entity offset, not additional structure fields.

The decompiled planting path in `nitmod_weapons.c` near line 6646 sets
flag bit 1 and copies the objective's first entity-state integer (`s.number`)
into the association field. This is not a pointer despite Ghidra's float
pointer type. The corresponding ET260 planting path in `g_weapon.c` sets
`traceEnt->etpro_misc_1 |= 1`, but does not save the objective number.

Current `BotGetTargetDynamite` instead performs spatial/damage checks on
armed dynamite. It is not equivalent to the original association scan.

Required next implementation group:

- Verify both objective-trigger and constructible planting branches in disassembly.
- Introduce a typed, server-owned objective association with explicit reset on
  spawn/reuse; audit defuse and explosion lifecycle before consuming it.
- Match the original entity scan and association semantics; do not silently
  substitute a proximity test or count all armed dynamite.
- Check the original branch after storing the count: the disassembly jumps
  to 0xb1ed6, apparently sharing a subsequent comparison/abort path. Confirm
  the operand before porting that observable behavior.
- Add full production-function WASM tests for objective mismatch, multiple
  charges, entity reuse, defuse, missing target, and script continuation.

No asset or engine change is necessary for this server-side state. Existing
counting behavior is intentionally unchanged until its lifecycle is mapped.
