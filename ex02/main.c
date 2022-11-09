#include "node.h"

int main(int argc, char **argv) {
    char *ip = 0;
    if (argc > 1) {
        ip = argv[1];
    }

    runNode(processString, welcomeText, sendInput, ip);
    pthread_exit(0);
}
