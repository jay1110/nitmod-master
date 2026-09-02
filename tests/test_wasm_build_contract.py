"""Source contracts, not an Emscripten build."""
from pathlib import Path
import re
import unittest
ROOT = Path(__file__).resolve().parents[1] / "src_2.60"

class WasmBuildContract(unittest.TestCase):
    def test_entrypoints(self):
        for directory, prefix in (("game", "g"), ("cgame", "cg"), ("ui", "ui")):
            for suffix, symbol, result in (("main", "vmMain", "int"), ("syscalls", "dllEntry", "void")):
                source = (ROOT / directory / (prefix + "_" + suffix + ".c")).read_text()
                self.assertEqual(len(re.findall(r"^NITMOD_MODULE_EXPORT " + result + r" " + symbol + r"\s*\(", source, re.M)), 1)

    def test_macro(self):
        source = (ROOT / "game/q_shared.h").read_text()
        self.assertRegex(source, r'#if defined\(__EMSCRIPTEN__\)\s+#define NITMOD_MODULE_EXPORT __attribute__\(\(visibility\("default"\)\)\)\s+#else\s+#define NITMOD_MODULE_EXPORT\s+#endif')

    def test_syscall_adapter_contract(self):
        header = (ROOT / "game/nitmod_syscall_abi.h").read_text()
        wasm, native = header.split("#else", 1)
        self.assertIn('NITMOD_MODULE_EXPORT int vmWasmAbi1(void) { return 1; }', wasm)
        self.assertRegex(native, r'#define NITMOD_WASM_ABI_EXPORT\s*\n')
        self.assertIn("typedef intptr_t (QDECL *nitmod_syscall_t)(intptr_t *);", wasm)
        self.assertIn("typedef int (QDECL *nitmod_syscall_t)(int, ...);", native)
        self.assertIn("nitmodSyscall((intptr_t[]){NM_SLOTS(__VA_ARGS__)})", wasm)
        for directory, prefix in (("game", "g"), ("cgame", "cg"), ("ui", "ui")):
            source = (ROOT / directory / (prefix + "_syscalls.c")).read_text()
            self.assertIn("nitmod_syscall_abi.h", source)
            self.assertIn("dllEntry( nitmod_syscall_t syscallptr )", source)
            self.assertIn("#define syscall NITMOD_SYSCALL", source)
            self.assertIn("nitmodSyscall = syscallptr;", source)
            self.assertEqual(source.count("\nNITMOD_WASM_ABI_EXPORT\n"), 1)

    def test_qagame_wasm_entrypoint_slots(self):
        source = (ROOT / "game/g_main.c").read_text()
        signature = source.split("NITMOD_MODULE_EXPORT int vmMain(", 1)[1].split(") {", 1)[0]
        native, tail = signature.split("#ifdef __EMSCRIPTEN__", 1)
        self.assertEqual(re.findall(r"int (\w+)", native), ["command"] + ["arg%d" % i for i in range(7)])
        self.assertEqual(re.findall(r"int (\w+)", tail), ["arg%d" % i for i in range(7, 12)])
        self.assertIn("#endif", tail)

    def test_side_module_setup(self):
        source = (ROOT / "CMakeLists.txt").read_text()
        setup = source.split("function(nitmod_module", 1)[0]
        self.assertRegex(setup, r'if\(EMSCRIPTEN\)[\s\S]*?set_property\(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE\)[\s\S]*?endif\(\)')
        self.assertIn('tools/verify_wasm_module.py', source)
        self.assertIn('set(NITMOD_ARCH "wasm32"', setup)
        self.assertIn('add_library(${target} MODULE ${ARGN})', source)
        self.assertIn('target_compile_options(${target} PRIVATE -fvisibility=hidden)', source)
        self.assertIn('target_link_options(${target} PRIVATE -sSIDE_MODULE=1)', source)
        self.assertIn('target_link_options(${target} PRIVATE "LINKER:--fatal-warnings")', source)

    def test_revive_signature_shared(self):
        header = (ROOT / "game/g_local.h").read_text()
        self.assertRegex(header, r'qboolean ReviveEntity\( gentity_t \*ent, gentity_t \*traceEnt \);')
        self.assertNotRegex((ROOT / "game/g_svcmds.c").read_text(), r'extern\s+void\s+ReviveEntity')
        self.assertRegex((ROOT / "game/g_weapon.c").read_text(), r'qboolean ReviveEntity\(')

if __name__ == "__main__":
    unittest.main()
