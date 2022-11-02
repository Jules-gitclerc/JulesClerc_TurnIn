#include "server.h"

Server *s = NULL;
void *welcomeMessage = NULL;
int welcomeSize = 0;

Server *setUpServerConnection() {
    Server *s = calloc(sizeof(Server), 1);
    s->sock = socket(AF_INET, SOCK_STREAM, 0);
    s->addr.sin_family = AF_INET;
    s->addr.sin_addr.s_addr = INADDR_ANY;
    s->addr.sin_port = htons(8080);
    s->addrlen = sizeof(s->addr);
    s->maxClients = 5;
    s->clientSocks = calloc(sizeof(int), s->maxClients);
    s->tv.tv_sec = 0;
    s->tv.tv_usec = 0;
    bind(s->sock, (struct sockaddr *) &s->addr, s->addrlen);
    listen(s->sock, s->maxClients);
    return s;
}

void closeServer(Server *s) {
    for (int i = 0; i < s->maxClients; i++) {
        if (s->clientSocks[i] != 0) {
            close(s->clientSocks[i]);
        }
    }
    close(s->sock);
    free(s->clientSocks);
    free(s);
}


int serverSendReceive(Server *s, void *buffer) {
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(s->sock, &readfds);

    for (int i = 0; i < s->maxClients; i++) {
        if (s->clientSocks[i] != 0) {
            FD_SET(s->clientSocks[i], &readfds);
        }
    }

    int activity = select(s->maxClients + 1, &readfds, NULL, NULL, &s->tv);
    if (FD_ISSET(s->sock, &readfds)) {
        int newSock = accept(s->sock, (struct sockaddr *) &s->addr, (socklen_t *) &s->addrlen);
        for (int i = 0; i < s->maxClients; i++) {
            if (s->clientSocks[i] == 0) {
                s->clientSocks[i] = newSock;
                send(s->clientSocks[i], welcomeMessage, welcomeSize, 0);
                break;
            }
        }
    }
    int val = 0;
    for (int i = 0; i < s->maxClients; i++) {
        if (FD_ISSET(s->clientSocks[i], &readfds)) {
            val = read(s->clientSocks[i], buffer, BUFF);
            if (val == 0) {
                close(s->clientSocks[i]);
                s->clientSocks[i] = 0;
            } else {
                for (int j = 0; j < s->maxClients; j++) {
                    if (s->clientSocks[j] != 0 && j != i) {
                        send(s->clientSocks[j], buffer, val, 0);
                    }
                }
            }
        }
    }
    return val;
}