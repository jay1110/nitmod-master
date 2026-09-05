# Recovered body bounds and fast-solid prediction

The original `nitrox_HitboxHeight` body-height decisions are now applied to
qagame's typed entity bounds immediately after pmove and before linking.  The
mapped `g_realBody` bits select a 36-unit standing box (bit 2), a 4-unit prone
box (bit 4), and an 18-unit crouched box (bit 8).  Any enabled segmented
`g_hitboxes` mode selects the same recovered 4-unit prone body box.  The
horizontal expansion branch is deliberately not repeated because this ET 2.60
tree already uses `-18..18`; expanding it again would produce `-21..21` and
would not match the original.

The client `cg_fastSolids` path is active again: all solids remain available to
fireteam traces, while ordinary prediction clips against the nearby 512-unit
set.  Both snapshot arrays and the inline-model midpoint index are explicitly
bounded, which preserves the recovered behavior without reproducing unsafe
native indexing in WASM.

`g_realHead` bit 0 now also selects the original symmetric
`[-6,-6,-6]..[6,6,6]` temporary head cube.  Disabled mode retains ET's
asymmetric `[-6,-6,-2]..[6,6,10]` box.  The old module obtains its precise
position through private MDX helpers; the reconstruction uses the typed engine
`tag_head` lookup and its existing stance fallback instead of copying private
offsets.  The other segmented `g_hitboxes` bits remain open.  No package or
menu asset is changed by this batch.
