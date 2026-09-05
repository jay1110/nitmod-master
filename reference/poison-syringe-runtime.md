# Poison syringe runtime reconstruction

Original references: qagame `Weapon_Poison` and the poisoned-client branch in
`ClientThink_real`; cgame original death cause 59 and the poisoned view flag.

WP_POISON_SYRINGE now uses the shared melee prediction path and emits the same
fire transaction in cgame/qagame. The server traces 64 units from the typed
activate muzzle, accepts only a living client outside spawn protection, and
honors friendly fire outside LMS. A hit latches attacker, increments the poison
stack, sets the original overloaded eFlag 0x00200000, and starts its tick timer.

The original `g_poison` Cvar is registered and live-updated by the ordinary game
Cvar table. Without bit 4, fallback damage/interval are 1/50 ms; with bit 4 they
are 10/1500 ms. A parsed nonzero poison.weap damage overrides the fallback.
Each tick multiplies damage by the stack count and retains attacker attribution.
Death, spectator state, or an empty stack clears the visual poison flag. The
native obituary is transported safely as syringe plus a private marker; an
original server cause 59 maps directly to MOD_POISON and the existing cgame
view warp/obituary implementation.

The item and UI player preview already use the appended poison-syringe record,
so no pak model/menu change is required. The spawn loadout now mirrors the
recovered original condition: any nonzero `g_poison` plus the fifth First Aid
unlock grants the typed poison syringe with its active weapon-definition ammo
and clip values. Health-pack and cabinet cleansing consumes options 2 and 8
through the shared poison reset helper. A successful syringe hit emits NCS
sound slot 8 through ET's typed general-sound primitive; cgame resolves both
that event and original private event 100 through the bounded server sound
table. Admin-applied poison remains open.
Browser gameplay replay is not a unit-test substitute.
