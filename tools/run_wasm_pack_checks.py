"""Run actual normal pack throws with engine boundary doubles."""
from pathlib import Path
import shutil
import subprocess

root = Path(__file__).resolve().parents[1]
emcc, node = shutil.which("emcc"), shutil.which("node")
if not emcc or not node:
    raise SystemExit("Put Emscripten and Node.js on PATH first")
for name in ("pack_team", "limbo_charge", "native_pack_charge", "pack_sink"):
    target = root / ("build/wasm/test_" + name + ".js")
    target.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run([emcc, "tests/test_nitmod_" + name + "_wasm.c",
        "src_2.60/game/bg_misc.c", "src_2.60/game/q_shared.c", "src_2.60/game/q_math.c",
        "src_2.60/game/nitmod_skills.c", "src_2.60/game/nitmod_protocol.c",
        "-Isrc_2.60/game", "-DGAMEDLL", "-O1", "-sASSERTIONS=1",
        "-sENVIRONMENT=node", "-o", str(target)], cwd=root, check=True)
    subprocess.run([node, str(target)], cwd=root, check=True)
