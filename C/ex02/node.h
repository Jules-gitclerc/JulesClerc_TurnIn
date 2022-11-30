//
// Created by Jules Clerc on 06/11/2022.
//

#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H

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
#include <curses.h>
#include <termios.h>
#include <pthread.h>

#include "../ex0/client.h"
#include "../ex0/server.h"
#include "../ex1/data.h"
#include "../ex1/inputThread.h"

extern bool runningServer;
bool runningServer;
extern bool runningClient;
bool runningClient;

void runNode(void (*processData)(void*, bool), void (*welcome)(void), void (*parse)(char*), char *ip);

void *runServer(void *buff);

void *runClient(void *buff);

void processString(void* buff, bool onServer);

void sendInput(char *buff);

void welcomeText();

#endif //UNTITLED_NODE_H
