#include <stdio.h>
#include <string.h>
#include "module_load_check.h"
#define CHECK(x) do { if(!(x)) { fprintf(stderr, "loader check %d\n", __LINE__); return 1; } } while(0)
static int tokens[3], opens, symbols, closes, order[3], failOpen, failSymbol, failClose;
static void *FakeOpen(const char *path) {
    int index = opens++;
    (void)path;
    return index == failOpen ? NULL : &tokens[index];
}
static void *FakeSymbol(void *handle, const char *name) {
    int index = symbols++;
    if(strcmp(name, index % 2 ? "dllEntry" : "vmMain")) return NULL;
    return index == failSymbol ? NULL : handle;
}
static int FakeClose(void *handle) {
    int index = (int)((int *)handle - tokens);
    order[closes++] = index;
    return index == failClose ? -1 : 0;
}
int main(void) {
    static const moduleLoader_t loader = { FakeOpen, FakeSymbol, FakeClose };
    static const char *paths[] = { "cgame", "qagame", "ui" };
    int mode, failure, expected, i;
    for(mode = 0; mode < 4; ++mode) for(failure = 0; failure < (mode == 2 ? 6 : 3); ++failure) {
        opens = symbols = closes = 0;
        failOpen = mode == 1 ? failure : -1;
        failSymbol = mode == 2 ? failure : -1;
        failClose = mode == 3 ? failure : -1;
        CHECK(CheckModuleLoads(paths, 3, &loader) == (mode != 0));
        expected = mode == 1 ? failure : mode == 2 ? failure / 2 + 1 : 3;
        CHECK(closes == expected);
        for(i = 0; i < closes; ++i) CHECK(order[i] == expected - 1 - i);
    }
    CHECK(CheckModuleLoads(paths, 0, &loader));
    CHECK(CheckModuleLoads(paths, 4, &loader));
    CHECK(CheckModuleLoads(NULL, 3, &loader));
    CHECK(CheckModuleLoads(paths, 3, NULL));
    return 0;
}
