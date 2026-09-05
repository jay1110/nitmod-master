# Tripmine team-limit reconstruction

The original qagame counts its tracked tripmine entities by the team stored in
the entity-state `teamNum` field and rejects placement once that count reaches
`team_maxTripmines` (default 5).

The typed port performs the same check before allocating an entity. It scans
only live non-client entities whose weapon is `WP_TRIPMINE`, assigns the
placing client's Axis/Allies team to new mines, and keeps spectator placement
invalid. A zero or negative limit therefore disables placement, matching the
original `count >= limit` comparison.

Every server frame also publishes the remaining Axis and Allies slots through
the game-manager entity's `time` and `time2` fields. These are the typed ET
fields at original offsets `0x54` and `0x58`; the existing landmine counts stay
in `otherEntityNum` and `otherEntityNum2` at offsets `0x8c` and `0x90`.

The cgame ammo HUD now consumes those team-wide `time/time2` values whenever
the active weapon is `WP_TRIPMINE`, exactly parallel to its existing landmine
handling. Missing game-manager state safely displays zero.
