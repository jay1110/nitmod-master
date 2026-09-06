"""Source regression for stop dispatch; does not exercise the renderer."""
from pathlib import Path

root = Path(__file__).resolve().parents[1]
text = (root / "src_2.60/ui/ui_main.c").read_text()
body = text.split("static void UI_StopCinematic(int handle) {", 1)[1].split(
    "static void UI_DrawCinematic", 1)[0]
assert "abs(" not in body
for kind in ("MAP", "NETMAP", "CLAN"):
    assert f"handle == -UI_{kind}CINEMATIC" in body
assert body.index("ui_currentMap.integer >= uiInfo.mapCount") < body.index("uiInfo.mapList[")
assert body.index("uiInfo.teamCount > MAX_TEAMS") < body.index("UI_TeamIndexFromName")
assert "uiInfo.mapList[ui_currentMap.integer].cinematic = -1;" in body
assert "uiInfo.serverStatus.currentServerCinematic = -1;" in body
assert "uiInfo.teamList[i].cinematic = -1;" in body
print("Cinematic signed dispatch, bounds and reset source checks passed")
