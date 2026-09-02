# Reload preference flags

## Per-call Pmove input

Both cg_predict setup paths now assign a capability-gated preference word
from the same cvars used for userinfo. Both g_active setup paths assign the
word from pers.bAutoReloadAux/pers.bAltReloadAux. It is appended to mod-local
pmove_t as nitmodReloadPreferenceFlags, not serialized into playerState_t,
usercmd_t or snapshots; pmoveExt_t remains unchanged. All modules must be
rebuilt together after this private structure change.

NITMOD_BuildPmoveReloadPolicy consumes this explicit input independently of
pmoveExt resets. The 102400 local/server policy comparisons now also check
the per-call projection, plus a reset/null-pmext case. Source-contract checks
require refresh in all four setup locations and the matching client capability
gate. Existing client-slot initialization clears the entire client; spawn
preserves clientPersistant_t, including the new preference. Server callers
rebuild the word from that persistent data rather than from stale pmext memory.

This is live input delivery only. Stock PM_CheckForReload still does not read
the new field or dispatch the reconstructed weapon flow. End-to-end prediction,
respawn and reconnect validation in the actual engine remains outstanding.

## Live preference transport (not gameplay activation)

cg_main now registers archived cg_weapAltReloads with conservative default 0
(this default is a port decision, not a proven original registration default).
Its update joins the existing client-flag refresh path. CG_setClientFlags uses
the shared encoder; it publishes bit 0x10 only after the new RELOAD_PREFS
capability (bit 11) is acknowledged. Existing autoReload and other stock flag
semantics, timenudge/maxpackets tuple and demo guard remain unchanged.
An acknowledgement, removed feature or protocol mismatch republishes the
flags. Initialization clears capabilities before existing cvar registration
publishes initial flags, preventing carry-over to an unsupported server.

qagame retains the incoming preference in pers.bAltReloadAux, independent of
pmoveExt and the existing bAutoReloadAux. Bot userinfo explicitly clears it.
This is preference storage only: no active weapon code reads the new member.
The capability advertises transport, NOT completed reconstructed gameplay.
Both feature masks include it; older peers do not receive the added flag from
this client without acknowledgement. The server storage itself is passive
and can decode the known original bit without altering movement or weapons.

All host modules build. Source-contract tests verify registration/default,
update triggering, demo/capability gating, acknowledgement/mismatch refresh
and server decode/reset. Existing exhaustive codec tests remain in place.
These checks do not substitute for an in-engine join/reconnect/userinfo test.

Original CG_setClientFlags_part_0 derives local autoReload/altReload values
from cg_autoReload.integer > 0 and cg_weapAltReloads.integer > 0, and packs
them into cg_uinfo bits 0x01 and 0x10. The three-integer wire tuple remains
flags, timenudge, maxpackets. No native pmoveExt field should be accessed via
the original client's private +0x80 offset.

Server ClientUserinfoChanged extracts bit 4 at ELF 0x4b5a2..0x4b5ae,
storing it both in its private preference field and pmext (+0x5328 relative
to the original client, +0x88 relative to original pmext). Bit 0 is stored
at 0x4b5b6..0x4b5bf. This confirms producer/consumer agreement for the
secondary-attack reload setting; it is not a guessed unused protocol bit.

NITMOD_EncodeReloadPreferences replaces ONLY these two bits in an existing
flag word and uses >0 semantics, preserving unrelated/high bits. The decoder
returns a typed, normalized preference pair. NITMOD_BuildReloadPolicyFromFlags
projects received flags and a native usercmd directly to the common decision
policy without changing native pmoveExt. Thus local cvar-derived flags and
server-received flags have an explicit shared interpretation.

3200 combinations cover seven low flag bits plus an unrelated high bit,
and INT_MIN/-1/0/1/INT_MAX for each cvar. Additional 102400 comparisons
check the flag-derived policy against the existing local-input builder over
16 wbuttons patterns and both weapon preference flags. Null-input rejection,
idempotent encoding and unrelated-bit preservation are checked.

The codec's initial isolated stage has now been wired as described above.
It does not change the userinfo tuple or other preference flags. Full engine
replay and gameplay integration remain outstanding. Runtime overrides of weapon auto-reload defaults were
not established in this increment; no such behavior was invented.
