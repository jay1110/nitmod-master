# Engine module filenames

The original-package filename convention supplied by the user is authoritative:

| Target | cgame | ui | qagame |
| --- | --- | --- | --- |
| Windows x86 | cgame_mp_x86.dll | ui_mp_x86.dll | qagame_mp_x86.dll |
| Linux i386 | cgame.mp.i386.so | ui.mp.i386.so | qagame.mp.i386.so |
| Linux x86_64 | cgame.mp.x86_64.so | ui.mp.x86_64.so | qagame.mp.x86_64.so |
| macOS | cgame_mac | ui_mac | qagame_mac |
| WASM | cgame.mp.wasm32.so | ui.mp.wasm32.so | qagame.mp.wasm32.so |

ModuleArtifactName.cmake implements these names. Windows x64 host tests remain
separately named *.host.windows64.dll; they are not x86 engine modules. No Linux
or Mac binaries are fabricated by renaming Windows outputs. Mac names do not
certify legacy bundle packaging, CPU support or runtime ABI.

A fresh MSVC Win32 Release build produced all three x86 DLLs. objdump confirms
PE i386 format and public vmMain/dllEntry exports in each. CMake now supplies
an explicit Windows module-definition file; previously host DLLs lacked these
exports. The outputs are copied to build/windows-x86. Engine loading/gameplay
is not verified by these format and export checks.

The clean build also exposed UI_SAVEGAME_SHOT and FEEDER_SAVEGAMES dependencies
on the old modified asset header. Their historical ET values (258 and 0x10)
are now guarded code-local definitions for retained native handlers. pak remains
unchanged; no assertion of original Nitmod savegame functionality is made.
