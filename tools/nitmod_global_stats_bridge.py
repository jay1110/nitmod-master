"""Explicitly configured HTTP-to-original-UDP adapter; loopback by default.

No database is synthesized. Only a matching response from the configured UDP
peer is returned. The browser origin must be supplied by the host operator.
"""
import argparse
import json
import re
import socket
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from urllib.parse import parse_qs, urlsplit

GUID = re.compile(r"[0-9a-zA-Z]{32}\Z")
INTEGER = re.compile(r"[+-]?[0-9]+\Z")


def query_stats(guid, upstream, timeout=3):
    if not GUID.fullmatch(guid):
        raise ValueError("invalid GUID")
    # Original cl_sin port bytes 21 1b = network port 8475.
    # connect() restricts accepted UDP replies to the resolved peer.
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp:
        udp.settimeout(timeout)
        udp.connect(upstream)
        udp.send(b"\xb0gsg " + guid.encode("ascii"))
        packet = udp.recv(1401)
    if len(packet) > 1400 or not packet.startswith(b"ps "):
        raise ValueError("invalid upstream packet")
    payload = packet[3:].rstrip(b"\x00").decode("ascii")
    tokens = payload.split()
    if len(tokens) != 16 or tokens[0].lower() != guid.lower():
        raise ValueError("upstream identity or field count mismatch")
    values = []
    for token in tokens[1:]:
        if not INTEGER.fullmatch(token):
            raise ValueError("invalid statistic")
        value = int(token)
        if not -(2**31) <= value < 2**31:
            raise ValueError("statistic overflow")
        values.append(value)
    return {"guid": guid, "values": values, "payload": payload}


def handler(upstream, origin):
    class Handler(BaseHTTPRequestHandler):
        def log_message(self, *_):
            pass  # Do not write player identifiers into access logs.

        def reply(self, status, value):
            data = json.dumps(value).encode("utf-8")
            self.send_response(status)
            self.send_header("Content-Type", "application/json")
            self.send_header("Content-Length", str(len(data)))
            self.send_header("Cache-Control", "no-store")
            self.send_header("Access-Control-Allow-Origin", origin)
            self.send_header("Vary", "Origin")
            self.end_headers()
            self.wfile.write(data)

        def do_GET(self):
            if self.headers.get("Origin") != origin:
                self.reply(403, {"error": "origin denied"})
                return
            target = urlsplit(self.path)
            params = parse_qs(target.query)
            if target.path != "/stats" or set(params) != {"guid"} or len(params["guid"]) != 1:
                self.reply(400, {"error": "expected /stats?guid=<32 alphanumeric characters>"})
                return
            guid = params["guid"][0]
            if not GUID.fullmatch(guid):
                self.reply(400, {"error": "invalid GUID"})
                return
            try:
                self.reply(200, query_stats(guid, upstream))
            except (OSError, ValueError, UnicodeError):
                self.reply(502, {"error": "upstream unavailable or invalid"})

        def do_POST(self):
            if self.headers.get("Origin") != origin:
                self.reply(403, {"error": "origin denied"}); return
            if self.path != "/stats":
                self.reply(400, {"error": "expected /stats"}); return
            try:
                length = int(self.headers.get("Content-Length", "0"))
                if not 0 < length <= 1024:
                    raise ValueError("invalid body length")
                payload = self.rfile.read(length).decode("utf-8")
                parts = payload.split(" ", 18)
                if len(parts) != 19 or parts[0] != "ps" or not GUID.fullmatch(parts[1]):
                    raise ValueError("invalid upload")
                for token in parts[2:18]:
                    if not INTEGER.fullmatch(token) or not -(2**31) <= int(token) < 2**31:
                        raise ValueError("invalid statistic")
                if any(ord(c)<32 for c in parts[18]):
                    raise ValueError("invalid name")
                # Match the original 256-byte Q_strcat destination including
                # its prefix and terminating NUL; UDP excludes the NUL.
                packet = (b"\xb0" + payload.encode("utf-8"))[:255]
                with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as udp:
                    udp.connect(upstream); udp.send(packet)
                self.reply(200, {"sent": True})
            except (ValueError, UnicodeError):
                self.reply(400, {"error": "invalid upload"})
            except OSError:
                self.reply(502, {"error": "upstream unavailable"})
    return Handler


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--origin", required=True, help="exact permitted browser origin")
    parser.add_argument("--bind", default="127.0.0.1")
    parser.add_argument("--port", type=int, default=18767)
    parser.add_argument("--upstream-host", default="master.etmods.net")
    parser.add_argument("--upstream-port", type=int, default=8475)
    args = parser.parse_args()
    ThreadingHTTPServer((args.bind, args.port), handler(
        (args.upstream_host, args.upstream_port), args.origin)).serve_forever()
