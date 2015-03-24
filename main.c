#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"

#define TOLERANCE 0.1
#define BOMB_MARK 2
#define POLLUTION_MARK 100
#define MAX_NUMBER_OF_ITERATIONS 1000
#define BUFFER 128
#define ASCII_CODE_FOR_ZERO 48
#define END_OF_LINE '\n'
#define QUIET_MODE 0

/* TODO: Read the matrix from a file */
/* TODO: Add tests for the functions */ 
/* TODO: Add summary of the process. Adding execution time and the amount of memory required */ 
/* TODO: Add a graph of how the max distance is decreasing */
/* TODO: Find a function to inspect the code for good practices. */

/* Add function signatures here */
float matrix_distance(Matrix*, Matrix*);
float matrix_maximun_value(Matrix*);

Matrix* create_board(Matrix*);
Matrix* create_initial_board(void);

void copy_board(Matrix*, Matrix*);

float stop_criterion(Matrix*, Matrix*);

float make_operation(Matrix*, Matrix*, int, int);

float left(Matrix*, int, int);

float right(Matrix*, int, int);

float top(Matrix*, int, int);

float bottom(Matrix*, int, int);

void print_board(char*, Matrix*);

void write_data_to_file(float);

float stop_condition;

Matrix* create_initial_board_from_file(void);

FILE* file_stop_criterion;


int main(int argc, char **argv) {

  Matrix* initial_board;
  Matrix* current_board;
  Matrix* old_board;

  int i;
  int j;
  int counter = 0;
  int number_of_iterations;

  number_of_iterations = 0;
  initial_board = create_initial_board_from_file();

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

      print_board("Current Board", current_board);
      print_board("Old Board", old_board);

      printf("   Matrix distance:  %5.20f \n\n", matrix_distance(current_board, old_board));
      printf("   Maximun matrix value:  %5.20f \n\n", matrix_maximun_value(current_board));
      printf("   (Matrix_distance / Maximun_matrix_value) --> Stop Criterion:  %5.10f \n\n", (matrix_distance(current_board, old_board) / matrix_maximun_value(current_board)));
      printf("   TOLERANCE:  %5.10f \n\n", TOLERANCE);
    }

    number_of_iterations++;

    /*
  } while ((stop_criterion(current_board, old_board) >= TOLERANCE) &&
    (number_of_iterations >= MAX_NUMBER_OF_ITERATIONS));
    */
    /*
  } while (number_of_iterations < MAX_NUMBER_OF_ITERATIONS);
  */
  stop_condition = stop_criterion(current_board, old_board);

  write_data_to_file(stop_condition);

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

void write_data_to_file(float data) {
  file_stop_criterion = fopen("stop_criterion.dat", "a");

  if (! file_stop_criterion) {
    perror("There was a problem while open the file");
    exit(1);
  }

  fprintf(file_stop_criterion, "%2.5f \n", data);

  fclose(file_stop_criterion);
}

float stop_criterion(Matrix* current_board, Matrix* old_board) {
  return matrix_distance(current_board, old_board) / matrix_maximun_value(current_board);
}

Matrix* create_initial_board_from_file() {
  Matrix* initial_board;

  char* filename = "island/island.txt";
  char current_character;
  char line[BUFFER];
  int i;
  int line_counter = 0;
  int is_comment;

  int number_of_rows;
  int number_of_columns;
  int columns_counter;

  FILE *file = fopen(filename, "r");
  is_comment = 0;

  if (file != NULL) {
    while (fgets(line, sizeof(line), file) != NULL) {
      for (i = 0; i < BUFFER; i++) {
        if (line[i] == '\0') {

          /*
          printf("Breaking... \n");
          */
          break;
        }

        if (line[i] == '#') {
          is_comment = 1;
          continue;
        }

        if (line[i] == END_OF_LINE) {
          if (is_comment == 1) {
            is_comment = 0;
            continue;
          }
          line_counter++;
        }

        if (is_comment == 1) {
          continue;
        }

        if (line_counter == 0) {
          sscanf(line, "%d %d", &number_of_rows, &number_of_columns);
          initial_board = matrix_create(number_of_rows, number_of_columns);
        }

      /*
        printf("%c", line[i]);
        */
        /* Add checking error when the information is bigger that the information provided */
        if (line_counter > 0) {
          /* Store using line counter*/
          if (line[i] != ' ') {
            /*
            printf("%c", line[i]);
            */
            /* Check Ascii Table */
            matrix_set(initial_board, line_counter, columns_counter, (int) (line[i] - ASCII_CODE_FOR_ZERO));
            columns_counter++;
          }

          if (line[i] == END_OF_LINE) {
            columns_counter = 0;
          }
        }

        /*
        printf("character index(%d): %d \n", i, line[i]);
        printf("---> character index(%d): %c \n", i, line[i]);
        */
      }
      /*
      printf("---- end of line ----\n");
      */
    }

    fclose(file);
  } else {
    perror(filename);
    exit(1);
  }

  return initial_board;
}

void print_board(char* title, Matrix* board) {
    printf("   ----------------- %s -----------------------\n", title);
    matrix_display(board);
    printf("   ---------------------------------------------------\n\n");
}

