#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "matrix.h"

#include "functions.h"

#define GENERATE_STOP_CRITERION_DATA 1
#define QUIET_MODE 0
#define MAX_NUMBER_OF_ITERATIONS 1000
#define TOLERANCE 1e-4f
#define ENABLE_UI 0
#define DEFAULT_ISLAND_FILE "island/island.txt"

/* TODO: Read the matrix from a file */
/* TODO: Add tests for the functions */ 
/* TODO: Add summary of the process. Adding execution time and the amount of memory required */ 
/* TODO: Add a graph of how the max distance is decreasing */
/* TODO: Find a function to inspect the code for good practices. */

/* Add function signatures here */

/* USAGE: island/island.txt */
int main(int argc, char **argv) {

  Matrix* initial_board;
  Matrix* current_board;
  Matrix* old_board;

  int i;
  int j;
  int number_of_iterations;
  float error;
  int character;
  char path_to_file[121];

  if (ENABLE_UI) {
    printf("Insert the name of the file:   ");
    scanf("%s", path_to_file);
  } else {
    strcpy(path_to_file, DEFAULT_ISLAND_FILE);
  }


  /*
  while ((character = getchar()) != EOF) {
    printf("%c", character);
  }
  */

  number_of_iterations = 0;
  /* TODO: The user should pass the name of the file */
  initial_board = create_initial_board_from_file(path_to_file);

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

    number_of_iterations++;

    error = get_error(current_board, old_board);

    if (GENERATE_STOP_CRITERION_DATA) {
      write_data_to_file(error);
    }

    if (!QUIET_MODE) {
      printf("Iteration number: %d\n\n", number_of_iterations);

      print_board("Old Board", old_board);
      print_board("Current Board", current_board);

      printf("   Current Error:  %5.20f \n\n", error);
      printf("   TOLERANCE:  %5.10f \n\n", TOLERANCE);
    }

    if (number_of_iterations + 1 >= MAX_NUMBER_OF_ITERATIONS) {
      printf("The maximun number of iterations has been reached. \n");
    }

  } while ((error >= TOLERANCE) && (number_of_iterations < MAX_NUMBER_OF_ITERATIONS));

  printf("name of the file:   %s\n", path_to_file);

  matrix_free(current_board);
  matrix_free(initial_board);
  matrix_free(old_board);

  return 0;
}
