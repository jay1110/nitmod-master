# Player-search selection contract

The player-search list reserves its last row for progress/result text;
UI_SearchProgress clears that row's address. Join and status actions now
share a bounded selection/address helper and explicitly exclude this row,
even if stale address data remains. Invalid selections leave the status
address and connection cvars untouched and initiate no request.

Tests cover every row around the list boundaries with negative, empty,
summary-only, ordinary, full and excessive counts. The actual status menu
action is exercised for every invalid case. The join fixture now models
one server plus its summary row, rather than an impossible one-row result.
This corrects UI integration; no menu assets or protocol fields change.
