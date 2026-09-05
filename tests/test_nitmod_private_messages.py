from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]


def test_private_message_command_honors_original_runtime_contract():
    source = (ROOT / "src_2.60/game/g_cmds.c").read_text(encoding="utf-8")
    start = source.index("static void G_NITMOD_PrivateMessage(")
    end = source.index("void Cmd_SwapPlacesWithBot_f", start)
    function = source[start:end]

    assert 'G_NITMOD_LegacyCvarInteger("g_privateMessages", 1)' in function
    assert "G_NITMOD_ClientMuted(ent)" in function
    assert "ClientNumberFromString(ent, (char *)targetName)" in function
    assert "COM_BitCheck(target->client->sess.ignoreClients" in function
    assert 'va("lc \\"%s\\"", cleanMessage)' in function
    assert '!Q_stricmp(cmd, "m") || !Q_stricmp(cmd, "pm")' in source
    assert 'Q_stricmpn(cursor, "/pm ", 4)' in source
    assert 'Q_stricmpn(cursor, "/m ", 3)' in source
    assert source.count("G_NITMOD_TryChatPrivateMessage(ent)") == 3


if __name__ == "__main__":
    test_private_message_command_honors_original_runtime_contract()
