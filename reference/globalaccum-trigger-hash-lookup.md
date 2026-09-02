# Global accum trigger_if_equal cached lookup

The original global trigger branch reads the global accumulator and returns
without dispatch when unequal (ELF 0xb28a6..0xb28c6). On equality it parses the
recipient name and trigger identifier, hashes the name once (0xb2931), iterates
nitrox_FindByScriptNameHash (0xb2960), and dispatches G_Script_ScriptEvent
(0xb2982). A changed caller scriptId is remembered (0xb2998) without interrupting
remaining recipients; the final result is false in that case.

G_ScriptAction_GlobalAccum now uses the typed cached search for this branch.
Other globalaccum commands, parser errors and the no-match diagnostic are
unchanged and not newly certified. No protocol or cgame/ui change is needed.

The shared full-source fixture runs sixteen global and sixteen local scenarios:
equal/unequal values, caller included/excluded, completing/yielding caller action,
and live/unused first external recipient. Actual script dispatch observes ordered
recipients, including those after a yielding caller. A string-only match with a
wrong hash is excluded. Local and global accumulators have distinct values and
are checked unchanged, preventing accidental cross-storage use. Original call
instructions and the scriptId comparison are pinned against the hashed ELF.

This establishes the lookup branch only, not full globalaccum, original runtime
replay, Linux-i386 ABI or browser gameplay parity.
