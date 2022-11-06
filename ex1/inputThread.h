//
// Created by Jules Clerc on 02/11/2022.
//

#ifndef UNTITLED_INPUTTHREAD_H
#define UNTITLED_INPUTTHREAD_H

#include "data.c"

typedef struct BuffLock {
    pthread_mutex_t *lock;
    void *buffer;
} BuffLock;

#endif //UNTITLED_INPUTTHREAD_H
