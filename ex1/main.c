#define BUFF 1024

#include "inputThread.c"

int main() {
    if (littleEndian()) {
        printf("little endian\n");
    } else {
        printf("big endian\n");
    }
    int *poo = (int *) calloc(1, sizeof(int));
    *poo = 10;
    Data *d = makeData(poo, sizeof(int));
    free(poo);
    void *buffer = writeData(d);
    freeData(d);
    Data *read = readData(buffer);
    printf("got %i - expected 10\n", *(int *) read->arr);
    free(buffer);
    freeData(read);

    BuffLock *bl = makeBuffLock();

    pthread_t handle;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&handle, &attr, inputThread, bl);//inputBuffer);
    pthread_attr_destroy(&attr);

    while (runningMainThread) {
        /* // can be useful for testing lock
        if (pthread_mutex_trylock(bl->lock) == 0) {
            printf("i got lock\n");
            pthread_mutex_unlock(bl->lock);
        }
        */

        if (*(int *) bl->buffer != 0) {
            if (pthread_mutex_trylock(bl->lock) == 0) {
                Data *read = readData(bl->buffer);
                if (read) {
                    printf("got data: %s\n", (char *) read->arr);
                    memset(bl->buffer, 0, read->bytes + sizeof(int));
                    freeData(read);
                } else {
                    memset(bl->buffer, 0, BUFF + 1);
                }
                pthread_mutex_unlock(bl->lock);
            }
        }

    }

    freeBuffLock(bl);
    pthread_join(handle,
                 0);
    pthread_exit(0);
}
