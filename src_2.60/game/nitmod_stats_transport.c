#include "nitmod_stats_transport.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
/* Copy the packet before returning: disconnect may immediately reuse the slot.
 * keepalive lets map shutdown complete while the bounded HTTP request drains. */
EM_JS(int,NITMOD_StatsUpload,(const char *url,const char *packet),{
    let target;
    try { target=new URL(UTF8ToString(url));if(!["http:","https:"].includes(target.protocol)) return 0; }
    catch(e) { return 0; }
    target.pathname=(target.pathname.endsWith("/")?target.pathname.slice(0,-1):target.pathname)+"/stats";
    target.search="";target.hash="";
    const body=UTF8ToString(packet),controller=new AbortController();
    const timer=setTimeout(()=>controller.abort(),5000);
    fetch(target.href,{method:"POST",body,credentials:"omit",cache:"no-store",keepalive:true,signal:controller.signal})
        .catch(()=>{}).finally(()=>clearTimeout(timer));
    return 1;
});
/* Async callbacks touch JS-owned data only. C polls on the game thread; slot
 * replacement and shutdown abort requests before any state can be reused. */
EM_JS(int,NITMOD_StatsStart,(int client,const char *url,const char *guid),{
    const slots=globalThis.__nitmodStatsRequests ||= Object.create(null);
    if(slots[client]) slots[client].controller.abort();
    const item={controller:new AbortController(),status:0,text:""}; slots[client]=item;
    let target;
    try { target=new URL(UTF8ToString(url)); if(!["http:","https:"].includes(target.protocol)) throw 0; }
    catch(e) { delete slots[client]; return 0; }
    target.pathname=(target.pathname.endsWith("/")?target.pathname.slice(0,-1):target.pathname)+"/stats";
    target.search="";target.searchParams.set("guid",UTF8ToString(guid));target.hash="";
    const timer=setTimeout(()=>item.controller.abort(),5000);
    fetch(target.href,{signal:item.controller.signal,credentials:"omit",cache:"no-store"})
      .then(async response=>{
        if(!response.ok) throw new Error("stats response");
        const body=await response.text(); if(body.length>4096) throw new Error("stats size");
        const data=JSON.parse(body);
        if(typeof data.payload!=="string" || data.payload.length>1023) throw new Error("stats payload");
        item.text=data.payload; item.status=1;
      }).catch(()=>{item.status=-1;}).finally(()=>clearTimeout(timer));
    return 1;
});
EM_JS(int,NITMOD_StatsRead,(int client,char *out,int size),{
    const slots=globalThis.__nitmodStatsRequests;const item=slots?.[client];
    if(!item || !item.status) return 0;
    delete slots[client];
    if(item.status<0 || lengthBytesUTF8(item.text)>=size) return -1;
    stringToUTF8(item.text,out,size);return 1;
});
EM_JS(void,NITMOD_StatsCancel,(int client),{
    const slots=globalThis.__nitmodStatsRequests;const item=slots?.[client];
    if(item) { delete slots[client];item.controller.abort(); }
});
#else
int NITMOD_StatsUpload(const char *url,const char *packet) { return 0; }
int NITMOD_StatsStart(int client,const char *url,const char *guid) { return 0; }
int NITMOD_StatsRead(int client,char *out,int size) { return -1; }
void NITMOD_StatsCancel(int client) {}
#endif
