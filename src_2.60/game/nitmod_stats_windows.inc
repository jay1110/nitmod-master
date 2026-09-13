/* Windows bridge transport. Workers own WinHTTP handles; game thread owns jobs.
 * Cancellation joins before freeing memory or unloading this module. */
#include <windows.h>
#include <winhttp.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#ifdef _MSC_VER
#pragma comment(lib,"winhttp.lib")
#endif
#define STATS_JOBS 64
typedef struct statsJob_s {
    struct statsJob_s *next;
    HANDLE thread;
    volatile LONG cancel;
    int ok,post;
    char url[2048],body[1024],response[4097];
} statsJob_t;
static statsJob_t *queries[STATS_JOBS],*uploads[STATS_JOBS],*retired;
static int liveJobs;
static DWORD WINAPI StatsWorker(void *opaque) {
    statsJob_t *j=(statsJob_t *)opaque;
    WCHAR url[2048],host[1024],path[2048];
    URL_COMPONENTS u;
    HINTERNET session=NULL,connection=NULL,request=NULL;
    DWORD status=0,size=sizeof(status),got=0,total=0,started=GetTickCount();
    if(!MultiByteToWideChar(CP_UTF8,MB_ERR_INVALID_CHARS,j->url,-1,url,2048)) return 0;
    memset(&u,0,sizeof(u));u.dwStructSize=sizeof(u);
    u.lpszHostName=host;u.dwHostNameLength=1024;
    u.lpszUrlPath=path;u.dwUrlPathLength=2048;u.dwExtraInfoLength=(DWORD)-1;
    if(!WinHttpCrackUrl(url,0,0,&u) || (u.nScheme!=INTERNET_SCHEME_HTTP && u.nScheme!=INTERNET_SCHEME_HTTPS)) return 0;
    if(u.dwExtraInfoLength) {
        if(wcslen(path)+u.dwExtraInfoLength>=2048) return 0;
        wcsncat(path,u.lpszExtraInfo,u.dwExtraInfoLength);
    }
    session=WinHttpOpen(L"Nitmod",WINHTTP_ACCESS_TYPE_NO_PROXY,NULL,NULL,0);
    if(!session) goto done;
    if(!WinHttpSetTimeouts(session,5000,5000,5000,5000)) goto done;
    connection=WinHttpConnect(session,host,u.nPort,0);if(!connection) goto done;
    request=WinHttpOpenRequest(connection,j->post?L"POST":L"GET",path,NULL,NULL,NULL,
        u.nScheme==INTERNET_SCHEME_HTTPS?WINHTTP_FLAG_SECURE:0);
    if(!request || InterlockedCompareExchange(&j->cancel,0,0)) goto done;
    /* No automatic authentication or redirection of upload bodies. */
    status=WINHTTP_DISABLE_REDIRECTS|WINHTTP_DISABLE_COOKIES|WINHTTP_DISABLE_AUTHENTICATION;
    if(!WinHttpSetOption(request,WINHTTP_OPTION_DISABLE_FEATURE,&status,sizeof(status))) goto done;
    if(!WinHttpSendRequest(request,NULL,0,j->post?j->body:NULL,
        j->post?(DWORD)strlen(j->body):0,j->post?(DWORD)strlen(j->body):0,0)) goto done;
    if(InterlockedCompareExchange(&j->cancel,0,0) || !WinHttpReceiveResponse(request,NULL)) goto done;
    if(!WinHttpQueryHeaders(request,WINHTTP_QUERY_STATUS_CODE|WINHTTP_QUERY_FLAG_NUMBER,NULL,&status,&size,NULL)
        || status<200 || status>=300) goto done;
    if(j->post) { j->ok=1;goto done; }
    do {
        if(InterlockedCompareExchange(&j->cancel,0,0) || total==4096 || GetTickCount()-started>5000) goto done;
        if(!WinHttpReadData(request,j->response+total,4096-total,&got)) goto done;
        total+=got;
    } while(got);
    j->response[total]=0;j->ok=1;
done:
    if(request) WinHttpCloseHandle(request);
    if(connection) WinHttpCloseHandle(connection);
    if(session) WinHttpCloseHandle(session);
    return 0;
}
static void StatsFree(statsJob_t *j) {
    if(!j) return;
    InterlockedExchange(&j->cancel,1);
    WaitForSingleObject(j->thread,INFINITE);CloseHandle(j->thread);free(j);--liveJobs;
}
/* Canceled workers own their storage until completion. Never join an active
 * request from a player disconnect or replacement on the game thread. */
