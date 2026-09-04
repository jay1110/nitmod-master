#!/usr/bin/env python3
"""Create the versioned function inventory from the sorted Ghidra output.

The resulting CSV is deliberately committed.  It is the triage ledger for
reconstruction work: generated source identity stays reproducible while the
reviewed status and parity evidence are maintained in the checked-in file.
"""
from __future__ import annotations

import argparse
import csv
import pathlib
import re

FUNCTION = re.compile(
    r"^(?:[A-Za-z_][\w\s\*]+\s+)?([A-Za-z_]\w*)\s*\([^;]*\)\s*\{$",
    re.MULTILINE,
)
IGNORED = {"if", "for", "while", "switch"}
FIELDS = ["component", "source_file", "function", "ghidra_address", "target_module", "port_status", "parity_evidence", "notes"]

# Entries below are reviewed ports.  Further annotations are preserved from a
# previous CSV invocation, so regenerating after a decompiler split never
# erases review work.
SEED_ANNOTATIONS = {
    ("cgame", "cgame_client.c", "CG_RailTrail2"): (
        "cgame/cg_nitmod_debug.c", "ported_partial", "sorted-reference/full-cgame-keyed-rail-tests",
        "Color, keyed segment refresh and fade lifetime. See reference/client-keyed-rail-events.md."),
    ("cgame", "cgame_client.c", "CG_FindLocalEntity"): (
        "cgame/cg_localents.c", "ported_partial", "sorted-reference/full-cgame-keyed-rail-tests",
        "Typed group/segment lookup over active list, deliberately excludes freed slots."),
    ("cgame", "cgame_ui.c", "CG_RailTrail"): (
        "cgame/cg_nitmod_debug.c; cgame/cg_event.c", "ported_partial", "sorted-reference/full-cgame-keyed-rail-tests",
        "Original event 50 colored line/box dispatch; native ET behavior retained."),
    ("cgame", "cgame_effects.c", "CG_RailTrail_part_5"): (
        "cgame/cg_nitmod_debug.c", "ported_partial", "sorted-reference/full-cgame-keyed-rail-tests",
        "Twelve stable box segment identities and endpoint construction; live visual parity pending."),
    ("cgame", "cgame_client.c", "CG_BotDebugLine"): (
        "cgame/cg_nitmod_debug.c; cgame/cg_nitmod_events.c", "ported_partial", "original-ELF-0x5efe0/full-cgame-event-render-tests",
        "Original events 104-106: line, RGB basis and oriented box with native fade lifecycle. See reference/client-debug-vector-events.md."),
    ("cgame", "cgame_spawn.c", "SP_corona"): (
        "cgame/cg_nitmod_coronas.c; cgame/cg_spawn.c", "ported_partial", "original-ELF-0xb2d10/full-cgame-spawn-fixture",
        "1024 typed static map coronas with original server-key exclusions and color priority. See reference/client-static-map-coronas.md."),
    ("cgame", "cgame_client.c", "CG_Coronas"): (
        "cgame/cg_nitmod_coronas.c; cgame/cg_view.c", "ported_partial", "original-ELF-0x4a370/96-render-profiles",
        "Active map corona PVS, distance, direction, occlusion and scene submission. See reference/client-static-map-coronas.md."),
    ("cgame", "cgame_ui.c", "CG_Debriefing_InfoRequests"): (
        "cgame/cg_debriefing.c", "ported_partial", "original-ELF-0x39290/1536-request-profiles",
        "Map-list priority followed by player statistics without starvation; optional imhr nonblocking. See reference/client-debrief-page-lifecycle.md."),
    ("cgame", "cgame_ui.c", "CG_Debriefing_NextButton_KeyDown"): (
        "cgame/cg_debriefing.c; cgame/cg_nitmod_mapvote.c", "ported_partial", "original-ELF-0x36670/576-page-transitions",
        "Four views with original TDM/DM vote gates; local native page IDs retained. See reference/client-debrief-page-lifecycle.md."),
    ("ui", "ui_ui_misc.c", "UI_AdjustFrom640"): (
        "ui/ui_atoms.c; ui/ui_shared.c", "ported_partial", "original-ELF-0x10900/full-UI-widescreen-fixture",
        "Original aspect correction for pictures and text, seven viewport profiles. See reference/ui-widescreen-layout.md."),
    ("ui", "ui_ui_misc.c", "AdjustFrom640"): (
        "ui/ui_shared.c", "ported_partial", "original-ELF-0x38670/full-UI-widescreen-fixture",
        "UI model viewport scaling; cgame shared path unchanged. See reference/ui-widescreen-layout.md."),
    ("ui", "ui_ui_menu.c", "Menu_UpdatePosition"): (
        "ui/ui_shared.c", "ported_partial", "original-ELF-0x2ee10/full-UI-widescreen-fixture",
        "Centered menus, clouds and legacy full-background rules; idempotent source rectangles are a documented correction. See reference/ui-widescreen-layout.md."),
    ("ui", "ui_ui_misc.c", "_UI_MouseEvent"): (
        "ui/ui_main.c", "ported_partial", "original-ELF-0x27780/full-UI-widescreen-fixture",
        "Original widened virtual cursor range with overflow-safe deltas. See reference/ui-widescreen-layout.md."),
    ("ui", "ui_ui_draw.c", "UI_DrawMapCinematic"): (
        "ui/ui_main.c", "ported_partial", "original-ELF-0x1e1e0/full-UI-lifecycle-tests",
        "Rewritten cinematic lifecycle with shared validated catalog selection; delayed failure fallback retained. See reference/ui-map-preview.md."),
    ("ui", "ui_ui_draw.c", "UI_DrawMapPreview"): (
        "ui/ui_main.c", "ported_partial", "original-decompile/full-UI-catalog-tests",
        "Existing mapped rendering with bounded selection and campaign references; original off-by-one deliberately fixed. See reference/ui-map-preview.md."),
    ("qagame", "nitmod_weapons.c", "G_AddClassWeapons"): (
        "game/g_client.c", "ported_partial", "original-ELF-0x4ba20/full-qagame-spawn-tests",
        "Active rifle attachment limits and dualSMG grants plus g_medics bit 4 primary suppression. Native skill/ammo policy retained. See reference/active-spawn-equipment.md and reference/active-medic-loadout.md."),
    ("cgame", "cgame_pmove.c", "PM_WeaponUseAmmo"): (
        "game/bg_pmove.c; game/nitmod_weapon_clip.c; game/nitmod_weapon_consumption.c", "ported_partial", "shared-consumption/25344-full-module-cases",
        "Active exact-zero refill with synchronized war/noReload inputs; native ammo defaults retained. See reference/active-weapon-refill.md."),
    ("qagame", "nitmod_pmove.c", "PM_WeaponUseAmmo"): (
        "game/bg_pmove.c; game/nitmod_weapon_clip.c; game/nitmod_weapon_consumption.c", "ported_partial", "original-ELF-0x2aa40/25344-full-module-cases",
        "Shared active consumption and Akimbo hand selection; bit 0 and panzer war only. See reference/active-weapon-refill.md."),
    ("ui", "ui_ui_misc.c", "UI_ServersQsortCompare_bis"): (
        "ui/ui_nitmod_browser.c", "ported_partial", "original-decompile/8-server-human-sort-fixture",
        "Human population sort shared by insertion and qsort. See reference/ui-human-player-sort.md."),
    ("ui", "ui_ui_misc.c", "UI_ServersSort"): (
        "ui/ui_main.c; ui/ui_nitmod_browser.c", "ported_partial", "original-decompile/full-UI-status-fixture",
        "Column 2 selects status-derived human population; bounded async fallback differs from original retry policy. See reference/ui-human-player-sort.md."),
    ("cgame", "cgame_client.c", "CG_CheckAmmo"): (
        "cgame/cg_nitmod_ammo.c", "ported_partial", "original-decompile/full-cgame-warning-matrix",
        "Reserve thresholds and sound transitions; deliberate two-word ownership correction. See reference/client-ammo-warning.md."),
    ("ui", "ui_ui_draw.c", "UI_DrawCampaignDescription"): (
        "ui/ui_nitmod_description.c", "ported_partial", "original-decompile/full-UI-layout-fixture",
        "Shared bounded text renderer and validated catalog selection; malformed-input differences documented in reference/ui-description-layout.md."),
    ("ui", "ui_ui_draw.c", "UI_DrawGametypeDescription"): (
        "ui/ui_nitmod_description.c", "ported_partial", "original-decompile/full-UI-layout-fixture",
        "Original double-star paragraphs and baseline retained; browser screenshot parity pending. See reference/ui-description-layout.md."),
    ("cgame", "cgame_pmove.c", "PM_CheckForReload"): (
        "game/bg_pmove.c; game/nitmod_weapon_reload.c", "ported_partial", "original-ELF-0x19c80/production-request-matrix",
        "Active scoped and unscoped decision with replicated war mode; native auto-reload policy retained. See reference/active-scoped-reload.md."),
    ("qagame", "nitmod_pmove.c", "PM_CheckForReload"): (
        "game/bg_pmove.c; game/nitmod_weapon_reload.c", "ported_partial", "original-ELF-0x2a7a0/production-request-matrix",
        "Shared scoped war=2 reload and normal unscope transaction; original ability masks pending. See reference/active-scoped-reload.md."),
    ("cgame", "cgame_pmove.c", "PM_BeginWeaponReload"): (
        "game/bg_pmove.c; game/nitmod_weapon_reload_feedback.c", "ported_partial", "recovered-helper/production-start-matrix",
        "Active fifteen-identity validated start bundle including three scoped rifles; native Garand policy retained. See reference/active-scoped-reload.md."),
    ("qagame", "nitmod_pmove.c", "PM_BeginWeaponReload"): (
        "game/bg_pmove.c; game/nitmod_weapon_reload_feedback.c", "ported_partial", "recovered-helper/production-start-matrix",
        "Same fifteen-identity validated start as prediction; original dynamic definitions still pending. See reference/active-scoped-reload.md."),
    ("cgame", "cgame_pmove.c", "PM_ReloadClip"): (
        "game/bg_pmove.c; game/nitmod_weapon_reload.c", "ported_partial", "original-ELF-0xa500/full-module-transfer-fixture",
        "Active typed magazine transfer including Akimbo; current native capacities. See reference/active-reload-completion.md."),
    ("qagame", "nitmod_pmove.c", "PM_ReloadClip"): (
        "game/bg_pmove.c; game/nitmod_weapon_reload.c", "ported_partial", "original-ELF-0x12bf0/full-module-transfer-fixture",
        "Same active transfer and atomic validation as cgame; original weapon-definition loading remains pending. See reference/active-reload-completion.md."),
    ("cgame", "cgame_client.c", "CG_Letterbox"): (
        "cgame/cg_nitmod_view.c", "ported_partial", "original-ELF-0xbaec0/144-viewport-cases",
        "Original percentage/even-dimension viewport without native letterbox reduction; widened arithmetic documented. See reference/client-scope-viewport.md."),
    ("ui", "ui_ui_misc.c", "UI_BuildFindPlayerList"): (
        "ui/ui_nitmod_search.c", "ported_partial", "original-ELF-0x19d60/36-search-timelines",
        "Typed request lifecycle; deduplicated player-only matches and isolated status UI updates. Deliberate corrections documented in reference/ui-player-search.md."),
    ("ui", "ui_ui_misc.c", "UI_GetServerStatusInfo"): (
        "ui/ui_nitmod_status.c", "ported_partial", "original-ELF-0x151c0/decoder-and-live-menu-fixtures",
        "Bounded status rows and player storage; request/cancel and URL menu lifecycle tested. Browser transcript pending. See reference/ui-server-status.md."),
    ("cgame", "cgame_ents.c", "CG_DrawPicFullScreen"): (
        "cgame/cg_drawtools.c", "ported_partial", "original-ELF-0x50270/overlay-render-fixtures",
        "Full-screen scale and signed UV flips; six overlay consumers migrated. See reference/client-fullscreen-overlays.md."),
    ("cgame", "cgame_ents.c", "CG_FillRectFullScreen"): (
        "cgame/cg_drawtools.c", "ported_partial", "original-ELF-0x50340/overlay-render-fixtures",
        "Full-screen solid rectangle and renderer color reset; native fallback retained. See reference/client-fullscreen-overlays.md."),
    ("cgame", "cgame_ui.c", "CG_DrawFlashFade"): (
        "cgame/cg_draw.c", "ported_partial", "original-ELF-0x3da00/96-blackout-cases",
        "Original multiview and administrative blindness blackout synchronization. See reference/client-admin-blind.md."),
    ("cgame", "cgame_client.c", "CG_CalcFov"): (
        "cgame/cg_nitmod_view.c", "ported_partial", "original-ELF-0xbbe20/3024-FOV-cases",
        "Original poison/liquid FOV composition; existing zoom and sensitivity extracted and tested. Browser parity pending. See reference/client-poison-view.md."),
    ("cgame", "cgame_client.c", "CG_CalcViewValues"): (
        "cgame/cg_view.c; cgame/cg_nitmod_view.c", "ported_partial", "original-ELF-0xbc2b0/492-poison-lean-cases",
        "Poison camera rotation and g_weapons 256 lean divisor; not the complete original camera function. See reference/client-poison-view.md."),
    ("cgame", "cgame_client.c", "CG_CalculateWeaponPosition"): (
        "cgame/cg_nitmod_weapon_pose.c", "ported_partial", "original-ELF-0xbf590/typed-pose-matrix",
        "Original-protocol visual lean and complete pose extraction; snapshot firing/reload states normalized. Clock-reset deviation documented. See reference/client-weapon-pose.md."),
    ("cgame", "cgame_weapons.c", "CG_WeaponFireRecoil"): (
        "cgame/cg_weapons.c", "ported_partial", "original-ELF-0xcde60/32-seeds-per-weapon",
        "Existing native behavior verified; no new recoil feature. RNG draw count and kick state checked; browser replay pending. See reference/client-weapon-pose.md."),
    ("cgame", "cgame_ui.c", "CG_Debriefing_ParseHitRegions"): (
        "cgame/cg_debriefing.c", "ported_partial", "original-ELF-0x39a00/source-contract",
        "Four typed count/percentage pairs, exact arity and atomic commit. See reference/debrief-intermission-protocol.md."),
    ("qagame", "nitmod_cmds.c", "Cmd_IntermissionHitRegions_f"): (
        "game/g_cmds.c", "ported_partial", "original-ELF-0x60600/source-contract",
        "Typed HR_HEAD/ARMS/BODY/LEGS source and original count/percentage wire order. See reference/debrief-intermission-protocol.md."),
    ("ui", "ui_ui_parse.c", "ItemParse_bitflag"): (
        "ui/ui_shared.c; ui/ui_shared.h", "ported_partial", "original-ui-ELF-0x29a00/real-keyword-parser",
        "Typed trailing bitflag integer at wasm32 offset 0x274; actual Item_Parse tested. See reference/map-load-compatibility.md."),
    ("ui", "ui_ui_misc.c", "Script_ToggleCvarBit"): (
        "ui/ui_shared.c", "ported_partial", "original-ui-ELF-0x2cc20/160-cvar-cases",
        "Decimal string cvar XOR mask action; shared UI/cgame implementation. See reference/map-load-compatibility.md."),
    ("ui", "ui_ui_item.c", "Item_CheckBox_HandleKey"): (
        "ui/ui_shared.c", "ported_partial", "original-ui-ELF-0x34330/160-checkbox-cases",
        "Bitflag checkboxes leave mutation to action script; ordinary checkbox retained. Other input behavior not claimed. See reference/map-load-compatibility.md."),
    ("ui", "ui_ui_item.c", "Item_CheckBox_Paint"): (
        "ui/ui_shared.c", "ported_partial", "original-ui-ELF-0x36b20/160-paint-cases",
        "Bitflag masks integer cvar for display; no-text checked/unchecked draws verified. Full layout parity pending. See reference/map-load-compatibility.md."),
    ("qagame", "nitmod_script.c", "G_ScriptAction_Trigger"): (
        "game/g_script_actions.c; game/g_nitmod_bot_entities.c", "ported_partial", "original-named-trigger-branch/32-real-script-scenarios",
        "Named trigger uses cached script names; bots count as found but are not dispatched. Special targets unchanged. See reference/named-trigger-hash-lookup.md."),
    ("qagame", "nitmod_script.c", "G_ScriptAction_GlobalAccum"): (
        "game/g_script_actions.c; game/g_nitmod_bot_entities.c", "ported_partial", "original-global-trigger-branch/16-real-script-scenarios",
        "Global trigger_if_equal uses cached script-name iteration and defers caller termination; local/global storage isolation tested. Other commands not claimed. See reference/globalaccum-trigger-hash-lookup.md."),
    ("qagame", "nitmod_script.c", "G_ScriptAction_Accum"): (
        "game/g_script_actions.c; game/g_nitmod_bot_entities.c", "ported_partial", "original-local-trigger-branch/16-real-script-scenarios",
        "Local trigger_if_equal iterates cached script-name matches; caller scriptId change returns false after all recipients. Other accum commands not claimed. See reference/accum-trigger-hash-lookup.md."),
    ("qagame", "nitmod_script.c", "G_ScriptAction_TagConnect"): (
        "game/g_script_actions.c; game/g_nitmod_bot_entities.c", "ported_partial", "original-ELF-0xb2fd0/8-tag-configstring-scenarios",
        "Targetname priority retained; fallback uses cached script-name search. Real native tag setup/config write/angle reset tested; client render parity pending. See reference/tag-connect-hash-lookup.md."),
    ("qagame", "nitmod_spawn.c", "target_script_trigger_use"): (
        "game/g_target.c; game/g_nitmod_bot_entities.c", "ported_partial", "original-ELF-0xd8130/10-real-script-target-scenarios",
        "First cached aiName match replaces string lookup; self fallback and subsequent target dispatch retained. Full engine runtime parity pending. See reference/script-trigger-hash-lookup.md."),
    ("qagame", "nitmod_core.c", "nitrox_FindByClassNameHash"): (
        "game/g_nitmod_bot_entities.c", "ported_partial", "original-ELF-0x10e820/all-slot-cache-search-tests",
        "Typed forward inuse/cache search with exclusive start and level entity count; invalid pointer/count defenses. Original caller migration pending. See reference/cached-name-search.md."),
    ("qagame", "nitmod_core.c", "nitrox_FindByScriptNameHash"): (
        "game/g_nitmod_bot_entities.c", "ported_partial", "original-ELF-0x10e890/all-slot-cache-search-tests",
        "Typed forward script-name cache search; no string check or special zero/-1 handling. Original caller migration pending. See reference/cached-name-search.md."),
    ("qagame", "nitmod_mdx.c", "etpro_ScriptAction_SetValues"): (
        "game/g_script_actions.c; game/g_nitmod_bot_entities.c", "ported_partial", "original-ELF-0xb61a0/16-real-parser-link-scenarios",
        "Sticky classname_nospawn and classname refresh before relink; target/scriptname caches updated per parsed key. G_ModifyTOI and hash lookup consumers pending. See reference/target-script-name-hashes.md."),
    ("qagame", "nitmod_runtime.c", "ETInterface_GetEntityWorldAABB"): (
        "game/g_nitmod_bot_entities.c", "ported_partial", "original-ELF-0x2248f0/72-world-bounds-profiles",
        "Selected abs bounds plus client Z shift; cached MG42 fallback positioned from original handle. Script cache lifecycle and C++ dispatch remain pending. See reference/bot-world-aabb.md."),
    ("qagame", "nitmod_game.c", "G_CallSpawn"): (
        "game/g_spawn.c; game/g_nitmod_bot_entities.c", "ported_partial", "original-item-records/cache-stores/LMS-fixture",
        "Team-item cache write before LMS rejection and spawn callbacks mapped to native enums. Other Nitmod spawn differences not claimed. See reference/team-item-classname-cache.md."),
    ("qagame", "nitmod_unknown.c", "LaunchItem"): (
        "game/g_items.c; game/g_nitmod_bot_entities.c", "ported_partial", "original-item-records/cache-stores/typed-policy-tests",
        "Team-item cache write after classname assignment; source-order regression only for drop path. Other Nitmod launch differences not ported. See reference/team-item-classname-cache.md."),
    ("qagame", "nitmod_unknown.c", "Drop_Item"): (
        "game/g_items.c; game/g_nitmod_bot_entities.c", "ported_partial", "original-inlined-cache-reference/native-LaunchItem-delegation",
        "Native delegation reaches team-item cache hook; original inlines launch portion. Full drop physics and callbacks remain unverified. See reference/team-item-classname-cache.md."),
    ("qagame", "nitmod_runtime.c", "ETInterface_GetEntityLocalAABB"): (
        "game/g_nitmod_bot_entities.c", "ported_partial", "original-ELF-0x223ca0/256-selection-14-bounds-cases",
        "Typed local AABB adapter uses selected entity cache; map-spawn refresh and init/free lifetime tested. Dynamic item/script cache writers pending. See reference/bot-classname-cache.md."),
    ("qagame", "nitmod_runtime.c", "ETInterface_GetEntityEyePosition"): (
        "game/g_nitmod_bot_entities.c", "ported_partial", "original-ELF-0x224750/eye-bone-fixtures",
        "Concrete position query plus client signed viewheight; paired original bone method ignores bone ID. Null-output defense; custom C++ override dispatch and x87 bit parity pending. See reference/bot-eye-bone-position.md."),
    ("qagame", "nitmod_runtime.c", "ETInterface_GetEntityOrientation"): (
        "game/g_nitmod_bot_entities.c", "ported_partial", "original-ELF-0x2240e0/192-orientation-profiles",
        "Client viewangles or entity currentAngles passed to AngleVectors with optional forward/right/up outputs. Native layout checked; x87 bit parity and C++ vtable connection pending. See reference/bot-entity-orientation.md."),
    ("qagame", "nitmod_runtime.c", "ETInterface_GetEntityVelocity"): (
        "game/g_nitmod_bot_entities.c", "ported_partial", "original-ELF-0x224010/24-velocity-profiles",
        "Typed trajectory delta or mover oldOrigin delta times 50; original G_RunEntity write/read sequence maps oldOrigin. Invalid output guarded; x87 bit parity and C++ vtable connection pending. See reference/bot-entity-velocity.md."),
    ("qagame", "nitmod_runtime.c", "ETInterface_GetEntityPosition"): (
        "game/g_nitmod_bot_entities.c", "ported_partial", "original-ELF-0x223ec0/48-geometry-profiles",
        "Typed origin and rotated local bounds center; invalid handle/inuse returns 3 without output writes. Defensive null output check; x87 bit parity and C++ vtable connection pending. See reference/bot-entity-position.md."),
    ("qagame", "nitmod_omnibot.c", "Bot_Interface_InitHandles"): (
        "game/nitmod_bot_handle.c", "ported_partial", "original-ELF-table-reset/1024-slot-tests",
        "Typed record reset sets serial 1 and clears low two flag bits while preserving other bytes; isolated from runtime. See reference/bot-entity-handles.md."),
    ("qagame", "nitmod_omnibot.c", "Bot_Event_EntityDeleted"): (
        "game/nitmod_bot_handle.c (table mutation only)", "ported_partial", "original-ELF-serial-increment/exhaustive-wrap-tests",
        "Serial increment skips zero; preserves reserved/high flags. Original deletion event precedes mutation. Dispatch/cache cleanup/game hooks remain unported. See reference/bot-entity-handles.md."),
    ("qagame", "nitmod_omnibot.c", "HandleFromEntity"): (
        "game/nitmod_bot_handle.c", "ported_partial", "original-ELF-handle-fields/exhaustive-serial-tests",
        "Fixed-width index/serial packing only; no native pointer or C++ ABI emulation. Built but not gameplay-connected; lifetime table pending. See reference/bot-entity-handles.md."),
    ("qagame", "nitmod_omnibot.c", "EntityFromHandle"): (
        "game/nitmod_bot_handle.c", "ported_partial", "original-ELF-world-exception/checked-resolution-tests",
        "Resolves to checked slot using supplied serial/inuse arrays; preserves world exception and rejects malformed indices defensively. Runtime table and engine adapter pending. See reference/bot-entity-handles.md."),
    ("qagame", "nitmod_weapons.c", "G_LandmineThink"): (
        "game/g_missile.c; game/g_nitmod_mine_contact.c", "ported_partial", "original-ELF-team-owner-filter/12288-policy-cases",
        "Team/owner and bot team/spotted filters active before contact geometry. Original-default omnibot_flags registered; 12288 owner/team and 2048 bot cases. Bot pretrigger event/private variant pending. See reference/landmine-bot-filter.md."),
    ("qagame", "nitmod_unknown.c", "sEntWillTriggerMine"): (
        "game/g_nitmod_mine_contact.c", "ported_partial", "original-ELF-contact-policy/400-typed-policy-cases",
        "Precise contact Cvar default 0/archive registered; existing mine callers use typed latch/flags policy and truncation-equivalent bounds. Null guards defensive; private caller rules and x87 extreme-coordinate parity pending. See reference/precise-landmine-contact.md."),
    ("qagame", "nitmod_unknown.c", "LandMineTrigger"): (
        "game/g_missile.c", "ported_partial", "original-ELF-trigger-contents/full-source-transition-tests",
        "Native mine retains CONTENTS_BODY at link boundary; 100ms post-think, team+8, timestamp and onFireStart trigger latch verified in 36 profiles. Compiled shared layout maps 0xfc. Precise contact policy and private weapon 0x33 branch pending. See reference/landmine-trigger-transition.md."),
    ("qagame", "nitmod_unknown.c", "fire_grenade"): (
        "game/g_missile.c; game/g_nitmod_weapon_damage.c; game/g_nitmod_satchel_die.c", "ported_partial", "original-ELF-spawn-fields/typed-damage-tests",
        "Active damage masks 1/2/4/8 for native grenade/satchel/marker/smoke identities; dynamite initial CONTENTS_BODY corrected against ELF 0x8f246. Private balance tables, extra weapon identities and canister kicking pending. See reference/dynamite-spawn-collision.md and projectile damage references."),
    ("qagame", "nitmod_bg.c", "BG_RW_ParseDefinition"): (
        "game/nitmod_weapon_definition.c", "ported_partial", "original-i386-ammo-destinations/typed-parser-tests",
        "Strict classes plus nine native ammotable_t fields and three typed recoil attributes; staged defaults and atomic output commit. Other selected attributes reject. No global ammo mutation or gameplay activation. See reference/weapon-ammo-definition.md and reference/weapon-recoil.md."),
    ("qagame", "nitmod_bg.c", "BG_RegisterWeaponFromWeaponFile"): (
        "game/nitmod_weapon_definition.c; game/g_nitmod_weapon_definition.c", "ported_partial", "typed-section-parser/engine-source-double-tests",
        "Normal/alternate ammo-mask-recoil subset selection and engine source lifetime/fallback tested through composed adapter. Client assets skipped; full grammar and registry reload ownership pending. See reference/weapon-ammo-definition.md and reference/weapon-recoil.md."),
    ("qagame", "nitmod_bg.c", "BG_RegisterWeapon"): (
        "game/nitmod_weapon_paths.c; game/g_nitmod_weapon_definition.c", "ported_partial", "hash-pinned-original-case-operands/typed-path-tests",
        "44 typed weapon file/alternate mappings and bounded preferred/fallback loader; four private weapons excluded. No registered-state or full metadata lifecycle. See reference/weapon-definition-paths.md."),
    ("qagame", "nitmod_game.c", "G_TeamCount"): (
        "game/g_nitmod_teamcount.c", "ported_partial", "original-i386-table/active-typed-count-tests",
        "Active ordinary team/weapon counting includes selected or latched team-equivalent weapons, once per client, requester excluded. Nine mapped pairs tested in both directions. Rifle-grenade private-flag/base-rifle branch remains native exact-match behavior. See reference/team-weapon-count.md."),
    ("qagame", "nitmod_weapons.c", "G_IsWeaponDisabled"): (
        "game/g_nitmod_weapon_policy.c; game/g_nitmod_restrictions.c; game/nitmod_weapon_limits.c", "ported_partial", "original-i386-control-flow/typed-restriction-tests",
        "Active ordinary spawn/selection restriction composition with original mapped limits and Sten policy; native fallback on unavailable inputs. See reference/active-loadout-restrictions.md."),
    ("qagame", "nitmod_weapons.c", "G_CanPickupWeapon"): (
        "game/g_items.c; game/g_nitmod_weapon_adapter.c", "ported_partial", "original-ELF-0x71e30/full-qagame-pickup-matrix",
        "Active restriction and war/pickAny early returns with capability-gated denial. Ordinary classes retain native policy until original class masks are available. See reference/active-pickup-restrictions.md."),
    ("qagame", "nitmod_weapons.c", "G_SetClientWeapons"): (
        "game/g_nitmod_loadout.c", "ported_partial", "typed-loadout/integrated-policy-tests",
        "Active team/loadout primary denial and secondary latch transaction with capability-gated messages; changed-only clientinfo publication. See reference/active-loadout-restrictions.md."),
    ("qagame", "nitmod_cmds.c", "Cmd_SetClass_f"): (
        "game/g_nitmod_class_command.c; game/g_cmds_ext.c", "ported_partial", "original-ELF-0x5e880/full-qagame-dispatch",
        "Active command-table dispatch and recovered class/loadout handler; native weapon IDs and existing SetTeam flow retained. See reference/active-loadout-restrictions.md."),
    ("qagame", "nitmod_bg.c", "BG_WeaponIsPrimaryForClassAndTeam"): (
        "game/g_nitmod_restrictions.c", "ported_partial", "original-i386-class-tables/typed-classification-tests",
        "Original six-slot class tables mapped to native weapons; pickup override order preserved. 4000 combinations plus invalid bounds tested. Connected to isolated weapon policy, not native loadouts. See reference/weapon-restrictions.md."),
    ("qagame", "nitmod_weapons.c", "G_RemoveWeapons"): (
        "game/g_nitmod_weapons.c", "ported_partial", "original-ELF-item-identities/typed-inventory-tests",
        "42 mapped native identities; four Nitmod-only poison/bomb variants omitted. Active war=4 frame hook with per-spawn latch and native EV_NOAMMO. Ammo and surviving bits preserved. See reference/active-war-entry.md."),
    ("qagame", "nitmod_client.c", "ClientThink_checkWeapons"): (
        "game/g_nitmod_abilities.c (adrenaline reconciliation only)", "ported_partial", "original-i386-disassembly/typed-inventory-tests",
        "Mode-4 entry active after ClientEndFrame with connected-team guards and per-spawn gclient latch. Full qagame lifecycle-adapter tests; original demo-client facility absent in ET 2.60. Adrenaline and dynamic generic restrictions remain partial. See reference/active-war-entry.md."),
    ("qagame", "nitmod_unknown.c", "EntHasAdren"): (
        "game/g_nitmod_abilities.c", "ported_partial", "original-i386-disassembly/typed-eligibility-tests",
        "Typed entity/client eligibility wrappers use explicit first-aid unlock bit 0x10 and class mask. Nulls reject safely. Built but not gameplay-active; state ownership and inventory reconciliation pending. See reference/skill-abilities-disassembly.md."),
    ("qagame", "nitmod_client.c", "ClientHasAdren"): (
        "game/g_nitmod_abilities.c", "ported_partial", "original-i386-disassembly/typed-eligibility-tests",
        "Typed entity/client eligibility wrappers use explicit first-aid unlock bit 0x10 and class mask. Nulls reject safely. Built but not gameplay-active; state ownership and inventory reconciliation pending. See reference/skill-abilities-disassembly.md."),
    ("qagame", "nitmod_game.c", "G_SetPlayerScore"): (
        "game/nitmod_score.c; game/g_nitmod_score.c", "ported_partial", "original-i386-disassembly/typed-adapter-tests",
        "Active score adapter: ordered seven XP additions with integer truncation after each step. 823543 combinations and range/nonfinite cases tested. Invalid intermediates preserve old score; double rather than x87 extended precision is a documented edge difference. Engine replay pending; see reference/skill-score-disassembly.md."),
    ("qagame", "nitmod_game.c", "G_CalcRank"): (
        "game/nitmod_skills.c (isolated rank calculation)", "ported_partial", "original-ELF-table/exhaustive-numeric-tests",
        "Sum of seven levels and ten rank thresholds recovered from ELF 0x000b7010. All 6^7 valid inputs tested; original table compared to executable. Skill refresh, Lua and active session migration pending; see reference/skill-rank-disassembly.md."),
    ("qagame", "nitmod_game.c", "G_UpgradeSkill"): (
        "game/nitmod_skills.c (isolated rank calculation)", "ported_partial", "original-ELF-table/exhaustive-numeric-tests",
        "Only shared rank calculation recovered from ELF 0x000ce310. Lua interception, userinfo and ability side effects not ported. Native upgrade logic remains active; see reference/skill-rank-disassembly.md."),
    ("qagame", "nitmod_game.c", "G_LoseSkillPoints"): (
        "game/nitmod_skills.c (isolated loss transaction)", "ported_partial", "numeric-loss/executable-tests",
        "Subtracts XP and recomputes level/unlock mask without native ET level retention; returns actual rounded XP difference. Guards, Lua overrides, rank/ability side effects, team accounting and runtime activation remain pending. Nonfinite/overflow transactions rejected deliberately."),
    ("qagame", "nitmod_unknown.c", "P_WorldEffects"): (
        "game/nitmod_air.c; game/g_nitmod_air.c; game/g_active.c", "ported_partial", "i386-air-constants/adapter-tests",
        "Active typed air adapter preserves native breather and sound/damage flow; zero unlock bits keep the 15s perk off. Numeric timelines compared against baseline ET. Signed clock overflow saturates. Extended skill activation and engine replay pending."),
    ("qagame", "nitmod_game.c", "G_SetPlayerSkill"): (
        "game/nitmod_skills.c (isolated evaluator)", "ported_partial", "numeric-control-flow/executable-tests",
        "Highest level and independent unlocked mask reconstructed with per-skill level limits, negative-disabled thresholds and global disable. Not applied to native client state; Lua, score side effects and coordinated six-level migration remain pending. See docs/skill-level-integration.md."),
    ("qagame", "nitmod_weapons.c", "G_SweepForLandmines"): (
        "game/g_nitmod_mine_sweep.c", "ported_partial", "original-i386-disassembly/executable-tests",
        "Original ELF 0x0008dbe0: origin +/- radius box query with 1024 slots, then constant false. Original caller uses result only for HQ warning. Typed adapter integrated, 80 query/return cases; original runtime replay pending. See reference/mine-satchel-disassembly.md."),
    ("qagame", "nitmod_weapons.c", "G_FreeSatchel"): (
        "game/g_nitmod_satchel_free.c", "ported_partial", "original-i386-disassembly/executable-tests",
        "ELF 0x8a570 clears free callback, checks missile/connected/covert owner, restores satchel inventory without an event. Typed ET mapping; null/index guards are defensive differences. 600 state cases; original runtime replay pending."),
    ("qagame", "nitmod_weapons.c", "Nit_SatchelDie"): (
        "game/g_nitmod_satchel_die.c", "ported_partial", "original-i386-disassembly/executable-tests",
        "ELF 0x8a5f0: corpse contents, next-tick explosion, inventory restore and conditional EV_NOAMMO. Activated at satchel spawn only for g_damageweapons mask 0x2; original default 0/flags 0 verified from ELF. 32 handler cases and 256 flag masks; other bits unported; defensive null/index guards."),
    ("qagame", "nitmod_weapons.c", "Nit_WeapDie"): (
        "game/g_nitmod_weapon_damage.c", "ported_partial", "original-i386-disassembly/executable-tests",
        "ELF 0x89390: clear free, corpse contents, time+1 explosion scheduling without owner changes. Activated for smoke-bomb g_damageweapons mask 0x8 with original 40 HP and bounds. 256 masks/8 death cases; other consumers and gameplay replay pending."),
    ("qagame", "nitmod_weapons.c", "G_ExplodeSatchels"): (
        "game/g_nitmod_entities.c; game/g_missile.c", "ported_partial", "detonation-selection/executable-tests",
        "Owner and inclusive 2000-unit range mapped to typed entities. Stable registration-order snapshot with generation and membership revalidation deliberately avoids reference list-compaction skips and reused slots. Tests exercise range, adjacent entries, ownership and callback mutations; original chain-reaction replay pending."),
    ("qagame", "nitmod_weapons.c", "nitrox_FadeLandmines"): (
        "game/g_nitmod_entities.c; game/g_missile.c", "ported_partial", "owner-cleanup/executable-tests",
        "Reverse owner-list cleanup integrated through G_FadeItems. Clears parent and ownerNum before release; mines remove both map markers. Tests cover adjacent matches, other owners, map mines, repeated cleanup and slot reuse. Native timeout gates retained; null-owner rejection deliberate; engine replay pending."),
    ("qagame", "nitmod_weapons.c", "nitrox_FadeSatchels"): (
        "game/g_nitmod_entities.c; game/g_missile.c", "ported_partial", "owner-cleanup/executable-tests",
        "Reverse owner-list cleanup integrated through G_FadeItems. Clears parent and ownerNum before release; mines remove both map markers. Tests cover adjacent matches, other owners, map mines, repeated cleanup and slot reuse. Native timeout gates retained; null-owner rejection deliberate; engine replay pending."),
    ("qagame", "nitmod_weapons.c", "G_CountTeamLandmines"): (
        "game/g_nitmod_entities.c; game/g_missile.c", "ported_partial", "typed-lifecycle/executable-tests",
        "Counts armed team mines from typed registry, capped at native MAX_TEAM_LANDMINES. Throw/map placement, explosion/free and map reset hooked. Tests cover arming, team changes, duplicate/removal/reuse, independent satchels and overflow. Nitmod team_maxLandmines Cvar and engine replay pending."),
    ("qagame", "nitmod_weapons.c", "G_FindSatchel"): (
        "game/g_nitmod_entities.c; game/g_missile.c", "ported_partial", "typed-lifecycle/executable-tests",
        "First owner match in creation-ordered satchel list; spawn, explosion, free and map reset hooked. Tests use real gentity_t and exercise order, slot reuse, reset and fatal overflow adapter. Original engine replay and multi-satchel detonation parity pending."),
    ("qagame", "nitmod_core.c", "nitrox_InitEntityArray"): (
        "game/nitmod_entity_array.c", "ported_partial", "control-flow/executable-tests",
        "Typed borrowed entity-pointer container; 1024 entries, duplicate suppression, full-before-duplicate check and ordered removal tested. Engine consumers and original fatal overflow adapter remain pending; invalid container checks are deliberate hardening."),
    ("qagame", "nitmod_core.c", "nitrox_AddEntityToEntityArray"): (
        "game/nitmod_entity_array.c", "ported_partial", "control-flow/executable-tests",
        "Typed borrowed entity-pointer container; 1024 entries, duplicate suppression, full-before-duplicate check and ordered removal tested. Engine consumers and original fatal overflow adapter remain pending; invalid container checks are deliberate hardening."),
    ("qagame", "nitmod_core.c", "nitrox_RemoveEntityFromEntityArray"): (
        "game/nitmod_entity_array.c", "ported_partial", "control-flow/executable-tests",
        "Typed borrowed entity-pointer container; 1024 entries, duplicate suppression, full-before-duplicate check and ordered removal tested. Engine consumers and original fatal overflow adapter remain pending; invalid container checks are deliberate hardening."),
    ("qagame", "nitmod_core.c", "nitrox_SetConfigstring"): (
        "game/nitmod_config_store.c; game/g_nitmod_config.c", "ported_partial", "storage-transitions/executable-tests",
        "655-slot typed store and dirty tracking tested including empty, duplicate, invalid and maximum-length values. Immediate and dirty-pass sends remain capability-gated. Rejection replaces original unsafe/truncating writes; network replay pending."),
    ("qagame", "nitmod_core.c", "nitrox_GetConfigstring"): (
        "game/g_nitmod_config.c", "ported_partial", "source-build",
        "Bounded copy from typed NCS store with index validation; engine error-path replay pending."),
    ("qagame", "nitmod_core.c", "nitrox_CSIndex"): (
        "game/nitmod_config_index.c; game/g_utils.c; game/g_nitmod_config.c", "ported_partial", "control-flow/executable-tests",
        "Case-sensitive first-empty-slot search, reserved index zero and creation overflow tested. Four recovered asset ranges use authoritative native allocation plus NCS mirrors. Arbitrary NCS ranges are rejected; original private sound +84 offset is not used for native ET events."),
    ("qagame", "nitmod_game.c", "G_UpdateKillingSpree"): (
        "game/nitmod_spree.c; game/g_nitmod_config.c; game/g_combat.c", "ported_partial", "positive-streak/executable-tests",
        "Positive streak accounting and g_announcer bit 0 thresholds tested through 100 kills, resets and overflow. Death hook follows PM_DEAD/intermission guard; negotiation does not reset streaks. Negative streaks, best-spree persistence and private revive options remain pending."),
    ("cgame", "cgame_nitrox.c", "nitmod_AddSpreePrint"): (
        "game/nitmod_announcements.c; cgame/cg_nitmod_config.c", "ported_partial", "producer-payloads/executable-tests",
        "Shared announcement decoder: type 2 is a death spree; kill/death/revive counts use recovered producer values. Private text/sound tables and multi-kill table remain unresolved."),
    ("cgame", "cgame_nitrox.c", "nitrox_NextKey"): (
        "", "deferred", "callgraph-review",
        "Shared helper has no recovered product callsite outside duplicated decompiler declarations."),
    ("cgame", "cgame_nitrox.c", "nitrox_AddPredictableDamage"): (
        "game/bg_misc.c", "ported", "control-flow/source-build",
        "Mapped to typed playerState damage feedback and shared landing prediction."),
    ("cgame", "cgame_nitrox.c", "Nit_RemoveWordInString"): (
        "cgame/cg_nitmod.c", "ported", "source/build",
        "Safe typed string implementation."),
    ("cgame", "cgame_nitrox.c", "nitrox_MinimizeET_f"): (
        "cgame/cg_nitmod.c", "ported", "source/build",
        "Original platform-not-supported message retained."),
    ("cgame", "cgame_nitrox.c", "nitmod_PrintCGS"): (
        "cgame/cg_nitmod.c", "ported", "source/build",
        "Native configstring diagnostic."),
    ("cgame", "cgame_nitrox.c", "nitrox_ClassNumForLetter"): (
        "cgame/cg_nitmod.c", "ported", "source/build",
        "Mapped to ET 2.60 player-class enums."),
    ("cgame", "cgame_nitrox.c", "nitrox_ClampFloat"): (
        "cgame/cg_nitmod.c", "ported", "source/build",
        "Typed clamp implementation."),
    ("cgame", "cgame_nitrox.c", "nitrox_ClampInt"): (
        "cgame/cg_nitmod.c", "ported", "source/build",
        "Typed clamp implementation."),
    ("cgame", "cgame_nitrox.c", "nitrox_stripLeadingSpaces"): (
        "cgame/cg_nitmod.c", "ported", "source/build",
        "Safe in-place leading-space removal."),
    ("cgame", "cgame_nitrox.c", "checkGuid"): (
        "cgame/cg_nitmod.c", "ported", "source/build",
        "Original 32-character checksum rule."),
    ("qagame", "nitmod_core.c", "nitmod_SendChargeTimes"): (
        "game/g_nitmod_config.c", "ported_partial", "wire-order/source-build",
        "Capability-gated compatibility improvement."),
    ("qagame", "nitmod_core.c", "nitrox_AddPredictableDamage"): (
        "game/bg_misc.c", "ported", "control-flow/source-build",
        "Mapped to typed playerState damage feedback and shared landing prediction."),
    ("qagame", "nitmod_core.c", "nitmod_NCSvar"): (
        "game/g_main.c; game/g_nitmod_config.c", "ported_partial", "cvar-change/source-build",
        "Refreshes the typed ET 2.60 cvar subset only when one of those cvars changes."),
    ("qagame", "nitmod_core.c", "nitrox_CheckNGUIDSum"): (
        "game/g_nitmod_config.c", "ported", "control-flow/source-build",
        "Included in the safe typed NGUID validator with the recovered 33-byte checksum."),
    ("qagame", "nitmod_core.c", "nitrox_GUIDCheckValid"): (
        "game/g_nitmod_config.c", "ported", "control-flow/source-build",
        "Mapped to the safe typed NGUID validator; invalid length is rejected before inspection."),
    ("qagame", "nitmod_core.c", "nitrox_AlphaNumValid"): (
        "game/g_nitmod_config.c", "ported", "control-flow/source-build",
        "Mapped to ASCII alphanumeric validation inside the typed NGUID validator."),
    ("qagame", "nitmod_core.c", "nitrox_NextKey"): (
        "", "deferred", "callgraph-review",
        "Shared helper has no recovered product callsite outside duplicated decompiler declarations."),
    ("qagame", "nitmod_core.c", "nitrox_CacheClientIP"): (
        "game/g_client.c; game/g_nitmod_config.c; game/g_local.h", "ported", "control-flow/source-build",
        "Mapped to a typed address/host/port cache refreshed from client userinfo."),
    ("qagame", "nitmod_core.c", "nitrox_HitboxHeight"): (
        "", "deferred", "source-review",
        "Depends on unresolved g_realBody/g_hitboxes policy and custom hitbox consumers."),
    ("qagame", "nitmod_core.c", "nitrox_ResetNumObjectives"): (
        "", "deferred", "source-review",
        "Resets native objective count plus a second unresolved mod-only counter."),
    ("qagame", "nitmod_core.c", "nitrox_CreateDirectory"): (
        "", "deferred", "callgraph-review",
        "Used by the anti-cheat path and performs native filesystem access; it belongs behind the planned platform backend."),
    ("qagame", "nitmod_core.c", "nitrox_GetTokenForString"): (
        "", "deferred", "source-review",
        "This is a lookup into an absent generated perfect-hash table, not a general token parser; its command-to-ID mapping must be recovered before porting."),
    ("qagame", "nitmod_core.c", "BG_BuildFilePath"): (
        "game/g_nitmod_config.c", "ported", "control-flow/source-build",
        "Typed bounded path builder preserves the recovered separator behavior for later platform backends."),
    ("qagame", "nitmod_core.c", "nitrox_ClampFloat"): (
        "game/g_nitmod_config.c", "ported", "control-flow/source-build",
        "Typed in-place floating-point clamp."),
    ("qagame", "nitmod_core.c", "nitrox_ClampInt"): (
        "game/g_nitmod_config.c", "ported", "control-flow/source-build",
        "Typed integer clamp retaining the recovered nearest-integer conversion."),
    ("qagame", "nitmod_core.c", "nitrox_stripLeadingSpaces"): (
        "game/g_nitmod_config.c", "ported", "control-flow/source-build",
        "Safe in-place leading-space removal."),
    ("qagame", "nitmod_core.c", "nitrox_CrazyGravityCmd"): (
        "", "deferred", "source-review",
        "Depends on the absent n_crazyGravity Cvar and its gameplay implementation."),
    ("qagame", "nitmod_core.c", "Nit_GibAll"): (
        "", "deferred", "callgraph-review",
        "Only reached while disabling the unported panzerwar/sniperwar admin modes."),
    ("qagame", "nitmod_core.c", "nitrox_bigBufferPrint"): (
        "game/g_nitmod_config.c", "ported", "control-flow/source-build",
        "Typed explicit-buffer implementation preserves chunked print delivery and safely escapes command delimiters."),
    ("qagame", "nitmod_core.c", "nitmod_objective"): (
        "game/g_nitmod_config.c", "ported_partial", "call-sites/source-build",
        "Private per-player counters remain unported."),
    ("qagame", "nitmod_core.c", "nitmod_SendMapEndStats"): (
        "game/g_nitmod_config.c", "ported_partial", "wire-order/source-build",
        "2.60 base has no dedicated bodyshot counter."),
    ("qagame", "nitmod_core.c", "nitmod_SendNCS"): (
        "game/g_nitmod_config.c", "ported_partial", "ranges/source-build",
        "Capability-gated compatibility improvement."),
    ("qagame", "nitmod_core.c", "nitmod_SoundEvent"): (
        "game/g_nitmod_config.c; game/g_utils.c", "ported_partial", "control-flow/source-build",
        "Typed adapter uses ET 2.60's equivalent EV_GENERAL_SOUND temp entity; the reference entity-pool allocation optimization is omitted."),
    ("qagame", "nitmod_core.c", "nitmod_Sound_Global"): (
        "game/g_nitmod_config.c", "ported", "control-flow/source-build",
        "Typed EV_GLOBAL_SOUND temporary entity with a broadcast sound index."),
    ("qagame", "nitmod_core.c", "nitmod_Announce"): (
        "game/g_nitmod_config.c; cgame/cg_nitmod_config.c", "ported_partial", "tuple/protocol/source-build",
        "Actor/detail/type payload is capability-gated as nsp because the original event value collides with ET 2.60 EV_GENERAL_SOUND_VOLUME; private message/sound tables remain pending."),
    ("qagame", "nitmod_core.c", "Nit_HitSound"): (
        "game/g_nitmod_config.c; cgame/cg_nitmod_config.c", "ported_partial", "wire-values/source-build",
        "Transport only. Head event requires Sniperwar; team events depend on private protection/award state. Incorrect generic G_Damage producer removed."),
    ("qagame", "nitmod_core.c", "nitmod_SimpleCS"): (
        "game/g_nitmod_config.c", "ported_partial", "wire-order/source-build",
        "Only Cvars with typed 2.60 equivalents are populated; custom gameplay Cvars remain zero."),
    ("qagame", "nitmod_core.c", "nitmod_makeSC"): (
        "", "deferred", "source-review",
        "Original change detector is driven by mod-specific Cvars that are not part of ET 2.60."),
    ("qagame", "nitmod_core.c", "nitmod_removeSC"): (
        "", "deferred", "source-review",
        "Original cleanup targets the same unresolved mod-specific Cvar tracking state."),
    ("qagame", "nitmod_core.c", "nitrox_UpdateConfigstrings"): (
        "game/g_nitmod_config.c", "ported_partial", "ranges/source-build",
        "Engine mirror call-sites are reconstructed incrementally."),
    ("qagame", "nitmod_core.c", "nitrox_ParseMaxHP"): (
        "", "deferred", "source-review",
        "Original shares native CS_FILTERCAMS (39); a direct port would corrupt stock configstring semantics."),
    ("qagame", "nitmod_core.c", "nitrox_SendSkillLevels"): (
        "", "deferred", "original-i386-symbols/source-review",
        "Seven vmCvar string sources resolved; see reference/skill-thresholds-disassembly.md. Isolated 7x6 parser tested but sender not activated: native ET has five levels and needs coordinated XP/UI/state migration."),
    ("qagame", "nitmod_core.c", "nitrox_SendClassesMaxHP"): (
        "", "deferred", "source-review",
        "Depends on the unresolved custom class-maximum-health state."),
    ("qagame", "nitmod_core.c", "nitmod_cp"): (
        "", "deferred", "source-review",
        "The ncp numeric client-message table has not been reconstructed."),
    ("cgame", "cgame_nitrox.c", "nitrox_ProcessNewCS"): (
        "cgame/cg_nitmod_config.c", "ported_partial", "dispatch/source-build",
        "Only reconstructed custom ranges are handled."),
    ("cgame", "cgame_client.c", "CG_parseMapVoteListInfo"): (
        "cgame/cg_nitmod_mapvote.c", "ported", "control-flow/protocol-tests",
        "Typed bounded parser for original immaplist records."),
    ("cgame", "cgame_client.c", "CG_parseMapVoteTally"): (
        "cgame/cg_nitmod_mapvote.c", "ported", "control-flow/protocol-tests",
        "Bounded original imvotetally parser."),
    ("cgame", "cgame_client.c", "CG_MapVoteList_Draw"): (
        "cgame/cg_nitmod_mapvote.c", "ported", "control-flow/source-build",
        "Scrollable 19-row original-protocol map list and tally display."),
    ("cgame", "cgame_client.c", "CG_MapVote_VoteButton_KeyDown"): (
        "cgame/cg_nitmod_mapvote.c", "ported", "control-flow/protocol-tests",
        "Validated original single-vote request."),
    ("cgame", "cgame_client.c", "CG_MapVote_MultiVoteButton_KeyDown"): (
        "cgame/cg_nitmod_mapvote.c", "ported", "control-flow/protocol-tests",
        "Three bounded choices with duplicate rejection."),
    ("cgame", "cgame_client.c", "CG_MapVoteList_KeyDown"): (
        "cgame/cg_nitmod_mapvote.c", "ported", "control-flow/source-build",
        "Typed mouse row selection plus wheel and keyboard scrolling."),
    ("cgame", "cgame_client.c", "CG_MapVote_VoteButton_Draw"): (
        "cgame/cg_nitmod_mapvote.c", "ported", "control-flow/source-build",
        "Explicit single-vote control integrated into debriefing."),
    ("cgame", "cgame_client.c", "CG_MapVote_SetSelectedMap"): (
        "cgame/cg_nitmod_mapvote.c", "ported", "control-flow/source-build",
        "Validated selection and levelshot fallback."),
    ("cgame", "cgame_client.c", "CG_MapVote_MultiVoteButton_Draw"): (
        "cgame/cg_nitmod_mapvote.c", "ported", "control-flow/source-build",
        "Three original multi-vote controls."),
    ("cgame", "cgame_events.c", "CG_EntityEvent"): (
        "cgame/cg_event.c; cgame/cg_nitmod_events.c", "ported_partial",
        "ELF-event-table/control-flow/source-build",
        "Original IDs 1-103 mapped including typed EV_BODY_DP; remaining presentation parity is tracked separately."),
    ("ui", "ui_ui_misc.c", "UI_BuildServerDisplayList"): (
        "ui/ui_nitmod_browser.c", "ported_partial", "filter/refresh-runtime-matrix",
        "Nitmod and sv_NxAC browser filters are reconstructed; runtime transcript pending."),
}


