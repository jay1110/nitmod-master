# Class-menu and message popup integration

Original CG_ClassMenu_f (ELF 0x00032c00) rejects spectators, clears cgame
event handling and opens the normal/alternate class menu according to
cg_quickMessageAlt. The original command name is classmenu. Its existing
PK3 menus issue class commands for all five classes and soldier/engineer/
covert weapon submenus; these now reach the existing typed class handler.

The paired cgame/UI port adds this command, cursor reset to 639/479, UI
key capture, closure of previous menus and selection of wm_class or
wm_classAlt. Invalid local client indices and missing snapshots are rejected.

ABI adaptation: original Nitmod uses popup 15/16 for class menus and 17
for message mode. Native ET uses 15 for message mode. We retain ET's 15
and append class IDs 16/17 in the shared header. Both rebuilt cgame and
ui must be deployed together. ET:Legacy's CG_INGAME_POPUP implementation
forwards the integer unchanged to UI_SET_ACTIVE_MENU. No engine edits.

Message mode now opens original ingame_messagemode4 for cg_messageType 4,
otherwise ingame_messagemode, matching the original UI branch.

The cgame messageMode4 command is now registered, initializes type 4 and
clears old input before opening UI. messageSend routes that type to ma,
never public say, and retains the existing text/type/player reset and
empty-message handling. Original CG_MessageMode_f and CG_MessageSend_f
in cgame_client.c establish this mapping. This is the client path for
original Nitmod servers; reconstructed qagame adminchat authorization and
delivery are not implemented by this change.

Tests pin dispatch/source wiring and original names; native and WASM builds
are checked separately. Interactive class selection and popup parity have
not yet been tested in a browser. No pak/menu assets are modified.
