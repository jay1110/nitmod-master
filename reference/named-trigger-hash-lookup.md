# Named script trigger lookup

Only the ordinary named-recipient branch of G_ScriptAction_Trigger changes.
The original hashes the name once (ELF 0xb0cbd), calls the cached search
(0xb0cec), and skips entities with svFlags bit 8 (0xb0cf9). Native SVF_BOT is
also bit 8. Skipped bots still count as found; the original does not call
Bot_ScriptEvent here. Non-bots receive G_Script_ScriptEvent (0xb0d1b), and a
changed caller scriptId is remembered without stopping later recipients.

The typed implementation uses G_NITMOD_FindByScriptNameHash and removes the
native bot-dispatch fallback in this branch only. Special self/global/player/
activator branches are unchanged; in particular their bot semantics are not
claimed as ported. There are no protocol or client/UI changes.

Thirty-two full-source scenarios combine caller membership, completing/yielding
actions, an unused external recipient, and independent caller/external bot flags.
Real script dispatch checks ordered recipients and deferred caller termination;
the entity with matching text but a wrong cache is excluded. All-bot matches
return true without script callbacks or an unknown-name diagnostic. Original
hash/search/flag/event/scriptId instructions are pinned against the SHA-checked
reference ELF. No-match and malformed-input diagnostics are not newly tested.

Evidence is limited to this branch and deterministic host fixtures, not complete
script behavior, loaded Omni-bot support, original replay or browser gameplay.
