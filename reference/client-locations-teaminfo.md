# Client locations and original `tinfo`

## Wire layout correction

The original cgame `clientInfo_t` accesses location coordinates at three
consecutive integer offsets, followed by health and powerups. Its `tinfo`
record therefore contains six values:

`client x y z health powerups`

Native ET 2.60 uses five values (`client x y health powerups`). The receive
path now selects the stride from the detected server protocol, validates the
complete command before mutation, rejects invalid client indexes and stores a
typed three-component location. This prevents original Nitmod records from
shifting health, powerups and every following client record by one argument.

## Location files

`CG_NitmodLoadLocations` follows the original lookup order:

1. `maps/<rawmapname>_loc_override.dat`
2. `maps/<rawmapname>_loc.dat`

Files are read through engine filesystem syscalls, limited to the original
32768-byte bound, and parsed as `x y z "name"` records with comment/quoted
token handling. At most 1024 owned, bounded records are retained. All-zero
locations and incomplete records are ignored.

The closest location that is also in PVS is used. `cg_locations` bit 1 enables
custom locations in the fireteam overlay, bit 2 in original team chat, bit 8
allows `Unknown`, and bit 16 appends the native grid location. The
`cg_locationMaxChars` limit is applied to fireteam text. Native ET260 team-chat
format and five-value `tinfo` remain unchanged.

The loader reads compatible files supplied by the connected server/PK3; this
port adds or modifies no pak/menu asset. Parser tests cover comments, quoted
names, signed positions, all-zero filtering, incomplete records, empty input
and reset behavior. CTest/WASM smoke tests do not establish visual parity on a
live server.
