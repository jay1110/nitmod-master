# Field-Ops rejected-support charge policy

Original qagame consumes the artillery/airstrike support cost before validating
availability and line of sight.  `g_fieldOps` bit 2 restores the complete cost
when the support call is rejected; bit 4 restores half; the default zero keeps
the complete cost consumed.

The reconstructed server uses the typed `playerState_t::classWeaponTime`, team
Lieutenant charge time and Signals skill.  A shared helper is used for rejected
smoke-marker airstrikes and direct artillery calls, including capacity,
spectator, no-impact and blocked-sky paths.  Refunds are clamped to the normal
fully-charged lower bound so repeated rejection cannot create excess charge.
