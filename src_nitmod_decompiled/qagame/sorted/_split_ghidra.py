#!/usr/bin/env python3
"""Split and mechanically clean Ghidra qagame decompilation into nitmod_*.c/.h modules."""

from __future__ import annotations

import collections
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent
SRC_C = ROOT / "qagame.mp.i386.so.c"
SRC_H = ROOT / "qagame.mp.i386.so.h"

LIBC_NAMES = {
    "getpagesize", "ldexp", "fputs", "fmod", "__errno_location", "sigemptyset",
    "sprintf", "srand", "lrint", "getpid", "localeconv", "mkdir", "strerror",
    "getsockname", "strcoll", "memcmp", "qsort", "inet_ntoa", "asin", "sqrtf",
    "signal", "realloc", "sinh", "__isoc99_fscanf", "__divdi3", "__xstat",
    "__gmon_start__", "calloc", "system", "strncpy", "putchar", "sendto",
    "pow", "listen", "lseek64", "fgets", "rename", "memset", "_IO_getc",
    "floor", "strrchr", "dlsym", "modf", "__moddi3", "tmpnam", "exp",
    "ungetc", "tmpfile", "gettimeofday", "strtol", "__ctype_toupper_loc",
    "free", "__lxstat64", "backtrace_symbols", "atan", "floorf", "sigaction",
    "dlerror", "fflush", "ceilf", "sqrt", "accept", "ioctl", "socket",
    "__ctype_b_loc", "fseek", "strsignal", "fclose", "__umoddi3", "tanh",
    "_setjmp", "mktime", "fsync", "clock", "acos", "strtoul", "strlen",
    "fopen", "cos", "unlink", "freopen", "setlocale", "clearerr", "feof",
    "strcpy", "ftell", "longjmp", "printf", "bind", "strcasecmp", "close",
    "fwrite", "frexp", "fprintf", "strstr", "time", "log10", "setvbuf",
    "strncat", "remove", "malloc", "atan2", "fputc", "strtok", "strnlen",
    "sleep", "backtrace", "memmove", "__ctype_tolower_loc", "strcat", "log",
    "__fxstat64", "setsockopt", "rand", "utimes", "gmtime", "memchr",
    "strncmp", "open64", "_IO_putc", "__udivdi3", "strpbrk", "tan", "fread",
    "strftime", "cosh", "strcspn", "sin", "gethostbyname", "recvfrom",
    "_Unwind_Resume", "ferror", "strcmp", "dlopen", "__cxa_finalize", "exit",
    "difftime", "backtrace_symbols_fd", "sincos", "dlclose", "recv", "getenv",
    "strtod", "strchr", "vsnprintf", "localtime", "__xstat64", "__isoc99_sscanf",
    "inet_addr", "__cxa_atexit", "operator.delete", "operator.new",
}

SQLITE_EXTRA = (
    "btree", "vdbe", "pager", "pcache", "wal", "fkParent", "fkLookup",
    "fkScan", "window", "sqlite", "renameColumn", "renumberCursors",
    "setAllPagerFlags", "getSafetyLevel", "estimateIndex", "pageFree",
    "pageInsert", "substSelect", "autoIncrement", "resetAccumulator",
    "exprTable", "exprRow", "finalizeAgg", "returnSingleInt", "xferCompatible",
    "updateAccumulator", "updateFromSelect", "invalidateTemp", "getRowTrigger",
    "functionDestroy",
)

LUA_PREFIXES = (
    "lua_", "luaL_", "luaB_", "luaK_", "luaD_", "luaH_", "luaC_", "luaV_",
    "luaX_", "luaO_", "luaG_", "luaF_", "luaS_", "luaM_", "luaP_", "luaT_",
    "luaU_", "luaZ_", "luaopen_", "luaA_", "luaE_", "luaY_", "luaI_",
)

