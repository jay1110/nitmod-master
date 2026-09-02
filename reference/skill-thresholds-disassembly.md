# Skill threshold reconstruction

qagame SHA-256: `84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49`.
GNU objdump `-d --disassemble=nitrox_SendSkillLevels` resolves the sender at
ELF `0x0010f640` (size `0x1aa`). The PIC base is `0x002a4614`.
Each va call formats `%s` from a vmCvar object's address plus 16, its string
member; these are not raw skill threshold arrays.

| Key | Symbol | ELF object address | Skill index |
| --- | --- | --- | --- |
| S | g_skillSoldier | 0x02e45a60 | 5 (heavy weapons) |
| M | g_skillMedic | 0x02e4a380 | 2 (first aid) |
| E | g_skillEngineer | 0x02e43d20 | 1 (engineering) |
| F | g_skillFieldOps | 0x02e46ea0 | 3 (signals) |
| C | g_skillCovertOps | 0x02e479e0 | 6 (covert ops) |
| B | g_skillBattleSense | 0x02e416e0 | 0 (battle sense) |
| L | g_skillLightWeapons | 0x02e38b60 | 4 (light weapons) |

The cgame decompile's CG_UpdateSkills and InitSkillLevelStructure confirm
the key/index mapping and five parsed thresholds after level zero. The
original qagame `skillLevels` data symbol is 168 bytes at `0x002a5640`.
`objdump -s --start-address=0x2a5640 --stop-address=0x2a56e8` shows seven
identical six-int rows: 0, 20, 50, 90, 140, 200. These are binary initial
values, not proof of runtime Cvar defaults after initialization.

Native ET declares NUM_SKILL_LEVELS=5 and a single const threshold array.
The new nitmod_skills parser stores a separate 7x6 matrix; it does not alter
that ABI or advertise/dispatch sl. Level-up, XP calculation, UI, save-state
and network consumers must be audited together before activation.

The parser intentionally rejects missing/extra fields, partial decimal tokens
and overflow; it accepts spaces/commas as separators and signed integers.
The original strtok/strtol parser was permissive and could copy uninitialized
values on short input. No malformed-input parity is claimed. The parser does
not enforce monotonicity or invent gameplay meaning for negative values.
