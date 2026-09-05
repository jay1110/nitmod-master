from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "src_2.60/game/g_nitmod_omnibot.c").read_text(encoding="utf-8")
ADAPTER = (ROOT / "src_2.60/game/g_nitmod_etbot_interface.cpp").read_text(encoding="utf-8")
MAIN = (ROOT / "src_2.60/game/g_main.c").read_text(encoding="utf-8")
LOADER = (ROOT / "src_2.60/omnibot/common/BotLoadLibrary.cpp").read_text(encoding="utf-8")
SHELL = Path(r"C:/Users/micha/Documents/GitHub/etlegacy/src/web/shell.html")


def test_wasm_module_name_matches_browser_preload():
    assert 'return "omnibot_et.wasm32.so";' in SOURCE
    if SHELL.exists():
        shell = SHELL.read_text(encoding="utf-8")
        assert "var OMNIBOT_MODULE = 'omnibot_et.wasm32.so';" in shell


def test_status_uses_real_adapter_state():
	assert "Bot_Interface_IsLoaded()" in SOURCE
	assert "typed ETInterface active=%i" in SOURCE
	assert "adapter is not linked yet" not in SOURCE


def test_typed_adapter_uses_original_nitmod_contract():
	assert 'Omnibot_LoadLibrary(17,' in ADAPTER
	assert '"omnibot_et"' in ADAPTER
	assert 'Bot_Interface_InitHandles();' in MAIN
	assert 'Bot_Interface_Update();' in MAIN
	assert 'Bot_Interface_Shutdown();' in MAIN


def test_cgame_wasm_pmove_uses_direct_trace_callbacks():
	pmove = (ROOT / "src_2.60/game/bg_pmove.c").read_text(encoding="utf-8")
	helper = pmove.split("void PM_NITMOD_TraceWorld", 1)[1].split("// movement parameters", 1)[0]
	assert '#if defined(CGAMEDLL) && defined(__EMSCRIPTEN__)' in helper
	assert 'CG_TraceCapsule_World(' in helper
	assert 'CG_TraceCapsule(' in helper
	assert 'G_NITMOD_WasmTraceCapsule' not in pmove


def test_empty_wasm_path_uses_preloaded_module_in_working_directory():
	assert '(path && path[0]) ? path : "."' in LOADER
	assert '"./%s.wasm32.so"' in LOADER


def test_external_bots_never_enter_et260_legacy_aas_botlib():
	client = (ROOT / "src_2.60/game/g_client.c").read_text(encoding="utf-8")
	assert '!G_NITMOD_LegacyCvarInteger("omnibot_enable", 0) &&' in client
	assert 'case BOTAI_START_FRAME:' in MAIN
	assert 'G_NITMOD_LegacyCvarInteger("omnibot_enable", 0)' in MAIN


def test_probe_validates_original_export_table_without_initializing_it():
	assert "ExportBotFunctionsFromDLL" in SOURCE
	assert "exportFunctions(&exports, sizeof(exports))" in SOURCE
	assert "exports.initialize" in SOURCE
	assert "exports.update" in SOURCE
	assert "exports.shutdown" in SOURCE
	assert "exports.initialize(" not in SOURCE
