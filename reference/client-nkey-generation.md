# Missing NKey creation and verified loading

Original reference: `cgame/sorted/cgame_nitrox.c`,
`nitrox_GenerateNKeyFile` (call-site return 0x108bc9), `G_SHA1`,
`nitrox_ReadNKey` (0x108e3a return site). These labels are not all function
entrypoints. Existing decoder documentation uses ELF-relative addresses.

New typed unit `cg_nitmod_key.c` reconstructs the key format and lifecycle:

- `%S%j%M%d%w%U%H` produces exactly 14 local-time timestamp bytes, using the
  engine's qtime_t instead of native time()/localtime().
- One-block SHA-1 produces uppercase hexadecimal. The first 28 characters
  occupy key positions 2..29. Four A..Z checksum characters occupy 30,31,0,1.
- The original quarter-step acceptance bounds raise the checksum residue to
  100, making the sum of all 32 ASCII characters divisible by 100.
- Base64 produces exactly 44 file bytes, with one trailing `=` and no file
  newline or NUL. The existing decoder validates the result independently.
- A missing nkey.dat triggers creation through engine filesystem calls.
  A second existence check precedes writing. Existing valid or corrupt
  identities are never intentionally replaced. Failed/short/mismatched
  readback cannot publish n_guid. No recursive retry loop is used.

Intentional differences and remaining limitations:

- The original unbounded rejection RNG loop is replaced with bounded selection
  over its acceptance interval (four rand() calls). Format/checksum semantics
  match; random-number consumption and output distribution do not.
- Existing corrupt files are preserved, unlike the original overwrite path.
- This is the original weak, time-derived game identifier, not a secure
  authentication secret, hardware attestation, or collision-proof identity.
- Engine FS APIs provide no exclusive-create/atomic-rename guarantee. The
  double check is not a cross-process locking mechanism.
- Browser restart persistence depends on the engine's filesystem sync. That
  and acceptance by a real original dedicated server remain unverified.
- No key or GUID is printed; tests use in-memory files and create no real
  player identity. No pak, PK3, menu, or original binary changes.

Verification: a timestamp SHA-1 golden value independently computed with
.NET SHA1, 2,928 day/random-choice format-and-decoder cases, malformed-time
rejection, and mock filesystem tests for creation, reuse, unavailable clock,
write-open failure, short/corrupt readback, and preservation of valid/corrupt
existing files. CMake and historical SCons both include the new unit.
