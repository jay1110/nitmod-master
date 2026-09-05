from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def read(relative: str) -> str:
    return (ROOT / relative).read_text(encoding="utf-8", errors="replace")


def main() -> None:
    public = read("src_2.60/game/bg_public.h")
    pmove = read("src_2.60/game/bg_pmove.c")
    server = read("src_2.60/game/g_active.c")
    client = read("src_2.60/cgame/cg_predict.c")

    for field in ("nitmodCrouchStandTime", "nitmodStandCrouchTime",
                  "nitmodProneDelay", "nitmodCrouchStandDelay",
                  "nitmodStandCrouchDelay"):
        assert field in public, f"missing shared stance field: {field}"

    assert server.count('G_NITMOD_LegacyCvarInteger("n_crouchStandDelay", 0)') == 2
    assert server.count('G_NITMOD_LegacyCvarInteger("n_standCrouchDelay", 0)') == 2
    assert server.count('G_NITMOD_LegacyCvarInteger("n_proneDelay", 0)') == 2
    assert client.count("NITMOD_SimpleConfig()->crouchStandDelay") == 2
    assert client.count("NITMOD_SimpleConfig()->standCrouchDelay") == 2
    assert client.count("NITMOD_SimpleConfig()->proneDelay") == 2
    assert "pm->pmext->nitmodCrouchStandTime" in pmove
    assert "pm->pmext->nitmodStandCrouchTime" in pmove
    assert "pm->ps->weapon != WP_MORTAR_SET" in pmove

    assert "((pm->nitmodProneDelay & ~2) == 1) ? 1750 : 750" in pmove

    print("nitmod stance-delay contract: ok")


if __name__ == "__main__":
    main()
