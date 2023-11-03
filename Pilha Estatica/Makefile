CC = gcc
programa = main

main: main.c PilhaEstatica.c PilhaEstatica.h
	$(CC) -o $(programa) main.c PilhaEstatica.c

clean:
	rm *.o $(programa)

exec:
	$(CC) -o $(programa) main.c PilhaEstatica.c
	./$(programa)
