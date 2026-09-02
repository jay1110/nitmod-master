# Original NCS receive and consumers

Original CG_ServerCommand accepts ncs without a capability handshake.
nitrox_ProcessNewCS uses models 0..255, sounds 256..511, shaders 512..543,
shaderstate 544, skins 545..608, objectives 609..626, spawns 627..642 and
fireteams 643..654. The typed store and those ranges already existed, but
reception was gated and several triggered parsers still read engine
configstrings. This batch connects the original receive path and consumers.

NITMOD_AssetConfigString translates specific native consumer indices into
the NCS store only for original Nitmod serverinfo. It does not globally
change CG_ConfigString, engine ABI indices or raw gamestate storage.
Stock and reconstructed serverinfo retain existing native reads. Initial
model/sound/shader/skin loading and event sound-name lookups use the helper;
later NCS updates continue to register the corresponding assets.

Original OID keys b/r replace native cia/cix for team shader references.
Both formats now reject out-of-range shader references. Original spawn
count uses CS_MULTI_INFO key n; labels use NCS key s, not spawn_targ.
Original fireteam ID uses n, not id. The unnamed decompiler global
0x10d2e7 maps to ELF 0xfd2e7, the final 'n' of the BGn string. Empty fireteam
slots and non-16-character membership masks are rejected before the parser
reads either eight-character half. Spawn count is bounded before writing.

Tests drive actual ncs commands at the edges of all four asset ranges,
verify registration handles and store-to-consumer mapping, parse an OID
with an invalid shader reference, create/remove a fireteam, and process an
original-key spawn target. They reject index 655 and verify no capabilities
are implicitly granted. These tests use a synthetic engine callback, not
the deployed server. Exact full resync ordering, other engine configstring
ranges, event IDs and original snapshot layouts remain incomplete. This
change does not certify that prior allocator or indirect-call crashes are
fixed. No original PK3/asset was edited.
