both: client server

client: client.c client.h clientMain.c
	gcc -o client -g clientMain.c

server: server.c server.h serverMain.c
	gcc -o server -g serverMain.c

clean:
	rm *.o

fclean:
	rm client
	rm server
	rm vg*
