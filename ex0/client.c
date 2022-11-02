#include "client.h"

Client *c = NULL;

Client *connectAsClient(char *ip) {
    Client *c = calloc(sizeof(Client), 1);
    c->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    c->server.sin_family = AF_INET;
    c->server.sin_addr.s_addr = inet_addr(ip);
    c->server.sin_port = htons(8080);
    c->tv.tv_sec = 0;
    c->tv.tv_usec = 0;
    if (connect(c->sock, (struct sockaddr *) &c->server, sizeof(c->server)) < 0) {
        printf("Connection failed\n");
        return NULL;
    }
    return c;
}

int receiveData(Client *c, char *buffer) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(c->sock, &readfds);
    int activity = select(c->sock + 1, &readfds, NULL, NULL, &c->tv);
    if (FD_ISSET(c->sock, &readfds)) {
        int val = recv(c->sock, buffer, BUFF, 0);
        if (val == 0) {
            return -1;
        } else {
            return val;
        }
    }
    return 0;
}
