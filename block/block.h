//
// Created by Jules Clerc on 26/11/2022.
//

#ifndef UNTITLED_BLOCK_H
#define UNTITLED_BLOCK_H

#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdbool.h>

#include "./sha256/sha256.h"
#include "../ex1/data.h"

//our blockchain will be data agnostic, allowing it to have more modular use in the future for whatever type of data we want to put in it
/* struct Data {
    void * arr;     // data being held
    int byteSize;     //size of data
} */

typedef struct Block {
    int index;
    // array holding the hash off the previous block
    BYTE preHash[SHA256_BLOCK_SIZE];     //macros provided in header
    //  array holding hash of data within block
    BYTE dataHash[SHA256_BLOCK_SIZE];
    Data *data;     // pointer to data stored in this block
    int nonce;     // int representing the proof of work validating this block
    time_t timestamp;
    struct Block *next;     // next block in the chain
} Block;

typedef struct Blockchain {
    Block * base;         //genesis block of the chain, unchanged once chain is initialized
    Block *cur;        // the current top of the chain, used for addition of new blocks
    int len;            // the number of blocks in the chain
} Blockchain;

Block *makeBlock(Data *d, Block *pre);
// This is where we create a block and do the proof of work algorithm.
// For the creation of single block we hash the previous block and store it in this new block for later validation.
// For the genesis block we hash some arbitrary data and store that.
// Then we fill up the new block struct (everything except the dataHash) start its nonce at 0, we increment the nonce until the hash result satisfies our proof of work condition.
// For this function I made 2 helper functions hashBlock(Block *bm BYTE *buff) and hashBlockData(Block *b, BYTE *buff).
// hashBlock hashes the whole block and stores it in the buff. hashBlockData hashes a block without its dataHash.
// hashBlock is used to generate the preHash and hashBlockData iss used to generate the dataHash.

Blockchain *makeBlockchain();
// creates struct and initializes the chain with genesis block

bool addBlock(Blockchain *bc, Block *b);
// When we receive a block to add to our chain we  must first validate it.
// Return false if Block is not valid, if Block is valid add it to the chain, and update the chain’s cur value,then return true.

bool validateChain(Blockchain *bc);
// In this function you go through the chain and check a block to make sure its preHash matches the hashed value of the previous block.
// You also check to make sure that the block’s dataHash matches a newly computed hash of the block and its data.

void printBlock(Block *block);
// Prints out the information of the block, including their hashes and data (specified with the Block’s data type). In this case we are simply printing out an integr for the data field

void printChain(Blockchain *bc, void (*printFunc)(Block*));
// prints the blocks of the chain. Including their hashes and data

void freeBlockchain(Blockchain *bc);
// frees all dynamic memory used for the Blockchain including all data and Blocks

void saveChain(char *file, Blockchain *bc);
// saves blockchain data to disk

Blockchain *loadChain(char *file);
// loads blockchain data from disk

#endif //UNTITLED_BLOCK_H
