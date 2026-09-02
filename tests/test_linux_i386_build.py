"""Host-side orchestration tests; these do not execute a Linux compiler."""
import importlib.util
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
EXPORTS = "1: 00001000 20 FUNC GLOBAL DEFAULT 7 vmMain\n2: 00002000 20 FUNC GLOBAL DEFAULT 7 dllEntry\n"
spec = importlib.util.spec_from_file_location("linux_build", ROOT / "tools/run_linux_i386_build.py")
build_tool = importlib.util.module_from_spec(spec)
spec.loader.exec_module(build_tool)


class LinuxBuildTests(unittest.TestCase):
    def test_artifact_names_follow_target_not_cached_arch(self):
        policy = (ROOT / "tools/cmake/ModuleArtifactName.cmake").as_posix()
        cases = [("Windows", 8, "OFF", "qagame.host.windows64.dll"),
                 ("Windows", 4, "OFF", "qagame_mp_x86.dll"),
                 ("Darwin", 8, "OFF", "qagame_mac"),
                 ("Linux", 4, "OFF", "qagame.mp.i386.so"),
                 ("Linux", 8, "OFF", "qagame.mp.x86_64.so"),
                 ("Emscripten", 4, "ON", "qagame.mp.wasm32.so"),
                 ("Linux", 8, "OFF", None)]
        with tempfile.TemporaryDirectory() as tmp:
            script = Path(tmp) / "names.cmake"
            for system, pointers, wasm, expected in cases:
                arch = "x86_64" if expected == "qagame.mp.x86_64.so" else "i386"
                script.write_text(f'set(CMAKE_SYSTEM_NAME {system})\n'
                    f'set(CMAKE_SIZEOF_VOID_P {pointers})\nset(EMSCRIPTEN {wasm})\n'
                    f'set(NITMOD_ARCH {arch})\ninclude("{policy}")\n'
                    'nitmod_artifact_name(qagame name suffix)\nmessage("${name}${suffix}")\n')
                result = subprocess.run(["cmake", "-P", str(script)], capture_output=True, text=True)
                self.assertEqual(result.returncode == 0, expected is not None, result.stderr)
                if expected:
                    self.assertIn(expected, result.stderr)
    def fixtures(self, root):
        build = root / "build/linux-i386"
        build.mkdir(parents=True)
        header = bytearray(52)
        header[:7] = b"\x7fELF\x01\x01\x01"
        struct.pack_into("<HHI", header, 16, 3, 3, 1)
        for name in ("cgame", "qagame", "ui"):
            (build / (name + ".mp.i386.so")).write_bytes(header)
        (root / "reference").mkdir()
        (root / "original_nitmod_shared_objects_32bit").mkdir()
        lines = []
        for name in build_tool.MODULES:
            data = ("original fixture " + name).encode()
            (root / "original_nitmod_shared_objects_32bit" / name).write_bytes(data)
            lines.append(hashlib.sha256(data).hexdigest() + "  " + name)
        (root / "reference/original_nitmod_i386.sha256").write_text("\n".join(lines))
        return build

    def test_all_targets_before_tests(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp).resolve()
            self.fixtures(root)
            calls = []
            def fake(args, **kw):
                calls.append((args, kw))
                return subprocess.CompletedProcess(args, 0, stdout=EXPORTS)
            report_path = build_tool.run(root, fake)
            report = json.loads(report_path.read_text())
            self.assertFalse(report["full_parity_verified"])
            self.assertEqual(set(report["reconstructed_modules"]), set(build_tool.MODULES))
            self.assertNotEqual(report["original_reference_modules"], report["reconstructed_modules"])
            self.assertEqual(len(calls), 6)
            self.assertIn("-DBUILD_TESTING=ON", calls[0][0])
            self.assertIn("-DNITMOD_REQUIRE_LINUX_I386=ON", calls[0][0])
            self.assertIn("-DCMAKE_MODULE_LINKER_FLAGS=-m32", calls[0][0])
            self.assertNotIn("--target", calls[1][0])
            self.assertEqual(calls[2][0][0], "ctest")
            self.assertIn("--no-tests=error", calls[2][0])
            self.assertTrue(all(kw["cwd"] == root and kw["check"] for _, kw in calls))
            self.assertTrue(all(args[:3] == ["readelf", "--dyn-syms", "--wide"] for args, _ in calls[3:]))

    def test_entrypoints_must_be_public_defined_functions(self):
        build_tool.verify_exports(EXPORTS, "fixture")
        for replacement in ("LOCAL DEFAULT 7", "GLOBAL HIDDEN 7", "GLOBAL DEFAULT UND"):
            with self.assertRaises(ValueError):
                build_tool.verify_exports(EXPORTS.replace("GLOBAL DEFAULT 7", replacement), "fixture")
        for bad in ("", EXPORTS.replace("FUNC", "OBJECT"), EXPORTS.replace("vmMain", "other")):
            with self.assertRaises(ValueError):
                build_tool.verify_exports(bad, "fixture")

    def test_no_success_report_on_failure(self):
        for failure in ("build", "export", "reference"):
            with tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                build = self.fixtures(root)
                if failure == "reference":
                    (root / "original_nitmod_shared_objects_32bit/ui.mp.i386.so").write_bytes(b"changed")
                def fake(args, **kwargs):
                    if failure == "build" and "--build" in args:
                        raise subprocess.CalledProcessError(1, args)
                    return subprocess.CompletedProcess(args, 0, stdout="" if failure == "export" else EXPORTS)
                with self.assertRaises((ValueError, subprocess.CalledProcessError)):
                    build_tool.run(root, fake)
                self.assertEqual(list(build.glob("verification-*.json")), [])
                self.assertEqual(list(build.glob("*.tmp")), [])

    def test_fail_fast_at_each_stage(self):
        for stage in range(3):
            calls = []
            def fail(args, **kw):
                calls.append(args)
                if len(calls) == stage + 1:
                    raise subprocess.CalledProcessError(1, args)
            with self.assertRaises(subprocess.CalledProcessError):
                build_tool.run(ROOT, fail)
            self.assertEqual(len(calls), stage + 1)

    def test_cmake_architecture_policy(self):
        policy = (ROOT / "tools/cmake/ValidateLinuxI386.cmake").as_posix()
        cases = [
            ("ON", "Linux", "i386", 4, "OFF", True),
            ("ON", "Linux", "i386", 8, "OFF", False),
            ("ON", "Windows", "i386", 4, "OFF", False),
            ("ON", "Linux", "x86_64", 4, "OFF", False),
            ("ON", "Linux", "i386", 4, "ON", False),
            ("OFF", "Windows", "i386", 8, "OFF", True),
            ("OFF", "Emscripten", "wasm32", 4, "ON", True),
        ]
        with tempfile.TemporaryDirectory() as tmp:
            script = Path(tmp) / "policy.cmake"
            for strict, system, arch, pointers, wasm, succeeds in cases:
                script.write_text(
                    f'set(NITMOD_REQUIRE_LINUX_I386 {strict})\n'
                    f'set(CMAKE_SYSTEM_NAME {system})\n'
                    f'set(NITMOD_ARCH {arch})\n'
                    f'set(CMAKE_SIZEOF_VOID_P {pointers})\n'
                    f'set(EMSCRIPTEN {wasm})\n'
                    f'include("{policy}")\nnitmod_validate_linux_i386()\n')
                result = subprocess.run(["cmake", "-P", str(script)], capture_output=True, text=True)
                self.assertEqual(result.returncode == 0, succeeds, result.stderr)

    def test_reject_wrong_or_missing_artifacts(self):
        for bad in (b"MZ" + bytes(50), b"\0asm" + bytes(48), b"\x7fELF\x02\x01\x01" + bytes(45), b"", None):
            with tempfile.TemporaryDirectory() as tmp:
                build = self.fixtures(Path(tmp))
                target = build / "ui.mp.i386.so"
                if bad is None:
                    target.unlink()
                else:
                    target.write_bytes(bad)
                with self.assertRaises((ValueError, FileNotFoundError)):
                    build_tool.verify_modules(build)


if __name__ == "__main__":
    unittest.main()
