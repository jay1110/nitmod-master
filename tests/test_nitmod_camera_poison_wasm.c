#include "g_local.h"
#include <assert.h>
#include <stdio.h>
int main(void) {
    static gclient_t client;
    static gentity_t portal;
    int flags, camera;
    assert(!G_NITMOD_IsViewingCamera(NULL));
    for(flags = 0; flags < 2; ++flags) for(camera = 0; camera < 2; ++camera) {
        client.ps.eFlags = flags ? NITMOD_EF_POISONED : 0;
        client.cameraPortal = camera ? &portal : NULL;
        assert(!!G_NITMOD_IsViewingCamera(&client) == (flags && camera));
    }
    puts("WASM camera/poison discriminator: flag and portal combinations passed");
    return 0;
}
