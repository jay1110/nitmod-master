# Skill levels lost through Info_ValueForKey scratch-buffer reuse

Reported live state: original protocol, s=5555555, xp=62 in all seven
categories, but both native and display levels zero. Unlock masks were intact.

CG_NewClientInfo passes Info_ValueForKey(configstring, "s") directly to
NITMOD_DecodeClientSkills. Info_ValueForKey owns two rotating static buffers.
The decoder previously called NITMOD_UsesOriginalProtocol before parsing;
its gamename/csLayout lookups reuse those buffers and overwrite the supplied
skill string. Failed parsing left the zero-initialized clientInfo arrays zero.
Tests using string literals or caller-owned arrays did not exercise this bug.

The decoder now parses exactly seven digits into a private integer array
before any protocol lookups. It then validates the protocol-specific maximum
and commits both output arrays atomically. Original level five is retained
for display; native ability-table levels remain capped at four. Malformed
values and unsupported levels still leave outputs unchanged.

Regression coverage uses actual Info_ValueForKey results, both scratch-buffer
parities and original Nitmod / reconstructed et260 / ETmain server information.
The user's all-five input must produce display=5 and native=4 in all seven
skills. The new regression failed before the fix. Existing exhaustive digit
and rejection tests remain in place. No server XP or unlock values are changed.

An advertised next threshold of zero is separate from this buffer issue;
server-configured thresholds are not replaced by guessed defaults.
Browser verification remains pending. No pak, PK3 or original modules changed.
