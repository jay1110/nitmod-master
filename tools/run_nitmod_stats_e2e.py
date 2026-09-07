"""Actual WASM/HTTP/UDP/Lua receive path with a local original-protocol peer."""
from pathlib import Path
from datetime import datetime,timezone
import importlib.util
import json
import socket
import subprocess
import threading
import sys
import hashlib
from http.server import ThreadingHTTPServer
root=Path(__file__).resolve().parents[1]
browser_mode='--browser' in sys.argv
out=root/'build'/('lua-stats-e2e-'+datetime.now(timezone.utc).strftime('%Y%m%dT%H%M%S.%fZ'));out.mkdir()
spec=importlib.util.spec_from_file_location('bridge',root/'tools/nitmod_global_stats_bridge.py')
bridge=importlib.util.module_from_spec(spec);spec.loader.exec_module(bridge)
sources=['tests/test_nitmod_stats_e2e.c','src_2.60/game/g_nitmod_global_stats.c','src_2.60/game/nitmod_stats_transport.c','src_2.60/game/g_nitmod_lua.c','src_2.60/game/nitmod_sha1.c','src_2.60/game/q_shared.c','src_2.60/game/q_math.c']+[str(p.relative_to(root)) for p in sorted((root/'src_2.60/lua51').glob('*.c'))]
cmd=[str(Path.home()/'emsdk/upstream/emscripten/emcc.bat'),*sources,'-Isrc_2.60/game','-DGAMEDLL','-O1','-sASSERTIONS=1','-sALLOW_MEMORY_GROWTH=1','-sEXIT_RUNTIME=1','-sENVIRONMENT=web,node','-o',str(out/'test.js')]
subprocess.run(cmd,cwd=root,check=True)
udp=socket.socket(socket.AF_INET,socket.SOCK_DGRAM);udp.bind(('127.0.0.1',0));udp.settimeout(.2)
stop=threading.Event();packets=[]
def serve_udp():
    while not stop.is_set():
        try: data,peer=udp.recvfrom(2048)
        except socket.timeout: continue
        packets.append(data.hex())
        guid=b'PP'+b'0'*30
        if data==b'\xb0gsg '+guid:
            udp.sendto(b'ps '+guid+b' '+b' '.join(str(i).encode() for i in range(15)),peer)
http=ThreadingHTTPServer(('127.0.0.1',0),bridge.handler(udp.getsockname(),'http://nitmod-test.local'))
browser_done=threading.Event();browser_log=[]
if browser_mode:
    origin=f'http://localhost:{http.server_port}'
    (out/'test.html').write_text(r'''<!doctype html><meta charset="utf-8"><title>Nitmod Lua transport acceptance</title><pre id="output">Running WASM acceptance...\n</pre><script>
    const output=document.getElementById('output');
    var Module={arguments:[location.origin],print(t){output.textContent+=t+'\n';if(t.includes('cancellation: PASS'))fetch('/result',{method:'POST',body:output.textContent});},printErr(t){output.textContent+=t+'\n';},onAbort(t){output.textContent+='FAIL: '+t;fetch('/result',{method:'POST',body:output.textContent});}};
    </script><script src="/test.js"></script>''')
    page=(out/'test.html').read_text().replace('arguments:[location.origin]',
        'arguments:['+json.dumps(f'http://127.0.0.1:{http.server_port}')+']')
    (out/'test.html').write_text(page)
    class BrowserHandler(bridge.handler(udp.getsockname(),origin)):
        def do_GET(self):
            if self.path in ('/test.html','/test.js','/test.wasm'):
                data=(out/self.path[1:]).read_bytes();self.send_response(200)
                self.send_header('Content-Type',{'/test.html':'text/html','/test.js':'text/javascript','/test.wasm':'application/wasm'}[self.path])
                self.send_header('Content-Length',str(len(data)));self.end_headers();self.wfile.write(data)
            else: super().do_GET()
        def do_POST(self):
            if self.path=='/stats':
                super().do_POST();return
            if self.path!='/result' or self.headers.get('Origin')!=origin:
                self.send_error(403);return
            length=int(self.headers.get('Content-Length','0'))
            if not 0<length<100000:self.send_error(400);return
            browser_log.append(self.rfile.read(length).decode());self.send_response(204);self.end_headers();browser_done.set()
    http.RequestHandlerClass=BrowserHandler
workers=[threading.Thread(target=serve_udp),threading.Thread(target=http.serve_forever)]
for worker in workers:worker.start()
try:
    if browser_mode:
        print(f'BROWSER_TEST_URL={origin}/test.html',flush=True)
        browser_done.wait(180)
        log='\n'.join(browser_log)
        result=subprocess.CompletedProcess([],0 if 'cancellation: PASS' in log and 'FAIL:' not in log else 1,log,'')
    else:
        result=subprocess.run(['node',str(out/'test.js'),f'http://127.0.0.1:{http.server_port}'],cwd=root,capture_output=True,text=True,timeout=20)
finally:
    http.shutdown();http.server_close();stop.set()
    for worker in workers:worker.join()
    udp.close()
expected_upload=b'\xb0ps '+b'PP'+b'0'*30+b' 0 0 0 2 1 0 0 0 0 0 0 0 0 0 0 0 E2E Player'
if packets.count(expected_upload.hex())!=1:
    result=subprocess.CompletedProcess(result.args,1,result.stdout,result.stderr+'Expected exactly one original upload packet\n')
manifest=sources+['tools/nitmod_global_stats_bridge.py','src_2.60/game/nitmod_global_awards.h','src_2.60/game/g_nitmod_global_stats.h','src_2.60/game/nitmod_stats_transport.h','tools/run_nitmod_stats_e2e.py']
(out/'result.json').write_text(json.dumps(dict(command=cmd,exit_code=result.returncode,stdout=result.stdout,stderr=result.stderr,udp_requests=packets,sources={s:hashlib.sha256((root/s).read_bytes()).hexdigest() for s in manifest}),indent=2))
print(result.stdout+result.stderr);print(out)
raise SystemExit(result.returncode)
