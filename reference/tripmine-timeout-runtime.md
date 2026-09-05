# Tripmine owner cleanup

Original `nitrox_RemoveTripmines` frees every tracked tripmine whose parent is
the departing player. Its callers are gated by `n_tripmineTimeout` during
disconnect and team changes.

The reconstruction scans typed live entities instead of recreating the private
pointer array. It matches `WP_TRIPMINE` and the owner pointer, clears ownership,
then frees each match. Poison mines and landmines retain separate policies.
