#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

/* Add function signatures here */

int main(int argc, char **argv) {
  Matrix* mat;
  int n = 5;
  int m = 4;
  int i;
  int j;
  float random_value;
  
  mat = matrix_create(n, m);

  for (i = 0; i < mat->number_of_rows; i++) {
    for (j = 0; j < mat->number_of_columns; j++) {
      random_value = (rand() % 20) * 2.0;
      matrix_set(mat, i, j, random_value);
    }
  }

  matrix_display(mat);

  matrix_free(mat);

  return 0;
}
