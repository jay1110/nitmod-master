from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CMDS = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
MAIN = (ROOT / "src_2.60/game/g_main.c").read_text(encoding="utf-8")
LOCAL = (ROOT / "src_2.60/game/g_local.h").read_text(encoding="utf-8")
CG_DRAW = (ROOT / "src_2.60/cgame/cg_draw.c").read_text(encoding="utf-8")


def test_vote_caller_is_typed_and_published_by_bit_four():
    assert "int\t\t\tcallerClientNum" in LOCAL
    assert 'G_NITMOD_LegacyCvarInteger("g_voting", 1) & 4' in CMDS
    assert '"%s (called by %s)"' in CMDS


def test_late_voters_only_and_success_refund_are_wired():
    assert "level.time - level.voteInfo.voteTime >= 30000" in MAIN
    assert "level.voteInfo.voteYes + level.voteInfo.voteNo" in MAIN
    assert "(votingOptions & 2)" in MAIN
    assert "caller->pers.voteCount--" in MAIN
    assert "level.voteInfo.callerClientNum = -1" in MAIN


def test_cgame_does_not_treat_caller_annotation_as_kick_target():
    assert 'strstr(buffer, " (called by ")' in CG_DRAW
    assert "if(callerSuffix) *callerSuffix = '\\0'" in CG_DRAW


if __name__ == "__main__":
    test_vote_caller_is_typed_and_published_by_bit_four()
    test_late_voters_only_and_success_refund_are_wired()
    test_cgame_does_not_treat_caller_annotation_as_kick_target()
    print("nitmod g_voting option checks passed")
