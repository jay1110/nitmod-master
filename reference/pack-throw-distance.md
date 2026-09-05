# Pack throw distance

Original qagame reads `g_throwDistance` at both normal class-weapon launch
sites: `Weapon_Medic` and `Weapon_MagicAmmo`.  The value scales the clamped
view direction before the original random vertical impulse is added.

The reconstructed typed paths now consume the registered legacy cvar with the
original default 75.  No artificial clamp is applied, preserving server policy
for zero, negative and unusually large configured values.  Limbo/admin pack
drops use separate random velocity logic and are not conflated with these two
class-weapon paths.
