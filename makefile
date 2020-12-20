all: main.o exec.o redirect.o
	gcc -g -o main main.o exec.o redirect.o
main.o: main.c exec.h redirect.h
	gcc -c main.c
redirect.o: redirect.c exec.h
	gcc -c redirect.c
exec.o: exec.c
	gcc -c exec.c
run:
	./main
