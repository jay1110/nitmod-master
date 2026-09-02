/* Minimal, intentionally unauthenticated health endpoint for the Nitmod web
 * companion. Privileged bridge operations are added only with authentication
 * and an explicit request schema; never expose game-server control by default. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET socket_t;
#define close_socket closesocket
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
typedef int socket_t;
#define INVALID_SOCKET (-1)
#define close_socket close
#endif

static const char response[] =
    "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n"
    "Cache-Control: no-store\r\nConnection: close\r\n\r\n"
    "{\"protocol\":1,\"service\":\"nitmod-companion\",\"capabilities\":[]}";

int main(int argc, char **argv) {
    int port = 27961;
    struct sockaddr_in address;
    socket_t listener;

    if (argc == 3 && strcmp(argv[1], "--port") == 0) {
        port = atoi(argv[2]);
    }
    if (port < 1 || port > 65535) {
        fprintf(stderr, "usage: %s [--port 1..65535]\n", argv[0]);
        return 2;
    }
#ifdef _WIN32
    { WSADATA data; if (WSAStartup(MAKEWORD(2, 2), &data) != 0) return 1; }
#endif
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener == INVALID_SOCKET) return 1;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons((unsigned short)port);
    if (bind(listener, (struct sockaddr *)&address, sizeof(address)) != 0 || listen(listener, 8) != 0) {
        close_socket(listener);
        return 1;
    }
    fprintf(stderr, "nitmod companion listening on http://127.0.0.1:%d/v1/capabilities\n", port);
    for (;;) {
        socket_t peer = accept(listener, NULL, NULL);
        if (peer == INVALID_SOCKET) continue;
        send(peer, response, (int)(sizeof(response) - 1), 0);
        close_socket(peer);
    }
}
