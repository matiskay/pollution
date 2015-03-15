all:
	 gcc -c matrix.c
	 gcc -c main.c
	 gcc -o main matrix.o main.o

test_matrix:
	 gcc test_matrix.c -o test_matrix.out
	 ./test_matrix.out

test:	 test_matrix

clean:
	 rm *.out

run:
	 gcc -c matrix.c
	 gcc -c main.c
	 gcc -o pollution matrix.o main.o
	 ./pollution

debug:
	gcc -g main.c -o pollution
	gdb pollution
