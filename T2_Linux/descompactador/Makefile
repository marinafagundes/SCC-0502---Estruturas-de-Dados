CC = gcc
CFLAGS = -Wall
programa = descompactador

all: descompactador

Descompactado: main.c descompactador.c
    $(CC) -o $(programa) descompactador.c main.c

run: descompactador
    ./$(programa)

clean:
    rm $(programa)
