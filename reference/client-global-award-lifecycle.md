# Global award notification integration

Reference: original `nitrox_DrawPopup` (ELF32 0x49750), sorted
`cgame_nitrox.c`, and `pop`/`popaw` in sorted `cgame_servercmds.c`.
This supersedes the earlier generic-pop-only limitations recorded in
client-notification-chat-batch.md. The eleven award titles/descriptions
were already present; this change completes their shared notification path.

Awards now use the same fade/hold transition as generic notifications:
hold begins at the first sampled full-opacity frame; fade zero pauses the
state; finite durations clamp to the original bounds. Double time arithmetic
replaces the award path's overflowing signed subtraction. The shared active
state also activates the existing spree placement rule.

Ordinary pop messages still print while an award is active but cannot replace
or restart it. Original code temporarily copies that text and overwrites it
with the award description next frame; the port avoids the redundant copy.
The generic renderer does not draw a duplicate award panel. Reset clears the
award and its notification state. Missing client info suppresses rendering
without preventing the timer from expiring.

Rendering now uses original limboFont2/style 7, medium-blue background,
description-derived width/height, a 50-unit panel and three text baselines
at one quarter, one half and three quarters of panel height plus half the
description text height. The right widescreen anchor is retained/restored.
Empty award descriptions intentionally retain the original narrow panel.

Tests cover all eleven award lifecycles, ordinary-message priority, delayed
sampling, disabled fade, integer-limit timestamps, reset, invalid commands,
actual panel draw dimensions, duplicate-render exclusion and one-time logging.
Browser visual comparison remains open; no award sound is invented.
Pak, original modules and server-side award computation are unchanged.
