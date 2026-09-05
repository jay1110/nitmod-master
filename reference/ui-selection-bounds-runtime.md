# Active UI selection safety

UI_FeederSelection now rejects invalid catalogue counts and indices before
reading or changing state for servers, player lists, team lists, native
head models and Q3 head models. Head selections also require a nonempty
model name. Server selections require a nonnegative engine server index.

Previously the server branch indexed displayServers without checking the
selection, and the player/team branches saved arbitrary indices. Bounds
checks on counts also prevent a corrupt count from legitimizing an index
outside a fixed-size array. Invalid selections preserve the previous state
and produce no engine calls. This does not implement address-based selection
preservation when an asynchronously rebuilt list changes row ordering.

The active server-preview path now registers levelshots/unknownmap if the
requested map shader cannot be loaded, not only when the mapname is empty.
No asset is changed. Native success-path selection and cvar behavior remain.

The full UI fixture covers five feeder types, four count states, four index
states and two shader outcomes (160 cases), plus a negative engine index.
It checks read/write/registration counts, selection atomicity and actual
preview handles through UI_FeederSelection and the real syscall wrappers.

This is active UI hardening, not a new reconstructed gameplay feature or
proof of original UI parity. cgame and qagame have no behavior changes in
this step. Browser interaction and concurrent server-list refresh still
need end-to-end coverage. No pak, menu or original module files were edited.
