"""Pin the inspected i386 reward operand; never execute or mutate the original."""
import hashlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
data = (ROOT / "original_nitmod_shared_objects_32bit/qagame.mp.i386.so").read_bytes()
assert hashlib.sha256(data).hexdigest() == "84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49"
# This original's .text addresses equal file offsets here. llvm-objdump:
# 4802d: testb $0x10,0xee0(%esi), followed by je 480a3.
# 0xee0 is Light Weapons in the recovered reward array, not First Aid 0xed8.
assert data[0x4802d:0x48036] == bytes.fromhex("f6 86 e0 0e 00 00 10 74 6d")
assert data[0x48048:0x4804d] == bytes.fromhex("b8 2f 00 00 00")
print("Original poison grant: Light Weapons reward operand and weapon 47 verified")
