#include "block.h"

int main() {
    bool load = false;
	Blockchain *chain = makeBlockchain();
	Block *tamper;
	if (!load) {
		int chainSize = 5;
		for (int i = 0; i < chainSize; i++) {
			int *data = calloc(1, sizeof(int));
			*data = i;
			Data *d = makeData(data, sizeof(int));
			free(data);
			Block *b = makeBlock(d, chain->cur);
			addBlock(chain, b);
			printBlock(b);
			if (i == chainSize / 2) {
				tamper = b;
			}
		}
	}
	printf("\n");
	printf("is this chain valid? %s\n", validateChain(chain) ? "true" : "false");
	saveChain("blockchain.sav", chain);
	Data *d = tamper->data;
	*((int*)(d->arr)) = 100;
	printf("is this chain valid? %s\n", validateChain(chain) ? "true" : "false");
	freeBlockchain(chain);
	chain = loadChain("blockchain.sav");
	printf("\n");	
	printChain(chain, printBlock);
	printf("\n");
	freeBlockchain(chain);
	return 0;
}
