"""Verify original pack prediction gate and its source integration."""
from pathlib import Path
import shutil
import subprocess

root = Path(__file__).resolve().parents[1]
emcc, node = shutil.which("emcc"), shutil.which("node")
if not emcc or not node:
    raise SystemExit("Put Emscripten and Node.js on PATH first")
client = (root / "src_2.60/cgame/cg_predict.c").read_text()
move = (root / "src_2.60/game/bg_pmove.c").read_text()
assert client.count("NITMOD_PackPredictionInputs(&cg_pmove,cg.snap->ps.clientNum);") == 2
assert "!PM_NITMOD_PackChargeAvailable(pm)" in move
for weapon in ("WP_AMMO", "WP_MEDKIT"):
    assert "!pm->nitmodPackChargeEnabled && pm->ps->weapon == " + weapon in move
target = root / "build/wasm/test_pack_prediction.js"
target.parent.mkdir(parents=True, exist_ok=True)
subprocess.run([emcc, "tests/test_nitmod_pack_prediction_wasm.c",
    "src_2.60/game/nitmod_skills.c", "src_2.60/game/nitmod_protocol.c",
    "-Isrc_2.60/game", "-DGAMEDLL", "-O1", "-sASSERTIONS=1",
    "-sENVIRONMENT=node", "-o", str(target)], cwd=root, check=True)
subprocess.run([node, str(target)], cwd=root, check=True)
for name, sources, defines in (
    ("pack_mask_handshake", ["src_2.60/cgame/cg_nitmod_config.c", "src_2.60/game/bg_classes.c"], ["-DCGAME", "-Isrc_2.60/cgame"]),
    ("pack_settings_sender", [], ["-DGAMEDLL"]),
):
    target = root / ("build/wasm/test_" + name + ".js")
    subprocess.run([emcc, "tests/test_nitmod_" + name + "_wasm.c", *sources,
        "src_2.60/game/q_shared.c", "src_2.60/game/q_math.c", "src_2.60/game/nitmod_protocol.c",
        "-Isrc_2.60/game", *defines, "-O1", "-sASSERTIONS=1", "-sENVIRONMENT=node",
        "-o", str(target)], cwd=root, check=True)
    subprocess.run([node, str(target)], cwd=root, check=True)
