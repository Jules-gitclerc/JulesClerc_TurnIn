//
// Created by Jules Clerc on 01/11/2022.
//

#ifndef UNTITLED_CLIENT_H
#define UNTITLED_CLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <fcntl.h>

typedef struct Client {
    int sock;
    struct timeval tv;
    struct sockaddr_in server;
} Client;

#define BUFF 1024

extern Client *c;

Client *connectAsClient(char *ip);
int receiveData(Client *c, char *buffer);
#endif //UNTITLED_CLIENT_H
