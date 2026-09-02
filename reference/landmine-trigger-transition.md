# Landmine trigger collision transition

Latest follow-up: the typed precise contact consumer and its default-off Cvar
are now active; see precise-landmine-contact.md. Earlier pending notes below
describe the state before that port. Private mine/caller behavior remains open.

Update: the previously unmapped 0xfc field is now recovered as onFireStart;
see the trigger-latch section below. The initial audit is retained as history.

Original LandMineTrigger is ELF 0x8de70, size 0xad. Instructions at 0x8de73
and 0x8de93 load 0x04000000 and store it in the mapped contents field before
trap_LinkEntity. The native implementation instead changed contents to
CONTENTS_CORPSE. It now uses CONTENTS_BODY, consistent with the recovered spawn
value. These two exact instruction encodings are checked against the
SHA-256-pinned reference artifact in test_weapon_cvars_reference.py.

The native weapon branch retains its existing nextthink=time+100,
think=LandminePostThink, teamNum+=8 and s.time=time. The original private
weapon 0x33 instead schedules a smoke callback and sound; that branch is not
mapped onto WP_LANDMINE. The additional original store at entity offset 0xfc
is also not ported without a verified semantic field mapping. Accordingly this
is partial trigger reconstruction, not whole-function parity.

The full-qagame integration test now directly calls actual LandMineTrigger and
LandMinePostTrigger for two teams, three times and BODY/CORPSE starting contents
(12 profiles). The engine double requires exactly one link call with the whole
entity unchanged except for BODY contents at that boundary. After return it
checks the whole entity against the expected timer, callback, team and timestamp
changes. Post-trigger must only select G_ExplodeMissile at time+300. Unexpected
engine calls fail the test. Existing 720 projectile damage profiles still pass.

No real world link, contact detection, mine visibility, arming operation or
original runtime replay is exercised. The change needs live collision and
client-prediction comparison; it introduces no new network message. Native and
WASM builds and all 80 CTests pass.

## Trigger latch mapped to onFireStart

The compiled layout probe now reports density=244, dmgFlags=248,
onFireStart=252 (0xfc), onFireEnd=256, nextWeapon=260 and teamNum=264, each
four bytes, identically in ET 2.60 and ET:Legacy. gentity_t.s starts at offset
zero, additionally asserted by the native full-source test. Original trigger
instructions at 0x8ded2/0x8ded7 store integer 1 at 0xfc. The read/test/branch
at 0x8e1cf in original sEntWillTriggerMine uses this latch to select the broad
distance test when precise triggering is enabled. Both instruction sequences
are pinned against original bytes. This identifies an entity-type-specific
trigger latch, not a fire timestamp for this mine.

LandMineTrigger now sets s.onFireStart=1 after the timestamp, preserving original
link-call ordering. The transition test covers initial latch values -3, 0 and 7,
expanding to 36 profiles. The whole-object link-boundary check proves the latch
is still unchanged during linking and becomes 1 afterward. Post-trigger retains
it. Current cgame's normal missile loop-sound path does not use onFireStart for
volume; its mine rendering branch uses teamNum/density/modelindex2. No new
cgame or ui message/parser is required by this field write.

The precise-contact Cvar/geometry and private mine variant remain unported;
setting the original latch alone does not implement that behavior. Native/WASM
builds, all 80 CTests and the actual 60-row compiled shared-layout comparison
pass. This is still not original gameplay or browser rendering parity.
