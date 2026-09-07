"""Verify recovered pack charge arithmetic with an exact rational oracle."""
from pathlib import Path
import shutil
import subprocess

root = Path(__file__).resolve().parents[1]
emcc, node = shutil.which("emcc"), shutil.which("node")
if not emcc or not node:
    raise SystemExit("Put Emscripten and Node.js on PATH first")
target = root / "build/wasm/test_charge_cost.js"
target.parent.mkdir(parents=True, exist_ok=True)
subprocess.run([emcc, "tests/test_nitmod_charge_cost_wasm.c",
    "src_2.60/game/nitmod_skills.c", "src_2.60/game/nitmod_protocol.c",
    "-Isrc_2.60/game", "-O1", "-sASSERTIONS=1", "-sENVIRONMENT=node",
    "-o", str(target)], cwd=root, check=True)
subprocess.run([node, str(target)], cwd=root, check=True)
