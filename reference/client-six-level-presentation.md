# Six-level original client presentation

Original CG_NewClientInfo accepts seven skill digits; the original reward
table has five upgrade texts per skill, and CG_Debriefing_PlayerSkills_Draw
draws five stars (sorted cgame_ui.c, Ghidra 0x48a29 entry region).

Previously one level-five digit caused the native max-four parser to reject
the whole vector. Original-server skill reception now preserves 0..5 in a
separate clientInfo nitmodSkillLevels array. Existing ET consumers receive
min(level,4), so baseline abilities and array indices stay within the native
range. This is an explicit compatibility projection, NOT implementation of
Nitmod level-five gameplay or its configurable per-ability unlock masks.
Native ET input still rejects level five. Invalid vectors leave both outputs
unchanged; freshly initialized clientinfo therefore remains neutral.

Promotion detection and messages use the original display levels and the
hash-pinned Nitmod reward table. A 4->5 change does not repeat the native
level-four secondary-weapon selection side effects. Debriefing displays five
80%-size stars, spaced width-4, matching the original draw routine; native
servers keep four stars. No engine playerState, weapon enum, server protocol,
or pak files change. Other skill display consumers remain to migrate.

Tests enumerate all 279936 original seven-skill combinations and verify
projection, native isolation, malformed/short/excess input and atomic failure.
Existing reward-string binary-reference tests remain. Actual promotions and
star rendering still require original-server/browser comparison.