WEAPON_KEYS = (
    "weapon", "ammo", "reload", "akimbo", "panzer", "mortar", "landmine",
    "satchel", "tripmine", "dynamite", "flamethrower", "grenade", "riflenade",
    "airstrike", "artillery", "mg42", "emplaced", "knife", "flame", "poison",
    "weap", "fireweapon", "clip",
)

ADMIN_KEYS = (
    "admin", "ban", "mute", "kick", "warn", "shout", "referee", "shrubbot",
    "rcon", "greeting", "permission", "levelcmd",
)


def sanitize_ident(name: str) -> str:
    name = name.strip()
    repl = {
        "::": "__",
        "~": "dtor_",
        "<": "_",
        ">": "_",
        ".": "_",
        ",": "_",
        " ": "_",
        "*": "star",
        "&": "amp",
        "+": "plus",
        "-": "minus",
        "=": "eq",
        "!": "not",
        "[": "_",
        "]": "_",
        "(": "_",
        ")": "_",
    }
    for a, b in repl.items():
        name = name.replace(a, b)
    name = re.sub(r"_+", "_", name).strip("_")
    if not name:
        name = "unnamed"
    if name[0].isdigit():
        name = "n_" + name
    return name


def clean_text(s: str) -> str:
    s = re.sub(r"(?m)^[ \t]*// WARNING:.*\n", "", s)
    s = re.sub(r"(?m)^[ \t]*// Function: .*\n", "", s)
    s = s.replace("longdouble", "long double")
    s = re.sub(r"\bundefined8\b", "uint64_t", s)
    s = re.sub(r"\bundefined5\b", "uint64_t", s)
    s = re.sub(r"\bundefined6\b", "uint64_t", s)
    s = re.sub(r"\bundefined7\b", "uint64_t", s)
    s = re.sub(r"\bundefined4\b", "uint32_t", s)
    s = re.sub(r"\bundefined3\b", "uint32_t", s)
    s = re.sub(r"\bundefined2\b", "uint16_t", s)
    s = re.sub(r"\bundefined1\b", "uint8_t", s)
    s = re.sub(r"\bundefined\b", "uint8_t", s)
    s = re.sub(r"\b__regparm[123]\s+", "", s)
    s = re.sub(r"\b__thiscall\s+", "", s)
    s = re.sub(r"\b__fastcall\s+", "", s)
    s = re.sub(r"\b__cdecl\s+", "", s)
    s = re.sub(r"\bcode\s*\*", "void *", s)
    s = re.sub(r"\bFUN_([0-9a-fA-F]+)", r"unk_func_\1", s)
    s = re.sub(r"\bDAT_([0-9a-fA-F]+)", r"g_unk_\1", s)
    s = re.sub(r"\bPTR_([A-Za-z0-9_+]+)", lambda m: "g_ptr_" + sanitize_ident(m.group(1)), s)
    s = re.sub(r"\biVar(\d+)", r"tmp_i\1", s)
    s = re.sub(r"\buVar(\d+)", r"tmp_u\1", s)
    s = re.sub(r"\bpuVar(\d+)", r"tmp_pu\1", s)
    s = re.sub(r"\bpiVar(\d+)", r"tmp_pi\1", s)
    s = re.sub(r"\bpcVar(\d+)", r"tmp_pc\1", s)
    s = re.sub(r"\bpbVar(\d+)", r"tmp_pb\1", s)
    s = re.sub(r"\bppuVar(\d+)", r"tmp_ppu\1", s)
    s = re.sub(r"\blVar(\d+)", r"tmp_l\1", s)
    s = re.sub(r"\bdVar(\d+)", r"tmp_d\1", s)
    s = re.sub(r"\bfVar(\d+)", r"tmp_f\1", s)
    s = re.sub(r"\bcVar(\d+)", r"tmp_c\1", s)
    s = re.sub(r"\bbVar(\d+)", r"tmp_b\1", s)
    s = re.sub(r"\bsVar(\d+)", r"tmp_s\1", s)
    s = re.sub(r"\bunaff_([A-Z0-9]+)", r"saved_\1", s)
    s = re.sub(r"\bin_([A-Z0-9]+)", r"inreg_\1", s)
    s = re.sub(r"\bprocessEntry\s+", "", s)
    s = re.sub(
        r"\b([A-Za-z_][\w]*)\._(\d+)_(\d+)_",
        r"GHIDRA_FIELD(\1, \2, \3)",
        s,
    )
    # illegal C identifiers with dots / destructor names
    s = re.sub(r"\b([A-Za-z_][\w]*)\.(\d+)", r"\1_\2", s)
    s = s.replace("~Init", "dtor_Init")
    s = s.replace("~string", "dtor_string")
    s = re.sub(r"\n{3,}", "\n\n", s)
    return s


