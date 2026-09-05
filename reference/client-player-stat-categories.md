# Player statistics category port

Original CG_parseWeaponStatsGS_cmd and CG_parseWeaponStats_cmd iterate
26 bits of the weapon mask, reading five counters per selected category.
Their aWeaponInfo table is the verified original cgame ELF table at
0x12b0e0. Headshot columns are enabled for categories 0..8 and 18..20;
this intentionally retains even the original knife/panzer/flamethrower flags.

The common tuple validator, cached gameStats_t rows and text/window output
now use the protocol-dependent category count and shared names/headshot
metadata. ET stays at 22 categories. Invalid mask bits still reject the
whole tuple before mutation. No shared gameplay stats enum was expanded.

Tests exercise every category independently under both protocols through
both actual parsers, checking names, headshot-column presence, cache rows,
and transactional rejection of the first unsupported bit. This ports the
weapon section only; original skill/rank presentation and live browser
parity are not asserted. Pak assets and original binaries remain unchanged.
