# Artillery hint runtime

Original `nitrox_SpawnArtyHint` creates broadcast entity type 58 for a field
ops artillery salvo. `artilleryHintThink` retains it while a matching
`WP_ARTY` missile from the same owner and firing timestamp exists, then gives
the marker one final one-second state before freeing it.

The reconstructed qagame implements that ownership and timestamp contract
using typed `gentity_t` fields. It creates one marker with the first damaging
shell when `g_artilleryHints` is exactly 1. The cgame accepts type 58 for both
original and reconstructed Nitmod sessions, filters it to the local team and
uses the recovered 400/576-unit pulse thresholds. `cg_artilleryHints` and
`cg_objectiveHints` are registered in UI as archived controls. No menu or PK3
asset was changed.

The same dispatcher now selects construction-marker IDs by protocol. Original
Nitmod uses wire type 31; reconstructed ET 2.60 uses
`ET_CONSTRUCTIBLE_INDICATOR` (32). This prevents localhost build hints from
disappearing and prevents native `ET_MOVERSCALED` entities (31) from being
mistaken for Nitmod hints. Explosive indicators retain their shared type 13.
