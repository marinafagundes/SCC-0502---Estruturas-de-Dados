CC = gcc
CFLAGS = -Wall
programa = PilaouFilha

all: PilaouFilha

PilaouFilha: main.c PilaouFilha.c
	$(CC) -o $(programa) PilaouFilha.c main.c

run: PilaouFilha
	./$(programa)

clean:
	rm $(programa)

