CC = gcc
programa = main

main: main.c ListaEstatica.c ListaEstatica.h
	$(CC) -o $(programa) main.c ListaEstatica.c

clean:
	rm *.o $(programa)

exec:
	$(CC) -o $(programa) main.c ListaEstatica.c
	./$(programa)
