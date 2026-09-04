# Original automatic weapon selection

CG_OutOfAmmoChange is at original cgame ELF 0xc91f0 (2821 bytes).
The sorted source is cgame_client.c. New cg_nitmod_ammo.c implements its
selection decisions using existing normalized ET weapon IDs and weapon banks.
cg_weapons.c applies the result through the existing finish/next-weapon paths.

Original-specific differences from the previous ET behavior:

- Pliers and a satchel detonator with pending ammo stay selected.
- Forced smoke-bomb exhaustion prefers Luger, then Colt. Dynamite, landmine
  and the representable tripmine prefer pliers.
- Satchel selects its detonator directly; mounted mortar/MG42 selects the
  portable variant without finish effects, matching the original early returns.
- Forced panzer/detonator exhaustion scans primary bank 3 first, skipping
  panzerfaust, then bank 2 and bank 4. ET previously preferred pistols after
  panzerfaust and could select the panzer again in later fallback.
- Only original IDs 36..38 (GPG40, M7, silenced Colt) use the alternate-parent
  step. The ET opposite-team-equivalent preference is not present here.
- General fallback scans primaries, pistols, then the current bank before
  invoking ordinary next-weapon selection.

The bank sentinel is important: finding zero selects WP_NONE and finishes
the decision, instead of skipping to another bank. This unusual detail was
checked against actual instructions at 0xc9396..0xc93af (forced branch) and
0xc9311..0xc932a (general branch). Bank 3 has twelve actual entries; bank 2
contains terminating zeroes. A depleted pistol bank can therefore terminate
selection before later banks. It is not a guessed fallback policy.

Unimplemented original poison syringe/bomb/mine IDs are still not represented
or aliased. The common typed bank already omits unsupported entries. Invalid
current-bank lookups start from bank/cycle zero instead of using unchecked or
stale original locals. Native and nitmod_csLayout=et260 paths retain ET behavior.
No server commands, weapon grants, shared weapon numbering or pak data change.

CheckAmmoSelection covers all 4096 primary ownership masks with/without a pistol
and force on/off (16384 cases), and checks both the decision helper and actual
CG_OutOfAmmoChange dispatch. Eleven explicit tool/deployment/alternate cases,
detonator retention/exhaustion and reconstructed-protocol bypass are included.
The dispatcher fixture deliberately holds binocZoomTime during finish calls:
it checks the chosen weapon, not audio/zoom/history side effects. Actual firing,
reload timing and browser/dedicated gameplay parity still require live validation.
