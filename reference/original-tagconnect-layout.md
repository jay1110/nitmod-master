# Original-server TAGCONNECT layout

The supplied original cgame CG_ParseTagConnects loops from 0x309 (777) to
0x349 (841 exclusive). ET 2.60 CS_TAGCONNECTS is 829 with 64 slots, so the old
client scanned 829..892 and interpreted unrelated original-server data after
840 as tag attachment tuples. This is a demonstrated source/layout mismatch;
the specific remote server gamestate from the reported error was not captured.

NITMOD_TagConnectBase selects 777 for serverinfo gamename=nitmod unless the
reconstructed server advertises nitmod_csLayout=et260. Other gamenames retain
the native layout. This uses no new handshake on original servers and grants
no feature bits. The reconstructed qagame registers the explicit layout marker
as read-only serverinfo so its nitmod gamename is not confused with the original
layout. Update local reconstructed qagame alongside cgame; older reconstructed
nitmod builds without the marker are not distinguishable using this rule.

Startup scanning uses the selected range. Original-layout incremental updates
are routed before native overlapping objective/dlight handlers. The native
TAGCONNECT branch is disabled for original layout, so indices 841..892 cannot
reach that parser solely because of their ET baseline positions. The tag tuple
parser itself and its error checks are unchanged; malformed real tag data still
fails instead of being silently skipped.

Full-source cgame tests cover stock ET, original nitmod and explicitly marked
reconstructed nitmod, both range endpoints, unrelated decoy data and sequenced
cs updates through the real dispatcher. Original slot 841 is also tested as
non-TAGCONNECT. No PK3 files are changed or required on existing servers.

This repairs TAGCONNECT selection only, not all original configstring ranges.
Models, characters, players, objectives, fireteams and other original/native
range differences still need coordinated reconstruction. Successful unit tests
and WASM builds are not a verified remote join or rendering test.
