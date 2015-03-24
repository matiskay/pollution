#include <stdio.h>
#include "minunit.h"
#include "matrix.h"

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


static char * test_matrix_equal() {
  Matrix* mat1;
  Matrix* mat2;
  
  mat1 = matrix_create(2, 2);
  mat2 = matrix_create(2, 2);

  /*
   * +---+---+
   * | 1 | 2 |
   * +---+---+
   * | 2 | 1 |
   * +---+---+
   */

  matrix_set(mat1, 0, 0, 1);
  matrix_set(mat1, 0, 1, 2);

  matrix_set(mat1, 1, 0, 2);
  matrix_set(mat1, 1, 1, 1);

  matrix_set(mat2, 0, 0, 1);
  matrix_set(mat2, 0, 1, 2);

  matrix_set(mat2, 1, 0, 2);
  matrix_set(mat2, 1, 1, 1);

  mu_assert("error, The Matrices are equal", matrix_equal(mat1, mat2));

  matrix_set(mat2, 1, 1, 0);

  mu_assert("error, The Matrices are not equal", matrix_equal(mat1, mat2) == 0);
  return 0;
}

/* TODO: Test the number of memory that we have to allocate */
/* TODO: Add a test to check if v is created or not */
static char * test_matrix_create() {
  Matrix* mat;

  mat = matrix_create(3, 4);

  /*
   * +---+---+---+---+
   * | 1 | 2 | 5 | 0 |
   * +---+---+---+---+
   * | 2 | 1 | 4 | 1 |
   * +---+---+---+---+
   * | 0 | 0 | 1 | 0 |
   * +---+---+---+---+
   */

  mu_assert("error, the number of rows is not equal to 3", mat->number_of_rows == 3);
  mu_assert("error, the number of columns is not equal to 4", mat->number_of_columns == 4);
  return 0;
}

static char * test_matrix_number_of_columns() {
  Matrix* mat;

  mat = matrix_create(3, 4);
  mu_assert("error, the number of rows is not equal to 4", matrix_number_of_columns(mat) == 4);
  return 0;
}

static char * test_matrix_number_of_rows() {
  Matrix* mat;

  mat = matrix_create(3, 4);
  mu_assert("error, the number of rows is not equal to 3", matrix_number_of_rows(mat) == 3);
  return 0;
}

/* Set and get are related */
static char * test_matrix_get() {
  Matrix* mat;

  mat = matrix_create(3, 4);

  matrix_set(mat, 0, 0, 1);
  matrix_set(mat, 0, 1, 2);
  matrix_set(mat, 0, 2, 5);
  matrix_set(mat, 0, 3, 0);

  matrix_set(mat, 1, 0, 2);
  matrix_set(mat, 1, 1, 1);
  matrix_set(mat, 1, 2, 4);
  matrix_set(mat, 1, 3, 1);

  matrix_set(mat, 2, 0, 0);
  matrix_set(mat, 2, 1, 0);
  matrix_set(mat, 2, 2, 1);
  matrix_set(mat, 2, 3, 0);

  mu_assert("error, A[0, 0] is not equal to 1", matrix_get(mat, 0, 0) == 1);
  mu_assert("error, A[1, 1] is not equal to 1", matrix_get(mat, 1, 1) == 1);
  mu_assert("error, A[1, 2] is not equal to 4", matrix_get(mat, 1, 2) == 4);
  mu_assert("error, A[2, 3] is not equal to 1", matrix_get(mat, 2, 3) == 0);
  mu_assert("error, A[0, 2] is not equal to 5", matrix_get(mat, 0, 2) == 5);
  return 0;
}


static char * test_unit() {
  mu_assert("error, test_unit 1 != 1", 1 == 1);
  return 0;
}

static char * all_tests() {
  mu_run_test(test_unit);
  mu_run_test(test_matrix_create);
  mu_run_test(test_matrix_get);
  mu_run_test(test_matrix_number_of_rows);
  mu_run_test(test_matrix_number_of_columns);
  mu_run_test(test_matrix_equal);

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
  }
  else {
    printf("-_-_-_-_-_-_-_,------,      o \n");
    printf("_-_-_-_-_-_-_-|   /\\_/\\ \n");
    printf("-_-_-_-_-_-_-~|__( ^ .^)  +     + \n");
    printf("_-_-_-_-_-_-_-  \"\"  \"\" \n");
    printf(KGRN " ✓ ALL TESTS PASSED \n" RESET);
  }
  printf("Tests run: %d\n", tests_run);
  return result != 0;
}
