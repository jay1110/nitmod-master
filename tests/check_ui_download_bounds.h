extern const char *UI_DownloadInfo(const char *name);
static float downloadCounters[3];
static int QDECL DownloadSyscall(int command, ...) {
    va_list args;
    const char *name;
    float value;
    int bits;
    if(command != UI_CVAR_VARIABLEVALUE) { fprintf(stderr, "unexpected download syscall %d\n", command); exit(2); }
    va_start(args, command); name = va_arg(args, const char *); va_end(args);
    if(!strcmp(name, "cl_downloadSize")) value = downloadCounters[0];
    else if(!strcmp(name, "cl_downloadCount")) value = downloadCounters[1];
    else if(!strcmp(name, "cl_downloadTime")) value = downloadCounters[2];
    else { fprintf(stderr, "unexpected download cvar %s\n", name); exit(2); }
    memcpy(&bits, &value, sizeof(bits)); return bits;
}
static int CheckDownloadBounds(void) {
    char size[64];
    const char *text;
    int i, errors = 0, oldTime = uiInfo.uiDC.realTime;
    dllEntry(DownloadSyscall);
    if(UI_DownloadPercent(2147483647, 1) != 100 || UI_DownloadPercent(1, 0) ||
       UI_DownloadPercent(-1, 10) || UI_DownloadPercent(1, 3) != 33 ||
       UI_DownloadRate(4096, 1000, 1999) || UI_DownloadRate(4096, 1000, 2000) != 4096 ||
       UI_DownloadRate(4096, 2147483647, (-2147483647-1))) ++errors;
    UI_ReadableSize(size, sizeof(size), 1610612736);
    if(strcmp(size, "1.50 GB")) ++errors;
    downloadCounters[0] = 8192; downloadCounters[1] = 4096; downloadCounters[2] = 1000;
    uiInfo.uiDC.realTime = 2000;
    text = UI_DownloadInfo("nitmod.pk3");
    if(!strstr(text, "(50%)") || !strstr(text, "4 KB/s")) ++errors;
    downloadCounters[0] = 1; downloadCounters[1] = FLT_MAX;
    text = UI_DownloadInfo("large.pk3");
    if(!strstr(text, "(100%)")) ++errors;
    downloadCounters[0] = 2147483648.f; downloadCounters[1] = 4096;
    uiInfo.uiDC.realTime = 4097000;
    for(i = 0; i < 80; ++i) text = UI_DownloadInfo("slow.pk3");
    if(strstr(text, "-1") || !strstr(text, "596522 hr")) ++errors;
    downloadCounters[1] = -1;
    if(!strstr(UI_DownloadInfo(NULL), "Estimating")) ++errors;
    downloadCounters[1] = 4096; uiInfo.uiDC.realTime = (-2147483647 - 1);
    if(!strstr(UI_DownloadInfo("clock-reset.pk3"), "Estimating")) ++errors;
    uiInfo.uiDC.realTime = oldTime;
    return errors;
}
