# Accuracy console protocol

The original CG_parseBestShotsStats_cmd and CG_parseTopShotsStats_cmd in
sorted/cgame_client.c use the 26-entry aWeaponInfo table (ELF VA 0x12b0e0).
Best/worst match records use one-based categories; individual-weapon
accuracy responses use zero-based categories. Both layouts remain unchanged.

The four console commands bstats/bstatsb/astats/astatsb now accept all
original categories and use the matching original names/codes. Codes were
read from the hash-pinned original cgame table, including TPMN, PGAS and
PGASMINE. ET uses its original 22-entry table. Percentage multiplication
is widened before division as an intentional overflow safety improvement.

The full cgame fixture calls both presentation parsers in best/worst modes
for every original and ET category and checks the category label/code,
accuracy and client name. Live server/browser parity remains unverified.
No assets, server wire format or shared gameplay statistics arrays change.
