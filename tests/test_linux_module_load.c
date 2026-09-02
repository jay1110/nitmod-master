#include <stdio.h>
#include <dlfcn.h>
#include "module_load_check.h"

static void *OpenModule(const char *path) {
    void *handle = dlopen(path, RTLD_NOW | RTLD_LOCAL);
    if(!handle) fprintf(stderr, "dlopen %s: %s\n", path, dlerror());
    return handle;
}
static void *FindSymbol(void *handle, const char *name) {
    void *address;
    const char *error;
    dlerror();
    address = dlsym(handle, name);
    error = dlerror();
    if(error || !address) {
        fprintf(stderr, "dlsym %s: %s\n", name, error ? error : "null address");
        return NULL;
    }
    return address;
}
static int CloseModule(void *handle) {
    int result = dlclose(handle);
    if(result) fprintf(stderr, "dlclose: %s\n", dlerror());
    return result;
}
int main(int argc, char **argv) {
    static const moduleLoader_t loader = { OpenModule, FindSymbol, CloseModule };
    const char *paths[3];
    int i;
    if(argc < 2 || argc > 4) { fprintf(stderr, "Expected one to three module paths\n"); return 1; }
    for(i = 1; i < argc; ++i) paths[i - 1] = argv[i];
    return CheckModuleLoads(paths, argc - 1, &loader);
}
