# Original fc receiver and frame application

The pinned original cgame ELF implements CG_ServerCommand at 0xa8e60.
Its PIC base is 0xa8e72 + 0x84dd2 = 0x12dc44. The five Q_stricmp
calls at 0xaa32c, 0xaa346, 0xaa360, 0xaa37a, 0xaa394 use these strings:

| ELF string address | Protected Cvar |
| --- | --- |
| 0x107786 | cl_profile |
| 0x105a05 | x |
| 0x10f27c | name |
| 0x1094e8 | sensitivity |
| 0x1016d7 | n_guid |

In particular, Ghidra's g_unk_00115a05 means literal `x`, not cl_guid.
The count check at 0xaa3a1 rejects requests once 64 entries exist, even
updates of existing names. Records contain two 256-byte strings. Names match
case-insensitively; a repeated name replaces its requested value. Demo
playback rejects commands. There is no reconstruction capability handshake.

The original frame path (sorted cgame_ui.c immediately after CG_UpdateCvars)
reads current values, compares case-insensitively, then prints, registers with
NULL vmCvar/flags zero, and sets mismatched values. It repeats every frame.
The port implements this with typed fixed storage and a cg_view frame hook.
Receiving fc does not change the engine Cvar immediately. Map-restart leaves
the list intact; full NITMOD_ClearConfigStrings clears it for a fresh session.

Intentional hardening: exact argument count; reject empty/overlong names and
overlong values instead of truncating; names restricted to ASCII letters,
digits and underscore; application also suppressed during demo playback;
current-value buffer expanded from 128 to 256 bytes. No extra protected name
has been guessed. No engine command string is constructed from fc values.
As in the original, previously set Cvar values are not restored at shutdown.

Full-cgame fixtures cover all protected names, malformed/oversized requests,
demo rejection, deferred application, case-insensitive replacement/comparison,
repeated enforcement, 64-entry saturation and session reset. The renderer
frame hook is compiled but these fixtures invoke the apply function directly.
This is client-side fc behavior only, not all Nitmod Cvars, a reconstructed
server forcecvar administration command, or live browser/server parity.
