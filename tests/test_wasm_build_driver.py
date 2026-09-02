"""Mocked build orchestration with real artifact framing checks."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

TOOLS = Path(__file__).resolve().parents[1] / "tools"
sys.path.insert(0, str(TOOLS))
import run_wasm_build as driver
sys.path.pop(0)

# Two no-op functions with a dynamic-link marker; not an ET ABI fixture.
DATA = (b"\0asm\x01\0\0\0\0\x0f\x08dylink.0\x01\x04\0\0\0\0"
        b"\x01\x04\x01\x60\0\0\x03\x03\x02\0\0"
        b"\x07\x22\x03\x06vmMain\0\0\x08dllEntry\0\x01\x0avmWasmAbi1\0\x01"
        b"\x0a\x07\x02\x02\0\x0b\x02\0\x0b")

class WasmDriver(unittest.TestCase):
    def fixtures(self, root):
        build = root / "build/wasm"
        build.mkdir(parents=True)
        paths = [build / (name + ".mp.wasm32.so") for name in ("cgame", "qagame", "ui")]
        for path in paths:
            path.write_bytes(DATA)
        return paths

    def test_build_and_recheck_all_outputs(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp).resolve()
            paths = self.fixtures(root)
            calls = []
            result = driver.run(root, lambda args, **kw: calls.append((args, kw)), lambda name: name)
            self.assertEqual(result, paths)
            self.assertEqual(len(calls), 2)
            self.assertEqual(calls[0][0][:2], ["emcmake", "cmake"])
            self.assertIn("-DBUILD_TESTING=OFF", calls[0][0])
            self.assertIn("-DNITMOD_REQUIRE_LINUX_I386=OFF", calls[0][0])
            self.assertEqual(calls[1][0][-4:], ["--target", "cgame", "qagame", "ui"])
            self.assertTrue(all(kw == {"cwd": root, "check": True} for _, kw in calls))

    def test_missing_sdk_does_not_run(self):
        calls = []
        with self.assertRaisesRegex(RuntimeError, "Activate an Emscripten SDK"):
            driver.run(TOOLS.parent, lambda *args, **kw: calls.append(args), lambda name: None)
        self.assertEqual(calls, [])

    def test_command_failures_stop(self):
        for fail_at in (1, 2):
            calls = []
            def runner(args, **kw):
                calls.append(args)
                if len(calls) == fail_at:
                    raise subprocess.CalledProcessError(1, args)
            with self.assertRaises(subprocess.CalledProcessError):
                driver.run(TOOLS.parent, runner, lambda name: name)
            self.assertEqual(len(calls), fail_at)

    def test_each_wrong_or_missing_output_rejected(self):
        for index in range(3):
            for missing in (False, True):
                with tempfile.TemporaryDirectory() as tmp:
                    root = Path(tmp)
                    paths = self.fixtures(root)
                    if missing:
                        paths[index].unlink()
                    else:
                        paths[index].write_bytes(b"!<arch>\n")
                    with self.assertRaises((ValueError, FileNotFoundError)):
                        driver.run(root, lambda *args, **kw: None, lambda name: name)

if __name__ == "__main__":
    unittest.main()
