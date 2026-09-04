# Limbo state access guards

Defensive corrections to typed cgame, not a new recovered gameplay feature:

- GetTeam bounds the three-entry teamOrder lookup and returns spectator for
  invalid indices without changing the stored selection.
- GetClass returns the same Soldier fallback used by BG_GetPlayerClassInfo,
  so GetCharacter no longer indexes character arrays with an unchecked class.
- GetRealTeam and secondary-count calculation guard the local client index.
- WeaponCount_ForSlot rejects unsupported slots.
- Team/class button handlers reject null or invalid button data before sound,
  requests or selection changes; the team-button renderer rejects before draw.

Keeping fallback access non-mutating is important: SendSetupMsg still checks
the raw selection and rejects malformed state instead of submitting a silently
rewritten choice. Existing valid team/class and weapon behavior is preserved.
This does not comprehensively validate every limbo panel or entity state.

Full-cgame tests exercise negative, maximum-int and capacity-boundary indices,
null buttons, invalid slots and unchanged stored selection. Unexpected engine
callbacks in these rejection paths fail the fixture. Existing all-team/class
selection tests cover the valid paths. No protocol fields, pak assets or
original binaries change. Browser interaction remains separately unverified.