def extract_func_name(proto: str) -> str:
    proto = proto.replace("\n", " ")
    proto = re.sub(r"\b(processEntry|__regparm[123]|__thiscall|__fastcall|__cdecl)\b", "", proto)
    m = re.search(r"([A-Za-z_~][\w:<>~]*)\s*\([^;]*\)\s*$", proto.strip())
    if m:
        return m.group(1)
    m = re.search(r"([A-Za-z_~][\w:<>~]*)\s*\(", proto)
    return m.group(1) if m else "unnamed"


CONTROL_START = re.compile(
    r"^(if|else|for|while|switch|do|try|catch)\b"
)

def looks_like_func_proto(text: str) -> bool:
    s = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    s = re.sub(r"//.*?$", " ", s, flags=re.M)
    s = " ".join(s.split())
    if not s or s.endswith(";"):
        return False
    if CONTROL_START.match(s):
        return False
    return bool(re.search(r"[A-Za-z_~][\w:<>~]*\s*\([^;]*\)\s*$", s))


def is_plt_stub(name: str, body: str) -> bool:
    if name in LIBC_NAMES:
        return True
    inner = body.strip()
    if not (inner.startswith("{") and inner.endswith("}")):
        return False
    inner = inner[1:-1]
    lines = [ln.strip() for ln in inner.splitlines() if ln.strip() and not ln.strip().startswith("//")]
    if len(lines) > 8:
        return False
    joined = " ".join(lines)
    calls = re.findall(r"\b([A-Za-z_][\w:]*)\s*\(", joined)
    calls = [c for c in calls if c not in {"if", "for", "while", "switch", "return", "sizeof"}]
    return len(calls) == 1 and calls[0] == name.split("::")[-1]


def name_matches_any(name: str, keys: tuple[str, ...]) -> bool:
    low = name.lower()
    return any(k in low for k in keys)


