COM = gcc -Wall -w -pedantic -c -g

data: main.c data.c data.h inputThread.c inputThread.h
	gcc -o data -g -Wall -w -lpthread -lcurses -pedantic main.c

test:
	valgrind --fair-sched=yes --leak-check=full --show-leak-kinds=all ./data

clean:
	rm *.o

fclean:
	rm *.o
	rm data
