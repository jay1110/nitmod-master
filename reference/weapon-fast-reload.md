# Fast reload duration

NITMOD_ReloadDuration uses the explicitly supplied light-weapon ability word,
bit 0x4. This is not a native ET skill level. The original gate is qagame
PM_BeginWeaponReload 0x28884, client 0x17d94. Supported original identities
are 2,3,7,8,10,14,31,38, from BG_isLightWeaponSupportingFastReload at
qagame 0x25f50 / cgame 0x154a0: Luger, MP40, Colt, Thompson, Sten,
silencer, FG42 and silenced Colt. Scoped FG42 and akimbo are not included.

The original scaling uses FILD integer load, FMULS with stored binary32
0x3f266666, then FISTP under round-toward-zero control, with no intervening
binary32 product store (server 0x28974..0x28994, client 0x17e84..0x17ea4).
The factor bytes are independently hash-pinned at qagame 0x22ee68 and
cgame 0x1000ec by the reference test. They represent 5452595/8388608,
slightly less than exact decimal 0.65: base duration 20 gives 12, not 13.

The portable implementation computes that rational using int64_t and divides
by 8388608. All int32 inputs fit the signed intermediate product.
This reproduces truncation of the exact product (normal extended-precision
x87 behavior) without depending on host float-expression rounding. Altered
x87 precision-control environments are not emulated or claimed as tested.
Negative durations/unsupported IDs/null output reject without changing output.
Absent ability or unsupported fast-reload weapon retains the original duration.

352352 cases compare 44 identities x 8 ability words x durations 0..1000
against a binary64 oracle and the real native fast-reload weapon classifier.
Boundary tests include INT_MAX, high unrelated ability bits, zero, the
20-to-12 rounding distinction and invalid inputs. Duration calculation is
also composed with the alternate-fire-to-reloading timing effect, preserving
all other state. Large-value oracle splits quotient/remainder to avoid a
rounded large floating product.

The arithmetic primitive is now active in both modules, as described below.
Binding original live ability bits and the complete reconstructed reload flow
still remains.

## Active arithmetic-only correction

NITMOD_ScaleFastReloadDuration is independent of weapon identity, skill level
or capability words. It implements the exact signed factor/truncation rule;
negative legacy inputs truncate toward zero, without changing the recovered
NITMOD_ReloadDuration API's existing rejection of negative durations.
NITMOD_ReloadDuration delegates its multiplication to this primitive after its
own validation and recovered eligibility check.

Native PM_BeginWeaponReload now uses the primitive instead of `reloadTime *=
.65f`, while retaining the original native condition: SK_LIGHT_WEAPONS level
at least 2 and BG_isLightWeaponSupportingFastReload. This does not reinterpret
an ET skill level as the original ability word. It corrects arithmetic only;
the recovered ability contract and full dispatcher are not activated. Timing
still uses existing READY add/firing overlap and the same body/first-person
events. The original factor remains pinned in both reference modules.

840 additional real native begin cases cover eight eligible weapons and two
ineligible controls (akimbo Luger and scoped FG42), four native skill levels,
seven durations including zero, negative legacy values and INT_MAX, and three
accepted weapon states. Tests temporarily override and restore each native
ammo record's reloadTime to cover rounding boundaries. An independent
quotient/remainder oracle checks the results; direct primitive checks include
INT_MIN, 20 -> 12 and 1000 -> 649. Event, inventory and first-person animation
selection are also verified. Existing 352352 recovered-duration cases remain.

Host build and all 66 CTests pass. This establishes the reviewed normal x87
precision arithmetic, not an engine replay under altered floating-point
control modes or Linux-i386/WASM build validation.