def classify(name: str, body: str) -> str:
    raw = name
    n = sanitize_ident(name)
    low = raw.lower()

    if is_plt_stub(raw, body) or raw in LIBC_NAMES:
        return "imports"
    if raw.startswith("FUN_") or n.startswith("unk_func_"):
        return "unknown"
    if raw.startswith(("_init", "_fini", "deregister_tm", "register_tm", "frame_dummy",
                       "__do_global", "__x86.get_pc", "_GLOBAL__")):
        return "runtime"
    if raw.startswith("std::") or "::" in raw or raw.startswith("operator"):
        return "runtime"
    if (
        "sqlite" in low
        or raw.startswith(("sqlite", "btree", "vdbe", "pager", "pcache", "wal"))
        or raw.startswith((
            "fkParent", "fkLookup", "fkScan", "window", "pageFree", "pageInsert",
            "substSelect", "renameColumn", "renumberCursors", "getSafetyLevel",
            "estimateIndex", "autoIncrement", "resetAccumulator", "finalizeAgg",
            "returnSingleInt", "xferCompatible", "updateAccumulator",
            "invalidateTemp", "getRowTrigger", "functionDestroy", "exprTable",
            "exprRow", "setAllPager",
        ))
    ):
        return "sqlite"
    if any(raw.startswith(p) for p in LUA_PREFIXES) or raw.startswith(("G_Lua", "Lua_")):
        return "lua"
    if raw.startswith(("Bot_", "Omnibot_", "OB_", "obUtil", "KeyVals")) or raw in {
        "IsOmnibotLoaded", "IsBot", "ENTINDEX", "INDEXENT", "EntityFromHandle",
        "HandleFromEntity", "GetEntityCenter", "SendDeferredGoals", "CheckForMG42",
        "UpdateMG42", "GetMG42s", "ClipLine", "LineAABBIntersection",
        "_GetEntityName", "_EmplacedGunIsMountable", "_TankIsMountable",
        "Simple_EmplacedGunIsRepairable",
    }:
        return "omnibot"
    if raw.startswith("NxAC_") or raw.startswith("NxAC"):
        return "anticheat"
    if raw.startswith(("Cmd_", "Svcmd_")):
        return "cmds"
    if raw.startswith(("PM_", "Pmove")):
        return "pmove"
    if raw.startswith(("BG_", "PC_")):
        return "bg"
    if raw.startswith("trap_"):
        return "traps"
    if raw.startswith(("SP_", "Touch_", "Use_", "Think_", "trigger_", "target_",
                       "func_", "props_", "Props_", "misc_", "mg42_", "alarmbox")):
        return "spawn"
    if raw.startswith(("G_Script", "script_")) or "script" in low and raw.startswith("G_"):
        if raw.startswith("G_Script") or raw.startswith("script_"):
            return "script"
    if raw.startswith("mdx_") or raw.startswith(("etpro_", "etseb_", "Init_Hit")):
        return "mdx"
    if raw.startswith(("Q_", "COM_", "Com_", "Info_")):
        return "shared"
    if raw.startswith("db_"):
        return "database"
    if name_matches_any(raw, ADMIN_KEYS) and (
        raw.startswith(("nitrox_", "Nit_", "nitmod_", "G_"))
        or "shrubbot" in low
        or raw.startswith(("AddIPBan", "UpdateIPBan", "ClearMaxLives", "MuteNumbers"))
    ):
        return "admin"
    if raw.startswith(("nitrox_SQLite",)) or "InitAdmin" in raw or "GetAdminLevel" in raw:
        return "admin"
    if raw.startswith(("Weapon_", "weapon_", "FireWeapon", "Bullet_Fire", "CalcMuzzle",
                       "G_Missile", "G_ExplodeMissile", "G_RadiusDamage", "G_RunMissile")):
        return "weapons"
    if name_matches_any(raw, WEAPON_KEYS) and raw.startswith(
        ("G_", "Nit_", "nitrox_", "nitmod_", "Pickup_", "Fire")
    ):
        return "weapons"
    if raw.startswith(("Client", "Spectator", "player_die", "PlayerDie", "SetClient",
                       "CopyToBodyQue", "BodySink", "WolfRevive", "StuckInClient")):
        return "client"
    if raw.startswith(("G_Damage", "G_Kill", "G_LogDeath", "G_LogKill", "G_Death",
                       "player_die", "LookAtKiller", "G_CanGib")):
        return "combat"
    if raw.startswith("nitrox_") or raw.startswith("Nit_") or raw.startswith("nitmod_"):
        if name_matches_any(raw, WEAPON_KEYS):
            return "weapons"
        if name_matches_any(raw, ADMIN_KEYS) or "sqlite" in low or "ban" in low or "mute" in low:
            return "admin"
        return "core"
    if raw.startswith("G_"):
        return "game"
    return "unknown"


def classify_game(raw: str) -> str:
    if raw.startswith("G_"):
        return "game"
    return "unknown"


