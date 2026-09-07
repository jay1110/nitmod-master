"""Run hit-sound lifecycle and related protocol contract checks from the repo."""
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def run(*args):
    subprocess.run(args, cwd=ROOT, check=True)


def main():
    emcc = shutil.which("emcc")
    node = shutil.which("node")
    if not emcc or not node:
        raise SystemExit("Put Emscripten and Node.js on PATH before running this check.")
    output = ROOT / "build" / "wasm"
    output.mkdir(parents=True, exist_ok=True)
    run(sys.executable, "tests/test_nitmod_protocol_contract.py", "src_2.60")
    common = ["-Isrc_2.60/game", "-O1", "-sASSERTIONS=1", "-sENVIRONMENT=node"]
    run(emcc, "tests/test_nitmod_hit_lifecycle_wasm.c",
        "src_2.60/cgame/cg_nitmod_config.c", "src_2.60/game/q_shared.c",
        "src_2.60/game/q_math.c", "src_2.60/game/nitmod_protocol.c",
        "-Isrc_2.60/cgame", "-DCGAME", *common,
        "-o", str(output / "test_hit_lifecycle.js"))
    run(node, str(output / "test_hit_lifecycle.js"))
    run(emcc, "tests/test_nitmod_clamp_wasm.c", *common,
        "-o", str(output / "test_hit_clamp.js"))
    run(node, str(output / "test_hit_clamp.js"))
    print("Hit lifecycle, clamp and complete protocol source contract passed.")


if __name__ == "__main__":
    main()
