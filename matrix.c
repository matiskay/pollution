#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

/* TODO: Add function to check the equality of the matrices. */

/* TODO: How to disable the memory? to test the function where there is not memory. */
Matrix* matrix_create(int n, int m) {
  Matrix* mat = (Matrix *) malloc(sizeof(Matrix));

  if (mat == NULL) {
    printf("Not enough memory! \n");
    exit(1);
  }

  mat->number_of_rows = n;
  mat->number_of_columns = m;

  mat->v = (float *) malloc(n * m * sizeof(float));

  return mat;
}

/* TODO: How to test matrix free */
void matrix_free(Matrix* mat) {
  free(mat->v);
  free(mat);
}

float matrix_get(Matrix* mat, int i, int j) {
  return mat->v[i * mat->number_of_columns + j];
}

void matrix_set(Matrix* mat, int i, int j, float v) {
  mat->v[i * mat->number_of_columns + j] = v;
}

int matrix_number_of_rows(Matrix* mat) {
  return mat->number_of_rows;
}

int matrix_number_of_columns(Matrix* mat) {
  return mat->number_of_columns;
}

void matrix_display(Matrix* mat) {
  int i;
  int j;

  for (i = 0; i < mat->number_of_rows; i++) {
    for (j = 0; j < mat->number_of_columns; j++) {
      printf("   %5.5f ", matrix_get(mat, i, j));
    }
    printf("\n");
  }
}

void matrix_display_integers(Matrix* mat) {
  int i;
  int j;

  for (i = 0; i < mat->number_of_rows; i++) {
    for (j = 0; j < mat->number_of_columns; j++) {
      printf("   %d ", (int) matrix_get(mat, i, j));
    }
    printf("\n");
  }
}

/* The easy way to compare is to compere the number of rows and columns */
int matrix_equal(Matrix* mat1, Matrix* mat2) {
  int i;
  int j;

  for (i = 0; i < mat1->number_of_rows; i++) {
    for (j = 0; j < mat1->number_of_columns; j++) {
      if (matrix_get(mat1, i, j) != matrix_get(mat2, i, j)) {
        return 0;
      }
    }
  }

  return 1;
}
