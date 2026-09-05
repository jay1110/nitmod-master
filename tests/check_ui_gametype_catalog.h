extern qboolean GameType_Parse(char **p, qboolean join);
static int CheckGameTypeCatalog(void) {
    static uiInfo_t saved, before;
    char buffer[8192], row[128], *cursor;
    int join, n, i, errors=0;
    const char *bad[]={"", "oops", "{ junk }", "{ { x name short description } }",
        "{ { 2147483648 name short description } }", "{ { -1 name short description } }",
        "{ { 1 name short description } { 1 other short description } }",
        "{ { 0 name short description }", "{ { 0 name short description } junk }"};
    saved=uiInfo;
    for(join=0;join<2;++join) for(n=0;n<=MAX_GAMETYPES+1;++n) {
        Q_strncpyz(buffer,"{ ",sizeof(buffer));
        for(i=0;i<n;++i) {
            if(join) Com_sprintf(row,sizeof(row),"{ \"Mode %d\" %d } ",i,i*3);
            else Com_sprintf(row,sizeof(row),"{ %d \"Mode %d\" M description } ",i*3,i);
            Q_strcat(buffer,sizeof(buffer),row);
        }
        Q_strcat(buffer,sizeof(buffer),"}"); cursor=buffer; before=uiInfo;
        if(GameType_Parse(&cursor,join)!=(n<=MAX_GAMETYPES)) ++errors;
        if(n>MAX_GAMETYPES) {
            if(memcmp(&before,&uiInfo,sizeof(uiInfo))) ++errors;
        } else {
            gameTypeInfo *catalog=join ? uiInfo.joinGameTypes : uiInfo.gameTypes;
            if((join ? uiInfo.numJoinGameTypes : uiInfo.numGameTypes)!=n) ++errors;
            for(i=0;i<n;++i) if(catalog[i].gtEnum!=i*3 || !catalog[i].gameType) ++errors;
        }
    }
    for(i=0;i<sizeof(bad)/sizeof(bad[0]);++i) {
        Q_strncpyz(buffer,bad[i],sizeof(buffer)); cursor=buffer; before=uiInfo;
        if(GameType_Parse(&cursor,qfalse) || memcmp(&before,&uiInfo,sizeof(uiInfo))) ++errors;
    }
    /* Actual unmodified Nitmod catalog, read only. */
    {
        FILE *file=fopen(NITMOD_GAMEINFO_PATH,"rb");
        if(!file) ++errors;
        if(file) {
            size_t size=fread(buffer,1,sizeof(buffer)-1,file); fclose(file); buffer[size]=0;
            cursor=buffer;
            if(strcmp(COM_ParseExt(&cursor,qtrue),"gametypes") || !GameType_Parse(&cursor,qfalse) ||
               uiInfo.numGameTypes!=9 || uiInfo.gameTypes[8].gtEnum!=8) ++errors;
        }
    }
    uiInfo=saved;
    if(errors) fprintf(stderr,"game-type catalog: %d failures\n",errors);
    return errors;
}