static void StatsReap(void) {
    statsJob_t **link=&retired,*j;
    while((j=*link)!=NULL) {
        if(WaitForSingleObject(j->thread,0)==WAIT_OBJECT_0) {
            *link=j->next;StatsFree(j);
        } else link=&j->next;
    }
}
static statsJob_t *StatsLaunch(const char *url,const char *body,const char *guid) {
    statsJob_t *j;size_t n;
    StatsReap();
    if(liveJobs>=STATS_JOBS*4) return NULL;
    if(!url || strlen(url)>1900 || (body && strlen(body)>=1024)) return NULL;
    j=(statsJob_t *)calloc(1,sizeof(*j));if(!j) return NULL;
    strcpy(j->url,url);n=strcspn(j->url,"?#");j->url[n]=0;
    if(n && j->url[n-1]=='/') j->url[--n]=0;
    strcat(j->url,"/stats");
    if(guid) { if(strlen(guid)!=32 || strspn(guid,"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz")!=32) { free(j);return NULL; }
        strcat(j->url,"?guid=");strcat(j->url,guid); }
    if(body) { strcpy(j->body,body);j->post=1; }
    j->thread=CreateThread(NULL,0,StatsWorker,j,0,NULL);
    if(!j->thread) { free(j);return NULL; }++liveJobs;return j;
}
int NITMOD_StatsUpload(const char *url,const char *packet) {
    int i;
    for(i=0;i<STATS_JOBS;++i) {
        if(uploads[i] && WaitForSingleObject(uploads[i]->thread,0)==WAIT_OBJECT_0) { StatsFree(uploads[i]);uploads[i]=NULL; }
        if(!uploads[i]) { uploads[i]=StatsLaunch(url,packet,NULL);return uploads[i]!=NULL; }
    }return 0;
}
void NITMOD_StatsCancel(int client) {
    statsJob_t *j;
    if(client>=0 && client<STATS_JOBS && (j=queries[client])!=NULL) {
        queries[client]=NULL;
        InterlockedExchange(&j->cancel,1);
        j->next=retired;retired=j;
    }
    StatsReap();
}
void NITMOD_StatsShutdown(void) {
    int i;
    for(i=0;i<STATS_JOBS;++i) NITMOD_StatsCancel(i);
    while(retired) {
        statsJob_t *j=retired;retired=j->next;StatsFree(j);
    }
    /* Only module shutdown must drain unrelated uploads. */
    for(i=0;i<STATS_JOBS;++i) if(uploads[i]) {
        WaitForSingleObject(uploads[i]->thread,INFINITE);StatsFree(uploads[i]);uploads[i]=NULL;
    }
}
int NITMOD_StatsStart(int client,const char *url,const char *guid) {
    if(client<0 || client>=STATS_JOBS) return 0;
    NITMOD_StatsCancel(client);queries[client]=StatsLaunch(url,NULL,guid);return queries[client]!=NULL;
}
/* Bridge payload consists solely of GUID, whitespace and integer tokens. */
int NITMOD_StatsRead(int client,char *out,int size) {
    statsJob_t *j;char *p;int n=0,result=-1;
    if(client<0 || client>=STATS_JOBS || !(j=queries[client])) return 0;
    if(WaitForSingleObject(j->thread,0)!=WAIT_OBJECT_0) return 0;
    if(!j->ok || !out || size<1) goto done;
    p=strstr(j->response,"\"payload\"");if(!p) goto done;p+=9;
    while(*p==' ' || *p=='\t' || *p=='\r' || *p=='\n') ++p;
    if(*p++!=':') goto done;
    while(*p==' ' || *p=='\t' || *p=='\r' || *p=='\n') ++p;
    if(*p++!='\"') goto done;
    while(*p && *p!='\"') {
        char c=*p++;
        if(c=='\\') { c=*p++;if(c=='n') c='\n';else if(c=='r') c='\r';else if(c=='t') c='\t';else goto done; }
        if(n>=size-1) goto done;out[n++]=c;
    }
    if(*p!='\"') goto done;out[n]=0;result=1;
done:
    StatsFree(j);queries[client]=NULL;return result;
}
