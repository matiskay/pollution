#include <stdio.h>
#include "minunit.h"
#include "matrix.h"
#include "functions.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

int tests_run = 0;

static char * test_create_initial_board_from_file() {

  Matrix* board;
  Matrix* expected_matrix;

  char* filename;
  filename = "test_island/test_island.txt";

  expected_matrix = matrix_create(2, 2);
  /*
  1 2
  3 4
  */
  matrix_set(expected_matrix, 0, 0, 1);
  matrix_set(expected_matrix, 0, 1, 2);

  matrix_set(expected_matrix, 1, 0, 3);
  matrix_set(expected_matrix, 1, 1, 4);

  board = create_initial_board_from_file(filename);

  /*
  print_board("board:  ", board);
  print_board("expected:  ", expected_matrix);
  */

  mu_assert("error, expected_matrix != board_from_file", matrix_equal(board, expected_matrix));
  return 0;
}

static char * test_create_initial_board_from_file_with_empty_lines() {

  Matrix* board;
  Matrix* expected_matrix;

  char* filename;
  filename = "test_island/test_island_empty_lines.txt";

  expected_matrix = matrix_create(2, 2);
  /*
  1 2
  3 4
  */
  matrix_set(expected_matrix, 0, 0, 1);
  matrix_set(expected_matrix, 0, 1, 2);

  matrix_set(expected_matrix, 1, 0, 3);
  matrix_set(expected_matrix, 1, 1, 4);

  board = create_initial_board_from_file(filename);

  /*
  print_board("board:  ", board);
  print_board("expected:  ", expected_matrix);
  */

  mu_assert("error, expected_matrix != board_from_file", matrix_equal(board, expected_matrix));
  return 0;
}

/* TODO: Rename to missing column */
static char * test_initial_board_missing_matrix_value() {

  Matrix* board;

  char* filename;
  filename = "test_island/test_island_missing_matrix_value.txt";

  board = create_initial_board_from_file(filename);

  print_board("board:  ", board);

  return 0;
}

static char * test_initial_board_missing_number_of_columns() {

  Matrix* board;
  char* filename;

  filename = "test_island/test_island_missing_number_of_columns.txt";

  board = create_initial_board_from_file(filename);

  return 0;
}

static char * test_initial_board_missing_row() {

  Matrix* board;
  char* filename;

  filename = "test_island/test_island_missing_row.txt";

  board = create_initial_board_from_file(filename);

  return 0;
}

static char * test_unit() {
  mu_assert("error, test_unit 1 != 1", 1 == 1);
  return 0;
}

/* How to captured exit? */
static char * all_tests() {
  mu_run_test(test_unit);

  mu_run_test(test_create_initial_board_from_file);

  mu_run_test(test_create_initial_board_from_file_with_empty_lines);

  /*
  mu_run_test(test_initial_board_missing_matrix_value);
  */


  /*
  mu_run_test(test_initial_board_missing_number_of_columns);
  */

  /*
  mu_run_test(test_initial_board_missing_row);
  */

  return 0;
}

int main(int argc, char **argv) {
  char *result = all_tests();
  if (result != 0) {
    printf("-_-_-_-_-_-_-_,------,      o \n");
    printf("_-_-_-_-_-_-_-|   /\\_/\\ \n");
    printf("-_-_-_-_-_-_-~|__( X .X)  +     + \n");
    printf("_-_-_-_-_-_-_- \"\"  \"\" \n");
    printf(KRED "✗ %s \n" RESET, result);
  } else {
    printf("-_-_-_-_-_-_-_,------,      o \n");
    printf("_-_-_-_-_-_-_-|   /\\_/\\ \n");
    printf("-_-_-_-_-_-_-~|__( ^ .^)  +     + \n");
    printf("_-_-_-_-_-_-_-  \"\"  \"\" \n");
    printf(KGRN " ✓ ALL TESTS PASSED \n" RESET);
  }
  printf("Tests run: %d\n", tests_run);
  return result != 0;
}
