from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/ui/ui_main.c").read_text(encoding="utf-8")


def test_localhost_is_not_hidden_or_rejected():
    block = SOURCE.split('Q_stricmp(name, "check_ServerStatus")', 1)[1]
    block = block.split('Q_stricmp(name, "ServerStatus_diagnose")', 1)[0]
    assert 'strcmp(s, "localhost")' not in block
    assert 'Menu_ShowItemByName( menu, "ctr_serverinfo", qtrue )' in block
    assert "UI_BuildServerStatus(qtrue);" in block


def test_browser_selection_is_bounded():
    block = SOURCE.split('Q_stricmp(name, "ServerStatus")', 1)[1]
    block = block.split('Q_stricmp(name, "InGameServerStatus")', 1)[0]
    assert "currentServer >= 0" in block
    assert "currentServer < uiInfo.serverStatus.numDisplayServers" in block
