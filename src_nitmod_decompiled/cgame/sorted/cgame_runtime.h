#ifndef CGAME_RUNTIME_H
#define CGAME_RUNTIME_H

/* ELF/C++ runtime remnants */

#include "nitmod_types.h"
#include "nitmod_globals.h"

int _init(EVP_PKEY_CTX *ctx);
void deregister_tm_clones(void);
void register_tm_clones(void);
void __do_global_dtors_aux(void);
void frame_dummy(void);
void _fini(void);

#endif

