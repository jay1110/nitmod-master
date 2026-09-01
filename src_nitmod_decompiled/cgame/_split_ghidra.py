#!/usr/bin/env python3
"""Split and mechanically clean the cgame Ghidra decompilation.

The original ``cgame.mp.i386.so.[ch]`` files remain untouched.  Running this
script creates the recovered, topic-oriented sources next to them.
"""

from __future__ import annotations

import importlib.util
import re
import sys
from pathlib import Path


SOURCE_ROOT = Path(__file__).resolve().parent
ROOT = SOURCE_ROOT / "sorted"
QAGAME_SPLITTER = SOURCE_ROOT.parent / "qagame" / "_split_ghidra.py"

spec = importlib.util.spec_from_file_location("ghidra_split_base", QAGAME_SPLITTER)
if spec is None or spec.loader is None:
    raise RuntimeError(f"Cannot load shared splitter: {QAGAME_SPLITTER}")
sys.dont_write_bytecode = True
base = importlib.util.module_from_spec(spec)
spec.loader.exec_module(base)


def classify(name: str, body: str) -> str:
    """Assign client-game functions to stable, reviewable modules."""
    raw = name
    low = raw.lower()

    if base.is_plt_stub(raw, body) or raw in base.LIBC_NAMES:
        return "imports"
    if raw.startswith(("_init", "_fini", "deregister_tm", "register_tm", "frame_dummy",
                       "__do_global", "__x86.get_pc", "_GLOBAL__", "processEntry")):
        return "runtime"
    if raw.startswith("FUN_"):
        return "unknown"
    if raw.startswith(("PM_", "Pmove")):
        return "pmove"
    if raw.startswith(("BG_", "PC_")):
        return "bg"
    if raw.startswith("trap_"):
        return "traps"
    if raw.startswith(("Q_", "COM_", "Com_", "Info_")):
        return "shared"
    if raw.startswith(("WM_", "Item", "Menu", "Script_", "Scroll_", "Display_", "Text_", "UI_",
                       "Tooltip", "Cui_", "String_", "Float_", "Color_", "Int_", "Rect_",
                       "Init_Display", "Gradient", "Window_", "IsVisible", "Controls_", "Binding",
                       "AdjustFrom", "Keyword", "C_Panel", "jP_SetHUD", "cf_")):
        return "ui"
    if raw.startswith("SP_"):
        return "spawn"
    if raw.startswith(("Vector", "_Vector", "Angle", "Axis", "Matrix", "CrossProduct",
                       "PlaneFrom", "ProjectPoint", "MakeNormal", "Perpendicular", "Rotate",
                       "Distance", "RadiusFrom", "ClearBounds", "AddPointToBounds", "PointInBounds",
                       "DirToByte", "ByteToDir", "ColorBytes", "NormalizeColor", "Clamp", "vecto",
                       "SnapVector", "Lerp", "SetPlane", "_DotProduct", "GetPerpendicular")):
        return "math"
    if raw.startswith(("ItemParse_", "MenuParse_", "SkipBraced", "SkipRest", "Parse1D",
                       "Parse2D", "Parse3D", "encode64", "decode64", "escape_", "unescape_",
                       "need_escape", "FileExists", "vtos", "tv", "va")):
        return "shared"
    if raw.startswith(("CG_Predict", "CG_Transition", "CG_Interpolate", "CG_BuildSolidList",
                       "CG_AdjustPosition", "CG_Trace", "CG_PointContents")):
        return "predict"
    if raw.startswith(("CG_ProcessSnapshots", "CG_ReadNextSnapshot", "CG_SetInitialSnapshot",
                       "CG_SetNextSnap", "CG_ExecuteNewServerCommands")):
        return "snapshot"
    if raw.startswith(("CG_ServerCommand", "CG_ConfigStringModified", "CG_Parse")):
        return "servercmds"
    if raw.startswith(("CG_ConsoleCommand", "CG_InitConsoleCommands", "CG_Argv", "CG_Args")):
        return "consolecmds"
    if raw.startswith(("CG_NewClientInfo", "CG_LoadClientInfo", "CG_RegisterClient", "CG_Player",
                       "CG_CustomSound", "CG_CopyClient")):
        return "players"
    if raw.startswith(("CG_EntityEvent", "CG_CheckEvents", "CG_Obituary", "CG_PainEvent")):
        return "events"
    if raw.startswith(("CG_Add", "CG_Position", "CG_CalcEntity", "CG_EntityEffects", "CG_General",
                       "CG_Item", "CG_Mover", "CG_Beam", "CG_Portal", "CG_Adjust")):
        return "ents"
    if raw.startswith(("CG_Missile", "CG_Bullet", "CG_Tracer", "CG_Explosion", "CG_Bleed",
                       "CG_Impact", "CG_Smoke", "CG_Flame", "CG_Rail", "CG_Gib")):
        return "effects"
    if raw.startswith(("CG_StartSound", "CG_Sound", "CG_Play", "CG_UpdateSound")):
        return "sound"
    if raw.startswith(("CG_Particle", "CG_AddParticle", "CG_SpawnParticle")):
        return "particles"
    if raw.startswith(("CG_Draw", "CG_OwnerDraw", "CG_Text", "CG_Fill", "CG_Paint", "CG_Menu",
                       "CG_Hud", "CG_Scoreboard", "CG_LoadPanel", "CG_Limbo", "CG_Debrief")):
        return "ui"
    if raw.startswith(("CG_FireTeam", "CG_Fireteam")):
        return "fireteams"
    if raw.startswith(("CG_Weapon", "CG_FireWeapon", "CG_RegisterWeapon", "CG_AddViewWeapon")):
        return "weapons"
    if raw.startswith(("CG_Init", "CG_Shutdown", "CG_DrawActiveFrame", "CG_Execute", "vmMain")):
        return "main"
    if raw.startswith(("nitrox_", "nitmod_", "Nit_", "NxAC_", "SHA1", "G_SHA", "MD5", "Crash_",
                       "install", "restore", "EnableStack", "DisableStack", "checkGuid")):
        return "nitrox"
    if raw.startswith("CG_"):
        return "client"
    return "unknown"


