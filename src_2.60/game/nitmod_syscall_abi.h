#ifndef NITMOD_SYSCALL_ABI_H
#define NITMOD_SYSCALL_ABI_H

/* Native ET 2.60 keeps its variadic ABI. The browser engine uses a pointer
 * to command/argument slots. Cast each expression before array construction;
 * do not read mixed pointer/int varargs as one type or guess an argument count.
 * Used only by the three engine adapters, after q_shared.h. */
#ifdef __EMSCRIPTEN__
#include <stdint.h>
#define NITMOD_WASM_ABI_EXPORT \
    NITMOD_MODULE_EXPORT int vmWasmAbi1(void) { return 1; }
typedef intptr_t (QDECL *nitmod_syscall_t)(intptr_t *);
#define NM_SLOT(x) ((intptr_t)(x))
#define NM_SLOTS_1(a) NM_SLOT(a)
#define NM_SLOTS_2(a, ...) NM_SLOT(a), NM_SLOTS_1(__VA_ARGS__)
#define NM_SLOTS_3(a, ...) NM_SLOT(a), NM_SLOTS_2(__VA_ARGS__)
#define NM_SLOTS_4(a, ...) NM_SLOT(a), NM_SLOTS_3(__VA_ARGS__)
#define NM_SLOTS_5(a, ...) NM_SLOT(a), NM_SLOTS_4(__VA_ARGS__)
#define NM_SLOTS_6(a, ...) NM_SLOT(a), NM_SLOTS_5(__VA_ARGS__)
#define NM_SLOTS_7(a, ...) NM_SLOT(a), NM_SLOTS_6(__VA_ARGS__)
#define NM_SLOTS_8(a, ...) NM_SLOT(a), NM_SLOTS_7(__VA_ARGS__)
#define NM_SLOTS_9(a, ...) NM_SLOT(a), NM_SLOTS_8(__VA_ARGS__)
#define NM_SLOTS_10(a, ...) NM_SLOT(a), NM_SLOTS_9(__VA_ARGS__)
#define NM_SLOTS_11(a, ...) NM_SLOT(a), NM_SLOTS_10(__VA_ARGS__)
#define NM_SLOTS_12(a, ...) NM_SLOT(a), NM_SLOTS_11(__VA_ARGS__)
#define NM_SLOTS_13(a, ...) NM_SLOT(a), NM_SLOTS_12(__VA_ARGS__)
#define NM_SLOTS_14(a, ...) NM_SLOT(a), NM_SLOTS_13(__VA_ARGS__)
#define NM_SLOTS_15(a, ...) NM_SLOT(a), NM_SLOTS_14(__VA_ARGS__)
#define NM_SLOTS_16(a, ...) NM_SLOT(a), NM_SLOTS_15(__VA_ARGS__)
#define NM_PICK_SLOTS(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,SELECT,...) SELECT
#define NM_SLOTS(...) NM_PICK_SLOTS(__VA_ARGS__, NM_SLOTS_16, NM_SLOTS_15, NM_SLOTS_14, NM_SLOTS_13, NM_SLOTS_12, NM_SLOTS_11, NM_SLOTS_10, NM_SLOTS_9, NM_SLOTS_8, NM_SLOTS_7, NM_SLOTS_6, NM_SLOTS_5, NM_SLOTS_4, NM_SLOTS_3, NM_SLOTS_2, NM_SLOTS_1)(__VA_ARGS__)
#define NITMOD_SYSCALL(...) nitmodSyscall((intptr_t[]){NM_SLOTS(__VA_ARGS__)})
#else
#define NITMOD_WASM_ABI_EXPORT
typedef int (QDECL *nitmod_syscall_t)(int, ...);
#define NITMOD_SYSCALL nitmodSyscall
#endif
#endif
