# Original cgame command compatibility

The typed ET 2.60 client now covers this additional group from the original
`CG_ServerCommand` dispatcher:

- `cvs <request> <cvar>` reads a local cvar and returns the original quoted
  `cvs` response. Names and response delimiters are validated before emission.
- `cpm_map` shares the original popup-message path with `cpm`.
- `announce` supports localized center text, priority and optional prefix.
- `gamechat` strips the ET chat escape byte, enters team-chat history, prints,
  and follows the reconstructed client-log setting.
- `DM <client>` stores a bounds-checked FFA winner and shows the valid client
  name during gametype 8 intermission.

`DM` state uses `-1` until a valid command arrives and remains independent of
the `#` snapshot, as observed in the supplied cgame reference.

No package, menu, animation script, PK3, or original module is changed.
