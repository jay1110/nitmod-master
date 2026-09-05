from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def main() -> None:
    local = (ROOT / "src_2.60/game/g_local.h").read_text(encoding="utf-8")
    cmds = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
    client = (ROOT / "src_2.60/game/g_client.c").read_text(encoding="utf-8")

    for field in ("nitmodSlashKillPending", "nitmodSlashKillChargeTime",
                  "nitmodSlashKillDeathTime"):
        assert field in local
        assert field in cmds
        assert field in client

    assert client.index("if(options & 1)") < client.index("else if(options & 2)")
    assert client.index("else if(options & 2)") < client.index("else if(options & 4)")
    assert "level.time - G_NITMOD_ClassChargeTime(client) / 2" in client
    assert "client->ps.classWeaponTime = level.time;" in client
    assert "level.time - client->nitmodSlashKillDeathTime" in client
    assert "G_NITMOD_ApplySlashKillCharge(client);" in client
    print("nitmod slash-kill charge policy: ok")


if __name__ == "__main__":
    main()
