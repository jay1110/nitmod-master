# Sixteen linked parts and primary weapon animation

Evidence: original CG_RW_ParseViewType accepts part indices below 0x10;
CG_GetPartFramesFromWeap in sorted/cgame_client.c exempts index 16 from
the hide-mask check but still evaluates its animation bit. The original
weapon animation loader in sorted/cgame_servercmds.c sets 0x10000 for the
animated primary model and packs the hide field with a shift of eight.

W_MAX_PARTS is now 16. This expands private cgame model storage, parser
bounds and the generic first-person attachment loop together. The parser's
primary animation bit follows that constant. CG_GetPartFramesFromWeap now
evaluates primary animation instead of returning early: prior sequences
with the selected bit contribute numFrames to the offset, then parent frames
minus firstFrame are added; backlerp is inherited. Unanimated parts retain
their state, hidden parts return false without mutation.

The original packed masks overlap: animation bits 8..15 occupy positions
also used by hide bits 0..7, and bit 16 overlaps hide bit 8. This format is
preserved, not reinterpreted as two independent 16-bit masks. The hide shift
uses unsigned arithmetic. Invalid slot/sequence/pointer inputs fail closed;
frame sums are computed in 64 bits and rejected if not representable as int.
These safety checks deliberately differ from unchecked original arithmetic.

Full-cgame tests cover all 17 identities including the primary model, every
native animation sequence, toggle bit and four animated/hidden combinations,
with bytewise refEntity checks. Existing team-part parser tests now exercise
all 16 slots in both views. Overflow and invalid index cases are covered.
The raw animation-file loading syscall path and browser-rendered animation
parity are not established by these tests. Mortar-specific attachment and
third-person generic linked-part rendering remain separate open work.
No pak assets, shared weapon IDs or engine/network structures are changed.
