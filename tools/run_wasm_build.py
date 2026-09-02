"""Build the three Emscripten side modules; does not certify browser runtime."""
from pathlib import Path
import shutil
import subprocess
import sys

from verify_wasm_module import verify


def run(root, runner=subprocess.run, locate=shutil.which):
    commands = {name: locate(name) for name in ("emcmake", "emcc", "cmake")}
    missing = [name for name, path in commands.items() if not path]
    if missing:
        raise RuntimeError("Activate an Emscripten SDK first; missing commands: " + ", ".join(missing))
    root = Path(root).resolve()
    build = root / "build" / "wasm"
    configure = [commands["emcmake"], commands["cmake"], "-S", str(root / "src_2.60"), "-B", str(build),
                 "-DCMAKE_BUILD_TYPE=Debug", "-DBUILD_TESTING=OFF", "-DNITMOD_REQUIRE_LINUX_I386=OFF",
                 "-DNITMOD_BUILD_CGAME=ON", "-DNITMOD_BUILD_QAGAME=ON", "-DNITMOD_BUILD_UI=ON",
                 "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=" + str(build),
                 "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG=" + str(build),
                 "-DPython3_EXECUTABLE=" + sys.executable]
    runner(configure, cwd=root, check=True)
    runner([commands["cmake"], "--build", str(build), "--config", "Debug",
            "--target", "cgame", "qagame", "ui"], cwd=root, check=True)
    paths = []
    for name in ("cgame", "qagame", "ui"):
        # Recheck even when the build considers the target up to date.
        path = build / (name + ".mp.wasm32.so")
        verify(path.read_bytes())
        paths.append(path)
    return paths


if __name__ == "__main__":
    try:
        outputs = run(Path(__file__).resolve().parents[1])
    except (RuntimeError, OSError, ValueError, subprocess.CalledProcessError) as error:
        raise SystemExit(str(error))
    for output in outputs:
        print("WASM artifact checked: " + str(output))
    print("Browser loading, import/ABI compatibility and gameplay parity remain unverified.")
