# Resolved-clip consumption and exact-zero refill

Update: native availability/consumption hand selection is now shared and
covered by executed tests; see `weapon-firing-clip-integration.md`. The refill
helper described here is now active; see active-weapon-refill.md for settings,
admission boundaries and full-module tests.

Original PM_WeaponUseAmmo: ELF 0x2aa40. Entry selects refill when weapon is
original panzer ID 5 and g_war.integer==1, otherwise g_noReload.integer bit 0.
This is g_noReload, not g_weapons. The two predicates form a logical OR.
Original reads g_noReload at entry even when the war branch wins; the port
accepts explicit values without introducing Cvar reads or registrations.

After clip/akimbo selection, the original subtracts amount at 0x2aabd and
tests the resulting clip for zero at 0x2aac7..0x2aacf. Only exact zero and
the refill predicate select the replacement. Replacement is the resolved
clip's ammoTableMP.defaultStartingClip (+0x10), not maxclip (+0x08), read
at 0x2aad8..0x2aaec. Reserve ammo is not modified by this operation.

NITMOD_ConsumeWeaponClip operates on native playerState_t. Caller supplies
the firing weapon, resolved native clip slot, amount, war/noReload values,
and the matching clip's ammotable_t. It changes only ammoclip[clip]. Slot
selection, akimbo hand choice and current weapon are deliberately not inferred.
Zero consumption on an already empty clip can refill, matching the original
post-subtraction test. Non-empty clips do not refill. Only war==1 grants the
panzer exception; other noReload bits do not grant refill.

Hardening: null/invalid native indices, negative amounts, negative clip counts
(including the infinite-ammo sentinel), overspending and a negative refill
value when refill actually occurs fail without mutation. Thus subtraction
cannot overflow and cannot produce negative ammunition. The original helper
itself does not guard overspending; its surrounding caller controls admission.
An invalid unused refill value does not affect a normal subtraction.

Tests cover 20580 combinations of native weapon IDs, war values, noReload
bit patterns and zero/nonzero amounts/clips, comparing the full playerState_t
against a one-slot expected change. Integer limits, infinite clips, invalid
arguments, negative refill rejection and zero refill are checked separately.
The helper builds in cgame and qagame but no gameplay call site is changed.

Still pending: real native clip aliases/akimbo selection, Cvar/protocol
ownership, surrounding fire admission and the knife alternative attack.
The observed original weaponstate==6 is not copied as native state 6:
ET 2.60's native enum has different state numbering. A semantic mapping
must be established before porting that override. This helper is not a full
PM_WeaponUseAmmo replacement or original-runtime parity proof.
