"""Isolated browser integration run; overlays HTML in memory, never edits engine/paks."""
from serve_nitmod_sqlite_acceptance import Handler as AssetHandler,ENGINE,ROOT
from http.server import ThreadingHTTPServer
from datetime import datetime,timezone
from urllib.parse import urlsplit
import json, argparse, zipfile, hashlib

LUA = """et.RegisterModname('Nitmod Lua acceptance')
local frames=0
local active=false
local demoChecked=false
local function log(s) et.G_Print('LUA_ACCEPT '..s..'\\n') end
local pong=false
function et_IPCReceive(sender,msg) assert(sender==1 and msg=='pong');pong=true end
function et_InitGame(t,s,r)
 log('INIT '..t..' '..r)
 assert(et.IPCSend(1,'ping')==1 and pong);log('IPC_PASS')
 local path='lua_acceptance_data/probe.lua'
 local text="#!/usr/bin/lua\\nreturn 42,'engine-vfs'"
 local f=et.trap_FS_FOpenFile(path,et.FS_WRITE);assert(f>0)
 assert(et.trap_FS_Write(text,#text,f)==#text);et.trap_FS_FCloseFile(f)
 local n;f,n=et.trap_FS_FOpenFile(path,et.FS_READ);assert(f>0 and n==#text)
 assert(et.trap_FS_Read(f,n)==text);et.trap_FS_FCloseFile(f)
 local loaded=assert(loadfile(path));assert(debug.getinfo(loaded).source=='@'..path);assert(loaded()==42)
 local a,b=dofile(path);assert(a==42 and b=='engine-vfs')
 package.path='lua_acceptance_data/?.lua';assert(require('probe')==42)
 local data='#!/usr/bin/lua\\n'..string.dump(function() return 42 end)
 local binary='lua_acceptance_data/probe.luac'
 f=et.trap_FS_FOpenFile(binary,et.FS_WRITE);assert(f>0)
 assert(et.trap_FS_Write(data,#data,f)==#data);et.trap_FS_FCloseFile(f)
 assert(assert(loadfile(binary))()==42)
 log('VFS_PASS')
end
function et_ClientConnect(c,f,b) log('CONNECT '..c..' '..f..' '..b) end
function et_ClientBegin(c) local d=tonumber(et.trap_Cvar_Get('sv_demoState')) or 0;local n=tonumber(et.trap_Cvar_Get('sv_demoClients')) or 0;assert(not(d>=1 and d<=3 and c<n),'begin for recorded client');log('BEGIN '..c) end
function et_ClientSpawn(c,r,t,h) log('SPAWN '..c..' '..r..' '..t..' '..h) end
function et_RunFrame(t)
 if not demoChecked and tonumber(et.trap_Cvar_Get('sv_demoState'))==2 and tonumber(et.trap_Cvar_Get('sv_demoClients'))>0 and et.gentity_get(0,'pers.connected')==2 then
  assert(et.gentity_get(0,'pers.netname')=='ETLegacyPlayer');demoChecked=true;log('DEMO_PASS 0 '..et.trap_Cvar_Get('sv_demoClients'))
 end
 frames=frames+1; if frames==60 then log('FRAMES '..t) end; if not active and et.gentity_get(0,'sess.sessionTeam')==2 and et.gentity_get(0,'health')>0 then active=true; log('ACTIVE '..et.gentity_get(0,'health')) end end
function et_ConsoleCommand(c)
 if c=='lua_accept_probe' then log('CONSOLE'); return 1 end
 if c=='lua_accept_afterrevive' then
  assert(et.gentity_get(0,'health')>0);assert(et.gentity_get(0,'ps.persistant',11)>0)
  log('REVIVE_PASS '..et.gentity_get(0,'health'));return 1
 end
 if c=='lua_accept_respawn' then
  et.gentity_set(0,'ps.powerups',1,0);et.G_Damage(0,1022,1022,9999,0,31);log('RESPAWN_DEAD');return 1
 end
 if c=='lua_accept_damage' then
  local before=et.gentity_get(0,'health');et.gentity_set(0,'ps.powerups',1,0);et.gentity_set(0,'ps.powerups',11,600000)
  et.G_Damage(0,1022,1022,20,0,65);local after=et.gentity_get(0,'health')
  assert(before-after==10,'adrenaline damage mismatch '..before..' '..after)
  log('DAMAGE_PASS '..before..' '..after);et.gentity_set(0,'ps.powerups',11,0)
  et.G_Damage(0,1022,1022,150,0,31);log('DEAD '..et.gentity_get(0,'health'));return 1
 end
end
function et_Obituary(v,k,m) log('OBITUARY '..v..' '..k..' '..m) end
function et_ClientCommand(c,cmd) if cmd=='lua_accept_client' then log('CLIENTCOMMAND '..c); return 1 end end
function et_ShutdownGame(r) log('SHUTDOWN '..r) end
function et_Quit() log('QUIT') end
"""

