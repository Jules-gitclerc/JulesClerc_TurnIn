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

#define BUFF 1024

bool littleEndian();
Data *makeData(void *dat, int bytes);
void *writeData(Data *d);
Data *readData(void *buffer);
void freeData(Data *d);
void *flipEndian(void *buff, int size);

#endif //UNTITLED_DATA_H
