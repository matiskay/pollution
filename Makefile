CC=gcc

all:
	 $(CC) -c matrix.c
	 $(CC) -c main.c
	 $(CC) -c functions.c
	 $(CC) -o pollution matrix.o functions.o main.o

test_matrix: clean
	 $(CC) -c matrix.c
	 $(CC) -c test_matrix.c
	 $(CC) -o test_matrix matrix.o test_matrix.o
	 ./test_matrix

test_functions: clean
	 $(CC) -c matrix.c
	 $(CC) -c functions.c
	 $(CC) -c test_functions.c
	 $(CC) -o test_functions matrix.o functions.o test_functions.o
	 ./test_functions

test:	 test_matrix

clean:
	 rm *.out || echo "No *.out files"
	 rm *.o || echo "No *.o files"
	 rm -rf *.dSYM || echo "No *.dSYM folders"
	 rm pollution || echo "No file pollution"
	 rm test_matrix || echo "No file test_matrix"
	 rm stop_criterion.dat || echo "No file stop_criterion.dat"

run:
	 $(CC) -c main.c
	 $(CC) -c matrix.c
	 $(CC) -c functions.c
	 $(CC) -o pollution matrix.o functions.o main.o
	 ./pollution

debug:
	$(CC) -g main.c -o pollution
	gdb pollution

image:
	gnuplot stop_criterion.plt
