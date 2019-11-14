all: main.o
	gcc -o stat_app.out main.o

main.o: main.c
	gcc -c main.c

run:
	./stat_app.out