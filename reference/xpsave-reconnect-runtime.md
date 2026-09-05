# Nitmod XP-save reconnect runtime

The original `nitrox_XPSave_LoadXP` at `0x001035d0` gates loading with bit 1
of `g_XPSave`. Its expiry branch compares elapsed real time with
`g_XPSaveMaxAge` unless bit 4 is set.

The reconstructed ET 2.60 tree now applies those proven controls to its typed
IP reconnect cache:

- bit 1 enables cache insertion, lookup, serialization and restoration;
- `g_XPSaveMaxAge` is interpreted in seconds and safely saturated when
  converted to engine milliseconds;
- bit 4 disables expiry;
- disabling persistence clears serialized `xpbackup*` values on the next
  session write;
- lookup iterates `MAX_XPSTORAGEITEMS`, not the unrelated 1024-entry ban list;
- the four parsed address bytes are copied into the comparison word without
  an unaligned pointer cast.

This is reconnect/session persistence only. Original database/GUID identity
and unproven bits are deliberately not inferred from raw offsets.
