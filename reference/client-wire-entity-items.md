# Dedicated Nitmod entity and item decoding

Original cgame CG_AddEntity (sorted cgame_client.c) dispatches 0x20 to
construction rendering, 0x21 to mover/marker rendering, 0x22 to CG_Bomb,
0x26 to CG_Player (corpse), and 0x2e to the game manager. ET 2.60's enum
has extra unused entries and cannot be used directly. Original CG_CheckEvents
(sorted cgame_events.c) subtracts 0x3b from standalone event entities.

Snapshot decoding now translates these types before weapon-field decoding,
interpolation, collision-list building and rendering. Event numbers themselves
remain original wire numbers for the existing event dispatcher. Translation
is performed exactly once in CG_ReadNextSnapshot and only for the original
protocol. Reserved/unmapped types 56..58 are suppressed, not guessed.

Original bg_itemlist is at cgame ELF 0x12ed00, 73 records, stride 56.
Class-name mapping replaces direct use of original indices for ET_ITEM and
pickup events. Original medpacks 24/60 map to the typed medpack; ammunition
32/33/34 map to typed ammo. Original magicammo3 uses the same three model
paths, tag 12, type 1 and quantity 50 as magicammo2; its typed presentation
therefore reuses magicammo2. Private poison/bomb items remain unsupported.
Items encountered after joining are registered on demand because the server's
item-use mask also follows original ordering. Assets are not modified.

This corrects concrete dispatch causes of missing planted tripmines,
construction markers and standalone obituary events. It is not proof that
all missing map textures are fixed; live renderer/filesystem verification is
still required. No duplicate obituary printing was added: CG_AddPMItem already
prints to the console. The four private weapon identities (47,48,50,51) remain
excluded from typed selection; merely adding them to a bank is insufficient.

Tests: check_entity_wire.h covers relevant types, all 255 event offsets,
pack identities and invalid item IDs. Existing snapshot tests now use the
actual original event base, and all 97 CTest tests pass.

Animation compatibility also accepts clean EOF after the ten mandatory
weapon rows. Missing alternate-switch rows use IDLE1, missing DROP2 uses DROP;
partial rows remain errors. This is a documented safe fallback, not exact
original animation parity. The remaining reported server asset files were
not supplied directly; browser verification remains necessary.
