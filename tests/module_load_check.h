#ifndef NITMOD_MODULE_LOAD_CHECK_H
#define NITMOD_MODULE_LOAD_CHECK_H
/* Test infrastructure only: never invokes an engine entrypoint. */
typedef struct {
    void *(*open)(const char *path);
    void *(*symbol)(void *handle, const char *name);
    int (*close)(void *handle);
} moduleLoader_t;

static int CheckModuleLoads(const char *const *paths, int count, const moduleLoader_t *loader) {
    void *handles[3];
    int i, opened = 0, failed = 0;
    if(!paths || !loader || !loader->open || !loader->symbol || !loader->close || count < 1 || count > 3)
        return 1;
    for(i = 0; i < count; ++i) {
        if(!paths[i] || !paths[i][0]) { failed = 1; break; }
        handles[opened] = loader->open(paths[i]);
        if(!handles[opened]) { failed = 1; break; }
        ++opened;
        if(!loader->symbol(handles[opened - 1], "vmMain") ||
           !loader->symbol(handles[opened - 1], "dllEntry")) { failed = 1; break; }
    }
    /* Keep modules loaded together, then unwind even after a failed lookup. */
    while(opened) if(loader->close(handles[--opened]) != 0) failed = 1;
    return failed;
}
#endif
