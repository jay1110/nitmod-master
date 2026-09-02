# Active alternate-key reload input

## Original evidence

qagame `PM_CheckForReload` at `0x2a7d4..0x2a7f9` and cgame at
`0x19cb4..0x19cd9` read command wbuttons: bit 8 requests reload directly;
bit 1 also requests reload when the separate alternate-reload preference
is nonzero. The preference is stored at different original pmove-extension
offsets (server +0x88, client +0x80); these offsets are not copied into the
native structures. Native WBUTTON_RELOAD and WBUTTON_ATTACK2 identify the
two input bits. Primary BUTTON_ATTACK is not a substitute.

## Activation

`NITMOD_ManualReloadRequested` provides the request predicate for both the
recovered policy builders and actual shared `PM_CheckForReload`.
It reads `pmove_t.nitmodReloadPreferenceFlags`, which is already refreshed
in both server Pmove construction paths and both client prediction paths.
The existing `cg_weapAltReloads` userinfo/prediction capability gate is
unchanged. Bots continue to default to the option disabled.

This activates only input interpretation. It does not bypass inventory,
weapon-state, timer, noWeapClips or weapon exclusions; scoped requests still
use the current native unscoping path. No original ability word is inferred
from a native skill level. No new network field or ABI layout is introduced.
The helper returns false for a null command and ignores unrelated flags.

## Verification

6336 executed comparisons cover 44 mapped identities, option off/on,
four reload/alternate-key combinations, three inventory scenarios,
READY/FIRINGALT/RELOADING and zero/positive weapon time. Each actual input
is compared to an independently selected ordinary reload-key request.
Primary attack is set in every scenario to check that it does not become
an alternate request. Whole player/extension state, body events and
weapon-condition calls are compared. Existing policy tests continue to
check preference encoding, decoding and both policy-builder interfaces.

The source contract verifies the active call and the pre-existing server,
client and capability-gated preference producers. Debug host build and
66/66 CTests pass. This does not establish network-transcript, complete
PM_Weapon scheduler, original-ELF replay or Linux-i386/WASM release parity.
