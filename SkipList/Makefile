CC = gcc
CFLAGS = -Wall
programa = SkipList

all: SkipList

SkipList: main.c SkipList.c
	$(CC) -o $(programa) SkipList.c main.c

run: SkipList
	./$(programa)

clean:
	rm $(programa)


