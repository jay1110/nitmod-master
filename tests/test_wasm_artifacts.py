import importlib.util
from pathlib import Path
import unittest

spec = importlib.util.spec_from_file_location("wasm_check", Path(__file__).resolve().parents[1] / "tools/verify_wasm_module.py")
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)

def section(kind, payload):
    assert len(payload) < 128
    return bytes((kind, len(payload))) + payload

HEADER = b"\0asm\x01\0\0\0"
DYLINK = section(0, b"\x08dylink.0\x01\x04\0\0\0\0")
EXPORTS = section(7, b"\x03\x06vmMain\0\0\x08dllEntry\0\x01\x0avmWasmAbi1\0\x01")
VALID = HEADER + DYLINK + section(1, b"\x01\x60\0\0") + section(3, b"\x02\0\0") + EXPORTS + section(10, b"\x02\x02\0\x0b\x02\0\x0b")

class WasmArtifacts(unittest.TestCase):
    def test_valid_and_unrelated_custom_sections(self):
        module.verify(VALID)
        module.verify(VALID + section(0, b"\x04name"))

    def test_bad_headers_and_truncation(self):
        for data in (b"!<arch>\n", b"MZ" + bytes(40), HEADER[:7], b"\0asm\x02\0\0\0", VALID[:-1], HEADER + b"\x07\xff\xff\xff\xff\x10"):
            with self.assertRaises(ValueError):
                module.verify(data)

    def test_missing_or_wrong_exports(self):
        for data in (HEADER + EXPORTS, HEADER + DYLINK,
                     VALID.replace(b"vmMain\0", b"vmMain\x03"),
                     VALID.replace(b"dllEntry", b"notEntry"), VALID + EXPORTS, VALID + DYLINK):
            with self.assertRaises(ValueError):
                module.verify(data)

    def test_missing_or_wrong_abi_marker(self):
        for data in (VALID.replace(b"vmWasmAbi1", b"vmWasmAbi2"),
                     VALID.replace(b"vmWasmAbi1\0", b"vmWasmAbi1\x03")):
            with self.assertRaises(ValueError):
                module.verify(data)

    def test_malformed_export_payload(self):
        for payload in (b"\x01\xff", b"\x01\x01\xff\0\0", b"\0\0",
                        b"\x02\x01x\0\0\x01x\0\x01"):
            with self.assertRaises(ValueError):
                module.verify(HEADER + DYLINK + section(7, payload))

if __name__ == "__main__":
    unittest.main()
