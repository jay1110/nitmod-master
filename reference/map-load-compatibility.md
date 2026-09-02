# Reported map-load failures: configstrings, animation assets, menu bits

## NCS 643 crash

NCS 643 is the first fireteam slot (256+256+32+1+64+18+16).
G_UpdateFireteamConfigString produces `\id\-1` for unused teams. Our store
incorrectly rejected every backslash, so mirroring this normal native value
aborted the server even without an NCS-capable client. Backslashes are now
preserved; quotes, CR and LF remain rejected before mutation. ET:Legacy's
src/qcommon/cmd.c quoted-token loop explicitly has no backslash escaping.
The existing quoted `ncs index "value"` framing is unchanged. Store tests cover
the exact empty-fireteam string, dirty/unchanged behavior and unsafe-write
non-mutation. This does not certify arbitrary oversized or malformed map data.

## UI bitflag

Original ui ELF symbols: ItemParse_bitflag 0x29a00, Script_ToggleCvarBit
0x2cc20, Item_CheckBox_HandleKey 0x34330, Item_CheckBox_Paint 0x36b20.
The typed item appends bitflag after toolTipData (offset 0x274 on wasm32,
checked with Emscripten); existing fields retain their offsets. Integer parsing,
decimal string XOR action and masked checkbox painting are implemented in the
shared ui/ui_shared.c, used by both ui and cgame. A bitflag checkbox does not
perform the ordinary boolean toggle before its action. Otherwise a click would
destroy unrelated flags or toggle twice.

Full-source UI tests parse five bitflag masks through Item_Parse and the real
keyword table/PC_Int_Parse. 160 value/mask cases invoke real checkbox input,
toggle action and no-text painting through observing display callbacks. A
regular checkbox regression remains. Complete layout, malformed masks and
browser interactions are not certified.

## Original assets are mandatory

The canonical ET 2.60 weapon table has no Poison Bomb, Poison Landmine, poison
syringe or Bomb weapon identity. Adding names to BG_IndexForString would conceal
the missing weapon model and risk protocol/prediction disagreement. The temporary
asset override approach has been withdrawn at the user's direction. Its builder
and tests were removed; it must not be shipped or loaded. Implement the actual
weapon identities, animation conditions and client/server contract in code.
Do not edit anything in pak, filter original script operands or supply replacement
menus. Existing dedicated servers distribute the original nitmod.pk3; connecting
the reconstructed WASM client to those servers is a required acceptance test.

The reported deployed line numbers do not match the local menu. The actual
ingame_vote_misc_refrcon.menu is not present in pak; its macro warnings remain
unresolved without the deployed file/include set. Mixing stock/Legacy/Nitmod
macro signatures is a plausible cause, not a verified deployment diagnosis.

## Applying the local results

Replace rebuilt modules as appropriate for their target, without changing assets
or requiring a server-side reconstructed mod merely to connect the WASM client.
Use the original server-distributed PK3 unchanged. No remote files were changed.
The subsequent animation-only vocabulary fix is documented in
reference/native-animation-vocabulary.md. It addresses the reported unknown
names without changing assets; weapon gameplay and original wire IDs remain
unported. The NCS/UI/parser fixes do not establish original-server compatibility.
The original i386 modules remain untouched and should use their original assets.
