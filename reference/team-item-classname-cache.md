# Team-item cache writes

The two original team-item cache writes are now mapped to native gitem_t
semantics by G_NITMOD_SetTeamItemClassnameHash. Only IT_TEAM with PW_REDFLAG
or PW_BLUEFLAG writes 0x3317f or 0x36af1 respectively. Other items leave the
existing cache untouched, including stale/nonzero values. The helper does
not classify by the entity's current classname.

Mapping evidence: original bg_itemlist records at 0x2a68f0 and 0x2a6928 name
team_CTF_redflag / team_CTF_blueflag. Their original type/tag tuples are
(5,5) and (5,6); ET 2.60 uses different enum values, so these raw numbers are
not copied into production comparisons. SHA-pinned tests check pointers,
strings, tuples and actual cache-writing instructions.

Runtime hooks:

- G_CallSpawn: immediately after matching the item, before LMS rejection,
  item initialization and script spawn callbacks (original 0xccb1a onward).
- LaunchItem: immediately after assigning classname, before trace/link and
  dropped-flag callbacks (original 0x7284d, stores 0x72c06/0x72c1d).
- Native Drop_Item delegates to LaunchItem, so it reaches the same hook.
  Original Drop_Item inlines this portion; no duplicate native write is needed.

Tests sweep all native item types, tags -1 through PW_NUM_POWERUPS and three
existing cache values, comparing the entire entity. Null inputs are guarded.
Real G_CallSpawn is exercised for both original-named flags under LMS, proving
the cache is written even when spawn returns false. Flag classname hashes are
also checked. LaunchItem hook ordering has a source regression, not a full
drop/trace/script runtime scenario. Other LaunchItem behavior is unchanged.

Map-spawn's later general refresh still applies. Script SetValues classname
refresh/respawn has since been connected (script-classname-cache.md); this
change does not claim complete dynamic
entity lifecycle or loaded Omni-bot compatibility.

Verification: native Windows-host build, 83/83 CTests, protocol/inventory
checks and real Emscripten builds of all three modules pass. Linux-i386 ABI
and full engine/browser gameplay remain unverified.
