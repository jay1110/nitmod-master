"""Orchestration controls; real SDK execution is a separate integration run."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import run_wasm_load_smoke as driver
sys.path.pop(0)


class LoadSmokeDriver(unittest.TestCase):
    def fixtures(self, root):
        build = root / "build/wasm"
        build.mkdir(parents=True)
        for name in ("cgame", "qagame", "ui"):
            (build / (name + ".mp.wasm32.so")).write_bytes(b"fixture")

    def test_commands_and_negative_control(self):
        with tempfile.TemporaryDirectory() as tmp, patch.object(driver, "verify") as verify:
            root = Path(tmp).resolve()
            self.fixtures(root)
            calls = []
            def runner(args, **kwargs):
                calls.append((args, kwargs))
                return subprocess.CompletedProcess(args, 0 if kwargs["check"] else 1)
            driver.run(root, runner, lambda name: name)
            self.assertEqual(verify.call_count, 3)
            self.assertEqual(len(calls), 6)
            self.assertEqual(calls[0][0].count("--embed-file"), 3)
            self.assertIn("-sMAIN_MODULE=1", calls[0][0])
            self.assertIn("-sENVIRONMENT=node", calls[0][0])
            paths = ["/nitmod/" + name + ".mp.wasm32.so" for name in ("cgame", "qagame", "ui")]
            for index, path in enumerate(paths, 1):
                self.assertEqual(calls[index][0][2:], [path])
            self.assertEqual(calls[4][0][2:], paths)
            self.assertEqual(calls[5][0][2:], ["/nitmod/missing.so"])
            self.assertTrue(all(kw == {"cwd": root, "check": i != 5}
                                for i, (_, kw) in enumerate(calls)))

    def test_missing_tools(self):
        with self.assertRaisesRegex(RuntimeError, "missing: emcc, node"):
            driver.run(".", locate=lambda name: None)

    def test_bot_probe_failure_propagates(self):
        with tempfile.TemporaryDirectory() as tmp, patch.object(driver, "verify"):
            root = Path(tmp)
            self.fixtures(root)
            def runner(args, **kwargs):
                if "--botlib-probe" in args:
                    raise subprocess.CalledProcessError(2, args)
                return subprocess.CompletedProcess(args, 0 if kwargs["check"] else 1)
            with self.assertRaises(subprocess.CalledProcessError):
                driver.run(root, runner, lambda name: name, entrypoints=True)

    def test_entrypoint_mode(self):
        with tempfile.TemporaryDirectory() as tmp, patch.object(driver, "verify"):
            root = Path(tmp).resolve()
            self.fixtures(root)
            calls = []
            def runner(args, **kwargs):
                calls.append(args)
                return subprocess.CompletedProcess(args, 0 if kwargs["check"] else 1)
            driver.run(root, runner, lambda name: name, entrypoints=True)
            self.assertEqual(calls[0][1], str(root / "tests/test_wasm_entrypoints.c"))
            self.assertIn(str(root / "build/wasm-load-smoke/module_entrypoints.js"), calls[0])
            self.assertEqual(len(calls), 9)
            self.assertEqual(calls[-3][2:], ["--botlib-probe", "/nitmod/qagame.mp.wasm32.so"])
            self.assertEqual(calls[-2][2:], ["--extension-probe", "/nitmod/cgame.mp.wasm32.so"])
            self.assertEqual(calls[-1][2:], ["--cvar-probe", "/nitmod/qagame.mp.wasm32.so"])
            self.assertTrue(all(args[1].endswith("module_entrypoints.js") for args in calls[1:]))

    def test_fail_fast(self):
        for fail_at in range(1, 6):
            with tempfile.TemporaryDirectory() as tmp, patch.object(driver, "verify"):
                root = Path(tmp)
                self.fixtures(root)
                calls = []
                def runner(args, **kwargs):
                    calls.append(args)
                    if len(calls) == fail_at:
                        raise subprocess.CalledProcessError(1, args)
                    return subprocess.CompletedProcess(args, 0)
                with self.assertRaises(subprocess.CalledProcessError):
                    driver.run(root, runner, lambda name: name)
                self.assertEqual(len(calls), fail_at)

    def test_negative_control_must_reject(self):
        for returncode in (0, 2):
            with tempfile.TemporaryDirectory() as tmp, patch.object(driver, "verify"):
                root = Path(tmp)
                self.fixtures(root)
                with self.assertRaisesRegex(RuntimeError, "negative control"):
                    driver.run(root, lambda args, **kw: subprocess.CompletedProcess(args, returncode),
                               lambda name: name)

    def test_bad_artifact_runs_nothing(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            self.fixtures(root)
            calls = []
            with self.assertRaises(ValueError):
                driver.run(root, lambda *args, **kw: calls.append(args), lambda name: name)
            self.assertEqual(calls, [])


if __name__ == "__main__":
    unittest.main()
