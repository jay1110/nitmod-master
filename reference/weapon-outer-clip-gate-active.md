# Active outer-only full-magazine gating for reviewed light weapons

The complete original begin bodies at qagame `0x28730..0x28a4f` and
cgame `0x17c40..0x17f5f` have no full-magazine veto. Ordinary requests
already check capacity in PM_CheckForReload; direct begin and the
raise-to-reload handoff are distinct entry paths.

`NITMOD_ReloadUsesOuterClipGate` now explicitly lists twelve reviewed
identities: Luger/Colt and their silenced variants, MP40, Thompson, Sten,
unscoped FG42 and the four akimbo variants. The active begin path retains
its legacy full-magazine guard for every other identity. This extends the
previous akimbo migration; it does not activate definition-dependent
midclip rules, ability words or a complete recovered reload dispatcher.

216 new actual begin/outer-request cases cover the twelve identities,
READY/FIRING/FIRINGALT, partial/full/overfull clips and both entry paths.
Direct begin starts without moving inventory; outer full/overfull requests
remain bytewise unchanged. Existing firing-state and scoped-return tests
now account for the direct FG42 handoff with a full magazine. Garand and
K43 retain their previous restrictions. Unsupported predicate inputs reject.

This can permit a redundant reload after a previously accepted FG42 scoped
request reaches the raise-to-reload handoff with a now-full magazine, as
allowed by the original begin structure. It does not make an ordinary
full-magazine key request start reload.

Complete host Debug build and 66/66 tests pass. Original-ELF gameplay
replay, full definition/ability binding and Linux-i386/WASM release validation
remain pending.

## Expanded completion verification

The original 216-case matrix is now expanded to 7776 scenarios by varying
the akimbo side clip independently, reserve 1/9/100 and all four native
first-person animation gates. Of these, 5472 start reload and execute the
actual transition stage through completion; 2304 outer full-magazine
requests remain rejected. Counts include repeated side-clip fixtures for
single weapons, whose behavior must be independent of that test parameter.

Started reloads first pass a positive-timer no-mutation check. Tests then
explicitly expire the timer and compare the full completed state with an
independent main-first transfer oracle. Overfull clips return excess to
reserve, including asymmetric akimbo combinations; total reserve-plus-clip
ammunition must remain unchanged. Animation suppression must not suppress
transfer. Completion emits no second event, and the entire pmove extension
is preserved. These are native integration tests, not full scheduler or
original-ELF execution. No production behavior changed in this test expansion.

Complete host Debug build and 66/66 tests pass.
