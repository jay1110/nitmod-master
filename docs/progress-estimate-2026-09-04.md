# Approximate recovery progress, 2026-09-04

These are low-confidence engineering estimates of functional reconstruction
relative to original Nitmod, including the reused ET baseline, NOT measured
function coverage, binary parity, or release readiness.

| Module | Approximate functional range | Main uncertainty |
| --- | --- | --- |
| UI | 50–65% | Full original menu/script behavior, layout and browser interaction parity |
| cgame | 35–50% | Complete weapon/prediction/protocol behavior, HUD parity and live-server regressions |
| qagame | 15–30% | Complete gameplay integration, admin/database/Lua/Omni-bot/integrity subsystems |

The function inventory is incomplete as a progress metric: cgame has 18
ported, 26 partial, 1 deferred and 1742 untriaged entries; qagame 11 ported,
75 partial, 13 deferred and 3879 untriaged; UI 17 partial and 773 untriaged.
Recent work is also recorded separately in reference documents, while parts
of docs/porting-status.md retain historical 'not ported' statements. Thus
neither raw inventory ratios nor passing builds establish completion.

The current suite contains 97 passing tests after recent batches; it is not
97% completion. Windows host tests and Emscripten module loading are distinct
from Linux-i386 release validation and browser/dedicated-server end-to-end
parity. No overall final-release completion percentage is established.
