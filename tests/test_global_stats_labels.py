"""Pin the visible global-stat labels and positions to the original ELF."""
from pathlib import Path
import struct


ROOT = Path(__file__).resolve().parents[1]
ELF = (ROOT / "original_nitmod_shared_objects_32bit/cgame.mp.i386.so").read_bytes()
SOURCE = (ROOT / "src_2.60/cgame/cg_nitmod_stats.c").read_text(encoding="utf-8")


def sections():
    table = struct.unpack_from("<I", ELF, 32)[0]
    count = struct.unpack_from("<H", ELF, 48)[0]
    return [struct.unpack_from("<10I", ELF, table + index * 40)
            for index in range(count)]


SECTIONS = sections()


def file_offset(address):
    for section in SECTIONS:
        section_type, virtual, offset, size = section[1], section[3], section[4], section[5]
        if section_type != 8 and virtual <= address < virtual + size:
            return offset + address - virtual
    raise AssertionError(f"unmapped ELF address {address:#x}")


def elf_string(address):
    offset = file_offset(address)
    return ELF[offset:ELF.index(b"\0", offset)].decode("ascii")


def main():
    positions = struct.unpack_from("<13i", ELF, file_offset(0x133E60))
    names2 = [elf_string(pointer) for pointer in
              struct.unpack_from("<13I", ELF, file_offset(0x133F00))]
    names = [elf_string(pointer) for pointer in
             struct.unpack_from("<13I", ELF, file_offset(0x133F40))]
    assert positions == tuple(range(0, 13 * 44, 44))
    assert tuple(names) == ("Kills", "Deaths", "Team", "Time", "Revives", "Tripmine",
                     "Goomba", "Scoped", "Fthrower", "Objs.", "Objs.", "Rounds",
                     "Satchel")
    assert tuple(names2) == ("", "", "kills", "played", "", "kills", "kills", "HS",
                      "kills", "const.", "dest.", "played", "kills")
    for value in positions:
        assert str(value) in SOURCE
    for value in names + names2:
        if value:
            assert f'"{value}"' in SOURCE
    assert "for(i = 0; i < 13; ++i)" in SOURCE
    assert "globalStats.transition == 1" in SOURCE
    assert "globalStats.transition == 2" in SOURCE


if __name__ == "__main__":
    main()