def collect_proto(lines, brace_idx: int) -> tuple[int, str] | None:
    j = brace_idx - 1
    while j >= 0 and lines[j].strip() == "":
        j -= 1
    if j < 0:
        return None
    proto_end = j
    while j >= 0:
        st = lines[j].strip()
        if st.startswith("//") or st.startswith("/*") or st.endswith("*/"):
            j -= 1
            continue
        if st == "" or st.endswith(",") or st.endswith("(") or (
            proto_end > j and not st.endswith(")") and "(" not in st
        ):
            j -= 1
            continue
        break
    k = j
    while k > 0:
        prev = lines[k - 1].strip()
        if prev.startswith("//") or prev.startswith("/*") or prev.startswith("*") or prev.startswith("WARNING"):
            k -= 1
            continue
        break
    proto = "".join(lines[k:brace_idx])
    if not looks_like_func_proto(proto):
        return None
    return k, proto


def parse_functions(text: str):
    lines = text.splitlines(keepends=True)
    n = len(lines)
    starts = []
    for i, line in enumerate(lines):
        if line.rstrip("\r\n") != "{":
            continue
        got = collect_proto(lines, i)
        if got:
            starts.append((got[0], i, got[1]))

    functions = []
    for idx, (k, brace_i, proto) in enumerate(starts):
        next_k = starts[idx + 1][0] if idx + 1 < len(starts) else n
        # body is from '{' through the last standalone '}' before the next function
        end = brace_i + 1
        last_close = brace_i
        for t in range(brace_i, next_k):
            if lines[t].rstrip("\r\n") == "}":
                last_close = t
        end = last_close + 1
        body = "".join(lines[brace_i:end])
        functions.append({
            "name": extract_func_name(proto),
            "proto": proto,
            "body": body,
            "start": k,
            "end": end,
        })

    first_fn = starts[0][0] if starts else 0
    globals_text = "".join(lines[:first_fn])
    return globals_text, functions


HEADER_TYPES = r'''#ifndef NITMOD_TYPES_H
#define NITMOD_TYPES_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#define GHIDRA_FIELD(obj, off, sz) (*(uint32_t *)((uint8_t *)&(obj) + (off)))

typedef uint8_t byte;
typedef uint8_t dwfenc;
typedef uint32_t dword;
typedef uint16_t word;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;

typedef void *pointer;

typedef struct gentity_s gentity_s;
struct gentity_s { uint8_t _opaque[1]; };

typedef struct obUserData_t obUserData_t;
struct obUserData_t { uint8_t _opaque[1]; };

typedef struct Vector Vector;
struct Vector { float x, y, z; };

typedef struct KeyVals KeyVals;
struct KeyVals { uint8_t _opaque[1]; };

typedef struct ostream ostream;
struct ostream { uint8_t _opaque[1]; };

typedef struct ios_base ios_base;
struct ios_base { uint8_t _opaque[1]; };

typedef struct locale locale;
struct locale { uint8_t _opaque[1]; };

typedef struct iostream iostream;
struct iostream { uint8_t _opaque[1]; };

typedef struct streambuf streambuf;
struct streambuf { uint8_t _opaque[1]; };

typedef struct allocator allocator;
struct allocator { uint8_t _opaque[1]; };

typedef struct stringstream stringstream;
struct stringstream { uint8_t _opaque[1]; };

typedef struct Init Init;
struct Init { uint8_t _opaque[1]; };

typedef struct string string;
struct string { uint8_t _opaque[1]; };

typedef FILE _IO_FILE;

#ifndef __linux__
typedef int sigset_t;
typedef int socklen_t;
typedef struct { int sa_family; char sa_data[14]; } sockaddr;
typedef struct { unsigned s_addr; } in_addr;
typedef unsigned in_addr_t;
typedef struct hostent hostent;
typedef long __off_t;
typedef long long __off64_t;
typedef unsigned __mode_t;
typedef int __pid_t;
typedef void (*__sighandler_t)(int);
typedef void *__gnuc_va_list;
typedef int (*__compar_fn_t)(const void *, const void *);
typedef long time_t;
typedef long clock_t;
typedef long ssize_t;
typedef struct tm tm;
typedef struct timeval timeval;
typedef struct timezone timezone;
typedef timezone *__timezone_ptr_t;
typedef struct stat stat;
typedef struct stat64 stat64;
typedef struct lconv lconv;
typedef struct sigaction sigaction;
typedef struct __jmp_buf_tag __jmp_buf_tag;
typedef int32_t __int32_t;
typedef struct evp_pkey_ctx_st EVP_PKEY_CTX;
#endif

#endif /* NITMOD_TYPES_H */
'''