base.ROOT = ROOT
base.SRC_C = SOURCE_ROOT / "cgame.mp.i386.so.c"
base.SRC_H = SOURCE_ROOT / "cgame.mp.i386.so.h"
base.classify = classify

# Ghidra often places a return type (and register annotation) on a line of its
# own.  The generic parser intentionally skips such lines; joining them first
# preserves the type rather than producing invalid implicit-int declarations.
_parse_functions = base.parse_functions


def parse_functions(text: str):
    text = re.sub(
        r"(?m)^((?:undefined(?:[1-8])?|void|bool|int|uint|float|double|char|byte|"
        r"long|short)(?:\s*\*)?(?:\s+__regparm[123])?)\s*\n"
        r"([A-Za-z_][\w.]*\s*\()",
        r"\1 \2",
        text,
    )
    return _parse_functions(text)


base.parse_functions = parse_functions
base.MODULE_META = {
    "main": ("Client-game VM lifecycle and frame orchestration", "cgame_main"),
    "client": ("Miscellaneous client-game logic", "cgame_client"),
    "ui": ("HUD, menus, scoreboards and drawing", "cgame_ui"),
    "ents": ("Client entity placement and scene submission", "cgame_ents"),
    "effects": ("Missiles, impacts and visual effects", "cgame_effects"),
    "weapons": ("Client weapon presentation and selection", "cgame_weapons"),
    "events": ("Entity events and event-driven effects", "cgame_events"),
    "players": ("Client/player model and character information", "cgame_players"),
    "predict": ("Client-side prediction and collision", "cgame_predict"),
    "snapshot": ("Snapshot processing and interpolation", "cgame_snapshot"),
    "servercmds": ("Server-command and config-string processing", "cgame_servercmds"),
    "consolecmds": ("Client console commands", "cgame_consolecmds"),
    "sound": ("Sound registration and playback", "cgame_sound"),
    "particles": ("Particle systems", "cgame_particles"),
    "fireteams": ("Fireteam UI and state", "cgame_fireteams"),
    "pmove": ("Player movement", "cgame_pmove"),
    "bg": ("Shared background game logic", "cgame_bg"),
    "traps": ("Engine trap syscalls", "cgame_traps"),
    "shared": ("Shared string and utility helpers", "cgame_shared"),
    "math": ("Vector, angle and geometry helpers", "cgame_math"),
    "spawn": ("Recovered map-entity spawn handlers", "cgame_spawn"),
    "nitrox": ("Nitrox extensions, integrity and crash reporting", "cgame_nitrox"),
    "runtime": ("ELF/C++ runtime remnants", "cgame_runtime"),
    "unknown": ("Unclassified recovered functions", "cgame_unknown"),
}


if __name__ == "__main__":
    base.main()
