#include "server.c"

int main() {
    int send = 0;
    welcomeSize = sizeof(int);
    welcomeMessage = calloc(welcomeSize, 1);
    memcpy(welcomeMessage, &send, welcomeSize);

    s = setUpServerConnection();
    int max = 5;
    int num = 0;
    if (s > 0) {
        bool runningServer = true;
        char* buffer = (char*)calloc(sizeof(char), BUFF + 1);
        int gotData = 0;
        while (runningServer) {
            gotData = serverSendReceive(s, buffer);
            if (gotData != 0) {
                printf("received %i\n", *(int*)buffer);
                num += *(int*)buffer;
                if (num >= max) {
                    printf("got enough data(%i), exiting now\n", num);
                    runningServer = false;
                }
                memset(buffer, 0, BUFF);
                gotData = 0;
            }
        }
        printf("server ended\n");
        free(buffer);
        closeServer(s);
    }
    free(welcomeMessage);
}