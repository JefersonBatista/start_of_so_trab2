all: main

main: trab2.c
    gcc -lpthread -o trab2 trab2.c

clean: trab2 *.o

