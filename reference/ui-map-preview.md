# UI map and campaign previews

UI_DrawMapCinematic was rewritten from the original mapped lifecycle
(UI ELF 0x1e1e0): handle -1 starts once, nonnegative handles run/set extents/draw,
failed starts become -2 and return for that frame, later frames use the static
preview. Campaigns use the static map preview without starting a movie.
Missing map names cannot be formatted as file paths. Existing selection
cleanup remains owned by the catalog/feeder paths.

Both preview entrypoints now resolve game type and map/campaign selection
before accessing arrays. The original/native >count check is deliberately
corrected to >=count. Invalid selections reset to row zero only for nonempty
bounded catalogs; empty/invalid catalogs draw unknownmap without a fake row.
Local game-type indices are validated before gameTypes[] access. Campaign
pin iteration is bounded and dereferences only pointers owned by the active
map catalog with non-null names. The original valid-layout rendering remains.

Full UI tests cover local/network selection, successful repeated playback,
failed playback and delayed fallback, count-equal selection reset, empty and
oversized catalogs, campaign fallback, invalid local game type and malformed
campaign map references. These are deterministic syscall/layout-state tests,
not live browser screenshot parity. No pak assets are changed.

## Filter/count boundary checks

UI_MapCountByGameType validates network game-type bit positions and
map/campaign counts before accessing arrays or shifting masks. Unsigned
masks support bit 31 without a signed-shift overflow. Visibility flags are
cleared across the bounded catalog, including invalid filters and entries
left over after a catalog shrinks. UI_SelectedMap rejects invalid bit positions.
Full-UI tests cover both feeders over all 32 bit positions, visible-row text,
out-of-range rows, oversized/negative catalogs and invalid local indices.

The decompiled UI_FeederCount in ui_ui_misc.c uses ui_netGameType for both
feeders 1 and 4. Both native feeders now share that filter, including ordinary
maps in the local list. UI_SelectedMap uses the same network category for
row-to-catalog mapping, matching UI_FeederSelection_part_24. Tests deliberately
set opposite local/network categories and verify counts and final-row text.
Local preview/cinematic selection retains its separate local game type, as
observed in UI_DrawMapPreview and UI_DrawMapCinematic; it is not globally
replaced by the network setting. Existing local-index safety guards remain.
This ports list behavior, not the complete skirmish/start-server workflow.
