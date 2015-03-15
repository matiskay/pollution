all:
	 gcc -c matrix.c
	 gcc -c main.c
	 gcc -o pollution matrix.o main.o

test_matrix:
	 gcc test_matrix.c -o test_matrix.out
	 ./test_matrix.out

test:	 test_matrix

clean:
	 rm *.out || echo "No *.out files"
	 rm *.o || echo "No *.o files"
	 rm -rf *.dSYM || echo "No *.dSYM folders"
	 rm pollution || echo "No file pollution"

run:
	 gcc -c matrix.c
	 gcc -c main.c
	 gcc -o pollution matrix.o main.o
	 ./pollution

debug:
	gcc -g main.c -o pollution
	gdb pollution
