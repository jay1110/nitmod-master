# UI text and demo file actions

This batch hardens existing typed UI code; it does not establish new Nitmod
feature parity or change the client/server protocol. No pak assets are changed.

## Text callback

Original reference: `src_nitmod_decompiled/ui/sorted/ui_ui_misc.c`, UI_FileText.
The symbol inventory records original ui ELF address 0x00015830. The decompiled
callback opens a file, reads the reported length into a static buffer, appends
a NUL and closes the handle. The existing typed implementation had the same
unchecked read/index pattern.

The reconstructed callback preserves that behavior for lengths 0..4095. Null
or empty paths, missing handles, negative lengths and lengths >=4096 return
NULL. Open handles are closed on rejected lengths. Empty files return an empty
string without a zero-byte read. Oversized text is rejected, not truncated into
a potentially incomplete menu script. These checks deliberately improve error
handling; they are not claims of original invalid-input parity. The filesystem
read trap has no returned byte count, so short-read detection remains an engine
contract. UI_FileText is declared internally for testing, not as a VM entrypoint.

## Demo actions

UI_LoadDemos now bounds each NUL-terminated filename by the returned-list buffer,
checks name length before comparing its suffix and publishes only entries
actually parsed/allocated. Negative counts, missing terminators and inflated
counts no longer scan arbitrary memory. Valid ordering and case-insensitive
protocol suffix removal are unchanged. Nonmatching short names retain the
existing behavior rather than being silently filtered.

deleteDemo now rejects invalid counts/indices and null/empty names before
calling the engine. Names containing separators, a drive prefix, dot/dot-dot,
or exceeding the basename bound cannot escape the demos directory. Normal
selection still requests `demos/<name>.dm_<protocol>`. Tests intercept the delete
trap: no real file is removed. This does not add demo command escaping or
redesign the separate RunDemo playback action.

## Verification

The full UI harness checks 12 file-length/handle combinations, null/empty paths,
144 delete-selection/name combinations, and five list-loading scenarios,
including short names, case-insensitive suffixes, negative/inflated counts and
an entirely unterminated 30000-byte list. It asserts exact reads, closes and
deletion paths. The full native suite passes 90/90. WASM side modules build;
browser file-menu scenarios and full gameplay parity remain unverified.
