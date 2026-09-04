# Validated limbo setup submission

The primary selected-slot accessor now shares the same normalization as the
selected-number accessor: invalid, empty or newly disabled selections reset
to primary index zero. Previously direct submission bypassed that normalization
and could send WP_NONE for a stale index. Secondary normalization is retained;
unsupported selected-slot requests return WP_NONE before mutating either slot.

CG_LimboPanel_SendSetupMsg validates the snapshot, local client, menu team and
class before indexing state. It validates both resolved weapons and their
protocol IDs before sending. Valid native/original `team <team> <class>
<primary> <secondary>` messages are unchanged. The spectator branch remains
separate. A non-forced submission with a spectator menu can no longer send zero
weapons to a playing team; this is intentional defensive behavior, not invalid
input parity with the original.

Original behavior reference: CG_LimboPanel_SendSetupMsg and
CG_LimboPanel_GetSelectedWeaponNum in sorted cgame_ui.c. The original already
falls back from restricted nondefault primary weapons; the new typed shared
path extends this safely to invalid selection indices. Existing original-only
class lists and weapon conversion continue to determine the sent values.

Tests submit actual non-forced setup messages for both protocols, both teams
and all five classes with invalid primary/secondary indices (20 cases), assert
exact commands, repaired selections and loadout flags. Additional invalid team,
class and missing-snapshot cases assert no command. Existing class/skill/quota
tests remain. Forced team-change UI side effects, live server acceptance and
browser interaction still need end-to-end verification. No pak assets change.
