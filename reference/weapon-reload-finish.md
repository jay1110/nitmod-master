# Reload completion and idle animation

Current integration: this helper now runs in the shared production movement
path; activation, tests and remaining limits are documented in
[active reload completion](active-reload-completion.md).

NITMOD_FinishWeaponReload composes the existing atomic clip transfer with
the native READY transition and the idle-animation effect. It requires native
WEAPON_RELOADING and expired weaponTime/weaponDelay. Invalid input or transfer
failure leaves state unchanged; unfinished timers/wrong state return pending.
Successful completion returns 1 even if the animation is suppressed.

Original qagame PM_Weapon calls PM_ReloadClip at 0x2bbdf, stores ready (0)
at 0x2bbec, then selects idle animation using bitmask 0x98601 over weapon
IDs 27..46 (0x2bc00..0x2bc14). Client equivalents are 0x1b0be, 0x1b0cb
and 0x1b0df..0x1b0f3. The six IDLE2 identities are original 27,36,37,42,43,46:
satchel detonator, GPG40, M7, deployed mortar, adrenaline, deployed MG42.
All other supported identities use IDLE1, matching native PM_IdleAnimForWeapon.

PM_StartWeaponAnim's gates also match native ET: pm_type below PM_DEAD,
pmext->weapAnimTimer <= 0, command weapon != WP_NONE. On success the previous
ANIM_TOGGLEBIT is inverted and the idle animation replaces the other bits.
No command-weapon equality test is invented; the original only tests nonzero.
The typed adapter changes neither pmove context nor extended player state.

3168 completion cases cover 44 identities, six movement types, three animation
timer values, present/absent command weapon and both toggle phases. Expected
inventory uses the separately exhaustively tested transfer helper; state and
animation expectations are checked independently. Repeated completion is a
no-op. Additional checks cover both pending timers, failed transfer and null
inputs. Entire player state, pmove context and pmoveExt are compared.

There is no completion event in this original branch. EV_FILL_CLIP belongs
to reload START, not finish. Its partial start integration is documented in
active-reload-start.md. The completion adapter is now invoked by active
PM_Weapon; outer gameplay/death checks remain the caller's job. Testing
the animation gate for dead/frozen movement types does not claim that live
gameplay should initiate or continue a reload in those states.
