"""Source ownership regression; not a renderer/runtime parity test."""
from pathlib import Path

root = Path(__file__).resolve().parents[1]
source = (root / "src_2.60/cgame/cg_weapons.c").read_text()
header = (root / "src_2.60/cgame/cg_local.h").read_text()
assert "ejectBrassCasingOrigin" not in source
assert "vec3_t nitmodBrassOrigin;" in header
assert "VectorCopy (brass.origin, cent->nitmodBrassOrigin);" in source
assert "VectorCopy (cent->nitmodBrassOrigin, re->origin);" in source
print("Per-entity brass origin producer/consumer source checks passed")
