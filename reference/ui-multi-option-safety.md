# Multi-option UI state validation

The inspected ItemParse keyword names already exist in the typed UI. This
batch does not add a missing keyword or claim a new original menu layout.
It fixes concrete failures in the shared multi-option widget implementation.

Item_Multi_Setting previously dereferenced a missing typeData pointer after
its guarded lookup. Item_Multi_HandleKey allowed an empty list to reach index
0 or -1 and write an unintended value. Counts exceeding MAX_MULTI_CVARS also
allowed lookups past the fixed arrays.

CountSettings now treats missing or out-of-range lists as empty; lookup and
input handling reject them before accessing values. Setting display preserves
undefinedStr when provided, otherwise displays None Defined for invalid/empty
state. Missing cvar bindings do not invoke read/write callbacks. Normal string
and numeric selection, wraparound, and Custom/undefinedStr fallback remain.

Original Item_Multi_HandleKey in ui_ui_item.c was inspected: its valid-list
behavior uses mouse2 for decrement and mouse1/enter/mouse3 for increment.
The invalid-state guards are deliberate defensive deviations, not additional
behavioral parity claims.

The existing full-UI fixture now tests missing data, null items, negative/zero/
oversized counts, absence of writes on invalid input, both list modes in both
directions at every position of a three-item list, custom labels, and missing
cvar bindings. Native build and all 90 CTest tests pass. WASM cgame/ui builds
and Node module/entrypoint probes are also run. These are not browser visual
or dedicated-server gameplay verification. Pak files remain unchanged.
