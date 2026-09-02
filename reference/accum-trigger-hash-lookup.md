# Local accum trigger_if_equal hash lookup

Only the local G_ScriptAction_Accum trigger_if_equal branch is changed. The
original hashes the requested script name once (0xb2335), iterates cached
matches (0xb235c), and sends each a trigger (0xb237e). It does not stop the
iteration when the caller's scriptId changes. That condition is remembered
and causes qfalse after all matches; otherwise the native return behavior is
retained. Other accum commands and globalaccum are not modified.

Sixteen full-source scenarios cover equal/unequal accumulator values, caller
included/excluded, caller action completing/yielding, and first external match
live/unused. Real script dispatch/run invokes an observing action. Yielding on
the caller preserves its new scriptId, and subsequent recipients must still
execute in ascending slot order. A string-only match has a deliberately wrong
cache and must never receive the event. The accumulator remains unchanged.

Reference checks pin original hash/search/event calls and scriptId comparison.
The existing no-match diagnostic and malformed-input handling are unchanged and
not newly runtime-tested. Complete accum command parity and real engine/browser
script execution remain unverified.

Verification: native Windows-host build, 83/83 CTests, original instruction,
protocol/inventory checks and real Emscripten builds of all three modules pass.
Linux-i386 ABI and loaded engine/browser gameplay remain unverified.
