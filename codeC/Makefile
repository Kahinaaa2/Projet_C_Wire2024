all: exec

main.o: main.c main.h
		@gcc -c main.c -o main.o

insertionavl.o: insertionavl.c insertionavl.h
		@gcc -c insertionavl.c -o insertionavl.o

rotationavl.o: rotationavl.c rotationavl.h
		@gcc -c rotationavl.c -o rotationavl.o

fonction.o: fonction.c fonction.h
		@gcc -c fonction.c -o fonction.o

exec: main.o insertionavl.o rotationavl.o fonction.o
		@gcc main.o insertionavl.o rotationavl.o fonction.o -o exec

clean:
		rm -f *.o
		rm -f exec
