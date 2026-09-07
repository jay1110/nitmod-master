# SQLite runtime provenance

Unmodified SQLite 3.36.0 amalgamation and header copied from the existing local
ETJump checkout, deps/sqlite. SQLite source includes its public-domain notice.
This is a portable SQLite file-format runtime, not a claim of identical SQLite
library internals to the older original Nitmod build.

SHA256 sqlite3.c: a299953a92f2a801fd3b1932a2ab9c0f284156c8e1b02feb5f951e116aa7012d
SHA256 sqlite3.h: bee52359ef4c116df715d3ae94d3d40f05efdb3e46e3f3697df77540c7d2ed2e

The initial integration uses readonly deserialized snapshots supplied by engine
VFS. SQLITE_OS_OTHER, OMIT_LOAD_EXTENSION, THREADSAFE=0 and OMIT_WAL remove host
filesystem, native extension loading, threading and WAL dependencies. The small
base VFS rejects file opens/deletes; no host DB paths are silently opened.
Randomness/time callbacks are deterministic placeholders used only by this
readonly snapshot runtime, not an entropy/time service for authentication.
