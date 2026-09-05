from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/game/g_items.c").read_text(encoding="utf-8")

flush = SOURCE.split("static void G_NITMOD_FlushItem", 1)[1].split(
    "void G_BounceItem", 1
)[0]
assert 'G_NITMOD_LegacyCvarInteger("g_flushItems", 1)' in flush
assert "!ent->item" in flush
assert "trace->plane.normal[2] <= 0.7f" in flush
assert "ProjectPointOnPlane(axis[0], forward, axis[2])" in flush
assert "AxisToAngles(axis, ent->s.angles)" in flush
assert "-64.f * backtrace.fraction" in flush
assert "G_SetOrigin(ent, settled)" in flush
assert "trace->entityNum != ENTITYNUM_WORLD" in flush

bounce = SOURCE.split("void G_BounceItem", 1)[1].split("void G_RunItemProp", 1)[0]
assert "G_NITMOD_FlushItem(ent, trace);" in bounce
assert "trace->endpos[2] += 1.0" not in bounce

print("Nitmod sloped-item flush checks passed")