def functions_in(path: pathlib.Path):
    text = path.read_text(encoding="utf-8", errors="replace")
    for match in FUNCTION.finditer(text):
        name = match.group(1)
        if name not in IGNORED:
            yield name


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--source", type=pathlib.Path, default=pathlib.Path("src_nitmod_decompiled"))
    parser.add_argument("--output", type=pathlib.Path, default=pathlib.Path("reference/port_inventory.csv"))
    args = parser.parse_args()

    prior = {}
    if args.output.exists():
        with args.output.open(newline="", encoding="utf-8") as input_file:
            for row in csv.DictReader(input_file):
                prior[(row["component"], row["source_file"], row["function"])] = row

    rows = []
    for component in ("cgame", "qagame", "ui"):
        sorted_dir = args.source / component / "sorted"
        for source in sorted(sorted_dir.glob("*.c")):
            for name in functions_in(source):
                row = {
                    "component": component,
                    "source_file": source.name,
                    "function": name,
                    "ghidra_address": "",
                    "target_module": "",
                    "port_status": "untriaged",
                    "parity_evidence": "",
                    "notes": "",
                }
                key = (component, source.name, name)
                if key in prior:
                    row.update({field: prior[key].get(field, "") for field in FIELDS})
                if key in SEED_ANNOTATIONS and row["port_status"] == "untriaged":
                    target, status, evidence, notes = SEED_ANNOTATIONS[key]
                    row.update(target_module=target, port_status=status,
                               parity_evidence=evidence, notes=notes)
                rows.append(row)

    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("w", newline="", encoding="utf-8") as output:
        writer = csv.DictWriter(output, fieldnames=FIELDS)
        writer.writeheader()
        writer.writerows(rows)
    print(f"wrote {len(rows)} rows to {args.output}")


if __name__ == "__main__":
    main()
