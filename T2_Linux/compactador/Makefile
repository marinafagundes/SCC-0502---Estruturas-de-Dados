CC = gcc
CFLAGS = -Wall
programa = compactador

all: compactador

compactador: main.c compactador.c
	$(CC) -o $(programa) compactador.c main.c

run: compactador
	./$(programa)

clean:
	rm $(programa)
