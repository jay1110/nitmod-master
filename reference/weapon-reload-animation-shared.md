# Shared reload animation selector

`NITMOD_ReloadAnimation` centralizes the selection previously duplicated
between native `PM_ReloadAnimForWeapon` and recovered feedback handling.
Rifle-grenade launchers select RELOAD2, deployed MG42 selects RELOAD3,
and the eight reviewed light weapons select RELOAD2 when fast reload is
enabled. All other identities retain RELOAD1. The helper is pure and has
no engine-service dependencies.

Native Pmove still resolves eligibility from its existing light-weapon
skill level. Recovered feedback still resolves the explicit ability bit.
The two inputs are not equated or synchronized by this extraction.
Mortar suppression, current-versus-target weapon selection, animation
timers, command-weapon/death gates and toggle-bit handling stay unchanged
in their callers. No gameplay rule or protocol field is added.

The previously inspected original begin branches select these animations
at qagame 0x28900 and following / cgame 0x17df0 and following; exact ability
integration remains pending. Existing feedback tests exercise animation
gates. New tests add 468 selector/native-wrapper cases across native and
adjacent invalid IDs, five skill levels and four explicit enable values.
Player-state immutability is checked for the native wrapper.

The first full build exposed an unnecessary engine-symbol dependency in an
isolated recoil test; the pure explicit identity switch removes it. The
subsequent complete host Debug build and all 66 CTests pass. This is shared
code integration, not original-ELF or Linux-i386/WASM release verification.
