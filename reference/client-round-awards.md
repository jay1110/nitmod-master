# Original round awards

Original cgame `awardNames` at ELF 0x13b320 contains 16 pointers, checked
directly against the unchanged original binary. They name frag/XP/goomba/
spree/headshot/damage/flying/accuracy/knife/revive/heal/revive-spree/panzer/
engineer/covertops/fieldops awards, not ET's 14 categories.

Original CG_Debreifing2_Awards_Parse reads wire slot 34, replaces semicolon
quote delimiters and consumes 16 name/team pairs. Original drawing skips
team 0, uses a 12-pixel row advance, 12-square award icons, and 13x9 team
flags at x+208. The reconstructed client now uses this layout and separate
typed storage for the original protocol. ET's server arrays and award enum
remain unchanged. Logical CS_ENDGAME_STATS maps to wire 34; notifications
invalidate the existing debrief cache. Initial map setup already clears it.

Names use a bounded shared 1024-byte pool. Parsing validates all 16 pairs
and commits only a complete record. Teams must be 0/1/2; excess tokens,
oversize input and missing pairs produce an empty award list. This is
deliberate defensive behavior beyond the original unchecked parser.

Tests check every row, colored names with spaces, all incomplete prefixes,
extra tokens, original slot mapping and cache invalidation through actual
server-command dispatch. All native tests and WASM load probes are run;
browser visual parity remains unverified. This ports client debrief display,
not the original server's computation of all 16 award winners. Pak unchanged.
