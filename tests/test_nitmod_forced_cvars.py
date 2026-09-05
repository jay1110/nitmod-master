from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/cgame/cg_nitmod_config.c").read_text(encoding="utf-8")
MAIN = (ROOT / "src_2.60/cgame/cg_main.c").read_text(encoding="utf-8")


assert "char original[256];" in SOURCE
assert "trap_Cvar_VariableStringBuffer(name, nitmodForcedCvars[i].original" in SOURCE
assert SOURCE.count("nitmodForcedCvars[i].original") >= 2
assert "void NITMOD_RestoreForcedCvars(void)" in SOURCE
assert "trap_Cvar_Set(entry->name, entry->original);" in SOURCE
assert MAIN.index("NITMOD_RestoreForcedCvars();") < MAIN.index("CG_NitmodLogShutdown();")

print("Nitmod forced-cvar capture and restoration checks passed")
