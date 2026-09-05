# Dynamite timer runtime

Original qagame reads `n_dynamiteTimer` while an engineer arms dynamite and
clamps it to 5000..60000 milliseconds. The value becomes both the entity's
explosion deadline and its network-visible timer duration.

The reconstructed qagame now uses one typed accessor for that policy, publishes
the same value in the simple client snapshot and formats the arming message
from it. This keeps authoritative explosion time, cgame countdown and displayed
seconds synchronized.
