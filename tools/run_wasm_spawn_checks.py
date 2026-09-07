"""Execute production spawn adapters in WASM with engine boundary stubs."""
from pathlib import Path
import shutil
import subprocess
import sys


def main():
    root = Path(__file__).resolve().parents[1]
    emcc, node = shutil.which("emcc"), shutil.which("node")
    if not emcc or not node:
        raise SystemExit("Activate Emscripten and Node before running spawn checks")
    output = root / "build" / "wasm" / "spawn-checks"
    output.mkdir(parents=True, exist_ok=True)
    subprocess.run([sys.executable, str(root / "tests/test_nitmod_poison_spawn_reference.py")],
                   cwd=root, check=True)
    for name in ("spawn_rewards_independent", "health_rewards", "secondary_weapon", "secondary_grant", "poison_spawn", "dm_tools", "satchel_spawn_lookup", "special_tools", "engineer_bomb", "primary_reserve", "spawn_alternates", "primary_selection"):
        target = output / (name + ".js")
        subprocess.run([
            emcc, str(root / "tests" / ("test_nitmod_" + name + "_wasm.c")),
            "src_2.60/game/bg_misc.c", "src_2.60/game/q_shared.c",
            "src_2.60/game/q_math.c", "src_2.60/game/nitmod_weapon_akimbo.c",
            "src_2.60/game/g_nitmod_abilities.c", "src_2.60/game/g_nitmod_adrenaline_grant.c",
            "-Isrc_2.60/game", "-DGAMEDLL",
            "-O1", "-sASSERTIONS=1", "-sENVIRONMENT=node", "-o", str(target),
        ], cwd=root, check=True)
        subprocess.run([node, str(target)], cwd=root, check=True)
    client_target = output / "client_class_lists.js"
    subprocess.run([
        emcc, "tests/test_nitmod_client_class_lists_wasm.c",
        "src_2.60/cgame/cg_nitmod_config.c", "src_2.60/game/bg_classes.c",
        "src_2.60/game/q_shared.c", "src_2.60/game/q_math.c", "src_2.60/game/nitmod_protocol.c",
        "-Isrc_2.60/game", "-Isrc_2.60/cgame", "-DCGAME", "-O1",
        "-sASSERTIONS=1", "-sENVIRONMENT=node", "-o", str(client_target),
    ], cwd=root, check=True)
    subprocess.run([node, str(client_target)], cwd=root, check=True)
    print("Spawn/class-selection checks passed; no engine or original-binary replay performed.")


if __name__ == "__main__":
    main()
