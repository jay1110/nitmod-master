#ifndef NITMOD_LUA_EVENTS_H
#define NITMOD_LUA_EVENTS_H
/* Include after bg_public.h. Original cgame event domain is 0..106. */
typedef char nitmod_lua_event_fits_wire[(EV_NITMOD_LUA_LAST<256 && ET_EVENTS+EV_NITMOD_LUA_FIRST<256)?1:-1];
static int NITMOD_LuaEventEncode(int original) {
    if(original<0 || original>106) return -1;
    return original?EV_NITMOD_LUA_FIRST+original:0;
}
static int NITMOD_LuaEventDecode(int native) {
    return native>=EV_NITMOD_LUA_FIRST && native<=EV_NITMOD_LUA_LAST?
        native-EV_NITMOD_LUA_FIRST:-1;
}
static int NITMOD_LuaEventServerDispatch(int native) {
    static const int handlers[]={0,
#ifndef NITMOD_EVENT_DEATH4
#define NITMOD_EVENT_DEATH4 -1
#define NITMOD_LUA_LOCAL_DEATH4
#endif
#define X(id,name,handler) handler,
#include "../cgame/cg_nitmod_eventmap.h"
#undef X
#ifdef NITMOD_LUA_LOCAL_DEATH4
#undef NITMOD_EVENT_DEATH4
#undef NITMOD_LUA_LOCAL_DEATH4
#endif
    };
    int original=NITMOD_LuaEventDecode(native);
    if(original<0) return native;
    if(original==95) return EV_NITMOD_THROW_KNIFE;
    if(original==100) return EV_NITMOD_SOUND;
    return original<(int)(sizeof(handlers)/sizeof(handlers[0])) && handlers[original]>=0?handlers[original]:0;
}
#endif
