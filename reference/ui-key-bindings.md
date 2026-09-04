# Original UI key-binding workflow

Reference: original ui.mp.i386.so g_bindings at ELF 0x593e0, 61 records
of 32 bytes; Controls_GetConfig, Controls_SetConfig, Controls_SetDefaults
and Item_Bind_HandleKey in sorted/ui_ui_misc.c and sorted/ui_ui_item.c.
The original table includes +attack2, dropobj and globalstats. The active
typed UI table now exposes these; weapalt remains available without a default
key for compatibility. The existing mvactivate entry is retained.

The original handler can edit commands outside its fixed default table by
querying engine key ownership. This path is now active, including adding a
binding, clearing the first binding on reselection of either existing key,
and clearing both bindings with Backspace. Known commands support two keys,
replacement on a third key, conflict reassignment and engine-side deletion.
Escape cancels without restarting input; character events and backtick keep
capture pending. Binding text already queries engine-owned key state.

Intentional corrections: capture remains owned by the initiating item even
when focus changes; null/empty command items are rejected; -1 is never sent
as a key to clear. Conflict handling keeps unrelated keys rather than copying
the original's redundant intermediate clear/rebind calls.

The native bind_t contained an unused id member although every initializer
provided command plus six binding fields. Removing this private, unreferenced
member repairs shifted defaults and implicit zero bind2 initialization. The
original binary also has the extra word, so corrected default application is
not claimed byte/behavior-identical to that malformed layout. Tests check
right/left default actions and the full editing lifecycle against engine key
state, not just the table contents.

ET:Legacy cl_input.c registers +attack2/-attack2 as IN_Wbutton0Down/Up.
globalstats already has a cgame handler; dropobj is forwarded to the dedicated
server by the engine. This does not implement a reconstructed qagame dropobj
handler or change network messages. No pak/menu assets were changed.
Actual browser menu/input verification remains pending.
