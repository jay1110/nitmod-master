from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_ui_links_protocol_parser_used_by_server_status():
    cmake = (ROOT / "src_2.60/CMakeLists.txt").read_text(encoding="utf-8")
    status = (ROOT / "src_2.60/ui/ui_nitmod_status.c").read_text(encoding="utf-8")
    ui_target = cmake.split("if(NITMOD_BUILD_UI)", 1)[1].split("endif()", 1)[0]
    assert "NITMOD_ParseProtocolInteger" in status
    assert "game/nitmod_protocol.c" in ui_target


if __name__ == "__main__":
    test_ui_links_protocol_parser_used_by_server_status()
