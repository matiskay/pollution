#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"

/* Add function signatures here */
float matrix_distance(Matrix* mat1, Matrix* mat2);

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


float matrix_distance(Matrix* mat1, Matrix* mat2) {
  /* Check the dimension of the matrices */
  float max = 0;
  float current_diff;

  for (i = 0; i < mat1->number_of_rows; i++) {
    for (j = 0; j < mat1->number_of_columns; j++) {
      current_diff = abs(matrix_get(mat1, i, j) - matrix_get(mat2, i, j));
      if (current_diff > max) {
        max = current_diff;
      }
    }
  }

  return max;
}
