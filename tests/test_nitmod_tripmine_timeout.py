from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MISSILE = (ROOT / "src_2.60/game/g_missile.c").read_text(encoding="utf-8")
CLIENT = (ROOT / "src_2.60/game/g_client.c").read_text(encoding="utf-8")
COMMANDS = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")

def test_tripmine_owner_cleanup_and_lifecycle_consumers():
    start = MISSILE.index("void G_NITMOD_RemoveTripmines")
    cleanup = MISSILE[start:MISSILE.index("G_LandmineThink", start)]
    assert "i = level.maxclients; i < level.num_entities" in cleanup
    assert "mine->s.weapon != WP_TRIPMINE" in cleanup
    assert "mine->parent != owner" in cleanup
    assert "mine->r.ownerNum = ENTITYNUM_NONE;" in cleanup
    assert "G_FreeEntity(mine);" in cleanup
    assert 'G_NITMOD_LegacyCvarInteger("n_tripmineTimeout", 1)' in CLIENT
    assert 'oldTeam != team && G_NITMOD_LegacyCvarInteger("n_tripmineTimeout", 1)' in COMMANDS

if __name__ == "__main__":
    test_tripmine_owner_cleanup_and_lifecycle_consumers()
    print("nitmod tripmine timeout checks passed")
