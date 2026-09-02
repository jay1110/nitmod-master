# First script-name hash consumer

target_script_trigger_use (original ELF 0xd8130) now uses the typed cached
script-name search instead of native G_Find's string comparison. aiName is
hashed and the first live cached match below level.num_entities is selected.
A matching string with a stale/nonmatching cache is not a match; a matching
cache is sufficient even if the current scriptName string differs.

The existing self-script fallback remains when no external match exists and
the entity has a scriptName pointer. Script trigger is delivered before the
unconditional G_UseTargets call, which still receives the original second
argument (other), not the otherwise unused activator parameter.

Ten full-source scenarios execute real G_Script_ScriptEvent/ScriptRun and
G_UseTargets, with an observing script action and observing target use callback.
They cover absent aiName, cache miss despite matching string, cache hit despite
different string, first of duplicate hits, unused first hit, and self-script
present/absent. Callbacks verify one recipient and script-before-target order.
Original calls and field access are pinned against the SHA-checked ELF.

No other string-based lookup is replaced. G_ModifyTOI remains deferred: its
Objective configstring/shader updates require separately verified server/client
protocol mapping. Actual engine map/runtime parity remains unverified.

Verification: native Windows-host build, 83/83 CTests, original instruction,
protocol/inventory checks and real Emscripten builds of all three modules pass.
Linux-i386 ABI and loaded engine/browser gameplay remain unverified.
