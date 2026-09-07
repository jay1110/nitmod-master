"""Execute production spawn adapters in WASM with engine boundary stubs."""
from pathlib import Path
import shutil
import subprocess


def main():
    root = Path(__file__).resolve().parents[1]
    emcc, node = shutil.which("emcc"), shutil.which("node")
    if not emcc or not node:
        raise SystemExit("Activate Emscripten and Node before running spawn checks")
    output = root / "build" / "wasm" / "spawn-checks"
    output.mkdir(parents=True, exist_ok=True)
    for name in ("spawn_rewards", "health_rewards", "secondary_weapon", "secondary_grant"):
        target = output / (name + ".js")
        subprocess.run([
            emcc, str(root / "tests" / ("test_nitmod_" + name + "_wasm.c")),
            "src_2.60/game/bg_misc.c", "src_2.60/game/q_shared.c",
            "src_2.60/game/q_math.c", "src_2.60/game/nitmod_weapon_akimbo.c",
            "-Isrc_2.60/game", "-DGAMEDLL",
            "-O1", "-sASSERTIONS=1", "-sENVIRONMENT=node", "-o", str(target),
        ], cwd=root, check=True)
        subprocess.run([node, str(target)], cwd=root, check=True)
    print("Spawn adapter checks passed; no engine or original-binary replay performed.")


if __name__ == "__main__":
    main()