MODULE_META = {
    "weapons": ("Weapons, ammo, missiles, fire logic", "nitmod_weapons"),
    "admin": ("Admin, bans, mutes, shrubbot/nitrox permissions", "nitmod_admin"),
    "cmds": ("Client and server console commands", "nitmod_cmds"),
    "pmove": ("Player movement (Pmove / PM_*)", "nitmod_pmove"),
    "bg": ("Shared bg_* animation, items, weapons tables", "nitmod_bg"),
    "client": ("Client think, connect, spectator, revive", "nitmod_client"),
    "combat": ("Damage, death, kill logging", "nitmod_combat"),
    "spawn": ("Map entity spawn (SP_*), triggers, props", "nitmod_spawn"),
    "game": ("Remaining G_* game logic", "nitmod_game"),
    "core": ("Nitmod / nitrox helpers not in admin/weapons", "nitmod_core"),
    "omnibot": ("Omni-bot interface", "nitmod_omnibot"),
    "lua": ("Embedded Lua VM and bindings", "nitmod_lua"),
    "sqlite": ("Embedded SQLite", "nitmod_sqlite"),
    "traps": ("Engine trap_* syscalls", "nitmod_traps"),
    "anticheat": ("NxAC anti-cheat", "nitmod_anticheat"),
    "script": ("Entity scripting", "nitmod_script"),
    "mdx": ("MDX hit detection / antilag helpers", "nitmod_mdx"),
    "shared": ("Q_ / COM_ / Info_ string helpers", "nitmod_shared"),
    "database": ("db_* persistence helpers", "nitmod_database"),
    "runtime": ("ELF/C++ runtime leftovers from the .so", "nitmod_runtime"),
    "unknown": ("Unnamed or unclassified Ghidra functions", "nitmod_unknown"),
}


def proto_to_decl(proto: str, name: str) -> str:
    cleaned = clean_text(proto).strip()
    # drop leading comments for header
    lines = [ln for ln in cleaned.splitlines() if not ln.strip().startswith("//")]
    text = "\n".join(lines).strip()
    text = re.sub(r"\s+", " ", text)
    if not text.endswith(";"):
        text = text.rstrip() + ";"
    # sanitize C++ names in decl
    if "::" in name or "~" in name or "." in name:
        san = sanitize_ident(name)
        text = text.replace(name, san, 1)
    return text


def sanitize_globals(gtext: str) -> str:
    out_lines = []
    for line in clean_text(gtext).splitlines():
        s = line.strip()
        if s.startswith("#include"):
            continue
        if not s:
            out_lines.append("")
            continue
        # uint8_t[3744] ammoTableMP;  -> uint8_t ammoTableMP[3744];
        m = re.match(r"^((?:const\s+)?)([A-Za-z_][\w\s\*]*)\[(\d+)\]\s+([A-Za-z_][\w]*)\s*;\s*$", s)
        if m:
            out_lines.append(f"{m.group(1)}{m.group(2).strip()} {m.group(4)}[{m.group(3)}];")
            continue
        out_lines.append(line.rstrip())
    return "\n".join(out_lines).strip() + "\n"


