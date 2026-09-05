# Campaign controls and persistence follow-up

Reference: UI_OwnerDrawVisible in sorted/ui_ui_misc.c and
BG_StoreCampaignSave in sorted/ui_ui_shared.c (original UI module).
This batch completes portability/bounds work on an existing typed campaign
path; it does not claim new Nitmod gameplay or a complete UI port.

The six map-exists ownerdraw flags and two playable/locked flags now use
UI_NitmodCampaignVisible. Valid selections retain the original count and
map <= progress comparisons. Flag combinations remain conjunctive. Invalid
catalog counts, campaign indices, map counts, selected maps and progress
hide the affected controls. Fractional valid map selectors retain integer
truncation; NaN and out-of-range values are rejected before conversion.
These bounds are intentional deviations from unchecked original accesses.

BG_StoreCampaignSave now emits the original little-endian i386 layout on
every host: ident, one-byte version, campaign count, case-folded profile hash,
then shortname hash, progress and exactly progress map hashes per campaign.
Hash accumulation is unsigned 32-bit modulo arithmetic. All record counts
are checked before FS_WRITE can truncate an existing save. Open failure
leaves the caller's header untouched. The engine's void FS_Write interface
cannot report partial writes; this is not an atomic filesystem transaction.

Tests invoke the actual ownerdraw dispatcher across all eight flags,
catalog/selection boundaries, all legal map counts/progress values, combined
flags and malformed float selectors. Writer tests compare independent
expected bytes and round-trip through the actual loader for empty, single
and full-capacity catalogs at every legal progress length. Invalid progress
in every record and invalid counts must cause no file open or input mutation.

No pak, PK3, menu assets, protocol or original reference modules changed.
Browser campaign-menu and real persistent filesystem testing remain pending.