float matrix_distance(Matrix* mat1, Matrix* mat2) {
  /* Check the dimension of the matrices */
  int i;
  int j;
  float max;
  float current_diff;

  max = fabs(matrix_get(mat1, 0, 0) - matrix_get(mat2, 0, 0));

  for (i = 0; i < mat1->number_of_rows; i++) {
    for (j = 0; j < mat1->number_of_columns; j++) {
      current_diff = fabs(matrix_get(mat1, i, j) - matrix_get(mat2, i, j));

      if (current_diff > max) {
        max = current_diff;
      }
    }
  }

  return max;
}

float matrix_maximun_value(Matrix* mat) {
  int i;
  int j;
  float max;
  float current_element;

  max = matrix_get(mat, 0, 0);

  for (i = 0; i < mat->number_of_rows; i++) {
    for (j = 0; j < mat->number_of_columns; j++) {
      current_element = matrix_get(mat, i, j);
      if (current_element > max) {
        max = current_element;
      }
    }
  }

  return max;
}

Matrix* create_initial_board() {
  int i;
  int j;

  Matrix* mat;

  mat = matrix_create(4, 5);

  /*
   *  0 0 0 0 0
   *  0 1 1 1 0
   *  0 0 2 1 0
   *  0 0 0 0 0
   */
  matrix_set(mat, 0, 0, 0);
  matrix_set(mat, 0, 1, 0);
  matrix_set(mat, 0, 2, 0);
  matrix_set(mat, 0, 3, 0);
  matrix_set(mat, 0, 4, 0);

  matrix_set(mat, 1, 0, 0);
  matrix_set(mat, 1, 1, 1);
  matrix_set(mat, 1, 2, 1);
  matrix_set(mat, 1, 3, 1);
  matrix_set(mat, 1, 4, 0);

  matrix_set(mat, 2, 0, 0);
  matrix_set(mat, 2, 1, 0);
  matrix_set(mat, 2, 2, 2);
  matrix_set(mat, 2, 3, 1);
  matrix_set(mat, 2, 4, 0);

  matrix_set(mat, 3, 0, 0);
  matrix_set(mat, 3, 1, 0);
  matrix_set(mat, 3, 2, 0);
  matrix_set(mat, 3, 3, 0);
  matrix_set(mat, 3, 4, 0);

  return mat;
}

Matrix* create_board(Matrix* initial_board) {
  Matrix* board;

  int i;
  int j;

  board = matrix_create(initial_board->number_of_rows, initial_board->number_of_columns);

  /*
   *  N = 100
   *
   *  0 0 0 0 0
   *  0 0 0 0 0
   *  0 0 N 0 0
   *  0 0 0 0 0
   */

  for (i = 0; i < initial_board->number_of_rows; i++) {
    for (j = 0; j < initial_board->number_of_columns; j++) {
      if (matrix_get(initial_board, i, j) == BOMB_MARK) {
        matrix_set(board, i, j, POLLUTION_MARK);
      } else {
        matrix_set(board, i, j, 0);
      }
    }
  }

  return board;
}

float make_operation(Matrix* matrix_rule, Matrix* mat, int row_index, int column_index) {

  /**
   * Direction's diagram
   *
   *                i - 1, j
   *    i, j - 1 <-   i,j   -> i, j + 1
   *                i + 1, j
   */

  /**
   * Extreme cases:
   * 5 x 9
   * +---+---+---+---+---+---+---+---+---+
   * | X | O | O | O | X | O | O | O | X |
   * +---+---+---+---+---+---+---+---+---+
   * | O |   |   |   |   |   |   |   | O |
   * +---+---+---+---+---+---+---+---+---+
   * | X |   |   |   |   |   |   |   | O |
   * +---+---+---+---+---+---+---+---+---+
   * | O |   |   |   |   |   |   |   | O |
   * +---+---+---+---+---+---+---+---+---+
   * | X | O | O | O | O | X | O | O | X |
   * +---+---+---+---+---+---+---+---+---+
   *
   * */
  if (matrix_get(matrix_rule, row_index, column_index) == 0) {
    return 0.0;
  }

  return (left(mat, row_index, column_index)
      + top(mat, row_index, column_index)
      + right(mat, row_index, column_index)
      + bottom(mat, row_index, column_index)) / 4;
}

float left(Matrix* mat, int row_index, int column_index) {
  if (column_index == 0) {
    return 0;
  }

  return matrix_get(mat, row_index, column_index - 1);
}

float right(Matrix* mat, int row_index, int column_index) {
  if (column_index == mat->number_of_columns - 1) {
    return 0;
  }

  return matrix_get(mat, row_index, column_index + 1);
}

float top(Matrix* mat, int row_index, int column_index) {
  if (row_index == 0) {
    return 0;
  }

  return matrix_get(mat, row_index - 1, column_index);
}

float bottom(Matrix* mat, int row_index, int column_index) {
  if (row_index == mat->number_of_rows - 1) {
    return 0;
  }

  return matrix_get(mat, row_index + 1, column_index);
}

void copy_board(Matrix* matrix_origin , Matrix* matrix_destination) {
  int i;
  int j;

  for (i = 0; i < matrix_origin->number_of_rows; i++) {
    for (j = 0; j < matrix_origin->number_of_columns; j++) {
      matrix_set(matrix_destination, i, j, matrix_get(matrix_origin, i, j));
    }
  }
}
