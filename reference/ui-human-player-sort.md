# Original human-player browser sorting

Original UI_ServersSort selects UI_ServersQsortCompare_bis for column 2. That
comparator reads the per-server human population and reverses its comparison
for descending order. UI_BuildServerDisplayList populates that array from
status `humans`, otherwise master `humans` when version contains `ET Legacy`,
otherwise the count of status player records with positive ping. The recovered
status branch is around labels 0x245f7..0x247b2 in ui_ui_misc.c.

The active port now uses that precedence and a shared comparator for binary
insertion and explicit qsort. Selecting the population column refreshes the
list so status-derived counts are obtained before insertion. Existing NxAC
status requests also populate this cache; no URL/menu actions are dispatched
by population parsing. Ordinary browser columns keep their engine comparator.

Status queries are asynchronous, shared with the existing NxAC query path.
Sort-only pending replies do not contribute repeatedly to player totals. After
five seconds they release the status slot and use bounded master `clients`
for that refresh. This timeout/fallback differs from the original randomized
retry and suspicious-server rejection policy; neither exact timing nor the
original server-rejection heuristics is claimed. Counts are clamped to 0..64.
The existing NxAC filter continues waiting for its authoritative status reply.

Full UI tests cover explicit humans, Legacy fallback, positive/zero/negative
ping rows, count bounds, eight-server ascending and descending population order,
pending-to-ready transitions and timeout fallback. All 97 host tests pass.
Live master-server/browser verification remains pending. No pak changes or
engine syscall/protocol extensions are required.
