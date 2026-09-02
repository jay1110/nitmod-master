"""Actual Emscripten dlopen smoke test in Node, not browser/ET ABI certification."""
from pathlib import Path
import argparse
import shutil
import subprocess
import sys

from verify_wasm_module import verify


def run(root, runner=subprocess.run, locate=shutil.which, entrypoints=False):
    commands = {name: locate(name) for name in ("emcc", "node")}
    missing = [name for name, path in commands.items() if not path]
    if missing:
        raise RuntimeError("Activate Emscripten and Node first; missing: " + ", ".join(missing))
    root = Path(root).resolve()
    paths = [root / "build/wasm" / (name + ".mp.wasm32.so")
             for name in ("cgame", "qagame", "ui")]
    for path in paths:
        verify(path.read_bytes())
    build = root / "build/wasm-load-smoke"
    build.mkdir(parents=True, exist_ok=True)
    output = build / ("module_entrypoints.js" if entrypoints else "module_load.js")
    # Reuse the native loader orchestration: RTLD_NOW|LOCAL, both entrypoints,
    # reverse-order cleanup on failure. Optional probes invoke only pre-init
    # dispatch branches; they do not initialize or simulate gameplay.
    source = "test_wasm_entrypoints.c" if entrypoints else "test_linux_module_load.c"
    compile_command = [commands["emcc"], str(root / "tests" / source),
                       "-sMAIN_MODULE=1", "-sENVIRONMENT=node", "-sALLOW_MEMORY_GROWTH=1",
                       "-sASSERTIONS=2", "-Wl,--fatal-warnings", "-o", str(output)]
    virtual = []
    for path in paths:
        destination = "/nitmod/" + path.name
        virtual.append(destination)
        compile_command.extend(["--embed-file", str(path) + "@" + destination])
    runner(compile_command, cwd=root, check=True)
    for path in virtual:
        runner([commands["node"], str(output), path], cwd=root, check=True)
    runner([commands["node"], str(output), *virtual], cwd=root, check=True)
    # Missing file must be rejected, not counted as a successful load.
    result = runner([commands["node"], str(output), "/nitmod/missing.so"], cwd=root, check=False)
    if result.returncode != 1:
        raise RuntimeError("Missing-module negative control did not exit with code 1")
    if entrypoints:
        runner([commands["node"], str(output), "--botlib-probe", virtual[1]], cwd=root, check=True)
        runner([commands["node"], str(output), "--extension-probe", virtual[0]], cwd=root, check=True)
        runner([commands["node"], str(output), "--cvar-probe", virtual[1]], cwd=root, check=True)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--entrypoints", action="store_true", help="also call dllEntry and pre-init vmMain probes")
    args = parser.parse_args()
    try:
        run(Path(__file__).resolve().parents[1], entrypoints=args.entrypoints)
    except (RuntimeError, OSError, ValueError, subprocess.CalledProcessError) as error:
        raise SystemExit(str(error))
    print("WASM dlopen/dlsym: three individual loads, concurrent load and missing-file rejection passed.")
    if args.entrypoints:
        print("vmWasmAbi1() == 1, dllEntry, thirteen-slot vmMain calls, seven pre-init queries and two console/argv callback probes passed; unexpected syscalls are fatal.")
        print("Known bot limitation reproduced: BOTAI_START_FRAME reaches BOTLIB_START_FRAME; probe stops there.")
        print("Unsupported cgame extension 1338 produces the expected CG_ERROR callback; not extension support.")
    print("Fresh Emscripten Node harness only; no browser or gameplay verification.")
