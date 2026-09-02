# Engine syscall numbering audit

Executed against the local ET:Legacy source on 2026-09-02:

```powershell
python -B tools/audit_engine_syscall_numbers.py C:/Users/micha/Documents/GitHub/etlegacy
```

The JSON report records SHA-256 for all seven inspected headers and every
ET 2.60 import name with its corresponding engine enum value and classification.
The parser accepts sequential values, literal decimal/hex values and resolved
symbol constants. It rejects unknown expressions, directives inside an enum,
duplicates and unresolved names instead of guessing C preprocessor behavior.
COM_TRAP_GETVALUE is read from the inspected engine q_shared.h, not hard-coded.

| Module | Same name and number | Different number | Name absent from engine enum |
| --- | --- | --- | --- |
| qagame | 65 | 0 | 147 |
| cgame | 147 | 0 | 0 |
| ui | 121 | 0 | 0 |

The qagame gap includes G_BOT_FREE_CLIENT (37), BOTLIB_PC_ADD_GLOBAL_DEFINE
(204), BOTLIB_START_FRAME (205) and many older AAS/AI bot interfaces. It is
not evidence of shifted common syscall numbers. Missing names must be checked
against the compiled engine dispatcher and actual reachable module paths;
this header-only audit does neither. Conversely, same-number results do not
establish argument counts, struct layouts, side effects or functional support.
The Legacy game header explicitly documents several retained Botlib entries
as compatibility dummies, reinforcing that equal numbering is not behavior.

No syscall numbers were changed and no Legacy files were modified. Blindly
renumbering or substituting the legacy Botlib commands would be unjustified.
Next checks are reachable bot call paths and structure/signature compatibility
for initialization/render/snapshot calls. This is not a browser test or an
original-module parity comparison.

Four regression tests cover numeric assignments/comments/aliases, unsupported
syntax and directives, missing/duplicate enum definitions and classification.
