CC = gcc
programa = main

main: main.c ListaLigada.c ListaLigada.h
	$(CC) -o $(programa) main.c ListaLigada.c

clean:
	rm *.o $(programa)

exec:
	$(CC) -o $(programa) main.c ListaLigada.c
	./$(programa)
