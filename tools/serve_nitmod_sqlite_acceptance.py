"""Read-only local browser acceptance server; leaves engine and game packs intact.

Serves the existing sibling ET:Legacy build and overlays only the three active
Nitmod modules. Public mirror assets are streamed through the same local origin.
"""
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
from urllib.parse import unquote, urlsplit
from urllib.request import Request, urlopen
import argparse
import shutil

ROOT = Path(__file__).resolve().parents[1]
ENGINE = ROOT.parent / 'etlegacy' / 'build-wasm'


class Handler(SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=str(ENGINE), **kwargs)

    def do_GET(self):
        path = unquote(urlsplit(self.path).path)
        if path.startswith('/mirror/'):
            relative = path[len('/mirror/'):]
            if '..' in relative or '\\' in relative or ':' in relative:
                self.send_error(400)
                return
            if relative.startswith('nitmod/') and relative.split('/')[-1] in {
                'cgame.mp.wasm32.so', 'qagame.mp.wasm32.so', 'ui.mp.wasm32.so'
            }:
                source = ROOT / 'build/wasm' / relative.split('/')[-1]
                self.send_response(200)
                self.send_header('Content-Type', 'application/wasm')
                self.send_header('Content-Length', str(source.stat().st_size))
                self.send_header('Cache-Control', 'no-store')
                self.end_headers()
                with source.open('rb') as stream:
                    shutil.copyfileobj(stream, self.wfile)
                return
            try:
                with urlopen(Request('https://etclan.de/etl/' + relative), timeout=60) as stream:
                    self.send_response(200)
                    for name in ('Content-Type', 'Content-Length'):
                        if stream.headers.get(name):
                            self.send_header(name, stream.headers[name])
                    self.end_headers()
                    shutil.copyfileobj(stream, self.wfile)
            except OSError:
                self.send_error(502, 'Public mirror asset unavailable')
            return
        super().do_GET()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--port', type=int, default=18766)
    args = parser.parse_args()
    if not (ENGINE / 'etl.html').is_file():
        parser.error('Existing ET:Legacy browser build is missing')
    print(f'http://127.0.0.1:{args.port}/etl.html?mirror=http://127.0.0.1:{args.port}/mirror/', flush=True)
    ThreadingHTTPServer(('127.0.0.1', args.port), Handler).serve_forever()
