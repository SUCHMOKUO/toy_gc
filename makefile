CC = clang

output: vm.o main.o
	$(CC) vm.o main.o -o main

main.o: main.c
	$(CC) -c main.c

vm.o: vm.c
	$(CC) -c vm.c

clean:
	rm *.o