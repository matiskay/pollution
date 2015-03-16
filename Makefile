all:
	 gcc -c matrix.c
	 gcc -c main.c
	 gcc -o pollution matrix.o main.o

test_matrix: clean
	 gcc -c matrix.c
	 gcc -c test_matrix.c
	 gcc -o test_matrix matrix.o test_matrix.c
	 ./test_matrix

test:	 test_matrix

clean:
	 rm *.out || echo "No *.out files"
	 rm *.o || echo "No *.o files"
	 rm -rf *.dSYM || echo "No *.dSYM folders"
	 rm pollution || echo "No file pollution"
	 rm test_matrix || echo "No file test_matrix"

run:
	 gcc -c matrix.c
	 gcc -c main.c
	 gcc -o pollution matrix.o main.o
	 ./pollution

debug:
	gcc -g main.c -o pollution
	gdb pollution