PEER = """et.RegisterModname('Nitmod Lua IPC peer')
assert(et.FindSelf()==1)
function et_IPCReceive(sender,msg)
 assert(sender==0 and msg=='ping');assert(et.IPCSend(0,'pong')==1)
end
"""

class Handler(AssetHandler):
    def end_headers(self):
        self.send_header("Cache-Control", "no-store")
        super().end_headers()
    def do_POST(self):
        if urlsplit(self.path).path!='/acceptance-log/'+self.server.output.name: self.send_error(404);return
        size=int(self.headers.get('Content-Length','0'))
        if size<0 or size>262144:self.send_error(413);return
        data=json.loads(self.rfile.read(size))
        with (self.server.output/'browser.jsonl').open('a',encoding='utf-8') as f:f.write(json.dumps(data)+'\n')
        self.send_response(204);self.end_headers()
    def do_GET(self):
        if urlsplit(self.path).path=='/mirror/nitmod/'+self.server.packname:
            raw=(self.server.output/self.server.packname).read_bytes()
            self.send_response(200);self.send_header('Content-Type','application/zip');self.send_header('Content-Length',str(len(raw)));self.end_headers();self.wfile.write(raw);return
        if urlsplit(self.path).path!='/lua-acceptance.html':return super().do_GET()
        html=(ENGINE/'etl.html').read_text(encoding='utf-8')
        html=html.replace("args.push('+map', mapParam);","args.push('+devmap', mapParam);",1)
        html=html.replace('function ensureGameData() {','function ensureGameData() { return downloadAllPaks();',1)
        html=html.replace('var args = [];',"var args = ['+set','fs_game','nitmod','+set','sv_public','0','+set','g_warmup','0','+set','g_doWarmup','0','+set','g_blueLimboTime','1000','+set','sv_master1','','+set','sv_master2','','+set','sv_master3','','+set','sv_master4','','+set','sv_master5','','+set','lua_modules','lua_acceptance.lua','+set','lua_allowedModules',''];",1)
        html=html.replace('return downloadModAssets();',"return downloadModAssets().then(function(){return installMod('nitmod');}).then(function(){Module.FS.mkdirTree('/home/web_user/.etlegacy/nitmod');Module.FS.writeFile('/home/web_user/.etlegacy/nitmod/lua_acceptance.lua',"+json.dumps(LUA)+");});",1)
        exports=json.loads((ROOT/'reference/acceptance/lua-original-exports.json').read_text())['exports']
        check='for _,name in ipairs({'+','.join(json.dumps(x) for x in exports)+'}) do assert(type(et[name])==\"function\",name) end\n'
        html=html.replace(json.dumps(LUA),json.dumps(check+LUA))
        html=html.replace("'lua_modules','lua_acceptance.lua'", "'lua_modules','lua_acceptance.lua,lua_acceptance_peer.lua'")
        html=html.replace("Module.FS.mkdirTree('/home/web_user/.etlegacy/nitmod');", "Module.FS.mkdirTree('/home/web_user/.etlegacy/nitmod');Module.FS.writeFile('/home/web_user/.etlegacy/nitmod/lua_acceptance_peer.lua',"+json.dumps(PEER)+");")
        telemetry="""<script>
        (function(){var playback=new URLSearchParams(location.search).has('serverdemo'),demoFinished=false;var pending=[],probed=playback,damaged=playback,ended=playback,respawn=playback,quitting=false;function finish(){etlSendCommand('lua_status');etlSendCommand('set lua_allowedModules DENY');setTimeout(function(){etlSendCommand('lua_status');quitting=true;if(playback)etlSendCommand('demo_stop');etlSendCommand('quit');},2000);}function record(kind,text){if(playback && !demoFinished && String(text).indexOf('LUA_ACCEPT DEMO_PASS')>=0){demoFinished=true;setTimeout(finish,500);}if(!damaged && String(text).indexOf('LUA_ACCEPT ACTIVE')>=0){damaged=true;etlSendCommand('lua_accept_damage');}if(!ended && String(text).indexOf('LUA_ACCEPT DEAD')>=0){ended=true;etlSendCommand('revive ETLegacyPlayer');setTimeout(function(){etlSendCommand('lua_accept_afterrevive');},1500);}if(!respawn && String(text).indexOf('LUA_ACCEPT REVIVE_PASS')>=0){respawn=true;etlSendCommand('lua_accept_respawn');etlSendCommand('forcetapout');setTimeout(function(){if(DEMO_MODE){etlSendCommand('demo_record lua_acceptance');setTimeout(function(){etlSendCommand('demo_stop');etlSendCommand('demo_play lua_acceptance');setTimeout(function(){etlSendCommand('demo_stop');setTimeout(finish,2000);},10000);},10000);}else finish();},12000);}if(!probed && String(text).indexOf('LUA_ACCEPT FRAMES')>=0){probed=true;etlSendCommand('lua_status');etlSendCommand('lua_accept_probe');etlSendCommand('cmd lua_accept_client');etlSendCommand('team b');}pending.push({kind:kind,text:String(text),time:Date.now()});}
        ['print','printErr'].forEach(function(name){var prior=Module[name];Module[name]=function(text){record(name,text);if(prior)prior(text);};});
        window.alert=function(message){record('error',String(message)+' STACK '+new Error().stack);};
        window.addEventListener('error',function(e){record('error',e.message);});
        window.addEventListener('unhandledrejection',function(e){record('rejection',e.reason);});
        var status=Module.setStatus;Module.setStatus=function(text){record('status',text);return status(text);};
        setInterval(function(){if(pending.length){var batch=pending.splice(0);fetch('/acceptance-log',{method:'POST',headers:{'Content-Type':'application/json'},body:JSON.stringify(batch)});}},1000);
        window.luaAcceptanceCommand=function(text){etlSendCommand(text);};window.addEventListener('pagehide',function(){if(pending.length)navigator.sendBeacon('/acceptance-log',JSON.stringify(pending.splice(0)));});
        })();</script>"""
        telemetry=telemetry.replace("DEMO_MODE",str(self.server.demo).lower())
        telemetry=telemetry.replace("'/acceptance-log'",json.dumps('/acceptance-log/'+self.server.output.name))
        html=html.replace('<script async type="text/javascript" src="etl.js"></script>',telemetry+'<script async type="text/javascript" src="etl.js"></script>')
        raw=html.encode();self.send_response(200);self.send_header('Content-Type','text/html; charset=utf-8');self.send_header('Cache-Control','no-store');self.send_header('Content-Length',str(len(raw)));self.end_headers();self.wfile.write(raw)

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--port',type=int,default=18768);parser.add_argument('--demo',action='store_true');args=parser.parse_args()
    out=ROOT/'build'/('lua-browser-'+datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S.%fZ'));out.mkdir()
    packname='nitmod_lua_acceptance_'+out.name.removeprefix('lua-browser-')+'.pk3'
    with zipfile.ZipFile(out/packname,'x',zipfile.ZIP_DEFLATED) as pak:
        for name in ('qagame','cgame','ui'):
            filename=name+'.mp.wasm32.so';pak.write(ROOT/'build/wasm'/filename,filename)
    (out/'run.json').write_text(json.dumps({'demo':args.demo,'engine_exit_workaround':False,'engine':{name:hashlib.sha256((ENGINE/name).read_bytes()).hexdigest() for name in ('etl.js','etl.wasm')}}))
    (out/'modules.json').write_text(json.dumps({name:hashlib.sha256((ROOT/'build/wasm'/(name+'.mp.wasm32.so')).read_bytes()).hexdigest() for name in ('qagame','cgame','ui')},indent=2))
    server=ThreadingHTTPServer(('127.0.0.1',args.port),Handler);server.output=out;server.packname=packname;server.demo=args.demo
    print(out,flush=True);print(f'http://127.0.0.1:{args.port}/lua-acceptance.html?map=oasis&nitmodpk3=nitmod_2.3.5.pk3,{packname}&mirror=http://127.0.0.1:{args.port}/mirror/',flush=True)
    server.serve_forever()
