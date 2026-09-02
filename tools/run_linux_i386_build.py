"""Build all native targets, test them, then check module ELF architecture.

Header validation is not an ABI/export/behavior parity certification.
"""
from pathlib import Path
from datetime import datetime, timezone
import hashlib
import json
import os
import struct
import subprocess
import tempfile
import uuid

MODULES = tuple(name + ".mp.i386.so" for name in ("cgame", "qagame", "ui"))


def reference_hashes(root):
    expected = {}
    for line in (root / "reference/original_nitmod_i386.sha256").read_text(encoding="utf-8").splitlines():
        if not line.strip() or line.lstrip().startswith("#"):
            continue
        fields = line.split()
        if (len(fields) != 2 or fields[1] not in MODULES or fields[1] in expected
                or len(fields[0]) != 64 or any(c not in "0123456789abcdefABCDEF" for c in fields[0])):
            raise ValueError("Invalid original reference manifest")
        expected[fields[1]] = fields[0].lower()
    if set(expected) != set(MODULES):
        raise ValueError("Reference manifest must name all three modules exactly once")
    for name, digest in expected.items():
        actual = hashlib.sha256((root / "original_nitmod_shared_objects_32bit" / name).read_bytes()).hexdigest()
        if actual != digest:
            raise ValueError("Original reference checksum mismatch: " + name)
    return expected


def write_verification(root, build, commands):
    originals = reference_hashes(root)
    report = {
        "schema_version": 1,
        "created_utc": datetime.now(timezone.utc).isoformat(),
        "full_parity_verified": False,
        "checks": ["configure", "build_all", "ctest", "elf32_i386_headers", "public_entrypoints", "original_sha256"],
        "commands": commands,
        "reconstructed_modules": {name: hashlib.sha256((build / name).read_bytes()).hexdigest() for name in MODULES},
        "original_reference_modules": originals,
    }
    # Unique reports preserve prior evidence without calling it the latest run.
    target = build / ("verification-" + uuid.uuid4().hex + ".json")
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(mode="w", encoding="utf-8", dir=build, suffix=".tmp", delete=False) as stream:
            temporary = Path(stream.name)
            json.dump(report, stream, indent=2, sort_keys=True)
            stream.write("\n")
        os.replace(temporary, target)
    finally:
        if temporary is not None and temporary.exists():
            temporary.unlink()
    return target


def verify_modules(build):
    for name in ("cgame", "qagame", "ui"):
        path = build / (name + ".mp.i386.so")
        header = path.read_bytes()[:52]
        if (len(header) != 52 or header[:7] != b"\x7fELF\x01\x01\x01"
                or struct.unpack_from("<HHI", header, 16) != (3, 3, 1)):
            kind = ("Windows PE/DLL (MZ)" if header.startswith(b"MZ") else
                    "WebAssembly side module" if header.startswith(b"\0asm") else
                    "wrong ELF class/architecture/type" if header.startswith(b"\x7fELF") else
                    "unknown or truncated format")
            raise ValueError("Expected little-endian ELF32 i386 shared module, got " + kind + ": " + str(path))


def verify_exports(output, path):
    exported = set()
    for line in output.splitlines():
        fields = line.split()
        if (len(fields) >= 8 and fields[3] == "FUNC"
                and fields[4] in ("GLOBAL", "WEAK")
                and fields[5] in ("DEFAULT", "PROTECTED")
                and fields[6] != "UND"):
            exported.add(fields[7])
    missing = {"vmMain", "dllEntry"} - exported
    if missing:
        raise ValueError("Missing public function exports in " + str(path) + ": " + ", ".join(sorted(missing)))


def run(root, runner=subprocess.run):
    root = Path(root).resolve()
    build = root / "build" / "linux-i386"
    commands = [
        ["cmake", "-S", str(root / "src_2.60"), "-B", str(build),
         "-DBUILD_TESTING=ON", "-DCMAKE_BUILD_TYPE=Debug", "-DNITMOD_ARCH=i386",
         "-DNITMOD_REQUIRE_LINUX_I386=ON",
         "-DCMAKE_C_FLAGS=-m32", "-DCMAKE_EXE_LINKER_FLAGS=-m32",
         "-DCMAKE_MODULE_LINKER_FLAGS=-m32", "-DCMAKE_SHARED_LINKER_FLAGS=-m32"],
        # Do not restrict this to the three modules: CTest needs executables.
        ["cmake", "--build", str(build)],
        ["ctest", "--test-dir", str(build), "--output-on-failure", "--no-tests=error"],
    ]
    for command in commands:
        runner(command, cwd=root, check=True)
    verify_modules(build)
    for name in ("cgame", "qagame", "ui"):
        path = build / (name + ".mp.i386.so")
        result = runner(["readelf", "--dyn-syms", "--wide", str(path)],
                        cwd=root, check=True, capture_output=True, text=True)
        verify_exports(result.stdout, path)
    return write_verification(root, build, commands)


if __name__ == "__main__":
    print("Build verification: " + str(run(Path(__file__).resolve().parents[1])))
