# Campaign UI loading and lookup

## Reference and scope

Original ui.mp.i386.so symbols: UI_LoadCampaigns 0x11c10 (includes its file
parser), UI_FindCampaignInCampaignList 0x11b90, UI_DescriptionForCampaign
0x119f0, UI_NameForCampaign 0x11ac0, BG_LoadCampaignSave 0x41e0.
The corresponding decompile is ui_ui_misc.c. This is a typed consolidation
and correction of the existing ET campaign path, not five previously absent
Nitmod gameplay features. UI_LoadCampaigns still owns file enumeration,
save-progress attachment and final catalog sorting.

ui_nitmod_campaign.c now owns campaign-record parsing, arena linking,
next-campaign ordering and current-map lookup. CMake and SCons use the same
implementation. No PK3, menu definition, campaign asset or protocol changed.

## Retained behavior

- Parse shortname, name, description, image, next, initial, type, maps and
  maptc through the engine PC interface and UI-owned String_Alloc storage.
- Type substring flags wolfsp/wolfmp/wolfsw/wolflms; initial SP unlock;
  cinematic/shot handles -1; mapTC upper corner lower corner plus 650.
- Semicolon-separated maps resolve case-insensitively against mapLoadName;
  use the first arena match, omit missing maps, retain duplicates and order.
- Follow the first initial SP campaign by next shortname; preserve complete
  records and their map pointers when sorting by campaign title afterwards.
- campaign.dat keeps its original i386 byte layout: little-endian 32-bit
  ident, one-byte version, 32-bit count/profile hash, then per-record hash,
  progress, and exactly progress completed-map hashes. Case-folded profile
  hash weights start at 119; trailing file bytes remain ignored.

## Deliberate fixes, not literal buggy-original parity

Records commit only at their closing brace. Missing shortnames, incomplete
records, overlong map tokens and more than ten resolved maps are rejected;
earlier complete records survive. File handles close on every parser exit.
This prevents an unfinished file's fields leaking into the next file.
The typed MAX_CAMPAIGNS limit is checked within each file, not only between
files. UI string-pool allocations retain the existing lifetime; aborted
record strings are not individually reclaimed.

Next-link traversal stops at a missing target or a visited campaign, instead
of looping forever on self-links/cycles. Unreachable records retain their
existing order. Current-map lookup restarts its map cursor for each campaign
and compares BSP load names, not colored display titles. Missing pointers
and invalid counts are skipped/rejected.

BG_LoadCampaignSave checks file length before every read, version, profile,
campaign count and progress before array access; all partial output is cleared
on failure. Explicit little-endian decoding replaces native-endian reads.
The writer is unchanged, including its existing native-endian portability
limitation; this change does not claim a completed macOS persistence backend.

## Checks

CheckCampaignCatalog in test_nitmod_ui_bitflag.c invokes the real parser with
engine token fixtures: every token-prefix truncation, partial-file recovery,
map-count/token-length boundaries, capacity limits, 64 three-node next-link
graphs and 30 campaign/map lookup positions. It also invokes UI_LoadCampaigns
end-to-end with a two-record file, missing save, chain order, sorting, arena
pointer retention, lookup, and a subsequent failed reload.

CheckCampaignSave tests every byte-prefix truncation of all eleven legal
progress lengths (0..10), signed/over-capacity counts, wrong profile/version,
empty saves and a full-capacity save. The mock refuses reads beyond the
advertised file length; failed loads must leave all output zeroed.

These are deterministic integration fixtures, not a live browser campaign-menu
or original-binary replay comparison. The subsequent body-lean port and its
resolved state mappings are documented in client-player-lean.md.
