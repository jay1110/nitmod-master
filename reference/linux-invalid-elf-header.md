# Linux loader: invalid ELF header

Observed locally: the Windows host-test artifact previously named
`qagame.mp.i386.so` starts with `4d 5a` (MZ/PE), not `7f 45 4c 46` (ELF).
CMake unconditionally applied the Linux filename to every native target.
The reported remote file has not been inspected, so uploading this host binary
is a supported explanation, not a verified identification of the remote bytes.
A renamed WASM module or an HTTP error page can produce the same loader error.

Windows x86 builds now use the original engine filename `qagame_mp_x86.dll`,
with analogous cgame/ui names. Windows x64 host tests remain separately named
`qagame.host.windows64.dll`: they cannot be renamed into x86 engine modules.
Darwin outputs use `qagame_mac`, `cgame_mac`, `ui_mac`. Linux retains
`*.mp.i386.so` / `*.mp.x86_64.so`. Cached NITMOD_ARCH=i386 cannot force a Windows
output into an ELF-looking name. Names do not certify legacy Mac packaging/ABI.
WASM filenames remain unchanged. Linux i386 naming rejects 64-bit pointers;
the strict Linux driver additionally checks compiler target macros, data model,
ELF32/EM_386/ET_DYN headers, public entrypoints and tests. Its format failures now
identify PE, WASM and wrong ELF variants separately. Old build outputs are not
deleted automatically and must not be deployed simply because they end in .so.

## Inspect the server file

Run on the Linux server:

```sh
file /home/jay/etserv/servera/nitmod/qagame.mp.i386.so
readelf -h /home/jay/etserv/servera/nitmod/qagame.mp.i386.so
```

Expected: ELF32, little endian, DYN, Intel 80386. These checks are necessary,
not sufficient for dependency, entrypoint or gameplay compatibility.

## Build reconstructed Linux modules

On a suitable Linux x86 machine, from this repository, use the existing
container build (requires a running Linux Docker engine):

```sh
docker build -f tools/linux-i386/Dockerfile -t nitmod-linux-i386 .
docker run --rm -v "$PWD:/workspace" -w /workspace nitmod-linux-i386
```

Or, with CMake, Python 3, binutils and gcc-multilib already installed:

```sh
python3 -B tools/run_linux_i386_build.py
```

Only after a successful run, use build/linux-i386/*.mp.i386.so and its unique
verification report. Build in a clean Linux checkout/build directory rather
than reusing a Windows CMake cache. Do not rename WASM or Windows outputs.

At this check, local Docker's Linux engine was unavailable and WSL Ubuntu
could not start (HCS_E_HYPERV_NOT_INSTALLED, virtualization disabled). No genuine
reconstructed Linux-i386 artifact or remote deployment was produced. Native
Windows test passes do not change that limitation. The untouched original i386
reference modules remain original artifacts, not reconstructed build results.
