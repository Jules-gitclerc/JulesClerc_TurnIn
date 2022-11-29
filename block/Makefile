COM = gcc -c -g -Wall -w -pedantic
S = sha256/
D = ../ex1/

block: main.c libBlock.a
	gcc -o block -g -Wall -w -pedantic main.c libBlock.a -lm

libBlock.a: sha256.o block.o $(D)data.o 
	ar rs libBlock.a $^

block.o: block.c block.h
	$(COM) block.c

$(D)data.o: $(D)data.c $(D)data.h
	$(MAKE) data.o -C $(D)

sha256.o: $(S)sha256.c $(S)sha256.h
	$(COM) $(S)sha256.c 

clean:
	rm -f *.o
	rm -f *.a
	$(MAKE) clean -C $(D)

fclean:
	rm -f *.o
	rm -f *.a
	rm -f block
	rm -f *.sav
	$(MAKE) clean -C $(D)
	rm -f vg*

