# Atomic UI game-type catalogs

The existing `GameType_Parse` production path consumed the original Nitmod
four-field records but incremented counts after writing into the live arrays.
An entry beyond MAX_GAMETYPES wrote outside the catalog. Parse errors also left
partially replaced state. This change stages both the normal four-field format
and the existing two-field join format, committing only on the outer closing
brace. The production gameinfo loader continues to use the normal format.

IDs are nonnegative decimal integers up to INT_MAX, need not be contiguous,
and may not repeat. Extra records, invalid numeric tokens and missing closing
braces reject the catalog and preserve its previous records and count.
These are deliberate validation improvements, not exact malformed-input parity.
Strings still use the existing UI string pool; failed parsing can consume pool
space. This change does not implement transactional pool allocation.

The full linked UI test covers both formats at sizes zero through capacity+1,
invalid numbers, duplicate IDs, missing braces, stray tokens and unchanged live
state on rejection. A mandatory read-only test loads the actual `pak/gameinfo.txt`
and checks its nine original modes. No assets are edited. This is UI parser
integration/hardening, not implementation of TDM/DM gameplay in qagame or new
cgame features. Browser gameplay validation remains outstanding.
