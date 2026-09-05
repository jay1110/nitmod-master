from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MAIN = (ROOT / "src_2.60/game/g_main.c").read_text(encoding="utf-8")
LOCAL = (ROOT / "src_2.60/game/g_local.h").read_text(encoding="utf-8")
LEGACY = (ROOT / "src_2.60/game/g_nitmod_legacy_cvars.c").read_text(encoding="utf-8")
SVCMDS = (ROOT / "src_2.60/game/g_svcmds.c").read_text(encoding="utf-8")

assert '{ &g_XPSave, "g_XPSave", "15"' in MAIN
assert '{ &g_XPSaveMaxAge, "g_XPSaveMaxAge", "86400"' in MAIN
assert "extern vmCvar_t\t\tg_XPSave;" in LOCAL
assert '"g_XPSave"' not in LEGACY
assert '"g_XPSaveMaxAge"' not in LEGACY
assert "g_XPSave.integer & 1" in SVCMDS
assert "g_XPSave.integer & 4" in SVCMDS
assert "g_XPSaveMaxAge.integer * 1000" in SVCMDS
assert "G_XPBackupExpired" in SVCMDS
assert "memcpy( &in, m, sizeof( in ) );" in SVCMDS
assert "i < MAX_XPSTORAGEITEMS" in SVCMDS

print("Nitmod XP-save runtime contract checks passed")
