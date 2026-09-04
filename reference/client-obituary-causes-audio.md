# Death-cause adapter, special kill text and audio

Original qagame modNames is a 280-byte table at ELF VA 0x2a7bc0:
69 causes followed by MOD_NUM_MODS. Its order differs from native ET 2.60,
starting with removed MOD_ROCKET before wire knife=5. CG_Obituary now
translates its local cause, without mutating the entity's original payload.
All same-named native causes are mapped; FG42_SCOPE aliases FG42SCOPE.
Private causes without a native equivalent map to MOD_UNKNOWN, not an
unrelated death. Invalid inputs also map to UNKNOWN. Native protocol does
not call the translator. Original switch-team=57 now reaches the intended
no-obituary branch instead of being treated as a mortar death.

Eight private attacker/victim text pairs are recovered from cgame
Obituaries_killedby at ELF 0x134940: goomba, poison, fear, shove, thrown
knife, bomb, poison gas and poison gas mine. Their native fallback wording
is replaced after cause dispatch. Full original weapon-custom obituary
strings and private self/world-death wording remain outstanding.

cg_obituary defaults to 1: text popup. Mode 2 uses team-chat storage plus
console output; 0 (and other non-popup values) uses console only. Mode 3/4
graphic rendering was subsequently added for mapped two-player weapon
kills (see client-graphic-obituaries.md); unsupported causes/media retain
a text fallback. Native text popup behavior stays unchanged. Chat uses the
original event clientNum, not an invented speaker identity.

cg_goatSound defaults to 3: bit 1 enables knife and bit 2 thrown-knife
sounds. Only a local attacker/victim hears these; the original submits the
same sample for target then attacker on channel 2 at the listener origin.
Goomba uses sound/player/gib.wav on channel 0 at the listener origin.
cg_tkSounds defaults to 1; same-team player kills use sound/nit/tk.wav,
excluding gametype 8, syringe, switch-team and null obituary pairs.
These hooks run after single-player death branches, in the valid attacker
path. Samples are cached and cleared on config reset. Invalid clients,
self-kills and nonpositive registered handles are not submitted.

Evidence: sorted/cgame_events.c:906–1050; media registration in
cgame_client.c:13300,13415,13520. Binary tables were inspected directly.
The independent test_original_death_causes.py reads all 69 original
modNames pointers and compares the active C mapping to the native enum.
Engine-double tests check 1,056 audio combinations, sample order, channel,
entity, volume and origin, plus representative and invalid cause mappings.

Remaining: full private graphic icon coverage, original text/style parity,
weapon-config overrides, private world/self messages and live server/audio
comparison. No qagame emissions, pak/PK3/menu edits or original binary edits.
