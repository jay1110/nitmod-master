# Alternate attack input contract

ET stores primary attack in `usercmd.buttons` and alternate attack in the
separate `usercmd.wbuttons` byte. Both bit constants happen to equal bit zero,
so combining `BUTTON_ATTACK | WBUTTON_ATTACK2` and testing `buttons` silently
aliases alternate attack to primary attack.

The shared pmove code now keeps the namespaces separate. Nitmod's knife throw
consumes `WBUTTON_ATTACK2` before normal weapon firing, while the optional
alternate-reload preference reads the same `wbuttons` field. Normal firing
continues to test only `BUTTON_ATTACK`. Since this is shared prediction code,
cgame and qagame receive identical input semantics.

The UI binding table already exposes `+attack2` (Mouse2 by default); no menu or
PK3 asset changes are required.
