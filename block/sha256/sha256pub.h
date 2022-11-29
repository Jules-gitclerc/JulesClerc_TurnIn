#ifndef SHAPUBLIC
#define SHAPUBLIC

#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 byte digest

typedef unsigned char BYTE;             // 8-bit byte
typedef unsigned int  WORD;             // 32-bit word, change to "long" for 16-bit machines

void sha256Hash(void *data, void *buff, int byteSize);

#endif
