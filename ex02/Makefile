N = ../ex0/
D = ../ex1/
COM = gcc -c -g -Wall -pedantic -w

node: main.c libNetThread.a
	gcc -o node -g -Wall -w -pedantic main.c libNetThread.a

libNetThread.a: node.o client.o server.o $(D)inputThread.o
	ar rs libNetThread.a $^

node.o: node.c node.h
	$(COM) node.c

inputThread.o: $(D)input.c $(D)input.h $(D)data.c $(D)data.h $(D)inputThread.c $(D)inputThread.h
	$(MAKE) inputThread.o $(D)

client.o: $(N)client.c $(N)client.h
	$(COM) $(N)client.c

server.o: $(N)server.c $(N)server.h
	$(COM) $(N)server.c

test1:
	valgrind --fair-sched=yes --leak-check=full --show-leak-kinds=all ./node

test2:
	valgrind --fair-sched=yes --leak-check=full --show-leak-kinds=all ./node 127.0.0.1

clean:
	rm *.o

fclean:
	rm *.o
	rm *.a
	rm node
	$(MAKE) clean -C $(D)
	$(MAKE) clean -C $(N)
	rm vg*

