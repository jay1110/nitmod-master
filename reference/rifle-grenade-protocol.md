# Rifle-grenade session and receive contract

Original qagame client+0xbe4 is emitted as `rn` by ClientUserinfoChanged
(sorted nitmod_client.c around 2735). It is the 26th integer (one-based)
in the original session%i string: writer loads it into tmp_u9, reader passes
the same address as its 26th numeric destination. Native ET session layout
is different; this does not authorize appending/reading the original format
without an explicit migration.

The cgame ELF's wordlist.2093 is at 0x12b2e0, size 0x2518, with eight-byte
pointer/token entries. nitrox_GetTokenForString returns the token at +4,
or 0x117 for an unknown name. tools/extract_client_tokens.py reads the
hash-pinned ELF and reconstructs 279 names without case-folding.
Relevant tokens: rn=0x89, w=0x49, lw=0x86, sw=0x88, lc=0x87.
CG_NewClientInfo case 0x89 uses strtol(base 10) into local_860; its whole
new client-info record starts cleared. This proves the client receive field,
not merely the server's chosen spelling.

Native cgame now receives optional rn into clientInfo_t.rifleGrenadeStatus.
It uses the existing strict signed-decimal parser: missing/malformed/overflow
values stay zero in the newly initialized record. This deliberately rejects
partial strings that original strtol may have accepted. Negative valid values
remain signed, rather than inventing a boolean wire restriction. Disconnect
clears the record as before. This is local cgame state, not playerState ABI.

The qagame rn producer is now active: SetWolfSpawnWeapons clears the status
before any early return and sets it from successful GPG40/M7 assignment.
ClientSpawn publishes updated userinfo after weapon assignment. Both human
and bot player configstrings carry rn. This does not grant additional weapons.

A native server-only session field owns the value; the existing 26-field
ET session string is unchanged. G_WriteClientSessionData writes a separate
nitmod_equipment<slot> Cvar containing canonical `1 0` or `1 1`. Reads default
to zero for missing, malformed or unknown versions; new sessions explicitly
initialize zero and write it, avoiding previous-occupant state inheritance.
This is a deliberate versioned persistence adaptation, not compatibility with
original Nitmod's longer session string. Executable adapter tests cover real
client fields, trap calls, roundtrip, slot bounds and legacy/malformed data.

The inner mid-life revocation path is now reconstructed in g_nitmod_rifle.c.
ClientThink_checkWeapons clears an owned and disabled original weapon 36/37,
then clears nonzero equipment state and calls ClientUserinfoChanged. The native
adapter maps these to GPG40/M7, publishes only on a status change and leaves
base rifle, ammo, selected/latched weapon and unrelated client fields intact.
No ownership means no operation, even if the session status remains set.
Tests compare complete client state and inspect it inside the publication
callback, checking ordering, both weapons, nonzero statuses and repeated calls.

Normal original G_DropWeapon and Pickup_Weapon alter weapon bits and alternate
weapons, but do not write client+0xbe4. Therefore ordinary drop/pickup hooks
must not derive this persisted status from ownership or ammunition. Native
drop/pickup code remains unchanged. Explicit restriction is a distinct path.

The adapter rejects invalid pointers/slots/weapons as deliberate hardening.
It uses the native ps.clientNum for publication; callers must maintain normal
entity/client slot identity. No full runtime weapon-check hook is enabled yet.
UI behavior and the complete restriction decision/guard integration remain pending.
Active rifle-grenade limit queries still retain native ET counting until that
revocation lifecycle is integrated. Servers without rn continue with zero.
Tests pin original token identities (including case distinction), verify the
active receive/reset source hooks and reuse existing signed-number tests.
They do not execute original CG_NewClientInfo or prove runtime transcript parity.
