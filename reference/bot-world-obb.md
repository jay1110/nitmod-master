# Bot oriented world bounds

ETInterface slot 22 (ELF 0x223b20) is reconstructed as the typed C adapter
G_NITMOD_BotEntityWorldOBB. Its five outputs are center, three axes and half
extents, in the original argument order. No C++ interface installation or
binary-compatible OBB structure is claimed.

The original only requires EntityFromHandle to resolve: unlike the neighboring
position and orientation methods it does not check inuse again. The world
exception therefore accepts unused world and stale world serials. Other stale
or unused entities fail with 3 without output writes. Success returns 0.

AnglesToAxis uses r.currentAngles for every entity, including clients. The
center is r.currentOrigin plus the rotated local (maxs + mins)/2. All three
axes are copied unchanged (axis[1] is the opposite of AngleVectors' right).
Half extents are (maxs - mins)/2, with no absolute value or sorting. A reversed
input box therefore yields negative half extents, exactly as the original.
There are no construction substitutions or player-specific branches here.

The full-qagame fixture covers 48 combinations of three slots, four rotations,
client pointer present/absent and normal/reversed asymmetric bounds. Expected
axes and transformed centers are independently specified constants. Entity
state must remain unchanged. Each null output, malformed handle, unused entity
and stale handle is tested, including success for unused/stale world handles.

Original slot hashes are in bot-loader-contract.json; regression checks pin
the immediate resolve-to-rotation control flow and extent subtraction bytes.
Defensive difference: any null output returns 3 before other output writes.
Double intermediates are used; extreme x87 rounding and aliased output buffers
are not certified. Actual library dispatch and gameplay parity remain pending.

Local/world AABB follow-up: construction selection and the cached classname
hash at original offset 0x5c0 have since been mapped. Internal selection/local
bounds stages are tested; complete adapters still await cached-hash lifecycle
reconstruction. See bot-aabb-stages.md.

Inventory limitation: the split source spells this method as
ETInterface::GetEntityWorldOBB on a multiline signature. The current C-oriented
CSV extractor does not recognize it, so no fictional normalized CSV row was
added. The ELF-derived slot inventory and this parity record track the method.

Verification: native Windows-host build, all 83 CTests, protocol/inventory
checks and real Emscripten builds of all three modules pass. Native Linux-i386
ABI, loaded-library dispatch and browser gameplay are not established.
