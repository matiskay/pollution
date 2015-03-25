#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "functions.h"
#include <string.h>

#define DEBUG_INITIAL_BOARD_FUNCTION 1
#define BUFFER 128
#define ASCII_CODE_FOR_NEW_LINE 10
#define ASCII_CODE_FOR_SPACE 32

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
  /*
  return matrix_distance(current_board, old_board) / matrix_maximun_value(current_board);
  */
  return matrix_distance(current_board, old_board);
}

/* TODO: Don't consider empty lines */
Matrix* create_initial_board_from_file(char* filename) {
  Matrix* initial_board;

  char current_character;
  char line[BUFFER];
  int i;

  /* Number of valid lines excluding lines that starts with # */
  int number_of_lines;
  int is_comment;

  int number_of_rows;
  int number_of_columns;
  int row_index;
  int column_index;
  int number_of_parameters_returned;

  FILE *file = fopen(filename, "r");

  is_comment = 0;

  column_index = 0;

  number_of_lines = 0;

  if (file != NULL) {
    while (fgets(line, sizeof(line), file) != NULL) {
      if (line[0] == ASCII_CODE_FOR_NEW_LINE) {
        continue;
      }

      for (i = 0; i < BUFFER; i++) {

        if (line[i] == '\0') {
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
          number_of_lines++;
        }

        if (is_comment == 1) {
          continue;
        }

        if (number_of_lines == 0) {
          number_of_parameters_returned = sscanf(line, "%d %d", &number_of_rows, &number_of_columns);

          if (number_of_parameters_returned < 2) {
            printf("You have to specify the number_of_rows and the number_of_columns");
            exit(10);
          }

          initial_board = matrix_create(number_of_rows, number_of_columns);
        } else {
          if (line[i] != ASCII_CODE_FOR_NEW_LINE && line[i] !=  ASCII_CODE_FOR_SPACE) {
            row_index = number_of_lines - 1;
            column_index = column_index % number_of_columns;

            if (DEBUG_INITIAL_BOARD_FUNCTION) {
              printf("row_index:   %d\n", row_index);
              printf("column_index:   %d\n", column_index);
              printf("current_value (character):   %c\n", line[i]);
              printf("current_value (integer):   %d\n", line[i]);
              printf("--------------------------------\n");
            }

            matrix_set(initial_board, row_index, column_index, (int) (line[i] - ASCII_CODE_FOR_ZERO));
            column_index++;
          } else if (line[i] == 10) {
            if (column_index % number_of_columns != 0) {
              printf("There is a missing value in the columns \n");
              matrix_free(initial_board);
              exit(88);
            }
          }
        }
      }
    }

    if (number_of_lines != number_of_rows + 1) {
      printf("There is a missing row in the file \n");
      matrix_free(initial_board);
      exit(77);
    }

    if (DEBUG_INITIAL_BOARD_FUNCTION) {
      printf("Number of valid lines in the file:  %d\n", number_of_lines);
      printf("Number of rows:  %d\n", number_of_rows);
      printf("Number of columns:  %d\n", number_of_columns);
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

  max = 0;

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
  /* TODO: Check if c has automatically casting in test */
  if ((int) matrix_get(matrix_rule, row_index, column_index) == 0) {
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
