CC=gcc

all:
	 $(CC) -c matrix.c
	 $(CC) -c main.c
	 $(CC) -o pollution matrix.o main.o

test_matrix: clean
	 $(CC) -c matrix.c
	 $(CC) -c test_matrix.c
	 $(CC) -o test_matrix matrix.o test_matrix.c
	 ./test_matrix

test:	 test_matrix

clean:
	 rm *.out || echo "No *.out files"
	 rm *.o || echo "No *.o files"
	 rm -rf *.dSYM || echo "No *.dSYM folders"
	 rm pollution || echo "No file pollution"
	 rm test_matrix || echo "No file test_matrix"
	 rm stop_criterion.dat || echo "No file stop_criterion.dat"

run:
	 $(CC) -c matrix.c
	 $(CC) -c main.c
	 $(CC) -o pollution matrix.o main.o
	 ./pollution

debug:
	$(CC) -g main.c -o pollution
	gdb pollution

image:
	gnuplot stop_criterion.plt
