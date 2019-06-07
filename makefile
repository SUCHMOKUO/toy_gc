output: vm.o main.o
	clang vm.o main.o -o main

main.o: main.c
	clang -c main.c

vm.o: vm.c
	clang -c vm.c

clean:
	rm *.o