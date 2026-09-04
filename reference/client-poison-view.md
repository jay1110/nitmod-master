# Poison camera, FOV and lean integration

Original cgame ELF CG_CalcFov 0xbbe20 and CG_CalcViewValues 0xbc2b0
(Ghidra 0xcbe20 and 0xcc2b0) read player eFlags bit 0x00200000.
The original qagame ClientThink_real poison tick also tests that bit before
reading g_poison and the poison weapon damage interval. It is not the native
ET EF_VIEWING_CAMERA meaning. NITMOD_EF_POISONED is consequently local to
the original-protocol view adapter; native/reconstructed et260 servers do not
activate it. No shared engine struct or qagame protocol was changed.

Implemented original visual behavior:

- First-person poison phase is timeSeconds * 0.3 * pi. Roll adds sin(phase)*36,
  yaw sin(phase)*24, pitch sin(phase*2.5)*12, after normal zoom sway.
- Lean follows poison rotation, so the displacement uses the combined angles.
  g_weapons bit 256 changes lean roll from lean/2 to lean/3.2; the full lean
  displacement remains unchanged. This completes the camera counterpart of
  the previously ported weapon/body lean.
- FOV poison phase is timeSeconds * 0.3 * 2*pi. Horizontal FOV adds sin*12;
  vertical FOV subtracts it. This adds to, rather than replaces, liquid warp.
  It sets RDF_UNDERWATER and the returned inwater result, as the original does.

CG_CalcFov is extracted from cg_view.c into cg_nitmod_view.c. Existing zoom
transitions, mounted FOV, intermission, game-view, death/follow handling,
liquid flags and mouse sensitivity remain in the real production function.
These existing paths are newly regression-tested, not newly ported features.
First-person poison/lean offsets are called where native lean previously ran;
native protocol retains its previous branch. The effect is recomputed from
base camera angles each frame rather than accumulated into network state.

## Verification

check_view.h runs in the full cgame test link. 3,024 actual CG_CalcFov calls
cover original/native/reconstructed layouts, poison on/off, air and each of
three liquids, 21 times, normal/sniper/binocular/tank/mounted/menu FOV.
The engine double requires exactly one world point-content query per call;
it checks projection, RDF flags, return value and zoom sensitivity.
492 poison/lean cases check combined angles and right-vector displacement.
Other syscalls remain unexpected/fatal in this test mode.

Native build, full CTest, WASM build and Node side-module entrypoint probes
are run. Live browser visual comparison and poison gameplay producers remain
outside this batch; this is not a claim of complete Nitmod parity.
Original binaries, PK3 contents and pak/menu assets remain unchanged.
