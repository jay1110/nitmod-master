# Weapon parser truncation and failed reloads

This is defensive integration work, not a claim of additional Nitmod gameplay
or instruction-for-instruction parser parity. No assets or wire structures
are changed.

## Corrected failure paths

CG_RW_ParseWeaponLinkPart, CG_RW_ParseWeaponLink, CG_RW_ParseViewType,
CG_RW_ParseClient and CG_RegisterWeaponFromWeaponFile previously broke out of
their loops on EOF and returned success. They now report an unterminated block
through CG_RW_ParseError. That function owns error-path source closure; callers
propagate failure without closing the handle a second time. A real closing
brace still completes each block normally.

CG_RegisterWeapon preserves the prior registered weaponInfo_t on a failed
forced parse. A first registration failure leaves an empty registered entry,
preventing repeated implicit load attempts; an explicit force can retry it.
No half-parsed part hierarchy, sound list or callback remains exposed after a
reported failure. Successful parsing replaces the previous entry normally.

This rolls back module-owned descriptor state only. Renderer/sound registration
calls already performed are engine-owned and are not undone or freed here.
It is not a memory-leak fix or a demonstrated explanation for a browser crash.
Separate weaponConfig parsing behavior and unsupported parser fields remain
outside this change.

## Regression coverage

The full-cgame fixture constructs a root/client/view/link/part hierarchy with
a registered model, sound and tag, then supplies zero through five closing
braces. It repeats these six cases with and without an existing registration,
twenty times (240 parse attempts). Assertions cover:

- EOF rejection at each nesting level and successful complete parsing;
- exactly one parser-source open/close;
- byte-for-byte preservation of a prior descriptor on failure;
- an empty cached entry on first failure;
- no non-forced retry after failure;
- successful replacement of prior data on a complete parse.

Native build, all 90 CTest tests, WASM build and Node loading/entrypoint probes
are run for this batch. Browser/server gameplay parity remains unverified.
