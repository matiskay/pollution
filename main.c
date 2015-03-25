#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"

#include "functions.h"

#define GENERATE_STOP_CRITERION_DATA 1
#define QUIET_MODE 0
#define MAX_NUMBER_OF_ITERATIONS 1000
#define TOLERANCE 1e-4f

/* TODO: Read the matrix from a file */
/* TODO: Add tests for the functions */ 
/* TODO: Add summary of the process. Adding execution time and the amount of memory required */ 
/* TODO: Add a graph of how the max distance is decreasing */
/* TODO: Find a function to inspect the code for good practices. */

/* Add function signatures here */

int main(int argc, char **argv) {

  Matrix* initial_board;
  Matrix* current_board;
  Matrix* old_board;

  int i;
  int j;
  int counter;
  int number_of_iterations;
  float stop_condition;

  number_of_iterations = 0;
  counter = 0;
  initial_board = create_initial_board_from_file("island/island.txt");

  if (! QUIET_MODE) {
    print_board("Initial board", initial_board);
  }
  
  current_board = create_board(initial_board);

  old_board = (Matrix *) malloc(sizeof(Matrix));

  old_board = matrix_create(current_board->number_of_rows, current_board->number_of_columns);

  do {
    copy_board(current_board, old_board);

    for (i = 0; i < current_board->number_of_rows; i++) {
      for (j = 0; j < current_board->number_of_columns; j++) {
        matrix_set(current_board, i, j, make_operation(initial_board, current_board, i, j));
      }
    }

    counter++;

    if (! QUIET_MODE) {
      printf("Iteration number: %d\n\n", counter);

      print_board("Old Board", old_board);
      print_board("Current Board", current_board);

      printf("   Matrix distance:  %5.20f \n\n", matrix_distance(current_board, old_board));
      printf("   Maximun matrix value:  %5.20f \n\n", matrix_maximun_value(current_board));
      /*
      printf("   (Matrix_distance / Maximun_matrix_value) --> Stop Criterion:  %5.10f \n\n", (matrix_distance(current_board, old_board) / matrix_maximun_value(current_board)));
      */
      printf("   TOLERANCE:  %5.10f \n\n", TOLERANCE);
    }

    number_of_iterations++;

    stop_condition = stop_criterion(current_board, old_board);

    if (GENERATE_STOP_CRITERION_DATA) {
      write_data_to_file(stop_condition);
    }
  } while ((stop_condition >= TOLERANCE) && (number_of_iterations < MAX_NUMBER_OF_ITERATIONS));

  matrix_free(current_board);
  matrix_free(initial_board);
  matrix_free(old_board);


  /*
  printf("The number of lines is %d\n", line_counter);
  printf("The number of rows is %d\n", number_of_rows);
  printf("The number of columns is %d\n", number_of_columns);
  */

  return 0;
}
