#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"

#define MATRIX_DISTANCE_TOLERANCE 0.0001
#define BOMB_MARK 2
#define POLLUTION_MARK 100

/* TODO: Read the matrix from a file */
/* TODO: Add tests for the functions */ 
/* TODO: Add summary of the process. Adding execution time and the amount of memory required */ 
/* TODO: Add a graph of how the max distance is decreasing */
/* TODO: Find a function to inspect the code for good practices. */

/* Add function signatures here */
float matrix_distance(Matrix*, Matrix*);
Matrix* create_board(void);

void copy_board(Matrix* , Matrix*);

float make_operation(Matrix*, int, int);

float left(Matrix*, int, int);

float right(Matrix*, int, int);

float top(Matrix*, int, int);

float bottom(Matrix*, int, int);

void print_board(char*, Matrix*);


int main(int argc, char **argv) {
  Matrix* current_board;
  Matrix* old_board;

  int i;
  int j;
  int counter = 0;
  
  current_board = create_board();

  old_board = (Matrix *) malloc(sizeof(Matrix));

  old_board = matrix_create(current_board->number_of_rows, current_board->number_of_columns);

  do {
    copy_board(current_board, old_board);

    for (i = 0; i < current_board->number_of_rows; i++) {
      for (j = 0; j < current_board->number_of_columns; j++) {
        matrix_set(current_board, i, j, make_operation(current_board, i, j));
      }
    }

    counter++;

    printf("Iteration number: %d\n\n", counter);

    print_board("Current Board", current_board);
    print_board("Old Board", old_board);

    printf("   Matrix distance:  %5.5f \n\n", matrix_distance(current_board, old_board));
  } while (matrix_distance(current_board, old_board) >= MATRIX_DISTANCE_TOLERANCE);

  matrix_free(current_board);
  matrix_free(old_board);

  return 0;
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
  float max = 0;
  float current_diff;

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

Matrix* create_board() {
  int i;
  int j;

  Matrix* mat;
  Matrix* board;

  mat = matrix_create(4, 5);
  board = matrix_create(4, 5);

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

  /*
   *  N = 100
   *
   *  0 0 0 0 0
   *  0 0 0 0 0
   *  0 0 N 0 0
   *  0 0 0 0 0
   */

  for (i = 0; i < mat->number_of_rows; i++) {
    for (j = 0; j < mat->number_of_columns; j++) {
      if (matrix_get(mat, i, j) == BOMB_MARK) {
        matrix_set(board, i, j, POLLUTION_MARK);
      } else {
        matrix_set(board, i, j, 0);
      }
    }
  }

  return board;
}

float make_operation(Matrix* mat, int row_index, int column_index) {

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
