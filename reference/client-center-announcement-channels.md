# Original client centerprints and announcements

Source references: `src_nitmod_decompiled/cgame/sorted/cgame_client.c`
(`CG_CenterPrint`, `CG_PrintAnnouncement`), `cgame_servercmds.c`
(`announce` dispatch), and `cgame_ui.c` (`CG_DrawCenterString`,
`CG_DrawAnnouncement`, `CG_Text_Paint_Ext`). These are behavior references,
not production code. Full binary/runtime parity is not established.

## Implemented

- Explicit-priority original `announce` messages own a separate 1024-byte
  buffer, position, width, line count and timer; ordinary centerprints remain
  independent. Negative priorities cannot replace an active announcement;
  nonnegative priorities can. Announcements start at current time plus 2000ms.
- Original centerprint rendering uses limboFont2 at scale .25, proportional
  centering, at most 56 displayed bytes per logical line, and font-height + 2
  baseline spacing. Its first baseline is Y minus eight times the line count.
- Original text style 7 now draws the .75 virtual-pixel black shadow found in
  `CG_Text_Paint_Ext`; styles 3 and 6 retain offsets 1 and 2. Native protocol
  behavior is unchanged.
- Timers use bounded duration validation and double arithmetic. Reset clears
  announcement ownership. HUD alignment is restored after drawing.

## Deliberate deviations and remaining limits

The decompiled announcement routine writes wrapping/counting state into the
centerprint globals, uses the centerprint width for some announcement drawing,
and clears the centerprint timer on announcement expiry. The port deliberately
uses each channel's own state rather than reproducing these cross-buffer writes.
An explicit active flag permits creation at time zero. Invalid widths and null
messages are rejected. Existing centerprint producer priority behavior is retained;
this is not a claim that every original producer or announcement bug is reproduced.

## Verification

`CheckCenterChannels` in `tests/test_original_charge_dispatch.c` exercises the
actual renderer through mocked drawing syscalls: proportional placement,
line spacing and fractional shadow offset; independent buffers, replacement
rules, expiry, reset, invalid inputs and native-protocol exclusion. Native build,
full CTest suite and WASM side-module/entrypoint checks are required. Live browser
appearance and dedicated-server transcripts still need validation.
