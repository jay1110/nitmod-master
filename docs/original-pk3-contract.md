# Mandatory recovery constraint

User decision: the entire pak directory is read-only for porting work. Do not
modify human_base.script, menus, headers, or any other asset in that directory.
Do not generate asset overrides or modified PK3s as a compatibility workaround.
Preserve pre-existing worktree modifications; a dirty asset is not permission
to reset or edit it.

The 153-file local byte baseline after the user restored menudef.h is recorded
in reference/pak-readonly.sha256. The nitmod_pak_readonly CTest rejects additions,
removals and content changes without writing assets. This records the accepted
local state, not independent proof that every file came from a published PK3.
Never refresh the baseline to conceal porting edits. Any user-authorized asset
baseline change must be explicit and reviewed separately from source recovery.

The WASM client must load the original nitmod.pk3 downloaded from existing
Nitmod dedicated servers. Requiring a reconstructed qagame or new capability
handshake on those servers does not meet this goal. Native reconstruction can
continue, but original-server compatibility must be independently established.

Next required evidence: exact original weapon IDs and item/animation mappings,
snapshot/playerState interpretation, original message framing and menu parser
semantics. Unknown weapon names must not be silently skipped or mapped to an
unrelated existing weapon. Native/WASM build success is not an original-server
join or gameplay test.
