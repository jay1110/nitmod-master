# Conditional menu visibility

Original UI ELF32 `Script_ConditionalHideShow`, VA 0x30510, size 0xf4,
matches the reference in `ui/sorted/ui_ui_misc.c`. It parses one target
name/group and reads the invoking item's Cvar through the display context.
The floating-point zero branch hides the target; nonzero shows it. It does
not read the target's Cvar or toggle the existing visibility.

Evidence: original instructions 0x30572 and 0x30581 read item+0x114 and call
DC+0x74 (Cvar/value callback); 0x305d8..0x305ff call Menu_ShowItemByName with
false. The nonzero branch iterates matching menu items and sets flag 4
(WINDOW_VISIBLE). The native typed equivalent uses item->cvar, item->parent,
DC->getCVarValue and the existing Menu_ShowItemByName helper.

Registered `condhideshow` in shared ui_shared.c so both ui and cgame can
execute the action. The unmodified original playonline.menu invokes it twice
after UpdateFilter to show/hide the NxAC icon and selector based on the Mod
filter's ui_browserNitmodonly value. This action alone does not implement
Nitmod/NxAC server-list filtering.

Defensive deviation: missing invoking item, parent or Cvar is a no-op rather
than dereferencing an invalid pointer. Existing hide behavior, including
cinematic cleanup, is retained. No menu/PK3/pak content is modified.

Full UI fixture tests exercise Item_RunScript dispatch with both original
target names, negative/zero/positive conditions, group matching, unrelated
items, missing targets, missing Cvar/argument, sequential commands and
cinematic cleanup. Existing bitflag parser/click tests remain in place.

Verification: native Debug build and final CTest run pass (88/88). Emscripten
build and fresh Node individual/concurrent module load and entrypoint probes
pass. Pak read-only and whitespace guards pass. Actual browser rendering and
server-list behavior have not been verified end-to-end.
