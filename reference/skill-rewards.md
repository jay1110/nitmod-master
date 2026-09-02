# Original skill reward text evidence

Artifact: cgame.mp.i386.so, SHA-256
`45db79d57b58d3a530c6fc7abbc39613accdb8d1804a2e3cb15324cee5fece7f`.
ELF symbol `cg_skillRewards`: virtual address `0x00138a00`, size `0x8c`
(35 i386 pointers). The decompiled CG_NewClientInfo uses a five-pointer
row stride. `tools/extract_skill_rewards.py` maps the pointers into this
hash-pinned ELF and reads their NUL-terminated strings without executing it.

The recovered production table is `cgame/cg_nitmod_skill_rewards.c`.
`nitmod_skill_rewards_reference` compares all 35 strings returned by its
compiled accessor against the original ELF; the executable also checks
invalid row/level bounds. No engine or rendering behavior is tested here.

| Skill | Level-five text (verbatim) |
| --- | --- |
| Battle sense | Improved lungs capacity |
| Engineering | Bombs |
| First aid | Improved Health Care |
| Signals | Faster stamina recharge & Improved ammopacks |
| Light weapons | Throwing knives |
| Heavy weapons | Mid Clip Reload |
| Covert ops | Reload in scoped view |

Text is evidence of the message, not an implementation specification for
the ability. The native four-level promotion table remains active. The new
table is linked into cgame but not called by promotion popups until those
abilities and six-level progression are reconstructed together.
