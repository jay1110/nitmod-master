# Original Omni-bot loader contract

Update: schema 2 now includes the complete 55-slot ETInterface relocation
inventory in bot-loader-contract.json; signatures/ABI semantics remain partial.

tools/extract_bot_loader.py reads only the SHA-256-pinned original qagame ELF.
It maps sections, decodes checked PIC address operands and reads the referenced
strings/immediates. It neither searches the machine for a library nor loads one.
The CTest regression asserts the recovered values and rejects altered artifacts.

Recovered contract:

- Bot_Interface_Init at ELF 0x21f430 requests interface version **17**, not 44.
- Library base name: omnibot_et. Export: ExportBotFunctionsFromDLL.
- Omnibot_LoadLibrary at 0x22a090 zeroes an i386 export table and calls the export
  with its pointer and **44-byte size**, not the interface version.
- On export success, table slot zero is called with the allocated engine-interface
  object and version 17. The loaded flag is set iff that initializer returns zero.
- Observed path formats: %s/%s.so, ./%s.so and %s/omni-bot/%s.so. These are
  forensic strings, not permission to load libraries from those paths.

The engine-interface allocation is a four-byte C++ object whose vtable pointer
is assigned at 0x21f46a. Its full virtual method order, signatures and return
conventions remain unreconstructed. A native 64-bit or WASM flat C table cannot
be assumed compatible with the original i386 object or its 44-byte exports.
The count alone does not establish all eleven export signatures.

The extractor records runtime_compatible=false deliberately. No loader, fake
success response, ABI cast or event-dispatch hook is added to production in this
step. The next requirement is a verified export-slot and engine-vtable inventory,
then typed adapters and transactional load/failure/unload tests. Existing bot
handle lifecycle maintenance remains active and independent of library loading.
Host rebuild and all 83 CTests pass, including the new forensic regression.

## Engine virtual table relocation inventory

_ZTV11ETInterface is at ELF 0x2a4240, size 0xe4. Its object address point is
0x2a4248, after the offset-to-top and RTTI entries. All 55 subsequent method
slots are R_386_32 dynamic relocations; raw file words are zero and cannot be
read as method addresses. The extractor resolves each relocation's dynamic
symbol, requires a defined function and zero addend, and records slot, mangled
symbol, ELF target address and SHA-256 of its code. Missing/duplicate slots or
unsupported relocation kinds fail. The test compares the whole versioned JSON
with regenerated results and injects a wrong relocation type as a negative case.

The first slots are AddBot, RemoveBot, ChangeTeam, ChangeClass, UpdateBotInput
and BotCommand. Four entries require care: 34/35/37/38 are inherited
IEngineInterface implementations rather
than ETInterface overrides. Slots 53 and 54 are complete-object and deleting
destructors, not gameplay callbacks. The exact list, including all methods and
hashes, is in the JSON. Names identify parameter encodings, but ordinary C++
mangling does not establish return types, struct layouts or calling conventions.

Reproduce with `python -B tools/extract_bot_loader.py --output
reference/bot-loader-contract.json` from the repository root. This remains a
read-only binary analysis, apart from writing that explicit report. No original
code is loaded, no library ABI is assumed compatible, and no production loader
is enabled. All 83 host tests pass.
