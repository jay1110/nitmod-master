#include "g_local.h"
#include "g_nitmod_records.h"
#include "g_nitmod_database.h"
#include "g_nitmod_legacy_cvars.h"
#include "nitmod_database.h"
static void SafeRecordText(const char *input,char *output,int capacity) {
    int used=0; for(;*input && used<capacity-1;++input) {
        unsigned char c=*input; if(c>=32 && c!='"' && c!='\\') output[used++]=c;
    } output[used]=0;
}
void G_NITMOD_PrintMapRecords(const nitmodDatabaseRecords_t *record,int flags) {
    static const char *labels[]={"Spree","Frag","Revive Spree"}; int j;
    if(!record) return;
    for(j=0;j<3;++j) if((flags&(1<<j)) && record->value[j]>0) {
        char name[64],date[32]; SafeRecordText(record->holder[j],name,sizeof(name)); SafeRecordText(record->date[j],date,sizeof(date));
        trap_SendServerCommand(-1,va("chat \"^g%s %s record: ^x%d ^gby ^7%s ^g(^x%s^g)\" -2",flags&8?"Previous":"Map",labels[j],record->value[j],name,date));
    }
}
void G_NITMOD_SaveMapRecords(void) {
    static const char *months[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
    static const char *labels[]={"Spree","Frag","Revive Spree"};
    nitmodDatabaseRecords_t record,old; qtime_t time;
    int i,j,exists,changed,length; void *before;
    if(NITMOD_DBUserCount()<0 || !G_NITMOD_LegacyCvarInteger("n_mapRecords",1) || !*level.rawmapname) return;
    if(!trap_RealTime(&time) || time.tm_mon<0 || time.tm_mon>11) return;
    memset(&record,0,sizeof(record)); Q_strncpyz(record.map,level.rawmapname,sizeof(record.map));
    for(i=0;i<level.numPlayingClients && i<MAX_CLIENTS;++i) {
        int n=level.sortedClients[i],values[3]; gclient_t *client;
        if(n<0 || n>=MAX_CLIENTS || !(client=g_entities[n].client)) continue;
        values[0]=G_NITMOD_BestKillSpree(n);
        values[1]=client->sess.kills; values[2]=client->nitmodBestReviveSpree;
        for(j=0;j<3;++j) if(values[j]>record.value[j]) {
            record.value[j]=values[j]; Q_strncpyz(record.holder[j],client->pers.netname,sizeof(record.holder[j]));
        }
    }
    for(j=0;j<3;++j) Com_sprintf(record.date[j],sizeof(record.date[j]),"%02d %s %04d %02d:%02d",
        time.tm_mday,months[time.tm_mon],time.tm_year+1900,time.tm_hour,time.tm_min);
    exists=NITMOD_DBRecords(record.map,&old); if(exists<0) return;
    before=NITMOD_DBExport(&length); if(!before) return;
    changed=NITMOD_DBUpdateRecords(&record);
    if(changed<0 || !G_NITMOD_DatabaseFlush()) {
        NITMOD_DBOpenWorking(before,length); NITMOD_DBFreeExport(before);
        G_LogPrintf("[SQLite] Map records could not be saved\n"); return;
    }
    NITMOD_DBFreeExport(before);
    for(j=0;j<3;++j) {
        if((changed&(1<<j)) && record.value[j]>0 && (exists || j || record.value[j]>=5)) {
            char name[64]; SafeRecordText(record.holder[j],name,sizeof(name));
            trap_SendServerCommand(-1,va("chat \"^2New Map %s record: ^x%d ^gby ^7%s\" -2",labels[j],record.value[j],name));
        }
        if(exists) G_NITMOD_PrintMapRecords(&old,(1<<j)|((changed&(1<<j))?8:0));
    }
}
