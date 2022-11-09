#include "inputThread.h"
#include "data.c"

//takes in an buffer with the size of the data in the buffer. It goes through byte by byte and flips the endianess of the data.
void *flipEndian(void *buff, int size) {
    void *newBuff = calloc(size, 1);
    for (int i = 0; i < size; i++) {
        memcpy(newBuff + i, buff + size - i - 1, 1);
    }
    return newBuff;
}

/*Receives a shared buffer with a pthread_mutex_t stored in it.  Pull the pthread_mutex_t out and store it. Test your code to make sure that this lock is properly connected to the pthread_mutex_t being used in main.
buffer is shared between this thread and the main thread. In a loop have this function take in user input and stores it in a buffer, when the user hits enter take in the string from the input buffer and copy it into the shared buffer via a Data struct. The main thread should then pick up that there is data in the buffer, and unpack it to display the string the user typed in.
If the user hits the escape key have the program end. Hint take in the user input charavter at a time, rather than line by line.*/
void *inputThread(void *buffer) {
    BuffLock *bl = (BuffLock *) buffer;
    // pthread_mutex_t *lock = *(pthread_mutex_t **) buffer;
    // char *inputBuffer = calloc(BUFF, 1);
    char *input = malloc(sizeof(char) * BUFF);
    int i = 0;
    int c = 0;
    while (runningMainThread) {
        c = getchar();
        if (c == 10) {
            if (pthread_mutex_trylock(bl->lock) == 0) {
                Data *d = makeData(input, i);
                void *data = writeData(d);

                if (littleEndian()) {
                    flipEndian(data, d->bytes + sizeof(int));
                }
                memcpy(bl->buffer, data, d->bytes + sizeof(int));
                freeData(d);
                free(data);
                memset(input, 0, BUFF);
                i = 0;
                pthread_mutex_unlock(bl->lock);
            }
        } else if (c == 27) {
            runningMainThread = false;
        } else {
            input[i] = c;
            i++;
        }
    }
    free(input);
    pthread_exit(0);
}

//create BuffLock struct, allocated buffer to size of BUFF, and initalize lock.
BuffLock *makeBuffLock() {
    BuffLock *bl = (BuffLock *) calloc(1, sizeof(BuffLock));
    bl->buffer = calloc(BUFF + 1, 1);
    bl->lock = (pthread_mutex_t *) calloc(1, sizeof(pthread_mutex_t));
    pthread_mutex_init(bl->lock, 0);
    return bl;
}

//frees allocated memory for buffer and lock as well as the memory for bl.
void freeBuffLock(BuffLock *bl) {
    free(bl->buffer);
    free(bl->lock);
    free(bl);
}
