//
// Created by Jules Clerc on 26/11/2022.
//

#include "block.h"

void hashBlock(Block *b, BYTE *buff) {
    int size = sizeof(b->index) + sizeof(b->preHash) + sizeof(b->dataHash) + sizeof(b->nonce) + sizeof(b->timestamp);
    BYTE *temp = calloc(1, size);
    memcpy(temp, &b->index, sizeof(b->index));
    memcpy(temp + sizeof(b->index), b->preHash, sizeof(b->preHash));
    memcpy(temp + sizeof(b->index) + sizeof(b->preHash), b->dataHash, sizeof(b->dataHash));
    memcpy(temp + sizeof(b->index) + sizeof(b->preHash) + sizeof(b->dataHash), &b->nonce, sizeof(b->nonce));
    memcpy(temp + sizeof(b->index) + sizeof(b->preHash) + sizeof(b->dataHash) + sizeof(b->nonce), &b->timestamp,
           sizeof(b->timestamp));
    sha256Hash(temp, buff, size);
    free(temp);
}

// hashBlockData iss used to generate the dataHash.
void hashBlockData(Block *b, BYTE *buff) {
    void *d = writeData(b->data);
    sha256Hash(d, buff, b->data->bytes + sizeof(int));
    free(d);
}

bool isValidProofOfWork(Block *b) {
    BYTE *hash = calloc(1, SHA256_BLOCK_SIZE);
    hashBlock(b, hash);
    bool valid = true;
    for (int i = 0; i < b->difficulty; i++) {
        if (hash[i] != 0) {
            valid = false;
            break;
        }
    }
    free(hash);
    return valid;
}

/* This is where we create a block and do the proof of work algorithm.*/
Block *makeBlock(Data *d, Block *pre) {
    Block *b = calloc(1, sizeof(Block));
    pre->next = b;
    b->data = d;
    b->index = pre->index + 1;
    b->timestamp = time(NULL);
    b->nonce = 0;
    b->next = NULL;
    hashBlock(pre, b->preHash);
    hashBlockData(b, b->dataHash);
    while (!isValidProofOfWork(b)) {
        b->nonce += 1;
    }
    return b;
}

// creates struct and initializes the chain with genesis block
Blockchain *makeBlockchain() {
    Blockchain *bc = malloc(sizeof(Blockchain));
    char *str = "Genesis Block";
    Data *d = makeData(str, strlen(str));
    Block *b = malloc(sizeof(Block));
    b->data = d;
    b->index = 0;
    b->nonce = 0;
    b->timestamp = time(NULL);
    b->next = NULL;
    memset(b->preHash, 0, SHA256_BLOCK_SIZE);
    hashBlockData(b, b->dataHash);
    bc->base = b;
    bc->cur = b;
    bc->len = 1;
    return bc;
}

/* When we receive a block to add to our chain we  must first validate it.
Return false if Block is not valid, if Block is valid add it to the chain, and update the chain’s cur value,then return true. */
bool addBlock(Blockchain *bc, Block *b) {
    if (validateChain(bc)) {
        bc->cur->next = b;
        bc->cur = b;
        bc->len++;
        return true;
    }
    return false;
}

/* In this function you go through the chain and check a block to make sure its preHash matches the hashed value of the previous block.
You also check to make sure that the block’s dataHash matches a newly computed hash of the block and its data.*/
bool validateChain(Blockchain *bc) {
    Block *cur = bc->base;
    while (cur->next != NULL) {
        BYTE hash[SHA256_BLOCK_SIZE];
        hashBlock(cur, hash);
        if (memcmp(hash, cur->next->preHash, SHA256_BLOCK_SIZE) != 0) {
            return false;
        }
        hashBlockData(cur->next, hash);
        if (memcmp(hash, cur->next->dataHash, SHA256_BLOCK_SIZE) != 0) {
            return false;
        }
        cur = cur->next;
    }
    return true;
}

// Prints out the information of the block, including their hashes and data (specified with the Block’s data type).
void printBlock(Block *block) {
    printf("Block #%d\n", block->index);
    printf("prev: ");
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
        printf("%02x", block->preHash[i]);
    }
    printf("\n");
    printf("data: ");
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
        printf("%02x", block->dataHash[i]);
    }
    printf("\n");
    printf("data: %d\n", *((int *) (block->data->arr)));
    printf("proof: %d\n", block->nonce);
    printf("-------------------\n");
}

// prints the blocks of the chain. Including their hashes and data
void printChain(Blockchain *bc, void (*printFunc)(Block *)) {
    Block *cur = bc->base;
    while (cur != NULL) {
        printFunc(cur);
        cur = cur->next;
    }
}

// frees all dynamic memory used for the Blockchain including all data and Blocks
void freeBlockchain(Blockchain *bc) {
    Block *cur = bc->base;
    while (cur != NULL) {
        Block *temp = cur;
        cur = cur->next;
        free(temp->data);
        free(temp);
    }
    free(bc);
}

// saves blockchain data to disk
void saveChain(char *file, Blockchain *bc) {
    FILE *fp = fopen(file, "wb");
    Block *cur = bc->base;
    while (cur != NULL) {
        fwrite(cur, sizeof(Block), 1, fp);
        cur = cur->next;
    }
    fclose(fp);
}

// loads blockchain data from disk
Blockchain *loadChain(char *file) {
    FILE *fp = fopen(file, "r");
    Blockchain *bc = malloc(sizeof(Blockchain));
    Block *b = malloc(sizeof(Block));
    fread(b, sizeof(Block), 1, fp);
    bc->base = b;
    bc->cur = b;
    bc->len = 1;
    while (!feof(fp)) {
        Block *temp = malloc(sizeof(Block));
        fread(temp, sizeof(Block), 1, fp);
        bc->cur->next = temp;
        bc->cur = temp;
        bc->len++;
    }
    fclose(fp);
    return bc;
}






