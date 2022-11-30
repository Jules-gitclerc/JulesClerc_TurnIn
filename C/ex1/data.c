#include "data.h"

bool runningMainThread = true;

//return true if your computer is little endian and false if it is big endian.
bool littleEndian() {
    int i = 1;
    char *p = (char*)&i;
    return (bool)*p;
}

//Takes in pointer to data and an amount of bytes that are in the data. It creates Data *d and allocates d->arr to the size of bytes and then copies the data from dat into d→arr.
Data *makeData(void *dat, int bytes) {
    Data *d = (Data*)calloc(1, sizeof(Data));
    d->arr = calloc(bytes, 1);
    d->bytes = bytes;
    memcpy(d->arr, dat, bytes);
    return d;
}

//Allocates a buffer with the exact size of the Data and then copies the data being pointed to by the Data struct into the buffer along with the size of the buffer. Returns a pointer to the buffer.
void *writeData(Data *d) {
    void *buffer = calloc(d->bytes + sizeof(int), 1);
    memcpy(buffer, &d->bytes, sizeof(int));
    memcpy(buffer + sizeof(int), d->arr, d->bytes);
    return buffer;
}

//Declares a Data struct. Reads from buffer created with the writeData function. First it reads size from the buffer (and copies it into the Data struct’s bytes field) so that it knows how much data is in the buffer. Then it reads that much data from the buffer and copies it into the Data struct’s arr field.
Data *readData(void *buffer) {
    Data *d = calloc(sizeof(Data), 1);
    memcpy(&d->bytes, buffer, sizeof(int));
    d->arr = calloc(d->bytes, 1);
    memcpy(d->arr, buffer + sizeof(int), d->bytes);
    return d;
}

//Free the allocated array in d and also d itself.
void freeData(Data *d){
    free(d->arr);
    free(d);
}

