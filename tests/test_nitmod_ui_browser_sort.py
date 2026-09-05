from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def main() -> None:
    source = (ROOT / "src_2.60/ui/ui_main.c").read_text(
        encoding="utf-8", errors="replace"
    )
    assert 'trap_Cvar_Set("ui_browserSortKey", va("%d", column))' in source
    assert "ui_browserSortKey.integer" in source
    assert "column > SORT_FAVOURITES" in source
    assert source.index("uiInfo.serverStatus.sortKey = Com_Clamp") > source.index(
        "UI_RegisterCvars();"
    )
    print("nitmod UI browser sort persistence: ok")


if __name__ == "__main__":
    main()
