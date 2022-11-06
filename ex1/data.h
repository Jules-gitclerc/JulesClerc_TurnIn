//
// Created by Jules Clerc on 02/11/2022.
//

#ifndef UNTITLED_DATA_H
#define UNTITLED_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include<stdbool.h>
#include <curses.h>
#include <termios.h>
#include <pthread.h>

typedef struct Data {
    int bytes;
    void *arr;
} Data;

extern bool runningMainThread;

#endif //UNTITLED_DATA_H
