# Reload input policy

NITMOD_BuildReloadPolicy resolves the request/settings inputs consumed by
NITMOD_DecideReload. Manual request is WBUTTON_RELOAD OR (WBUTTON_ATTACK2
AND explicit attack2-reload setting). The primary BUTTON_ATTACK field does
not participate. Auto reload is allowed when pmext.bAutoReload is nonzero OR
the recovered weapon ammo record's +0x38 flag is zero. Nonzero configuration
values, including negative values, retain the original truth semantics.

Evidence: qagame PM_CheckForReload 0x2a7d4..0x2a7f6 reads wbuttons bits
8 and 1, with the additional setting at original pmext +0x88. The client
equivalent at 0x19cb4..0x19cd6 uses pmext +0x80 instead. These different
private layouts must not be cast to stock ET structures. The adapter accepts
that setting explicitly and uses only native cmd.wbuttons and bAutoReload.
The automatic predicate reads pmext +0, then ammo record +0x38 at qagame
0x2a8e8..0x2a905 / cgame 0x19dd0..0x19ded.

The ammo-record flag is also an explicit input, named
weaponRequiresAutoReloadSetting. It is not falsely read from a stock
ammotable_t field. Extracting its per-weapon defaults and binding both extra
settings to synchronized live state remain open work. Scoped ability bits
and warMode are copied without alteration into the decision policy.

6912 combinations cover every wbuttons byte and -1/0/1 for the three
configuration inputs. The primary button byte is deliberately set independently.
Whole pmove/pmoveExt comparisons prove no mutation. Composition tests verify
primary fire alone does not force reload, enabled secondary fire does, and
an exempt weapon can automatically reload with the preference disabled.
Null inputs leave the output unchanged. No active input hook was installed.
