# Original location-debug display

Reference: CG_DrawActiveFrame in sorted/cgame_ui.c (location branch after
CG_AddScriptSpeakers), CG_AddOnScreenText in sorted/cgame_ents.c, and
CG_DrawOnScreenNames. Original cg_locations byte at offset 13 tests bit 2,
equivalent to integer bit 512. Original shader field 68096 is registered
as waterBubble in sorted/cgame_client.c.

The frame now submits location sprites for entries no farther than 3000
units, inside PVS, in the forward cone (dot > .6), and projected inside
640x480. Each sprite uses the original origin/oldorigin, radius strlen(name)
+ 8 and white RGBA. Its text is `index:name`, using the common original
distance scale, centered projection and 250-ms visibility fade.

Players and locations share the bounded sixteen-label queue, with players
queued first as in the original frame ordering. Sprites are independent of
text capacity. Location labels do not require spectator status; player
labels still enforce the existing spectator/shoutcaster/server-setting gate.
Draw-time rechecking prevents either setting from exposing stale queued text.

Projection is shared rather than duplicated and rejects nonfinite results,
invalid FOVs and points behind the camera. Labels own up to 95 characters,
enough for all numbered 63-character location names. Fade identity separates
client IDs from location IDs, rather than inheriting arbitrary slot history.
Reloading location records clears stale label state.

The location-number parser rejects NaN, infinities, strtod range errors and
values beyond finite float range before storing coordinates. Existing valid
file syntax and all-zero-location handling are retained. This batch only
reads location assets; no location file is created or edited.

Tests cover native/original protocol, bit 512 independently of bit 1, PVS,
near/exactly-3000/over-3000/behind/side locations, sprite type/shader/radius/
origin, actual trace dispatch for a non-spectator, projection center, invalid
label IDs and four nonfinite/overflow inputs. Existing spectator and wounded
label tests continue to exercise the shared pipeline. Native build and CTest,
WASM build and Node loading probes are run. Browser screenshot parity remains
unverified; PVS is checked after the cone for efficiency, and cg_draw2D=0
suppresses this debug display as a deliberate defensive behavior.

No pak, PK3, menu, original module or server message format is changed.
