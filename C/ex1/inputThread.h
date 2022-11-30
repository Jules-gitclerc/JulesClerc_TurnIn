//
// Created by Jules Clerc on 02/11/2022.
//

#ifndef UNTITLED_INPUTTHREAD_H
#define UNTITLED_INPUTTHREAD_H

#include <pthread.h>

typedef struct BuffLock {
    pthread_mutex_t *lock;
    void *buffer;
} BuffLock;

BuffLock *makeBuffLock();

void freeBuffLock(BuffLock *bl);

void *inputThread(void *buffer);
#endif //UNTITLED_INPUTTHREAD_H
