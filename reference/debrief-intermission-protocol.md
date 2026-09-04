# Nitmod debrief/intermission protocol

The intermission data flow consists of three required replies and optional hit regions:

1. `impkd`: configured maxclients kill/death pairs on original servers (64 in the native ET path).
2. `imwa`: the same number of total weapon-accuracy values, without an invented 100 percent cap.
3. `imws <client>`: 26 weapon-stat triples (`shots hits kills`).
4. `imhr <client>`: four hit-region pairs (`count percent`) in `HR_HEAD`,
   `HR_ARMS`, `HR_BODY`, `HR_LEGS` order.

The `imhr` layout and request ordering are mapped from decompiled original
functions `CG_Debriefing_InfoRequests` (`0x00039290`),
`CG_Debriefing_ParseHitRegions` (`0x00039a00`) and
`Cmd_IntermissionHitRegions_f` (`0x00060600`), as recorded in original_function_symbols.csv.

Original servers omit imhr for zero total hits. It is requested alongside imws
only for the original protocol and never blocks score requests. The reconstructed
qagame currently sends an all-zero reply instead; this is a deliberate difference.
The graphical hit-region panel now uses the six original gfx/hr shaders,
50x50 silhouette, red percentage-alpha overlays and original display order
Head/Torso/Arms/Legs. Both arms intentionally share HR_ARMS. A Regions/Weapons
toggle in the existing weapon-stat area adapts the layout to the ET panel;
this toggle and placement are not claimed as original Nitmod layout parity.
Absent replies display unavailable data rather than fabricated zero hits.
Browser rendering and gameplay parity remain unverified. The test currently
checks source wiring and original shader paths, not rendered pixels.

All cgame replies are parsed into temporary typed arrays. State and received
flags change only after exact arity, numeric syntax and value ranges pass.
Changing the selected player invalidates both player-specific replies (`imws`
and `imhr`). No pak or menu asset is involved in this protocol.
