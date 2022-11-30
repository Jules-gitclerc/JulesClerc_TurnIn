#include "node.h"

void runNode(void (*processData)(void *, bool), void (*welcome)(void), void (*parse)(char *), char *ip) {
    BuffLock *bl_input = makeBuffLock();
    BuffLock *bl_server = makeBuffLock();
    BuffLock *bl_client = makeBuffLock();
    pthread_t input;
    pthread_t server;
    pthread_t client;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    if (ip != 0) {
        c = connectAsClient(ip);
        if (c == NULL)
            return;
        printf("[client started]\n");
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_create(&client, &attr, runClient, bl_client);
    }

    s = setUpServerConnection();
    if (s != NULL) {
        printf("[server started]\n");
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_create(&server, &attr, runServer, bl_server);
    }

    if (s == NULL && ip == 0) {
        exit(84);
    }

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&input, &attr, inputThread, bl_input);
    pthread_attr_destroy(&attr);

    welcome();

    runningMainThread = true;
    while (runningMainThread) {
        if (*(int *) bl_server->buffer != 0 && runningServer) {
            if (pthread_mutex_trylock(bl_server->lock) == 0) {
                Data *read = readData(bl_server->buffer);
                if (read) {
                    processData(read->arr, 1);
                    memset(bl_server->buffer, 0, read->bytes + sizeof(int));
                    freeData(read);
                } else {
                    memset(bl_server->buffer, 0, BUFF + 1);
                }
                pthread_mutex_unlock(bl_server->lock);
            }
        }
        if (*(int *) bl_client->buffer != 0 && runningClient) {
            if (pthread_mutex_trylock(bl_client->lock) == 0) {
                Data *read = readData(bl_client->buffer);
                if (read) {
                    processData(read->arr, 0);
                    memset(bl_client->buffer, 0, read->bytes + sizeof(int));
                    freeData(read);
                } else {
                    memset(bl_client->buffer, 0, BUFF + 1);
                }
                pthread_mutex_unlock(bl_client->lock);
            }
        }
        if (*(int *) bl_input->buffer != 0) {
            if (pthread_mutex_trylock(bl_input->lock) == 0) {
                Data *read = readData(bl_input->buffer);
                if (read) {
                    if (runningServer) {
                        for (int j = 0; j < s->maxClients; j++) {
                            if (s->clientSocks[j] != 0) {
                                send(s->clientSocks[j], read->arr, strlen(read->arr), 0);
                            }
                        }
                    }
                    if (runningClient) {
                        parse(read->arr);
                    }
                    memset(bl_input->buffer, 0, read->bytes + sizeof(int));
                    freeData(read);
                } else {
                    memset(bl_input->buffer, 0, BUFF + 1);
                }
                pthread_mutex_unlock(bl_input->lock);
            }
        }
    }
    freeBuffLock(bl_input);
    freeBuffLock(bl_server);
    freeBuffLock(bl_client);
    pthread_join(input, 0);
    pthread_join(server, 0);
    pthread_join(client, 0);
    pthread_exit(0);
}

void *runServer(void *buff) {
    BuffLock *bl = (BuffLock *) buff;
    char *input = malloc(sizeof(char) * BUFF);
    int red = 0;
    runningServer = true;

    while (runningServer) {
        red = serverSendReceive(s, input);
        if (red > 0 && pthread_mutex_trylock(bl->lock) == 0) {
            Data *d = makeData(input, red);
            void *write = writeData(d);
            if (littleEndian()) {
                flipEndian(write, d->bytes + sizeof(int));
            }
            memcpy(bl->buffer, write, d->bytes + sizeof(int));
            free(write);
            freeData(d);
            red = 0;
            pthread_mutex_unlock(bl->lock);
        } else if (red < 0) {
            runningServer = false;
            runningMainThread = false;
        }
    }
    free(input);
    closeServer(s);
}

void *runClient(void *buff) {
    BuffLock *bl = (BuffLock *) buff;
    char *input = (char *) calloc(sizeof(char), BUFF + 1);
    runningClient = true;

    if (c == NULL || input == NULL)
        return NULL;
    while (runningClient) {
        int val = receiveData(c, input);
        if (val < 0) {
            runningClient = false;
        } else if (val > 0) {
            if (pthread_mutex_trylock(bl->lock) == 0) {
                Data *d = makeData(input, val);
                void *write = writeData(d);
                if (littleEndian()) {
                    flipEndian(write, d->bytes + sizeof(int));
                }
                memcpy(bl->buffer, write, d->bytes + sizeof(int));
                free(write);
                freeData(d);
                val = 0;
                pthread_mutex_unlock(bl->lock);
            }
        }
    }
    close(c->sock);
    return bl;
}

void processString(void *buff, bool onServer) {
    char *str = (char *) buff;

    if (onServer) {
        printf("[server] %s\n", str);
    } else {
        printf("[client] %s\n", str);
    }
}

void sendInput(char *buff) {
    if (runningMainThread && runningClient) {
        write(c->sock, buff, strlen(buff));
    }
}

void welcomeText() {
    Data *d = makeData("Welcome to the server!\n", 22);
    welcomeMessage = writeData(d);
    welcomeSize = d->bytes + sizeof(int);
    if (littleEndian()) {
        flipEndian(welcomeMessage, d->bytes + sizeof(int));
    }
    freeData(d);
}