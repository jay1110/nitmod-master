"""Local UDP/HTTP integration; never contacts the original master server."""
import importlib.util
import json
from pathlib import Path
import socket
import threading
import unittest
from urllib.request import Request, urlopen
from urllib.error import HTTPError
from http.server import ThreadingHTTPServer

spec = importlib.util.spec_from_file_location("bridge", Path(__file__).resolve().parents[1] / "tools/nitmod_global_stats_bridge.py")
bridge = importlib.util.module_from_spec(spec)
spec.loader.exec_module(bridge)
GUID = "PP" + "0"*30  # Valid original NGUID checksum, deliberately not hexadecimal.


class BridgeTest(unittest.TestCase):
    def test_upload_bytes_and_rejection(self):
        udp = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
        udp.bind(("127.0.0.1",0));udp.settimeout(.2)
        origin="http://localhost:18766"
        http=ThreadingHTTPServer(("127.0.0.1",0),bridge.handler(udp.getsockname(),origin))
        worker=threading.Thread(target=http.serve_forever);worker.start()
        url=f"http://127.0.0.1:{http.server_port}/stats"
        payload="ps "+GUID+" "+" ".join(map(str,range(16)))+" ^1Player Name"
        try:
            for bad in [payload.replace(" 15 "," 2147483648 "),payload+"\n",payload.replace(GUID,"bad")]:
                with self.assertRaises(HTTPError) as error:
                    urlopen(Request(url,data=bad.encode(),headers={"Origin":origin}))
                self.assertEqual(error.exception.code,400)
            with self.assertRaises(HTTPError) as error:
                urlopen(Request(url,data=payload.encode(),headers={"Origin":"http://denied"}))
            self.assertEqual(error.exception.code,403)
            with self.assertRaises(socket.timeout):udp.recvfrom(2048)
            with urlopen(Request(url,data=payload.encode(),headers={"Origin":origin})) as response:
                self.assertTrue(json.load(response)["sent"])
            self.assertEqual(udp.recvfrom(2048)[0],b"\xb0"+payload.encode())
            long_payload=payload+"x"*300
            with urlopen(Request(url,data=long_payload.encode(),headers={"Origin":origin})):pass
            self.assertEqual(udp.recvfrom(2048)[0],(b"\xb0"+long_payload.encode())[:255])
        finally:
            http.shutdown();http.server_close();worker.join();udp.close()

    def upstream(self, reply):
        udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        udp.bind(("127.0.0.1", 0)); udp.settimeout(3)
        address = udp.getsockname()
        requests = []
        def run():
            try:
                data, peer = udp.recvfrom(2048); requests.append(data)
                udp.sendto(reply, peer)
            finally:
                udp.close()
        thread = threading.Thread(target=run, daemon=True); thread.start()
        return address, thread, requests

    def test_udp_validation(self):
        valid = b"ps " + GUID.encode() + b" " + b" ".join(str(i).encode() for i in range(15))
        address, thread, requests = self.upstream(valid)
        result = bridge.query_stats(GUID, address); thread.join()
        self.assertEqual(requests, [b"\xb0gsg " + GUID.encode()])
        self.assertEqual(result["values"], list(range(15)))
        for packet in [b"bad", valid.replace(GUID.encode(), b"F"*32), valid+b" 16", valid.replace(b" 14",b" 2147483648")]:
            with self.subTest(packet=packet):
                address, thread, _ = self.upstream(packet)
                with self.assertRaises(ValueError): bridge.query_stats(GUID, address)
                thread.join()

    def test_http_origin_and_udp_round_trip(self):
        packet = b"ps " + GUID.encode() + b" 1"*15
        address, thread, requests = self.upstream(packet)
        http = ThreadingHTTPServer(("127.0.0.1",0), bridge.handler(address,"http://localhost:18766"))
        worker = threading.Thread(target=http.serve_forever,daemon=True); worker.start()
        url = f"http://127.0.0.1:{http.server_port}/stats?guid={GUID}"
        try:
            with self.assertRaises(HTTPError) as error: urlopen(Request(url,headers={"Origin":"http://denied"}))
            self.assertEqual(error.exception.code,403)
            self.assertFalse(requests)
            with urlopen(Request(url,headers={"Origin":"http://localhost:18766"})) as response:
                self.assertEqual(json.load(response)["values"],[1]*15)
                self.assertEqual(response.headers["Cache-Control"],"no-store")
        finally:
            http.shutdown();http.server_close();worker.join();thread.join()


if __name__ == "__main__": unittest.main()
