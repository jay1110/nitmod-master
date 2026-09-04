# Original UI catalogs: arenas, campaigns and mods

## Recovered behavior

The original ui ELF comparators are UI_SortArenas at 0x11270,
UI_SortCampaigns at 0x11320 and UI_SortMods at 0x15c90.
The sorted decompile is in ui_ui_misc.c. Its void return declarations are
decompiler artifacts: each comparator passes the result of strcmp to qsort.

Arenas sort by mapName; campaigns by campaignName. Both copy the title into
1024-byte scratch buffers, call Q_CleanStr and use case-sensitive strcmp.
Thus colors remain in stored/displayed titles but do not change ordering.
Mods sort by modName (directory), not modDescr, without stripping colors.
Equal keys have unspecified order, matching qsort rather than inventing a
case-insensitive or stable tie-break rule.

These sorts were absent from the ET UI loaders. The new ui_nitmod_catalog.c
supplies the typed comparators and bounded dispatch. Arena sorting runs at
the end of arena loading, before campaign parsing resolves mapInfos pointers.
Campaign sorting runs after chain order and savegame progress are assigned;
entire records move, preserving mapInfos/cpsCampaign pointers and progress.
Mod sorting runs after paired directory/description loading. Do not sort an
arena list after linking live campaign pointers; this is a load-time operation,
not an interactive reorder API. Reloading catalogs still follows the existing
load-arenas-then-load-campaigns lifecycle.

## Defensive integration

All three loaders now consume engine file-list strings with an explicit buffer
boundary rather than unbounded strlen scans. Mods require both strings in a
pair, permitting an empty description. Lists are initialized before the engine
call. Invalid/truncated suffixes stop parsing; valid preceding records remain.
Arenas/campaigns reject paths outside a single scripts-directory filename and
filenames that do not fit the existing 128-byte path buffer. Valid PK3 content
is only read, never rewritten. Negative/over-capacity sort counts do not enter
qsort; missing title pointers compare as empty strings, unlike the unchecked
original. Campaign file grammar and gameplay/network protocols are unchanged.

## Verification

CheckCatalog in test_nitmod_ui_bitflag.c tests 120 input permutations for each
of three catalogs, case-sensitive/color-stripped order, metadata retention,
campaign pointer retention, every prefix length of a paired-list sample, unsafe
paths and exact filename capacity. It also invokes the actual LoadMods menu
script against three FS fixtures: a valid unordered list with an empty description,
an entirely unterminated buffer, and a valid prefix followed by a broken record.
The test never opens, launches or modifies an installed mod.

No live browser/menu screenshot comparison is claimed by these fixture checks.
