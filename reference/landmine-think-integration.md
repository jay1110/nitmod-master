# Full-source initial mine think integration

The existing full-qagame executable now calls real G_LandmineThink in 16
profiles: ordinary human, teammate excluded, owner excluded, owner with pliers,
own-team bot excluded, spotted-enemy bot excluded, bot override, and precise
geometry boundary exclusion. Each runs with one candidate and with a second,
eligible human candidate. The latter ensures that rejected entries do not
prematurely terminate the search. There are 11 triggered and 5 untriggered cases.

The engine double checks exactly one radius-box query with bounds (-64,-64,-64)
to (64,64,64) and capacity MAX_GENTITIES, returning controlled entity numbers.
The actual team/owner and bot policies, mine-team/spotted accessors, geometric
test and LandMineTrigger execute. Full entity comparisons check the 100ms think
deadline, density expiry, trigger callback, team increment, timestamp and latch.
At the link boundary the trigger metadata must not yet be written. Excluded
profiles retain the scanning callback and do not link. No engine collision or
Omni-bot runtime is emulated. Native build and all 81 CTests pass; production
sources are unchanged by this integration-test step.

## Why Bot_Event_PreTriggerMine remains unported

Original ELF symbol 0x220700 first calls IsOmnibotLoaded and IsBot. At 0x22074e
it loads a second stack argument, passed to HandleFromEntity at 0x22075d. The
Ghidra one-parameter declaration omits this entity argument. The resulting
four-byte handle is sent as event 0x4b through a function pointer at offset 0x18
of the loaded bot interface (indirect call at 0x220793).

The current native tree has no equivalent loaded Omni-bot interface/handle
codec. ET's historical Botlib interface is not a compatible replacement. No
no-op event or raw native pointer is substituted for the missing four-byte
handle. Reconstruction must first establish handle lifetime/generation and
the versioned Omni-bot interface before wiring this event. This is an open
dependency, not a completed bot-event port. Original module remains unchanged.
