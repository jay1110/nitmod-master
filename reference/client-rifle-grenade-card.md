# Rifle-grenade restriction card

The limbo weapon renderer now uses the original `gfx/limbo/nadesoutofstock`
shader on KAR98 and CARBINE cards when their GPG40/M7 grenade quota is exhausted.
The shader is registered with RegisterShaderNoMip alongside outofstock and
stored in typed cgame media state. No asset is created, modified or packaged.

Reference: sorted cgame_client.c registers the shader into original cgs+131580;
cgame_ui.c CG_LimboPanel_WeaponPanel_DrawWeapon checks original wire rifles
22/23 against grenade weapons 36/37. It draws the overlay across the complete
card rectangle after the ordinary out-of-stock indicator and before the
position label. The port uses the same order and the name-font color, including
the 1.5 hover-alpha factor. Original cgame reference SHA-256:
45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f.

The overlay is original-protocol-only. Positive shader handles are required;
missing media does not issue an invalid draw. Restrictions use the already
ported direct grenade quota checker, never disable the base rifle. This does
not implement new qagame grenade restrictions or claim complete card parity.

Tests render the real card for five weapons, blocked/unlimited quotas and
three shader states (-1, 0, valid): 30 combinations. The callback verifies exact
overlay count and scaled rectangle and asserts that both base rifles remain
selectable. Native tests and WASM build/load probes pass; live browser hover,
asset loading and screenshot comparison remain open.
