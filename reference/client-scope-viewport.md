# Scope sway and viewport semantics

Original CG_CalcViewValues (cgame ELF 0xbc2b0) contains the zoom sway branch:
nonzero zoom and no EF_MG42_ACTIVE; spread is aimSpreadScale/255. FG42 scope
uses pitch/yaw minima 0.4/0.8, other weapons 0.1/0.2. Frequencies are 0.24/0.12
and amplitudes 0.13/0.7. The native code previously used the lower minima for
every weapon and additionally excluded EF_AAGUN_ACTIVE. Original protocol
now uses CG_NitmodZoomSway; native layout keeps its old branch. No random
draws, gameplay aimspread or network fields are modified.

Original CG_Letterbox (ELF 0xbaec0, Ghidra 0xcaec0) scales dimensions by the
supplied percentages, clears their low bit and optionally centers the result.
It does not read cg_letterbox or apply native ET's additional 85-percent
height reduction. CG_NitmodLetterbox now implements this for original servers;
uncentered calls preserve the preselected origin. The original inlined
CG_CalcViewValues normal viewport likewise uses full dimensions. Native and
reconstructed et260-layout server paths retain their letterbox behavior.

Deliberate safety difference: reject negative/nonfinite/unrepresentable
dimensions before conversion; use widened percentage arithmetic. Pixel-level
rounding at extreme float boundaries is not claimed bit-identical to x87.

Tests invoke the real CG_ZoomSway and CG_Letterbox adapters: 14,760 sway
combinations (3 protocols, 2 weapons, 4 flags, 3 zoom states, 5 spread values,
41 times); 144 viewport cases (4 resolutions, 3 percentages, centering and
letterbox toggles across 3 protocols); malformed-dimension rejection.
Full native CTest and WASM/Node entrypoint checks run. This closes two camera
differences, not the entire prediction or weapon subsystem. Live browser
visual parity remains unverified. Pak assets and original modules are unchanged.
