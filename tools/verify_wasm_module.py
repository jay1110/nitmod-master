"""Check WASM framing, dynamic-link marker and entrypoint exports.

Not a full WebAssembly validator: function bodies, indices, imports, ABI and
dynamic-link metadata contents still require toolchain/engine validation.
"""
from pathlib import Path
import sys


class Reader:
    def __init__(self, data):
        self.data, self.pos = data, 0

    def take(self, size):
        if size > len(self.data) - self.pos:
            raise ValueError("Truncated WASM field")
        result = self.data[self.pos:self.pos + size]
        self.pos += size
        return result

    def u32(self):
        value = 0
        for i in range(5):
            byte = self.take(1)[0]
            if i == 4 and byte > 15:
                raise ValueError("WASM u32 LEB128 overflow")
            value |= (byte & 127) << (7 * i)
            if not byte & 128:
                return value
        raise ValueError("Invalid WASM u32")

    def name(self):
        return self.take(self.u32()).decode("utf-8")


def verify(data):
    reader = Reader(data)
    if reader.take(8) != b"\0asm\x01\0\0\0":
        raise ValueError("Expected WebAssembly version 1, not an archive/native library")
    exports, seen_export, dynamic = {}, False, False
    while reader.pos < len(data):
        section_id = reader.take(1)[0]
        section = Reader(reader.take(reader.u32()))
        if section_id == 0:
            name = section.name()
            if name in ("dylink", "dylink.0"):
                if dynamic:
                    raise ValueError("Duplicate dynamic-link marker")
                dynamic = True
        elif section_id == 7:
            if seen_export:
                raise ValueError("Duplicate export section")
            seen_export = True
            for _ in range(section.u32()):
                name = section.name()
                kind = section.take(1)[0]
                section.u32()  # index: bounds are the full validator's job
                if name in exports:
                    raise ValueError("Duplicate export name: " + name)
                exports[name] = kind
            if section.pos != len(section.data):
                raise ValueError("Trailing export-section data")
    if not dynamic:
        raise ValueError("Missing dylink/dylink.0 side-module marker")
    for name in ("vmMain", "dllEntry", "vmWasmAbi1"):
        if exports.get(name) != 0:
            raise ValueError("Missing function export: " + name)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        raise SystemExit("usage: verify_wasm_module.py <module>")
    path = Path(sys.argv[1])
    verify(path.read_bytes())
    print(str(path) + ": WASM side-module framing/exports checked")