def main() -> None:
    print("Reading", SRC_C, "...")
    text = SRC_C.read_text(encoding="latin-1")
    print("Parsing functions...")
    globals_text, functions = parse_functions(text)
    print(f"Found {len(functions)} functions, {len(globals_text.splitlines())} global lines")

    buckets = collections.defaultdict(list)
    for fn in functions:
        mod = classify(fn["name"], fn["body"])
        buckets[mod].append(fn)

    print("Classification:")
    for k in sorted(buckets, key=lambda x: -len(buckets[x])):
        print(f"  {k:12s} {len(buckets[k]):5d}")

    (ROOT / "nitmod_types.h").write_text(HEADER_TYPES, encoding="utf-8")

    gclean = sanitize_globals(globals_text)
    (ROOT / "nitmod_globals.c").write_text(
        '#include "nitmod_types.h"\n#include "nitmod_globals.h"\n\n' + gclean,
        encoding="utf-8",
    )
    # globals header: extern each declaration
    gh = ['#ifndef NITMOD_GLOBALS_H', '#define NITMOD_GLOBALS_H', '', '#include "nitmod_types.h"', '']
    for line in gclean.splitlines():
        st = line.strip()
        if not st or st.startswith("//") or st.startswith("/*") or st.startswith("*"):
            continue
        if st.startswith("extern "):
            gh.append(st if st.endswith(";") else st + ";")
        else:
            gh.append("extern " + st.rstrip(";") + ";")
    gh += ["", "#endif", ""]
    (ROOT / "nitmod_globals.h").write_text("\n".join(gh), encoding="utf-8")

    # imports: declarations only
    imp = [
        "#ifndef NITMOD_IMPORTS_H",
        "#define NITMOD_IMPORTS_H",
        "",
        '#include "nitmod_types.h"',
        "",
        "/* libc / libstdc++ imports from the original .so PLT — do not compile stubs */",
        "",
    ]
    seen = set()
    for fn in buckets.get("imports", []):
        decl = proto_to_decl(fn["proto"], fn["name"])
        if decl not in seen:
            seen.add(decl)
            imp.append(decl)
    imp += ["", "#endif", ""]
    (ROOT / "nitmod_imports.h").write_text("\n".join(imp), encoding="utf-8")

    for mod, fns in buckets.items():
        if mod == "imports":
            continue
        stem = MODULE_META.get(mod, ("Other", f"nitmod_{mod}"))[1]
        title = MODULE_META.get(mod, ("Other", stem))[0]
        hpath = ROOT / f"{stem}.h"
        cpath = ROOT / f"{stem}.c"
        guard = stem.upper() + "_H"

        hlines = [
            f"#ifndef {guard}",
            f"#define {guard}",
            "",
            f"/* {title} */",
            "",
            '#include "nitmod_types.h"',
            '#include "nitmod_globals.h"',
            "",
        ]
        clines = [
            f'/* {title} — recovered from qagame.mp.i386.so Ghidra decompile */',
            '#include "nitmod_types.h"',
            '#include "nitmod_globals.h"',
            '#include "nitmod_imports.h"',
            f'#include "{stem}.h"',
            "",
        ]

        for fn in fns:
            proto = clean_text(fn["proto"])
            body = clean_text(fn["body"])
            name = fn["name"]
            if "::" in name or "~" in name or "." in name:
                san = sanitize_ident(name)
                proto = proto.replace(name, san, 1)
            clines.append(proto.rstrip())
            clines.append(body.rstrip())
            clines.append("")
            hlines.append(proto_to_decl(fn["proto"], fn["name"]))

        hlines += ["", "#endif", ""]
        hpath.write_text("\n".join(hlines) + "\n", encoding="utf-8")
        cpath.write_text("\n".join(clines) + "\n", encoding="utf-8")
        print(f"Wrote {cpath.name} ({len(fns)} funcs, {cpath.stat().st_size // 1024} KB)")

    print("Done.")


if __name__ == "__main__":
    main()
