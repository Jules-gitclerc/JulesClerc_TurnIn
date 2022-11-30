#include "client.c"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("please provide an ip to connect to\n");
        return 1;
    } else {
        c = connectAsClient(argv[1]);
        if (c > 0) {
            bool runningClient = true;
            char* buffer = (char*)calloc(sizeof(char), BUFF + 1);
            int recv = 0;
            int count = 0;
            int interval = 1000000;
            while (runningClient) {
                int val = receiveData(c, buffer);
                if (val < 0) {
                    runningClient = false;
                } else if (val > 0) {
                    printf("%i from server\n", *(int*)buffer);
                    memset(buffer, 0, BUFF);
                }
                if (count >= interval) {
                    write(c->sock, &recv, sizeof(int));
                    recv++;
                    count = 0;
                } else {
                    count++;
                }
            }
            free(buffer);
            close(c->sock);
            free(c);
        }
    }
}