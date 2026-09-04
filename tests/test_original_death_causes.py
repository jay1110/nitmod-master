"""Compare the active death-cause adapter with the original ELF modNames table."""
import pathlib
import re
import struct

root = pathlib.Path(__file__).resolve().parents[1]
data = (root / "original_nitmod_shared_objects_32bit/qagame.mp.i386.so").read_bytes()
start = struct.unpack_from("<I", data, 32)[0]
count = struct.unpack_from("<H", data, 48)[0]
sections = [struct.unpack_from("<10I", data, start + i * 40) for i in range(count)]

def offset(address):
    return next(s[4] + address - s[3] for s in sections
                if s[1] != 8 and s[3] <= address < s[3] + s[5])

names = []
for index in range(69):
    pointer = struct.unpack_from("<I", data, offset(0x2a7bc0) + index * 4)[0]
    names.append(data[offset(pointer):].split(b"\0", 1)[0].decode("ascii"))
source = (root / "src_2.60/cgame/cg_nitmod_events.c").read_text()
table = re.search(r"static const int causes\[\] = \{(.*?)\};", source, re.S).group(1)
actual = re.findall(r"\bMOD_\w+", table)
native = set(re.findall(r"\bMOD_\w+", (root / "src_2.60/game/bg_public.h").read_text()))
expected = ["MOD_FG42SCOPE" if name == "MOD_FG42_SCOPE" else
            name if name in native else "MOD_UNKNOWN" for name in names]
assert actual == expected, list(zip(names, actual, expected))
assert names[5] == "MOD_KNIFE" and names[57] == "MOD_SWITCHTEAM"
assert names[58] == "MOD_GOOMBA" and names[63] == "MOD_THROWKNIFE"
print("69 original ELF death-cause mappings verified; private causes remain explicit fallbacks")

data = (root / "original_nitmod_shared_objects_32bit/cgame.mp.i386.so").read_bytes()
start = struct.unpack_from("<I", data, 32)[0]
count = struct.unpack_from("<H", data, 48)[0]
sections = [struct.unpack_from("<10I", data, start + i * 40) for i in range(count)]
special = re.findall(r'case (\d+): \*message = "([^"]*)"; \*suffix = "([^"]*)";', source)
assert len(special) == 8
for cause, message, suffix in special:
    pointers = struct.unpack_from("<II", data, offset(0x134940) + int(cause) * 8)
    pair = [data[offset(p):].split(b"\0", 1)[0].decode("ascii") for p in pointers]
    assert pair == [message, suffix], (cause, pair, message, suffix)
print("Eight private killed-by text pairs verified against original cgame ELF")

ported = (root / "src_2.60/cgame/cg_nitmod_obituary.c").read_text()
rows = re.findall(r'\{ (NULL|"[^"]*"), (NULL|"[^"]*"), (\d+) \}, /\* (\d+) \*/', ported)
assert len(rows) == 69
ammo = [struct.unpack_from("<i", data, offset(0x12fd00) + weapon * 72 + 60)[0]
        for weapon in range(52)]
for message, suffix, weapon, index in rows:
    index = int(index)
    pointers = struct.unpack_from("<II", data, offset(0x134940) + index * 8)
    expected_pair = [None if p == 0 else data[offset(p):].split(b"\0", 1)[0].decode("ascii") for p in pointers]
    assert [None if s == "NULL" else s[1:-1] for s in (message, suffix)] == expected_pair
    expected_weapon = 1 if index == 63 else next((w for w, cause in enumerate(ammo) if cause == index), 0)
    assert int(weapon) == expected_weapon, (index, weapon, expected_weapon)
print("69 complete obituary text pairs and original first-match weapon mappings verified")
