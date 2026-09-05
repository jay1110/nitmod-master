# Configurable wounded-player limbo transition

Original qagame `G_Damage` at ELF 0x69380 (7848 bytes), recovered in
`nitmod_weapons.c`, normalizes g_forceLimboHealth as follows: positive values
are negated, negative values retained, zero selects -75. Registration at
0x2a8fa0 has default 75 and flags 0.

The active native G_Damage wounded-player branch now uses this normalized
threshold instead of FORCE_LIMBO_HEALTH. Health must be strictly below the
threshold and strictly above GIB_HEALTH; the original/native already-dead
guard remains. INT_MIN is handled without abs or negation overflow. Current
cvar state is read at the transition, so runtime changes apply immediately.

The full-qagame fixture executes G_Damage and the real limbo routine for ten
settings and 173 wounded health values (1730 cases). A NODROP contents fixture
avoids allocating a corpse while retaining real unlink, PMF_LIMBO and team
deployment queue mutations. Tests check exact resulting health, threshold
normalization, unlink count and queue membership. This is not a corpse-render
or browser test. Assets and client/server wire formats are unchanged.

Scope: only the wounded-to-limbo consumer is activated. Original G_Damage
also uses this threshold in additional special-damage and hit-feedback paths;
those require their own original MOD/flag mapping and are not claimed ported.
Team-change-without-killing still needs drop/spree/spawn lifecycle integration.
